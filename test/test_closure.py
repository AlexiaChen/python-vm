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
