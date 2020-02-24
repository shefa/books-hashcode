from simulated_annealing import *
from library import *
from ranking_utils import *
import random
import sys
import timeit

d_days=0
libraries=[]
books=[]

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

print("initial score",score(state))

simulated_annealing = SimulatedAnnealingWithNonImproveStoppingCriterion(
        random,
        get_neighbourhood_function(random),
        score,
        20,
        500,
        get_multiplicative_cooling_schedule_function(0.92),
        50000
    )

print(simulated_annealing.run(state))