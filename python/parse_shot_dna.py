#!/usr/bin/env python

def parse_shot_dna(S, D):
    dna_shot_pair = {}
    for i in xrange(len(S)):
        for j in xrange(len(D)):
            if round(S[i]/1000 + 5) == round(D[j] + 5):
                dna_shot_pair.update({{D[j-1]:D[j]}:S[i]})

    return dna_shot_pair


