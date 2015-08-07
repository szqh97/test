#!/usr/bin/env python
from numpy import *

def loadDataSet():
    postingList = [
            list('my dog has flea problems help please'.split(' ')),
            list('maybe not take him to dog park stupid'.split(' ')),
            list('my dalmation is so cute I love him'.split(' ')),
            list('stop posting stupid worthless garbage'.split(' ')),
            list('mr licks ate my stteak how to stop him'.split(' ')),
            list('quit buying wothless dog food stupid'.split(' '))
            ]
    classVec = [0,1,0,1,0,1]
    return postingList, classVec

def createVocabList(dataSet):
    vocabSet = set([])
    for document in dataSet:
        vocabSet = vocabSet|set(document)
    return list(vocabSet)

def setOfWords2Vec(vocabList, inputSet):
    returnVec = [0]*len(vocabList)
    for word in inputSet:
        if word in vocabList:
            returnVec[vocabList.index(word)] = 1
        else:
            print 'The world: %s is not in my vocabulary!' % word
    return returnVec

def trainNB0(trainMatrix, trainCategory):
    numTrainDocs = len(trainMatrix)
    numWords = len(trainMatrix[0])
    pAbusive = sum(trainCategory)/float(numTrainDocs)
    p0Num = zeros(numWords); p1Num = zeros(numWords)
    p0Denom = 0.0; p1Denom = 0.0
    for i in xrange(numTrainDocs):
        if trainCategory[i] == 1:
            p1Num += trainMatrix[i]
            p1Denom += sum(trainMatrix[i])
        else:
            p0num += trainMatrix[i]
            p0Denom += sum(trainMatrix[i])
    p1Vect = p1Num/p1Denom
    p0Vect = p0num/p0Denom

    return p0Vect, p1Vect, pAbusive


