#include <iostream>
#include <cstdio>
using namespace std;

const char  fInName [] = "test.in";
const char  fOutName [] = "test.out";

struct Node
{
    int key;
    Node* lChild;
    Node* rChild;
};

Node* find (int x, Node* node)
{
    if (node == NULL) return NULL;
    else
        if (x<node->key) find (x,node->lChild);
        else if (x>node->key) find (x, node->rChild);
            else return node;
}

void add (int x, Node* &node)
{
    if (node==NULL)
    {
        node = new Node;
        node->lChild=NULL;
        node->rChild=NULL;
        node->key=x;
    }
    else
    {
        if (x<node->key)
        {
            add(x,node->lChild);
        }
        else
            if (x>node->key)
            {
                add(x,node->rChild);
            }
    }
}

Node* findMinimum (Node* node)
{
    if (node == NULL) return NULL;
    else
        if (node->lChild==NULL)
        {
            return node;
        }
        else
        {
            return findMinimum(node->lChild);
        }
}

Node* findMaximum (Node* node)
{
    if (node == NULL) return NULL;
    else
        if (node->rChild==NULL)
        {
            return node;
        }
        else
        {
            return findMinimum(node->rChild);
        }
}

bool remove (int x, Node* &node)
{
    if (node==NULL)
    {
        return false;
    }
    else
    {
        if (x<node->key)
        {
           return  remove(x,node->lChild);
        }
        else if (x>node->key)
        {
            return remove(x,node->rChild);
        }
            else
            {
                if(node->lChild==NULL)
                {
                    Node* tmp = node;
                    node= node->rChild;
                    delete tmp;
                }
                else
                    if (node->rChild==NULL)
                    {
                        Node* tmp = node;
                        node = node->lChild;
                        delete tmp;
                    }
                    else
                    {
                        Node* tmp =findMinimum(node->rChild);
                        node->key=tmp->key;
                        remove(node->key,node->rChild);
                    }
            }
    }
}

int main ()
{
    FILE* fin = fopen ("test.in","r");
    Node* root = NULL;
    while (!feof (fin))
    {
        int tmp =0;
        fscanf (fin,"%d",&tmp);
        add (tmp,root);
    }
    fclose (fin);
    remove (root->key,root);
    return 0;
}
