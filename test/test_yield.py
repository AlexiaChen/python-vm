def foo():
    i = 0
    while i < 10:
        yield i
        i += 1

    return

for i in foo():
    print i
