keys = []
values = []

class B(object):
    def __init__(self):
        print "create"

    def __setattr__(self, k, v):
        if k in keys:
            print "in"
            index = keys.index(k)
            print index
            values[index] = v
        else:
            print "setattr"
            keys.append(k)
            values.append(v)

    def __getattr__(self, k):
        if k in keys:
            index = keys.index(k)
            return values[index]
        else:
            return None

b = B()
b.foo = 1
b.bar = 2
print b.foo
print b.bar
b.foo = 3
print b.foo
