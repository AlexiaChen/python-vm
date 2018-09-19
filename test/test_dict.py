d = {1 : "hello", "world" : 2}

print d
print d[1]
print d["world"]

d.setdefault(1, 2);
d.setdefault(2, 3);

print d[1]
print d[2]
del d[1]
print d
d.remove(2)
print d
