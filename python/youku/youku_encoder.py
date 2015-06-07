import time
import random
import math
def createSid():
    nowTime = int(time.time() *1000)
    random1 = random.randint(1000,1998)
    random2 = random.randint(1000,9999)
    return "%d%d%d" %(nowTime,random1,random2)

def getFileIDMixString(seed):
    mixed=[]
    source=list("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ/\:._-1234567890")
    seed=float(seed)
    for i in range(len(source)):
        seed = (seed * 211 + 30031 ) % 65536
        index = math.floor(seed /65536 *len(source))
        mixed.append(source[int(index)])
        source.remove(source[int(index)])
    #return ''.join(mixed)
    return mixed

def getFileId(fileId,seed):
    mixed=getFileIDMixString(seed)
    ids=fileId.split('*')
    realId=[]
    for ch in ids:
        realId.append(mixed[int(ch)])
    return ''.join(realId)
if __name__ == '__main__':
    print createSid()
    print getFileIDMixString(4528)
    fileId='3*31*3*3*3*61*3*13*3*3*36*17*48*21*17*55*31*17*61*31*14*14*3*3*36*13*67*31*31*10*21*32*58*31*13*14*3*48*15*13*10*48*55*15*55*10*36*31*15*31*61*10*67*15*3*61*17*13*13*14*11*36*48*21*36*10'
    seed=4528
    print getFileId(fileId,seed)
