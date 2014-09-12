#!/usr/bin/env python

def get_zeros(num_list):
    def get_m(n, m):
        if n == 0: return 0
        cnt = 0
        d, v = n//m, n%m 
        while not v :
            n = d
            if v == 0:
                cnt += 1
            else:
                return cnt
            d, v = n // m, n % m
        return cnt

    twos = map(lambda x: get_m(x, 2), num_list)
    fives = map(lambda x: get_m(x, 5), num_list)
    print min(sum(twos), sum(fives))


