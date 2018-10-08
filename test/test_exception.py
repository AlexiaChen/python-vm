try:
    raise StopIteration("hello")
except StopIteration, e:
    print e

except Exception as e:
    print e

finally:
    print "end"
