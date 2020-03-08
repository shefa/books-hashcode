from simulated_annealing import *
import random
import sys
import timeit

d_days=0
libraries=[]
books=[]


class Library:
    def __init__(self, id_=0, n=0, signup=0, capacity=0, books=None, books_aggr=None):
        self.id_ = int(id_)
        self.n = int(n)
        self.signup = int(signup)
        self.capacity = int(capacity)
        self.books = books if books else list()
        self.books_aggr = books_aggr if books_aggr else list()

    @staticmethod
    def from_file(filename):
        libraries = list()
        with open(filename, 'r') as file:
            [_b, l_libraries, d_days] = file.readline().strip().split()
            books = file.readline().strip().split()

            def sortByScore(x,y):
                if books[x]>books[y]:
                    return -1
                if books[x]<books[y]:
                    return 1
                return 0

            for i in range(len(books)):
                books[i]=int(books[i])
            for i in range(int(l_libraries)):
                [n, signup, capacity] = file.readline().strip().split()
                books_tmp=file.readline().strip().split()
                for j in range(len(books_tmp)):
                    books_tmp[j]=int(books_tmp[j])
                books_tmp=list(set(books_tmp))
                list.sort(books_tmp,cmp=sortByScore)
                books_aggr=[books[books_tmp[0]]]
                for j in range(len(books_tmp)-1):
                    books_aggr.append(books_aggr[j]+books[books_tmp[j+1]])

                libraries.append(Library(i, n, signup, capacity, books_tmp, books_aggr))

        return libraries, books, int(d_days)

def score(state):
    xx=set()
    sumz, time = 0, 0
    for i in [libraries[s] for s in state]:
        if time+i.signup>=d_days:
            continue
        
        maxBooks=(d_days-time-i.signup)*i.capacity
        curBooks=0
        for x in i.books:
            if x not in xx:
                xx.add(x)
                curBooks+=1
                if curBooks==maxBooks:
                    break

        if curBooks:
            time+=i.signup

    for i in xx:
        sumz+=books[i]

    return sumz

def score2(state):
    #xx=set()
    sumz, time = 0, 0
    for i in [libraries[s] for s in state]:
        if time+i.signup>=d_days:
            continue
        time+=i.signup
        maxBooks=(d_days-time)*i.capacity
        sumz+=i.books_aggr[min(maxBooks,len(i.books_aggr)-1)]

    return sumz

def read_state(file):
    with open(file, 'r') as file:
        #l_libraries = file.readline().strip()
        state = file.readline().strip().split()
        for i in range(len(state)):
            state[i]=int(state[i])
        return state

filename = sys.argv[1]
initial_solution = sys.argv[2]
libraries, books, d_days = Library.from_file(filename)
state = read_state(initial_solution)

max_score=score(state)

print("initial score",score(state))

def better_solution(scorez,solution):
    if score(solution) > max_score:
        print("found better solution", score(solution))
        f = open(initial_solution+'x', "w")
        f.write(str(solution)[1:-1].replace(',',''))
        f.close()


simulated_annealing = SimulatedAnnealingWithNonImproveStoppingCriterion(
        random,
        get_neighbourhood_function(random),
        score2,
        30,
        500,
        get_multiplicative_cooling_schedule_function(0.92),
        1500000,
        better_solution
    )

simulated_annealing.run(state)

def timeCompare(fn1,fn2):
    results=[0,0]
    results[0]+=timeit.timeit(lambda: fn1(), number=500)
    results[1]+=timeit.timeit(lambda: fn2(), number=500)
    results[0]+=timeit.timeit(lambda: fn1(), number=500)
    results[1]+=timeit.timeit(lambda: fn2(), number=500)
    print(results)
