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
    cnt_2 = sum(twos)
    cnt_5 = sum(fives)
    if cnt_2 <= cnt_5:
        return 1
    if cnt_2 > cnt_5:
        return 0


