#!/usr/bin/env python
import numpy as np
from numpy import *
import operator

def create_Dataset():
    group = np.array([[1.0, 1.1], [1.0, 1.0], [0, 0], [0, 0.1]])
    labels = ['A', 'A', 'B', 'B']
    return group, labels

def classify0(inX, dataSet, labels, k):
    dataSetSize = dataSet.shape[0]

    diffMat = tile(inX, (dataSetSize, 1)) - dataSet
    sqDiffMat = diffMat ** 2
    sqDistance = sqDiffMat.sum(axis=1)
    distance = sqDistance ** 0.5
    sortedDistIndicies = distance.argsort()

    classCount = {}
    for i in xrange(k):
        voteIlabel = labels[sortedDistIndicies[i]]
        classCount[voteIlabel] = classCount.get(voteIlabel, 0) + 1
        sortedClassCount = sorted(classCount.iteritems(), key = operator.itemgetter(1), reverse=True)
    return sortedClassCount[0][0]

def file2matix(filename):
    fr = open(filename)
    arrayOlies = fr.readlines()
    numberOfLines = len(arrayOlies)

    returnMat =  zeros((numberOfLines,3))
    classLabelVector=[]
    index = 0
    classLabelVector=[l.strip().split('\n') for l in arrayOlies]

