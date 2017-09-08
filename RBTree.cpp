#define RED 0
#define BLACK 1

#include<iostream>
#include<stdio.h>


using namespace std;


class RBNode
{
private:
 int Key;
 int Colour;
 RBNode *Left, *Right, *P;

public:


RBNode::RBNode(int key, int colour, RBNode *left, RBNode *right, RBNode *parent)
    {
    this->Key = key;
    this->Colour = colour;
    this->Left = left;
    this->Right = right;
    this->P = parent;
    }
int key()
    { return Key; }
int colour()
    { return Colour; }
RBNode *left()
    { return Left; }
RBNode *right()
    { return Right; }
RBNode *p()
    { return P; }
void setKey(int k)
    { Key = k; }
void setLeft(RBNode *z)
    { Left = z; }
void setRight(RBNode *z)
    { Right = z; }
void setParent(RBNode *z)
    { P = z; }
void setColour(int c)
    { Colour = c; }
};





class RBTree
{
private:
RBNode *Root;
RBNode *Nil;

public:
RBTree::RBTree()
    {
    Nil = new RBNode(112233, BLACK, NULL, NULL, NULL);
    Nil -> setLeft(Nil);
    Nil -> setRight(Nil);
    Nil -> setParent(Nil);
    Root = Nil;
    }

public:
int Height()
    {
    return h(Root);
    }

private:
#define MAX(a, b) (((a)>(b))?(a):(b))
int h(RBNode *z)
    {
    int a, b;
    if(z == Nil) return 0;
    a = h(z -> left());
    b = h(z -> right());
    return MAX(a, b) + 1;
    }

/* SUCCESSOR METHOD */
/* -------------------------------------------------------------- */

private:
RBNode *Successor(RBNode *z)
    {
    if(z -> right() != Nil)
        {
        z = z -> right();
        while(z -> left() != Nil) z = z -> left();
        }
    else
        {
        z = z -> p();
        while(z -> p() -> right() == z) z = z -> p();
        z = z -> p();
        }
    return z;
    }

/* -------------------------------------------------------------- */


/* EMPTY METHODS */
/* -------------------------------------------------------------- */
public:
bool isEmpty()
    { return Root == Nil; }

void Clear()
    { Root = Nil; }
/* -------------------------------------------------------------- */





/* QUERY METHOD */
/* -------------------------------------------------------------- */
public:
bool Query(int key)
    { return find(key) != Nil; }

private:
RBNode *find(int key)
    {
    RBNode *x = Root;
    while(x != Nil)
        {
        if(key > x -> key()) x = x -> right();
        else if(key < x->key()) x = x -> left();
        else return x;
        }
    return Nil;
    }
/* -------------------------------------------------------------- */

/* INSERTION METHODS */
/* -------------------------------------------------------------- */

public:
bool Insert(int key)
    {
    RBNode *n = new RBNode(key, RED, Nil, Nil, Nil);
    return insert(n);
    }


private:
bool insert(RBNode *z)
    {
    RBNode *y, *x;
    int key = z -> key();

    x = Root; y = Nil;
    while(x != Nil)
        {
        y = x;
        if(key > x -> key()) x = x -> right();
        else if(key < x -> key()) x = x -> left();
        else return false;
        }


    if(y == Nil) Root = z;
    else
        if(z->key() > y->key()) y->setRight(z);
        else y->setLeft(z);

    z->setParent(y);
    z->setColour(RED);
    InsertFixup(z);

    return true;
    }

void InsertFixup(RBNode *z)
    {
    RBNode *y;

    while(z -> p() -> colour() == RED)
        if(z -> p() -> p() -> left() == z -> p())   // p[z] is a left child
            {
            y = z -> p() -> p() -> right();     // y is z's uncle
            if(y -> colour() == RED)    // Case 1: z's uncle is RED
                {
                y -> setColour(BLACK);
                z -> p() -> setColour(BLACK);
                z -> p() -> p() -> setColour(RED);
                z = z -> p() -> p();
                }
            else
                {
                if(z -> p() -> right() == z)    // Case 2: z's uncle is BLACK and z is a right child
                    {
                    z = z -> p();
                    LeftRotate(z);
                    }
                // Case 3: z's uncle is BLACK and z is a left child
                z -> p() -> setColour(BLACK);
                z -> p() -> p() -> setColour(RED);
                RightRotate(z -> p() -> p());
                }
            }
        else
            {
            y = z -> p() -> p() -> left();     // y is z's uncle
            if(y -> colour() == RED)    // Case 4: z's uncle is RED
                {
                y -> setColour(BLACK);
                z -> p() -> setColour(BLACK);
                z -> p() -> p() -> setColour(RED);
                z = z -> p() -> p();
                }
            else
                {
                if(z -> p() -> left() == z)    // Case 5: z's uncle is BLACK and z is a left child
                    {
                    z = z -> p();
                    RightRotate(z);
                    }
                // Case 6: z's uncle is BLACK and z is a right child
                z -> p() -> setColour(BLACK);
                z -> p() -> p() -> setColour(RED);
                LeftRotate(z -> p() -> p());
                }
            }
    Root -> setColour(BLACK);
    }

/* -------------------------------------------------------------- */




/* DELETION METHODS */
/* -------------------------------------------------------------- */

public:
bool Delete(int key)
    {
    RBNode *z = find(key);
    if(z == Nil) return false;
    TreeDelete(z);
    return true;
    }

private:
void TreeDelete(RBNode *z)
    {
    RBNode *y, *x;

    if(z -> left() == Nil || z -> right() == Nil)
        y = z;
    else
        y = Successor(z);


    if(y -> left() == Nil) x = y -> right();
    else x = y -> left();

    x -> setParent(y -> p());
    if(y -> p() == Nil)
        Root = x;
    else
        if(y -> p() -> left() == y) y -> p() -> setLeft(x);
        else    y -> p() -> setRight(x);

    if(y != z) z -> setKey(y -> key());

    if(y -> colour() == BLACK)
        DeleteFixup(x);
    }

void DeleteFixup(RBNode *x)
    {
    RBNode *w;
    while(x -> colour() == BLACK && x != Root)
        {
        if(x -> p() -> left() == x)
            {
            w = x -> p() -> right();
            if(w -> colour() == RED)        // CASE 1
                {
                w -> setColour(BLACK);
                x -> p() -> setColour(RED);
                LeftRotate(x -> p());
                w = x -> p() -> right();
                }
            // w -> colour() == BLACK
            if(w -> left() -> colour() == BLACK && w -> right() -> colour() == BLACK)   // CASE 2
                {
                w -> setColour(RED);
                x = x -> p();
                }
            else
                {
                if(w -> right() -> colour() == BLACK)   // CASE 3
                    {
                    w -> left() -> setColour(BLACK);
                    w -> setColour(RED);
                    RightRotate(w);
                    w = x -> p() -> right();
                    }
                // w -> right() -> colour() == RED
                int c = x -> p() -> colour();      // CASE 4
                x -> p() -> setColour(BLACK);
                w -> setColour(c);
                w -> right() -> setColour(BLACK);
                LeftRotate(x -> p());
                x = Root;
                }
            }
        else
            {
            w = x -> p() -> left();
            if(w -> colour() == RED)        // CASE 5
                {
                w -> setColour(BLACK);
                x -> p() -> setColour(RED);
                RightRotate(x -> p());
                w = x -> p() -> left();
                }
            // w -> colour() == BLACK
            if(w -> right() -> colour() == BLACK && w -> left() -> colour() == BLACK)   // CASE 6
                {
                w -> setColour(RED);
                x = x -> p();
                }
            else
                {
                if(w -> left() -> colour() == BLACK)   // CASE 7
                    {
                    w -> right() -> setColour(BLACK);
                    w -> setColour(RED);
                    LeftRotate(w);
                    w = x -> p() -> left();
                    }
                // w -> left() -> colour() == RED
                int c = x -> p() -> colour();      // CASE 8
                x -> p() -> setColour(BLACK);
                w -> setColour(c);
                w -> left() -> setColour(BLACK);
                RightRotate(x -> p());
                x = Root;
                }
            }
        }
    x -> setColour(BLACK);
    }


/* -------------------------------------------------------------- */




/* ROTATION METHODS */
/* -------------------------------------------------------------- */
private:

void RightRotate(RBNode *y)
    {
    RBNode *x = y -> left();


    y->setLeft(x -> right());
    if(x -> right() != Nil)
        x -> right() -> setParent(y);

    x->setParent(y->p());
    if(y->p() != Nil)
        if(y->p()->right() == y)
            y->p()->setRight(x);
        else
            y->p()->setLeft(x);
    else
        Root = x;

    x -> setRight(y);
    y -> setParent(x);
    }

void LeftRotate(RBNode *x)
    {
    RBNode *y = x -> right();


    x->setRight(y -> left());
    if(y -> left() != Nil)
        y -> left() -> setParent(x);

    y->setParent(x->p());
    if(x->p() != Nil)
        if(x->p()->left() == x)
            x->p()->setLeft(y);
        else
            x->p()->setRight(y);
    else
        Root = y;

    y -> setLeft(x);
    x -> setParent(y);
    }
/* -------------------------------------------------------------- */



/* OUTPUT METHODS */
/* ----------------------------------------------- */

public:

void OutputTree()
    { if(Root != Nil) outputSubtree(Root, 0); }


void OutputSet()
    {
    if(Root != Nil) outputSubset(Root);
    cout << "\n";
    }

private:
void outputSubset(RBNode *z)
    {
    if(z -> left() != Nil) outputSubset(z -> left());
    cout << z -> key();
    if(z -> right() != Nil) outputSubset(z -> right());
    }

void outputSubtree(RBNode *z, int indentation)
    {
    if(z == Nil)
        {
        for(int i = 0; i < indentation; i++) cout << " ";
        cout << "nil\n";
        return;
        }
    outputNode(z, indentation);
    outputSubtree(z->left(), indentation + 2);
    outputSubtree(z->right(), indentation + 2);
    }


void outputNode(RBNode *z, int indentation)
    {
    for(int i = 0; i < indentation; i++) cout << " ";
    cout << z->key() << " " << (z->colour() == BLACK ? "BLACK" : "RED") << "\n";
    }

/* ----------------------------------------------- */


};








