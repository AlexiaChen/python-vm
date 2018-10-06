class A(object):
    def __init__(self):
        print "In A"

    def __getattr__(self):
        return 0

    def __add__(self, a):
        return 100

class B(A):
    pass

a = A()
print (a + a)

def foo(self, rhs):
    return 200

b = B()
b.__add__ = foo
print (b + b)
