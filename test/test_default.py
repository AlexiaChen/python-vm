def foo(a = 1):
    return a

print foo()

def make_func(x):
    def add(a, b = x):
        return a + b

    return add

add5 = make_func(5)
print add5(10)
