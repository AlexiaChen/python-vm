a = 1
b = "hello"
c = []
d = {}

print isinstance(a, object)
print isinstance(b, object)
print isinstance(c, object)
print isinstance(d, object)

t = type(1)
print t          # <type int>
print type(t)    # <type type>

i = 0
while i < 5:
    t = type(t)
    print t      # <type type>
    i = i + 1
