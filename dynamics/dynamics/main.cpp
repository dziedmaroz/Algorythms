#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <stack>
using namespace std;
//                     a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z
const char table[] = {'2', '2', '2', '3', '3', '3', '4', '4', '1', '1', '5', '5', '6', '6', '0', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9', '0'};
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";


struct Node
{   
    //char chNum;
    map<char, Node*> children;
    bool wrdBegin;
};

string wordToNumber (string word)
{
    string num = word;
    for (int i=0;i<word.length();i++)
    {
        if (word[i]>='A' && word[i]<='Z')
        {
            num[i] = table[word[i]-'A'];
        }
    }
    return num;
}


void addWord (string word, Node* &node, int pos)
{
    pos--;
    if (node->children[word[pos]]==NULL)
    {
        node->children[word[pos]]=new Node;
        node->children[word[pos]]->wrdBegin = false;       
    }
    if (pos==0)
    {
        node->children[word[pos]]->wrdBegin = true;
    }
    else
    {
        addWord (word,node->children[word[pos]],pos);
    }
}

bool contains (string word, Node* &node, int pos)
{
    if (pos==0)
    {
        return node->wrdBegin;
    }
    pos--;
    if (node->children[word[pos]]!=NULL) return contains(word,node->children[word[pos]],pos);
    return false;
}

void clear (Node* &node)
{
    map<char, Node*>::iterator iter;
    for (iter = node->children.begin(); iter!=node->children.end();iter++)
    {
        if (iter->second!=NULL) clear(iter->second);
    }
    delete  node;
}
int main ()
{
    Node* root = new Node;
    FILE* fin = fopen (file_in,"r");
    map<int, map<string , string> > words;  
    char number [10010];
    int resTable [10010][2];
    fscanf(fin,"%s",&number);
    for (int i=0;i<strlen(number);i++)
    {
        resTable[i][0] = 0;
        resTable[i][1] = 0;
    }
    int wordCount = 0 ;
    fscanf (fin,"%d",&wordCount);
    string word;
    string num;
    for (int i=0;i<wordCount;i++)
    {
        char tmpStr [110];
        fscanf (fin,"%s",&tmpStr);
        word = tmpStr;
        num = wordToNumber(word);
        addWord(num,root,num.length());
        words[num.length()][num]=word;
    }
    fclose (fin);
    for (int i=0;i<strlen(number);i++)
    {
        int k = i;
        Node* node = root;
        while (k>=0 && k<=i &&  node->children[number[k]]!=NULL)
        {
            node = node->children[number[k]];
            if (node->wrdBegin)
            {
                if (k==0)
                {
                    resTable[i][0]=1;
                    resTable[i][1]=0;
                }
                else
                {
                    if (resTable[k-1][0]!=0 && (resTable[i][0] > resTable[k-1][0]+1 || resTable[i][0]==0))
                    {
                        resTable[i][0] = resTable[k-1][0]+1;
                        resTable[i][1] = k ;
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

        stack<string> wrds;
        string tmpStr = string(number);
        int k=strlen(number)-1;
        while (k>=0)
        {
            wrds.push(words[k-resTable[k][1]+1][tmpStr.substr(resTable[k][1],k-resTable[k][1]+1)]);
            k = resTable[k][1]-1;
        }
        while (!wrds.empty())
        {
            fprintf(fout,"%s",wrds.top().c_str());
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
    clear (root);
    return 0;
}
