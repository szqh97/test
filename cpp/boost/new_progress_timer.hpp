#include <boost/progress.hpp>
#include <boost/static_assert.hpp>
template<int N = 2>
class new_progress_timer:public boost::timer
{
public:
    new_progress_timer(std::ostream &os = std::cout) : m_os(os)
    {
        BOOST_STATIC_ASSERT(N >= 0 && N <=10);
    }
    ~new_progress_timer()
    {
        try
        {
            std::istream::fmtflags old_flags = m_os.setf(std::istream::fixed, std::istream::floatfield);
            std::streamsize old_prec = m_os.precision(N);
            m_os << elapsed() << " s\n" << std::endl;
            m_os.flags(old_flags);
            m_os.precision(old_prec);
        }
        catch (...) {}
    }
private:
    std::ostream &m_os;
};
