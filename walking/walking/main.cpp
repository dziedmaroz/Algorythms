#include <stdio.h>
#include <vector>
#include <cmath>
using namespace std;

const char  file_in [] = "input.txt";
const char  file_out [] = "output.txt";

bool try_kuhn (int v, vector<vector<int> > &g, vector<int> &matching, vector<char> &visited) {
    if (visited[v])  return false;
    visited[v] = true;
    for (size_t i=0; i<g[v].size(); ++i) {
        int to = g[v][i];
        if (matching[to] == -1 || try_kuhn (matching[to],g,matching,visited)) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}

double dist (int x1, int y1, int x2, int y2)
{
    return pow((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2),0.5);
}

int  main(int argc, char **argv)
{
    int n, k;
    vector < vector<int> > g;
    vector<int> matching;
    vector<char> visited;
    FILE* fin = fopen(file_in,"r");
    fscanf (fin,"%d %d",&n,&k);
    int controlPoints [100][2];
    int favPlaces [100][2];
    for (int i=0;i<n;i++)
    {
        fscanf (fin,"%d %d",&controlPoints[i][0],&controlPoints[i][1]);
    }
    for (int i=0;i<k;i++)
    {
        fscanf (fin,"%d %d",&favPlaces[i][0],&favPlaces[i][1]);
    }
    fclose(fin);
    g = vector<vector<int> > (n);

    for (int i=1;i<n;i++)
    {

        for (int j=0;j<k;j++)
        {
            if (2*dist(controlPoints[i-1][0],controlPoints[i-1][1],controlPoints[i][0],controlPoints[i][1])>   (dist (controlPoints[i-1][0],controlPoints[i-1][1],favPlaces[j][0],favPlaces[j][1]) + dist (favPlaces[j][0],favPlaces[j][1],controlPoints[i][0],controlPoints[i][1])))
            {
                g[i].insert(g[i].end(),j);
            }
        }
    }

    matching.assign (k, -1);
    for (int v=0; v<n; ++v) {
        visited.assign (n, false);
        try_kuhn (v,g,matching,visited);
    }

    int count=0;
    for (int i=0; i<k; ++i)
        if (matching[i] != -1) count++;
    FILE* fout = fopen (file_out,"w");
    fprintf (fout,"%d %d\n",n+count,count);
    fclose (fout);
}
