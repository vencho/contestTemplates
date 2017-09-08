#include<stdio.h>
#include<iostream>

#include<conio.h>

#define MAX(a, b) (((a)>(b))?(a):(b))

using namespace std;


class AVLNode
{
private:

int Key, Height;
AVLNode *Left, *Right, *Parent;


public:
AVLNode::AVLNode(int key, int height, AVLNode *left, AVLNode *right, AVLNode *parent)
    {
    Key = key;
    Height = height;
    Left = left;
    Right = right;
    Parent = parent;
    }

int key()
{ return Key; }
int h()
{ return Height; }
AVLNode *left()
{ return Left; }
AVLNode *right()
{ return Right; }
AVLNode *p()
{ return Parent; }


void setHeight(int h)
{ Height = h; }
void setKey(int key)
{ Key = key; }
void setLeft(AVLNode *left)
{ Left = left; }
void setRight(AVLNode *right)
{ Right = right; }
void setParent(AVLNode *parent)
{ Parent = parent; }

};

class AVLTree
{
private:
AVLNode *Nil;
AVLNode *Root;

public:
AVLTree::AVLTree()
    {
    Nil = new AVLNode(112233, 0, NULL, NULL, NULL);
    Nil -> setLeft(Nil);
    Nil -> setRight(Nil);
    Nil -> setParent(Nil);
    Root = Nil;
    }


public:
int Height()
    {
    return Root -> h();
    }


/* INSERTION METHODS */
// ----------------- //

public:
bool Insert(int key)
    {
    AVLNode *z = new AVLNode(key, 1, Nil, Nil, Nil);
    return InsertNode(z);
    }

private:
bool InsertNode(AVLNode *z)
    {
    AVLNode *y = Nil, *x = Root;

    int key = z -> key();

    while(x != Nil)
        {
        y = x;
        if(key < x -> key())
            x = x -> left();
        else if(key > x -> key())
            x = x -> right();
        else return false;
        }

    z -> setParent(y);
    if(y == Nil) Root = z;
    else
        if(key < y -> key())
            y -> setLeft(z);
        else
            y -> setRight(z);

    while(y != Nil)
        {
        evalHeight(y);
        if(!isBalanced(y)) Balance(y);
        y = y -> p();
        }
    return true;
    }
// ----------------- //

/* DELETION METHODS */
// ---------------- //

public:
bool Delete(int key)
    {
    AVLNode *x = find(key);
    if(x == Nil) return false;

    DeleteNode(x);
    return true;
    }

private:
void DeleteNode(AVLNode *z)
    {
    AVLNode *x, *y;

    if(z -> left() == Nil || z -> right() == Nil) y = z;
    else y = Successor(z);

    if(y -> left() != Nil) x = y -> left();
    else x = y -> right();

    if(y -> p() == Nil)
        Root = x;
    else
        if(y -> p() -> left() == y)
            y -> p() -> setLeft(x);
        else
            y -> p() -> setRight(x);

//    if(x != Nil)
        x -> setParent(y -> p());

    if(y != z)
        z -> setKey(y -> key());

    if(x != Nil) x -> setParent(y -> p());

    x = y -> p();
    while(x != Nil)
        {
        evalHeight(x);
        if(!isBalanced(x)) Balance(x);
        x = x -> p();
        }
    }
// ---------------- //





/* QUERY METHODS */
// ------------- //

public:
bool Query(int key)
    {
    return (find(key) != Nil);
    }

private:
AVLNode *find(int key)
    {
    AVLNode *x = Root;
    while(x != Nil)
        {
        if(key < x -> key()) x = x -> left();
        else if(key > x -> key()) x = x -> right();
        else return x;
        }
    return Nil;
    }

// ------------- //


/* EMPTY METHODS */
// ------------- //

public:
bool isEmpty()
{ return Root == Nil; }

void Clear()
{ Root = Nil; }

// ------------- //


/* SUCCESSOR METHOD */
// ---------------- //

private:
AVLNode *Successor(AVLNode *z)
    {
    if(z -> right() != Nil)
        {
        z = z -> right();
        while(z -> left() != Nil) z = z -> left();
        return z;
        }
    else
        {
        while(z -> p() -> right() == z) z = z -> p();
        return z -> p();
        }
    }

// ---------------- //


/* BALANCING METHODS */
// ----------------- //

private:
void evalHeight(AVLNode *x)
    {
    int a, b;
    a = x -> left() -> h();
    b = x -> right() -> h();
    x -> setHeight(MAX(a, b) + 1);
    }


bool isBalanced(AVLNode *x)
    {
    int a = x -> left() -> h();
    int b = x -> right() -> h();

    if(a - b < 2 && a - b > -2) return true;
    else return false;
    }

void Balance(AVLNode *x)
    {
    AVLNode *y;
    if(x -> left() -> h() > x -> right() -> h())
        {
        y = x -> left();
        if(y -> left() -> h() >= y -> right() -> h())
            RightRotate(x);
        else
            {
            LeftRotate(y);
            RightRotate(x);
            }
        }
    else
        {
        y = x -> right();
        if(y -> right() -> h() >= y -> left() -> h())
            LeftRotate(x);
        else
            {
            RightRotate(y);
            LeftRotate(x);
            }
        }
    }
// ----------------- //



/* ROTATION METHODS */
// ---------------- //
private:

void LeftRotate(AVLNode *x)
    {
    AVLNode *y = x -> right();
    AVLNode *beta = y -> left();

    x -> setRight(beta);
    if(beta != Nil) beta -> setParent(x);



    y -> setParent(x -> p());
    if(x -> p() == Nil)
        Root = y;
    else
        if(x -> p() -> left() == x)
            x -> p() -> setLeft(y);
        else
            x -> p() -> setRight(y);

    x -> setParent(y);
    y -> setLeft(x);

    evalHeight(x);
    evalHeight(y);
    }

void RightRotate(AVLNode *y)
    {
    AVLNode *x = y -> left();
    AVLNode *beta = x -> right();

    y -> setLeft(beta);
    if(beta != Nil) beta -> setParent(y);


    x -> setParent(y -> p());
    if(y -> p() == Nil)
        Root = x;
    else
        if(y -> p() -> right() == y)
            y -> p() -> setRight(x);
        else
            y -> p() -> setLeft(x);

    y -> setParent(x);
    x -> setRight(y);

    evalHeight(y);
    evalHeight(x);
    }

// ---------------- //




/* OUTPUT METHODS */
// -------------- //

public:
void OutputTree()
    {
    if(Root != Nil) outputSubtree(Root, 0);
    }

void OutputSet()
    { if(Root != Nil) outputSubset(Root); cout << "\n"; }

private:
void outputSubset(AVLNode *x)
    {
    if(x -> left() != Nil) outputSubset(x -> left());
    cout << x -> key() << " ";
    if(x -> right() != Nil) outputSubset(x -> right());
    }

void outputSubtree(AVLNode *z, int indentation)
    {
    if(z == Nil)
        {
        for(int i = 0; i < indentation; i++) cout << " ";
        cout << "nil\n";
        return;
        }
    outputNode(z, indentation);
    outputSubtree(z -> left(), indentation + 2);
    outputSubtree(z -> right(), indentation + 2);
    }

void outputNode(AVLNode *z, int indentation)
    {
    for(int i = 0; i < indentation; i++) printf(" ");
    printf("%d [%d]\n", z -> key(), z -> h());
    }
// -------------- //

};
