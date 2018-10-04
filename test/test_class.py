class A(object):
    def __init__(self, v):
        self.value = v

    def __len__(self):
        return 37

a = A(1)
b = A(2)

l = []
l.append(1)
print l
print l.append
a.foo = l.append
a.foo(1)
print l

def func(self, s):
    print self
    print s

a.bar = func
A.bar = func

a.bar(a, "hello")
b.bar("world")

print len(a)
