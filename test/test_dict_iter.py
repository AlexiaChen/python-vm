d = {1 : "a", 2 : "b"}

for k in d:
    print k, d[k]

print d.keys()
for k in d.keys():
    print k, d[k]

for v in d.values():
    print v

print d.items()
for k, v in d.items():
    print k, v

print d.iterkeys()
for k in d.iterkeys():
    print k, d[k]

for v in d.itervalues():
    print v

for k, v in d.iteritems():
    print k, v

