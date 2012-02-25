#include <iostream>
#include <cstdio>
using namespace std;

const char  fInName [] = "test.in";
const char  fOutName [] = "test.out";
const int INFINTIE =276447232;
struct Node
{
    int key;
    Node* lChild;
    Node* rChild;
    int leftPath;
    int rightPath;
    Node* leaf;
    Node* parent;
};

Node* find (int x, Node* node)
{
    if (node == NULL) return NULL;
    else
        if (x<node->key) return find (x,node->lChild);
        else if (x>node->key) return find (x, node->rChild);
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
        node->parent=NULL;
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
            return findMaximum(node->rChild);
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
                    return true;
                }
                else
                    if (node->rChild==NULL)
                    {
                        Node* tmp = node;
                        node = node->lChild;
                        delete tmp;
                        return true;
                    }
                    else
                    {
                        Node* tmp =findMinimum(node->rChild);
                        node->key=tmp->key;
                        return remove(node->key,node->rChild);
                    }
            }
    }
}

void print (Node* root)
{
    if (root == NULL) return;
    if (root->lChild !=NULL) print (root->lChild);
    printf ("KEY: %d lPATH: %d rPATH: %d PARENT: %d KEYLEAF: %d\n",root->key,root->leftPath, root->rightPath,root->parent==NULL?INFINTIE:root->parent->key,root->leaf->key);
    if (root->rChild !=NULL) print (root->rChild);

}
int max (int x, int y)
{
    return x>y?x:y;
}
int min (int x, int y)
{
    return x<y?x:y;
}

void markup (Node* &root)
{
    if (root == NULL) return;
    if (root->rChild!=NULL) markup(root->rChild);
    if (root->lChild!=NULL) markup(root->lChild);
    root->leaf = NULL;
    if (root->rChild!=NULL)
    {
        root->rightPath=max(root->rChild->rightPath,root->rChild->leftPath)+1;
        root->rChild->parent=root;
    }
    else
    {
        root->rightPath =0;
    }
    if (root->lChild!=NULL)
    {
        root->leftPath = max (root->lChild->rightPath,root->lChild->leftPath)+1;
        root->lChild->parent = root;
    }
    else
    {
        root->leftPath=0;
    }
    if (root->lChild==NULL && root->rChild==NULL) root->leaf=root;
    else
    {
        if (root->lChild==NULL) root->leaf=root->rChild->leaf;
        else
        {
            if (root->rChild==NULL) root->leaf=root->lChild->leaf;
            else
            {
                if (root->leftPath>root->rightPath)
                {
                    root->leaf=root->lChild->leaf;
                }
                else
                {
                    if (root->leftPath<root->rightPath)
                    {
                        root->leaf=root->rChild->leaf;
                    }
                    else
                    {
                        root->leaf = root->rChild->leaf->key < root->lChild->leaf->key?root->rChild->leaf:root->lChild->leaf;
                    }
                }
            }
        }
    }
}

void process (Node* &result, Node* root)
{
    if (root!=NULL)
    {
        process(result,root->lChild);
        process(result,root->rChild);
    }
}

int main ()
{
    FILE* fin = fopen (fInName,"r");
    Node* root = NULL;
    while (!feof (fin))
    {
        int tmp =0;
        fscanf (fin,"%d\n",&tmp);
        add (tmp,root);
    }
    fclose (fin);
    root->parent=NULL;
    markup(root);
    print(root);
    remove (root->key,root);

    return 0;
}
