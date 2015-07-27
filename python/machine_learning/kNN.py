#!/usr/bin/env python
import numpy as np
from numpy import *
import operator
from os import listdir  

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

def file2matrix(filename):
    fr = open(filename)
    lines = fr.readlines()
    numberOfLines = len(lines)
    returnMat = zeros((numberOfLines,3))
    classLabelVector = []
    index = 0
    for line in lines:
        line = line.strip()
        listFromLine = line.split('\t')
        returnMat[index,:] = listFromLine[0:3]
        classLabelVector.append(int(listFromLine[-1]))
        index += 1
    return returnMat,classLabelVector

def autoNorm(dataSet):
    minVals = dataSet.min(0)
    maxVals = dataSet.max(0)
    ranges = maxVals - minVals
    normDataSet = zeros(shape(dataSet))
    m = dataSet.shape[0]
    normDataSet = dataSet - tile(minVals,(m,1))
    normDataSet = normDataSet/tile(ranges, (m,1))
    return normDataSet, ranges, minVals

def datingClassTest():
    hoRatio = 0.10
    datingDataMat, datingLabels = file2matrix('./datingTestSet2.txt')
    normMat, ranges, minVals = autoNorm(datingDataMat)
    m = normMat.shape[0]
    numTestVecs = int(m*hoRatio)
    errorCount = 0.0
    for i in range(numTestVecs):
        classifierResult = classify0(normMat[i,:], normMat[numTestVecs:m, :],\
                datingLabels[numTestVecs:m], 3)
        print "the classifier came back with: %d, the real answer is: %d"\
                % (classifierResult, datingLabels[i])
        if classifierResult != datingLabels[i]:
            errorCount += 1.0
        print "the total error rate is: %f" % ( errorCount/float(numTestVecs))


def image2vector(filename):
    returnVect = zeros((1, 1024))
    fr = open(filename)
    for i in xrange(32):
        linestr = fr.readline()
        #returnVect[0,32*i:32*i+i] = [int(x) for x in list(linestr)]
        for j in xrange(32):
            returnVect[0, 32*i+j] = linestr[j]
    return returnVect

def handwritingClassTest():
    hwLabels = []
    traingFileList = listdir('./trainingDigits')
    m = len(traingFileList)
    traingMat= zeros((m, 1024))
    for i in range(m):
        fileNamestr = traingFileList[i]
        fileStr = fileNamestr.split('.')[0]
        classNumStr = int(fileStr.split('_')[0])
        hwLabels.append(classNumStr)
        traingMat[i,:] = image2vector('./trainingDigits/%s' % fileNamestr)
    testFileList = listdir('./testDigits')

    errorCount = 0.0
    mTest = len(testFileList)
    for i in xrange(mTest):
        fileNamestr = testFileList[i]
        fileStr = fileNamestr.split('.')[0]
        classNumStr = int(fileStr.split('_')[0])
        vectorUnderTest = image2vector('./testDigits/%s' % fileNamestr)
        classifierResult = classify0(vectorUnderTest, traingMat, hwLabels, 3)
        print 'the classifier came back with %s, the real answer is: %s' % \
                (classifierResult,classNumStr)
        if classifierResult != classNumStr:
            errorCount += 1.0
            print "\n the total number of errors is : %d" % errorCount
            print "\n the total error rate is: %f" % (errorCount/float(mTest))
