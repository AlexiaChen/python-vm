print range(3)
print range(0, 10)
print range(10, 0, -2)

lst = list()
i = 0
while i < 10:
    lst.append(i)
    i += 1

print map(lambda x : x * 2, lst)
print filter(lambda x : x % 2 == 1, lst)
print sum(lst, 0)
