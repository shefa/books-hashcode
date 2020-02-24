def get_neighbourhood_function(rng):

    def neighbourhood_function(ranking):
        new_ranking = ranking[:]
        old_position = rng.randrange(len(ranking))
        if old_position==len(ranking)-1:
            old_position-=1
        new_position=old_position+1
        new_ranking[old_position], new_ranking[new_position] = new_ranking[new_position], new_ranking[old_position]
        return new_ranking, old_position, new_position

    return neighbourhood_function
