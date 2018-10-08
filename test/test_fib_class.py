class Fib(object):
    def __init__(self):
        self.a = 1
        self.b = 1
        self.i = 0

    def next(self):
        if self.i > 10:
            raise StopIteration("end of iteration")
        else:
            t = self.a
            self.a = self.a + self.b
            self.b = t
            self.i += 1
            return self.a

    def __iter__(self):
        return self

f = Fib()
for i in f:
    print i
