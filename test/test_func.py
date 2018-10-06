def fact(n):
    if n == 1:
        return 1
    else:
        return fact(n-1) * n

print fact(6)

def foo(a, *alist):
    return alist[0] + alist[1]

print foo(2, 3, 4)

def bar(a, b):
    return a + b

print bar(b = 3, a = 1)

def func(a, b = 2, *alist, **kwargs):
    t = a
    t += b
    for i in alist:
        t += i

    for v in kwargs.itervalues():
        t += v

    return t

print func(1, 2)
print func(1, c = 3)
print func(1, 2, 3, c = 4)

def foo(a, b, c = 100, d = 10):
    return a + b + c + d

print foo(1, 2, d = 2)
