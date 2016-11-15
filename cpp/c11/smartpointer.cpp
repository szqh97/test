#include <>
#include <string>
class Airecraft
{
private:
    std::string m_model;
public:
    int m_flyCount;
    weak_ptr<Airecraft> myWingMan;

};
