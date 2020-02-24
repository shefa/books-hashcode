
class Library:
    def __init__(self, id_=0, n=0, signup=0, capacity=0, books=None, books_ordered=None):
        self.id_ = int(id_)
        self.n = int(n)
        self.signup = int(signup)
        self.capacity = int(capacity)
        self.books = books if books else list()
        self.books_ordered = books_ordered if books_ordered else list()

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
                libraries.append(Library(i, n, signup, capacity, books_tmp))

        return libraries, books, int(d_days)