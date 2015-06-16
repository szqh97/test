#include <pthread.h>
#include <mutex>
#include <memory>
#include <boost/noncopyable.hpp>
namespace PthreadVersion
{
    template<class T>
        class Singleton: boost::noncopyable
    {
        public:
            static T& instance()
            {
                pthread_once(&ponce_, &Singleton::init);
                return *value_;

            }

        private:
            Singleton();
            ~Singleton();
            static void init()
            {
                value_ = new T();
            }

        private:
            static pthread_once_t ponce_;
            static T* value_;
    };

    template <class T> pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

    template <class T> T* Singleton<T>::value_ = NULL;
}

namespace CallOnceVersion
{
// This is not a Singleton! only one thread can get the instance.
//

    template<class T>
        class Singleton: boost::noncopyable
    {
        public:
            static std::unique_ptr<T> instance()
            {
                // call_once only called at first time, then return 0 if other thread call it again
                std::call_once(flag_, []{
                        value_.reset(new T); 
                        });
                return std::move(value_);
            }

        private:
            Singleton();
            ~Singleton();
        private:
            static std::once_flag flag_;
            static std::unique_ptr<T> value_;
    };

    template <class T> std::unique_ptr<T> Singleton<T>::value_;

    template <class T> std::once_flag Singleton<T>::flag_;
}

namespace SingletonSharedPtr
{

    template<class T>
        class Singleton: boost::noncopyable
    {
        public:
            static std::shared_ptr<T> instance()
            {
                // call_once only called at first time, then return 0 if other thread call it again
                std::call_once(flag_, []{
                        value_.reset(new T); 
                        });
                return value_;
            }

        private:
            Singleton();
            ~Singleton();
        private:
            static std::once_flag flag_;
            static std::shared_ptr<T> value_;
    };

    template <class T> std::shared_ptr<T> Singleton<T>::value_;

    template <class T> std::once_flag Singleton<T>::flag_;
}
