import math


def get_multiplicative_cooling_schedule_function(cooling_ratio_multiplier):
    """ Returns a cooling schedule function of the form f(T) = a*T, "a" being the cooling ratio multiplier - a real
    number between 0 and 1 (As specified in the proforma)

    :param cooling_ratio_multiplier: real number a, 0 <= a <= 1
    :return: pointer to the cooling schedule function
    """
    if cooling_ratio_multiplier < 0 or cooling_ratio_multiplier > 1:
        raise Exception("The value for the cooling ration multiplier 'a' must be 0 <= a <= 1")

    def cooling_schedule(temperature):
        return cooling_ratio_multiplier * temperature
    return cooling_schedule


class SimulatedAnnealingWithNonImproveStoppingCriterion:
    """ Generic implementation of simulated annealing with the stopping criterion: stop after inspecting a
    num_non_improve of solutions without finding a new best solution

    The neighbourhood function, cost function, initial temperature, temperature length, cooling schedule function
    and num_non_improve (for the stopping criterion) are specified by the user

    rng: Object, instance of the "Random" class - random number generator that SA uses for determining the
    probability of moving uphill

    neighbourhood_function: pointer to a function - neighbourhood function, preferably using the same RNG (rng).
    The result of the function must be a tuple, whose first element is the neighbouring solution

    cost_function: pointer to a function - cost function, supporting calculating the cost of initial as well as
    neighbouring solutions

    initial_temperature: real number - initial temperature TI
    temperature_length: integer - temperature length TL

    cooling_schedule_function: pointer to a function - cooling schedule f()

    num_non_improve: integer - stopping criterion
    """
    def __init__(
            self,
            rng,
            neighbourhood_function,
            cost_function,
            initial_temperature,
            temperature_length,
            cooling_schedule_function,
            num_non_improve,
    ):
        self.rng = rng
        self.neighbourhood_function = neighbourhood_function
        self.cost_function = cost_function
        self.initial_temperature = initial_temperature
        self.temperature_length = temperature_length
        self.cooling_schedule_function = cooling_schedule_function
        self.num_non_improve = num_non_improve

    def run(self, initial_solution):
        number_of_uphill_moves = 0
        iterations_since_last_improvement = 0

        temperature = self.initial_temperature
        current_solution = initial_solution[:]
        # calculate the cost of the initial solution
        current_solution_cost = self.cost_function(initial_solution)

        # take the best solution to be the initial solution
        best_solution = current_solution[:]
        best_solution_cost = current_solution_cost

        # Stopping criterion, part 1
        # Continue the process until iterations_since_last_improvement is equal to num_non_improve
        # this could be replaced with an infinite loop ("while True:"), as the stopping criterion will always be first
        # met in the check "Stopping criterion, part 2", implemented below.
        while iterations_since_last_improvement < self.num_non_improve:
            # stay at a temperature T for TL iterations
            for _ in range(self.temperature_length):
                # get the neighbour of a solution produced by the neighbourhood function.
                # as specified above, the neighbouring solution is the first parameter of the return value
                # any other parameters returned are stored as a tuple for later use
                neighbour = self.neighbourhood_function(current_solution)
                [neighbour_solution, rest] = neighbour[0], neighbour[1:]

                # calculate the cost of the neighbouring solution by using the cost function, using the cost of the
                # current solution as a basis, also passing any additional parameters produced by the neighbourhood
                # function
                neighbour_solution_cost = self.cost_function(neighbour_solution, current_solution_cost, *rest)
                delta_cost = neighbour_solution_cost - current_solution_cost

                # if the cost of the neighbouring solution is lower or equal to that of the current solution
                # accept the neighbouring solution as the current solution
                if delta_cost <= 0:
                    current_solution = neighbour_solution[:]
                    current_solution_cost = neighbour_solution_cost

                    # if the cost of the neighbouring solution is lower than that of the best solution
                    # accept the neighbouring solution as the best solution and reset the number of iterations
                    # without improvement
                    # otherwise, increment the number of iterations without improvement by 1
                    if current_solution_cost < best_solution_cost:
                        best_solution = current_solution[:]
                        best_solution_cost = current_solution_cost
                        iterations_since_last_improvement = 0
                    else:
                        iterations_since_last_improvement += 1

                # if the cost of the neighbouring solution is higher than that of the current solution
                # accept it with probability p = e^(-deltaCost / T). If accepted, record that an uphill move occurred.
                # Always increment the number of iterations without improvement by 1
                else:
                    p = math.exp(-delta_cost / temperature)
                    if self.rng.random() < p:
                        current_solution = neighbour_solution[:]
                        current_solution_cost = neighbour_solution_cost

                        number_of_uphill_moves += 1

                    iterations_since_last_improvement += 1

                # Stopping criterion, part 2
                # check if after an iteration at temperature T the num_non_improve of iterations is reached
                # if so, ignore the remaining length from TL and terminate execution
                if iterations_since_last_improvement >= self.num_non_improve:
                    break

            # after spending TL iterations at temperature T, invoke the cooling_schedule function to obtain the next
            # temperature T'
            temperature = self.cooling_schedule_function(temperature)

        return best_solution, best_solution_cost, number_of_uphill_moves
