#include <iostream>
#include <map>

using namespace std;

class CustomerUser {
public:
    CustomerUser(int ca, int cb, int ua, int ub):
        ca(ca), cb(cb), ua(ua), ub(ub) {}
    bool operator == (const CustomerUser& rc) const {
        return ca == rc.ca && cb == rc.cb && ua == rc.ua && ub == rc.ub;
    }

    bool operator <( const CustomerUser& rc) const {
        if (! (*this == rc)) {
            return ca <= rc.ca && cb <= rc.cb && ua <= rc.ua && ub < rc.ub;
        }
        else {
            return false;
        }
    }

private:
    CustomerUser();
    int ca, cb, ua, ub;
};

class comp {
public:
    bool operator() (const CustomerUser* pl, const CustomerUser* pr) const {
        return (*pl) < (*pr);
    }
};
int main()
{
    CustomerUser *a = new CustomerUser(0,1,2,3);
    CustomerUser *b = new CustomerUser(0,1,2,3);
    cout << (*a == *b) << endl;;


    std::map<CustomerUser*, int> userRelations;
    userRelations.insert(make_pair(new CustomerUser(0,1,2,3), 11));
    userRelations.insert(make_pair(new CustomerUser(0,1,2,3), 11));
    userRelations.insert(make_pair(new CustomerUser(0,1,2,3), 11));
    userRelations.insert(make_pair(new CustomerUser(0,1,2,3), 11));
    userRelations.insert(make_pair(new CustomerUser(0,1,2,3), 11));
    userRelations.insert(make_pair(new CustomerUser(0,1,2,3), 11));
    std::cout << userRelations.size() << endl;
    return 0;
}
