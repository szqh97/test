#include <iostream>
using namespace std;
enum CopyAlgoSelector { Conservative, Fast };

template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result, Int2Type<Conservative>)
{
    for (; first != last; ++first, ++result)
        *result = *first;
}

template <typename InIt, typename OutIt>
OutIt CopyImpl(InIt first, InIt last, OutIt result, Int2Type<Fast>)
{
    const size_t n = last-first;
    BitBlast(first, result, n * sizeof(*first));
    return result + n;
}
template <typename InIt, typename OutIt>
OutIt Copy(InIt first, InIt last, Out result)
{
    typedef TypeTraits<InIt>::
}

