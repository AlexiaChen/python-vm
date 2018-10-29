def foo():
    value = 1
    print value

    def bar(a = 3):
        print value
        inner_v = 4

        def func1():
            print a
            print value

        def func2():
            print a
            print inner_v

        return func1, func2

    return bar

f = foo()
f()
f, g = f()
f()
g()

def func(x = 5):
    def say():
        print x

    x = 3
    print x
    return say

f = func()
print "hello"
f()

def foo():
    x = 2
    def bar():
        print x

    x = 3

    return bar

f = foo()
f()
