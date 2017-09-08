#include"AVLTree.cpp"

using namespace std;



class AVLSet
{
private:
AVLTree *T;


public:

AVLSet::AVLSet()
    { T = new AVLTree(); }

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
