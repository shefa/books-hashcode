from simulated_annealing import *
from library import *
import sys
import timeit

d_days=0
libraries=[]
books=[]

def sortByScore(x,y):
    if books[x]>books[y]:
    	return 1
    if books[x]<books[y]:
    	return -1
    return 0

def score(state):
    xx=set()
    sumz, time = 0, 0
    for i in [libraries[s] for s in state]:
    	i.books_ordered=[]
    	if time+i.signup>=d_days:
    		continue
    	for x in i.books:
    		if x not in xx:
    			i.books_ordered.append(x)
    			xx.add(x)

    	if len(i.books_ordered)>0:
    		time+=i.signup
    		maxBooks=(d_days-time)*i.capacity
    		if maxBooks<len(i.books_ordered):
    			[xx.discard(j) for j in i.books_ordered[maxBooks:]]
    			del i.books_ordered[maxBooks:]

    return sum(books[i] for i in xx)

def score2(state):
    xx={}
    sumz, time = 0, 0
    for i in [libraries[s] for s in state]:
    	i.books_ordered=[]
    	if time+i.signup>=d_days:
    		continue
    	for x in i.books:
    		if x not in xx:
    			i.books_ordered.append(x)
    			xx[x]=1

    	if len(i.books_ordered)>0:
    		time+=i.signup
    		maxBooks=(d_days-time)*i.capacity
    		if maxBooks<len(i.books_ordered):
    			[xx.pop(j,None) for j in i.books_ordered[maxBooks:]]
    			del i.books_ordered[maxBooks:]


    for i in xx.keys():
        sumz+=books[i]

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
print(score(state))
print(timeit.timeit(lambda: score(state), number=1500))
print(timeit.timeit(lambda: score2(state), number=1500))
print(timeit.timeit(lambda: score(state), number=1500))
print(timeit.timeit(lambda: score2(state), number=1500))


