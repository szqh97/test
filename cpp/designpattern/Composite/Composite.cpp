#include "Composite.h"
#include <algorithm>
Composite::Composite(){}

Composite::~Composite(){}

void Composite::Operation()
{
    vector<Component*>::iterator comIter = comVec.begin();
    for (; comIter != comVec.end(); ++comIter)
    {
        (*comIter)->Operation();
    }
}

void Composite::Add(Component* com)
{
    comVec.push_back(com);
}

void Composite::Remove(Component* com)
{

    vector<Component*>::iterator it;
    it = find(comVec.begin(), comVec.end(), com);
    comVec.erase(it);
}

Component* Composite::GetChild(int index)
{
    if (index >= comVec.size())
    {
        return 0;
    }
    return comVec[index];
}

