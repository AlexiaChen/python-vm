class Z(object):
    def say(self):
        print "I am Z"

class X(Z):
    def say(self):
        print "I am X"

class Y(Z):
#    def say(self):
#        print "I am Y"
    pass

class B(Y, X):
    def say(self):
        print "I am B"

class A(Z):
    def say(self):
        print "I am A"
    pass

class C(B, A):
#    def say(self):
#        print "I am C"
    pass

c = C()
c.say()

c = Z()
sysgc()
c.say()

