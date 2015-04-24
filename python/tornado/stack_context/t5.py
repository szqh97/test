import contextlib

@contextlib.contextmanager
def process():
    try:
        yield 123
    except:
        pass

with process() as i:
    print i
    raise Exception, 3
