#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <stack>
using namespace std;
//                     a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z
const char table[] = {'2', '2', '2', '3', '3', '3', '4', '4', '1', '1', '5', '5', '6', '6', '0', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9', '0'};
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";


struct Node
{
    Node* children [10];
    bool wrdBegin;
    int id;
};

void wordToNumber (char* word, char* &num)
{
    for (uint i=0;i<strlen(word);i++)
    {
        if (word[i]>='A' && word[i]<='Z')
        {
            num[i] = table[word[i]-'A'];
        }
        else
        {
            num[i]=word[i];
        }
    }
    num[strlen(word)]='\0';
}


void addWord (char* word, Node* &node, int pos, int id)
{
    pos--;
    if (node->children[word[pos]-'0']==NULL)
    {
        node->children[word[pos]-'0']=new Node;
        for (int i=0;i<10;i++) node->children[word[pos]-'0']->children[i]=NULL;
        node->children[word[pos]-'0']->wrdBegin = false;
    }
    if (pos==0)
    {
        node->children[word[pos]-'0']->wrdBegin = true;
        node->children[word[pos]-'0']->id = id;
    }
    else
    {
        addWord (word,node->children[word[pos]-'0'],pos, id);
    }
}


void clear (Node* &node)
{
    for (int i=0;i<10;i++)
    {
        if (node->children[i]!=NULL) clear (node->children[i]);
        delete node->children[i];

    }
}
int main ()
{
    Node* root = new Node;
    for (int i=0;i<10;i++) root->children[i]=NULL;
    FILE* fin = fopen (file_in,"r");
    char** wordArr = new char*[50010];
    char number [10010];
    int resTable [10010][2];
    fscanf(fin,"%s",&number);
    for (uint i=0;i<strlen(number);i++)
    {
        resTable[i][0] = 0;
        resTable[i][1] = 0;
    }
    int wordCount = 0 ;
    fscanf (fin,"%d",&wordCount);
    char* num= new char [110];
    for (int i=0;i<wordCount;i++)
    {
        wordArr[i] = new char[110];
        fscanf (fin,"%s",wordArr[i]);
        wordToNumber(wordArr[i],num);
        addWord(num,root,strlen(num), i);

    }
    delete [] num;
    fclose (fin);
    for (uint i=0;i<strlen(number);i++)
    {
        int k = i;
        Node* node = root;
        while (k>=0 && k<=i &&  node->children[number[k]-'0']!=NULL)
        {
            node = node->children[number[k]-'0'];
            if (node->wrdBegin)
            {
                if (k==0)
                {
                    resTable[i][0]=1;
                    resTable[i][1]=node->id;
                }
                else
                {
                    if (resTable[k-1][0]!=0 && (resTable[i][0] > resTable[k-1][0]+1 || resTable[i][0]==0))
                    {
                        resTable[i][0] = resTable[k-1][0]+1;
                        resTable[i][1] = node->id;
                    }
                }
            }
            k--;
        }
    }

    FILE* fout = fopen(file_out,"w");
    if (resTable[strlen(number)-1][0]!=0)
    {
        fprintf (fout, "%d\n",resTable[strlen(number)-1][0]);
        stack<int> wrds;
        int k=strlen(number)-1;
        while (k>=0)
        {
            wrds.push(resTable[k][1]);
            k =k - strlen(wordArr[resTable[k][1]]);
        }
        while (!wrds.empty())
        {
            fprintf(fout,"%s",wordArr[wrds.top()]);
            wrds.pop();
            if (!wrds.empty())
            {
                fprintf(fout," ");
            }
        }
    }
    else
    {
        fprintf (fout,"No solution\n");
    }
    fclose (fout);
//    for (int i=0;i<50010;i++) delete[] wordArr[i];
//    delete [] wordArr;
//    clear (root);
//    delete root;
    return 0;
}
