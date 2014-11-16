#include "Strategy.h"
#include <iostream>
Context::Context(Strategy* pStrategy): m_pStrategy(pStrategy)
{
}

Context::~Context()
{
    delete m_pStrategy;
    m_pStrategy = NULL;
}

void Context::ContextInterface()
{
    if (m_pStrategy)
    {
        m_pStrategy->AlgorithmInterface();
    }
}

Strategy::Strategy() {}

Strategy::~Strategy() {}

ConcreateStrageA::ConcreateStrageA() {}

ConcreateStrageA::~ConcreateStrageA() {}

void ConcreateStrageA::AlgorithmInterface()
{
    std::cout << "AlgorithmInterface in ConcreateStrageA" << std::endl;
}
