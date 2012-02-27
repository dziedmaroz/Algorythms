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
        if (root->leftPath+root->rightPath > result->rightPath+result->leftPath)
        {
            result = root;
        }
        else
        {
            if (root->leftPath+root->rightPath == result->rightPath+result->leftPath)
            {
                int resLeftLRightSumm = result->lChild->leaf->key + result->rChild->leaf->parent->key;
                int resLeftRightLSumm = result->lChild->leaf->parent->key + result->rChild->leaf->key;

                int rooLeftLRightSumm = root->lChild->leaf->key + root->rChild->leaf->parent->key;
                int rooLeftRightLSumm = root->lChild->leaf->parent->key + root->rChild->leaf->key;

                if (resLeftLRightSumm>rooLeftLRightSumm || resLeftLRightSumm > rooLeftRightLSumm || resLeftRightLSumm > rooLeftLRightSumm || resLeftRightLSumm > rooLeftRightLSumm)
                {
                    result = root;                    
                }
                else
                {
                    if (resLeftLRightSumm==rooLeftLRightSumm && resLeftLRightSumm == rooLeftRightLSumm && resLeftRightLSumm == rooLeftLRightSumm && resLeftRightLSumm == rooLeftRightLSumm)
                        if (result->key>root->key) result = root;
                }
            }
        }
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
    Node* result = root;
    process(result,root);
    if ((result->leftPath+result->rightPath)%2!=0)
    {
        if (result->leftPath>result->rightPath)
        {
            int steps =
        }
        else
        {
            if (result->rightPath>result->leftPath)
            {

            }
            else
            {
                remove(result->key,root);
            }
        }
    }
    remove (root->key,root);

    return 0;
}
