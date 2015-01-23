#include <vector>
#include <mutex>

template <typename T> class container
{
    public:
        void add(T element);
        void addrange(int num, ...);
        void dump();
    private:
        std::mutex _lock;
        std::vector<T> _elements;
};
