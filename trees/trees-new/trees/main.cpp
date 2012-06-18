#include <cstdio>

struct Node
{
    Node* left;
    Node* right;
    Node* parent;


    int key;

    int leftPath;
    int rightPath;

    Node (int key, Node* parent)
    {
        this->key = key;

        this->left = NULL;
        this->right = NULL;
        this->parent = parent;

        this->leftPath=0;
        this->rightPath =0;

    }
};

void add (Node* &root, int key)
{
    if (key>root->key)
    {
        if (root->right==NULL)
        {
           root->right = new Node(key,root);
        }
        else
        {
            add (root->right,key);
        }
    }

    if (key<root->key)
    {
        if (key<root->key)
        {
            if (root->left==NULL)
            {
                root->left = new Node(key,root);
            }
            else
            {
                add (root->left,key);
            }
        }
    }
}

int max (int x, int y)
{
    return x>y?x:y;
}

void markup (Node* &root)
{
    if (root->left==NULL)
    {
        root->leftPath=0;
    }
    if (root->right==NULL)
    {
        root->rightPath = 0;
    }
    if (root->left!=NULL)
    {
        markup (root->left);
        root->leftPath = max (root->left->leftPath,root->left->rightPath)+1;
    }
    if (root->right!=NULL)
    {
        markup (root->right);
        root->rightPath = max (root->right->leftPath,root->right->rightPath)+1;
    }


}

void print (Node* root)
{
    printf ("KEY: %d\tlPath: %d\trPath:%d\tParent: %d\n",root->key,root->leftPath,root->rightPath,root->parent!=NULL?root->parent->key:NULL);
    if (root->left!=NULL) print(root->left);
    if (root->right!=NULL) print (root->right);
}

void cleanup (Node* &root)
{
    if (root->left!= NULL) cleanup (root->left);
    if (root->right!=NULL) cleanup (root->right);

    delete root->left;
    delete root->right;
}

void process (Node* root, Node* &bestFit)
{

}

int main ()
{
    const char path_in [] ="tst.in";
    const char path_out[] ="tst.out";

    FILE* file_in = fopen (path_in,"r");

    int key = 0;
    fscanf (file_in,"%d",&key);
    Node* root = new Node(key,NULL);
    while (!feof(file_in))
    {
        fscanf (file_in,"%d",&key);
        add (root,key);
    }
    fclose (file_in);
    markup (root);
    print (root);
    cleanup (root);
    delete root;
    return 0;
}
