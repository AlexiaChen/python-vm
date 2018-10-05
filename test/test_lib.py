def foo():
    global var
    var = 2

def fact(n):
    if n == 0:
        return 1
    else:
        return n * fact(n-1)

print __name__
print fact(6)
