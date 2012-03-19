#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <set>

using namespace std;
//                     a    b    c    d    e    f    g    h    i    j    k    l    m    n    o    p    q    r    s    t    u    v    w    x    y    z
const char table[] = {'2', '2', '2', '3', '3', '3', '4', '4', '1', '1', '5', '5', '6', '6', '0', '7', '0', '7', '7', '8', '8', '8', '9', '9', '9', '0'};
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";

struct Word
{
    char* word;
    char* number;
};
struct Res
{
    int count;
    int delim;
};

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

    Res** result = new Res* [10000];
    for (int i=0;i<10000;i++)
    {
        result[i]= new Res [10000];
        for (int j=0;j<10000;j++)
        {
            result[i][j].count=0;
            result[i][j].delim=j;
        }
    }



    char* number = new char[10000];
    int numLen = strlen(number);
    fscanf(fin,"%s",number);
    fscanf(fin,"%d",&wordCount);
    for (int i= 0;i<wordCount;i++)
    {
        Word* wrd = new Word;
        wrd->word = new char [100];
        fscanf(fin,"%s",wrd->word);
        wrd->number = wtn(wrd->word);


    }
    fclose (fin);

    for (int j=0;j<numLen;j++)
    {
        for (int i=j;i>0;i--)
        {
            char* tmp = new char [j-i+2];
            strncpy(tmp,number+i,j-i+1);
            tmp[j-i+1]='\0';

            if (wrd!=NULL)
            {
                result[i][j].count=1;
            }
            else
            {                 
                for (int k=i;k<j;k++)
                {
                    if (sgn(result[i][k].count*result[i+k+1][j].count))
                    {
                        if (result[i][j].count>result[i][k].count+result[k+1][j].count || result[i][j].count==0)
                        {
                            result[i][j].count = result[i][k].count+result[k+1][j].count;
                            result[i][j].delim = k;
                        }
                    }
                }
            }

        }
    }

    for (int i=0;i<wordCount;i++)
    {
        for (int j=0;j<wordCount;j++)
        {
            printf ("%3d",result[i][j].count);
        }
        printf("\n");
    }
    for (int i=0;i<10000;i++)
    {
        delete[] result[i];
    }
    delete[] result;
    delete[] number;    
    return 0;
}
