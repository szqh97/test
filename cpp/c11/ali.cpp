#include <iostream>
#include <vector>

int maxZeroListLength(const std::vector<int>& ivec, unsigned long begin, unsigned long end) {
    unsigned long curpos = begin;
    unsigned long beginpos = begin;
    int sum = 0;
    for (; curpos != end; ++curpos) {
        sum += ivec[curpos];
        if (sum == 0) {

        }
    }
}

false jum2Center(const std::vector<int>& ivec, int idxBeg, int idxEnd, int leftSum=0, int rightSum=0) {
    if(idxEnd - idxBeg < 6) return false;
    if (leftSum < rightSum) {
        idxBeg += 1;
        leftSum += ivec[idxBeg];
        //recurisiving
    }
    if (leftSum > rightSum) {
        idxEnd += 1;
        rightSum += ivec[idxEnd];
        //recursiving
    }

    if (leftSum == rightSum and )
}
bool splitFuck4(const std::vector<int>& ivec ) {
    if (ivec.size() < 7) return false;
    int sum = 0;

    return false;
}

int main()
{
    std::vector<int> ivec {2,5,1,1,1,1,4,1,7,3,7};
    return 0;
}
