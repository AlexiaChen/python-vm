import test_func
from test_func import foo, fact

#global var
#var = 1
#test_func.foo()
#print var
#print test_func.var

print fact(5)

l = [1, 2, 3, 4]
print map(lambda x : x + 1, l)
print filter(lambda x : x % 2 == 0, l)
print sum(l, 100)
