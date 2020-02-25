def get_neighbourhood_function(rng):

    def neighbourhood_function(ranking):
        new_ranking = ranking[:]
        old_position = rng.randrange(len(ranking))
        if old_position==len(ranking)-1:
            old_position-=1
        new_position=old_position+1
        new_ranking[old_position], new_ranking[new_position] = new_ranking[new_position], new_ranking[old_position]
        return new_ranking, old_position, new_position

    def neighbourhood_function2(ranking):
        new_ranking = ranking[:]
        [old_position, new_position] = rng.sample(range(len(ranking)), 2)

        are_adjacent = abs(old_position - new_position) == 1

        available_positions = [x for x in range(len(ranking)) if x != old_position] if are_adjacent else None

        while are_adjacent and rng.random() < 0.5:
            new_position = rng.choice(available_positions)
            are_adjacent = abs(old_position - new_position) == 1

        new_ranking.insert(new_position, new_ranking.pop(old_position))

        return new_ranking, old_position, new_position

    return neighbourhood_function
