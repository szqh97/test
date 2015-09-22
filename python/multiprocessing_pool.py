
import multiprocessing as mp

def f(x):
    f.q.put('Doing: ' + str(x))
    print x*x
    #return x*x

def f_init(q):
    f.q = q

def main():
    jobs = range(1,6)

    q = mp.Queue()
    p = mp.Pool(None, f_init, [q])
    results = p.imap(f, jobs)
    #p.apply_async(f,jobs)
    p.close()

#    for i in range(len(jobs)):
#        print q.get()
#        print results.next()

if __name__ == '__main__':
    main()


