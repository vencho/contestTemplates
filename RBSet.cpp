#include"RBTree.cpp"

using namespace std;



class RBSet
{
private:
RBTree *T;


public:

RBSet::RBSet()
    { T = new RBTree(); }

bool Query(int key)
    { return T -> Query(key); }

bool Delete(int key)
    { return T -> Delete(key); }

bool Insert(int key)
    { return T -> Insert(key); }

bool isEmpty()
    { return T -> isEmpty(); }

void Clear()
    { T -> Clear(); }

void OutputSet()
    { T -> OutputSet(); }

void OutputTree()
    { T -> OutputTree(); }

int Height()
    { return T -> Height(); }
};
