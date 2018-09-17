global x
x = 0

def func():
    global x
    x = 1

func()
print x

y = 2
def foo():
    print y

foo()
