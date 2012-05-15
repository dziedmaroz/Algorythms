#include <stdio.h>
#include <math.h>
const char file_in[] = "input.txt";
const char file_out[] = "output.txt";

struct Edge
{
    int from;
    int to;
    int weight;
};

struct Vertex
{
    int ID;
    int x;
    int y;
};

double dist (int x1, int y1, int x2, int y2)
{
    return pow((double)(x1-x2)*(x1-x2)+(y1-y2)*(y1-y2),0.5);
}

int main ()
{
    FILE* fin = fopen (file_in);
    Vertex favPoints [100];
    Vertex keyPoints [100];
    int favCount = 0;
    int keyCount = 0;

    fscanf(fin,"%d %d",&keyCount,&favCount);
    for (int i=0;i<keyCount;i++)
    {
        keyPoints[i].ID=i;
        fscanf (fin,"%d %d",&keyPoints[i].x,&keyPoints[i].y);
    }
    for (int i=0;i<favCount;i++)
    {
        favPoints[i].ID=i;
        fscanf (fin,"%d %d",&favPoints[i].x,&favPoints[i].y);
    }
    fclose (fin);

    for (int i=0;i<keyCount;i++)
    {
        for (int j=i+1;j<keyCount;j++)
        {
            for (int k=0;k<favCount;k++)
            {
                if (2*(dist(keyPoints[i].x,keyPoints[i].y,keyPoints[j].x,keyPoints[j].y))<(dist(keyPoints[i].x,keyPoints[i].y,favPoints[k].x,favPoints[k].y)+dist(keyPoints[j].x,keyPoints[j].y,favPoints[k].x,favPoints[k].y)))
                {
                   // добавляем ребро в граф
                }
            }
        }
    }

    return 0;
}
