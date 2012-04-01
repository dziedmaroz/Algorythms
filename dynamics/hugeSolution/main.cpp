#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <map>
#include <set>
using namespace std;
//                     a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z
const char table[] = {'2', '2', '2', '3', '3', '3', '4', '4', '1', '1', '5', '5', '6', '6', '0', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9', '0'};
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";



struct Word
{
    string word;
    string number;
};
struct Res
{
    int count;
    set<int> delim;
};

int cmp (Word wrd1, Word wrd2)
{
    return wrd1.number.compare(wrd2.number);
}

char* wtn (char* word)
{
    char* res = new char [strlen(word)+1];
    for (int i=0;i<strlen(word);i++)
    {
        if (word[i]>='A' && word[i]<='Z')
            res[i]=table[word[i]-'A'];
        else
            res[i]=word[i];
    }
    return res;
}

int sgn (int x){return x==0?0:1;}



int main ()
{
    FILE* fin = fopen ("input.txt","r");
    int wordCount = 0;
    map<int, map<string , Word> > words;
    Res** result = new Res* [10000];
    char* number = new char[10000];    
    fscanf(fin,"%s",number);
    int numLen = strlen(number);
    fscanf(fin,"%d",&wordCount);
    for (int i= 0;i<wordCount;i++)
    {
        Word wrd;
        char* tmp = new char [100];
        fscanf(fin,"%s",tmp);
        wrd.word = string(tmp);
        wrd.number = string(wtn(tmp));
        words[strlen(tmp)][wrd.number]=wrd;
        delete tmp;
    }
    for (int i=0;i<numLen;i++)
    {
        result[i]= new Res [numLen];
        for (int j=i;j<numLen;j++)
        {
            result[i][j].count=0;
            //result[i][j].delim.clear();
        }
    }
    fclose (fin);

    for (int j=0;j<numLen;j++)
    {
        for (int i=j;i>=0;i--)
        {
            char* tmp = new char [j-i+2];
            strncpy(tmp,number+i,j-i+1);
            tmp[j-i+1]='\0';
            //if (words[strlen(tmp)][string(tmp)].number!="")
            if(words.find(strlen(tmp))!=words.end() && words[strlen(tmp)].find(string(tmp))!=words[strlen(tmp)].end())
            {
                result[i][j].count=1;
                result[i][j].delim.clear();
                result[i][j].delim.insert(j);
            }
            else
            {
                for (int k=i;k<j;k++)
                {
                    if (result[i][k].count!=0 && result[k+1][j].count!=0)
                    {
                        if (result[i][j].count==0)
                        {
                            result[i][j].count = result[i][k].count+result[k+1][j].count;
                            result[i][j].delim.clear();
                            result[i][j].delim.insert(result[i][k].delim.begin(), result[i][k].delim.end());
                            result[i][j].delim.insert(result[k+1][j].delim.begin(),result[k+1][j].delim.end());
                        }
                        else
                        {
                            if (result[i][j].count>result[i][k].count+result[k+1][j].count)
                            {
                                result[i][j].count = result[i][k].count+result[k+1][j].count;
                                result[i][j].delim.clear();
                                result[i][j].delim.insert(result[i][k].delim.begin(), result[i][k].delim.end());
                                result[i][j].delim.insert(result[k+1][j].delim.begin(),result[k+1][j].delim.end());
                            }
                        }
                    }
                }
            }
            delete[] tmp;
        }
    }

    FILE* fout = fopen(file_out,"w");
    if (result[0][numLen-1].count!=0)
    {
        fprintf(fout,"%d\n",result[0][numLen-1].count);
        string numStr = string(number);
        int* tmpArr = new int[result[0][numLen-1].delim.size()];
        int k =0;
        for (set<int>::iterator i = result[0][numLen-1].delim.begin(); i!=result[0][numLen-1].delim.end();i++ )
        {
            tmpArr[k]=*i;
            k++;

        }
        fprintf(fout,"%s ",words[tmpArr[0]+1][numStr.substr(0,tmpArr[0]+1)].word.c_str());
        for (int i=1;i<result[0][numLen-1].delim.size();i++)
        {

            if (i+1==result[0][numLen-1].delim.size())
            {
                fprintf(fout,"%s",words[tmpArr[i]-tmpArr[i-1]][numStr.substr(tmpArr[i-1]+1,tmpArr[i]-tmpArr[i-1])].word.c_str());
            }
            else
            {
                fprintf(fout,"%s ",words[tmpArr[i]-tmpArr[i-1]][numStr.substr(tmpArr[i-1]+1,tmpArr[i]-tmpArr[i-1])].word.c_str());
            }
        }
        delete [] tmpArr;
        fprintf(fout,"\n");
    }
    else
    {
        fprintf(fout,"No solution\n");
    }


    for (int i=0;i<10000;i++)
    {
        delete[] result[i];
    }

    delete[] result;
    delete[] number;
    return 0;
}
