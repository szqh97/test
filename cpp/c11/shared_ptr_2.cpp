#include <iostream>
#include <memory>
#include <vector>
#include <string>

using namespace std;

class Item
{
public:
    Item(const string& title): title_(title){}
    virtual ~Item(){}
    virtual string Description() const = 0;
    string Title() const
    {
        return title_;
    }
private:
    string title_;
};

class Book: public Item
{
public:
    Book(const string& title, int pages):Item(title), pages_(pages){}
    virtual string Description() const
    {
        return "Book "  + Title();
    }
    int Pages() const
    {
        return pages_;
    }
private:
    int pages_;
};

class DVD: public Item
{
private:
    int tracks_;
public:
    DVD(const string& title, int tracks): Item(title), tracks_(tracks) {}
    virtual string Description() const
    {
        return "DVD: " + Title();
    }
    int Tracks() const
    {
        return tracks_;
    }
    
};

void dodynamic()
{
    vector<shared_ptr<Item>> items;
    items.push_back(shared_ptr<Book>(new Book("Effectiv STL", 400)));
    items.push_back(shared_ptr<DVD>(new DVD("Left of the Middle", 14)));

    for (vector<shared_ptr<Item>>::const_iterator it = items.begin(); it != items.end(); ++ it)
    {
        cout << (*it)->Description() << endl;
    }
}


int main ( int argc, char *argv[] )
{
    dodynamic();
    return 0;
}			/* ----------  end of function main  ---------- */
