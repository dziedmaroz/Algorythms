#include <cstdio>
#include <vector>

using namespace std;
int task_descr [50010][2];
int task_count;
const char fileIn [] ="input.txt";
const char fileOut [] ="output.txt";


int n; //
vector<int> g[50010]; //
bool used[50000];
vector<int> ans;

bool findLatest (int &to)
{
	bool finded = false;
	for (int i=0;i<task_count && !finded;i++)
	{
		if (!used[i])
		{
			to = i;
			finded = true;
		}
	}

	for (int i=to+1;i<task_count;i++)
	{
	    if (!used[i] && task_descr[i][1]<task_descr[to][1])
	    {
		to = i;
	    }
	}
	return finded;
}

void dfs (int v) {
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs (to);
	}
	ans.push_back (v);
}

void topological_sort() {
	for (int i=0; i<n; ++i)
		used[i] = false;
	ans.clear();
	int i=0;
	while (findLatest (i))
	{
	    dfs (i);
	}

}

int main ()
{
	FILE* fin = fopen (fileIn,"r");

	task_count = 0;
	fscanf (fin,"%d",&task_count);
	for (int i=0;i<task_count;i++)
	{
		fscanf (fin,"%d %d",&task_descr[i][0],&task_descr[i][1]);
	}
	fscanf(fin,"%d",&n);
	for (int i=0;i<n;i++)
	{
		int from =0;
		int to = 0;
		fscanf(fin,"%d %d",&from,&to);
		g[to-1].push_back(from-1);
	}
	fclose (fin);

	topological_sort();
	int lastTaskEnd = 0;
	int maxPenalty  = 0;
	int maxPenaltyId = 0;


	for (int i=0;i<ans.size();i++)
	{
	    lastTaskEnd+=task_descr[ans[i]][0];

	    if (maxPenalty<(lastTaskEnd-task_descr[ans[i]][1]))
	    {
		maxPenalty = lastTaskEnd-task_descr[ans[i]][1];
		maxPenaltyId = ans[i]+1;
	    }
	}

	FILE* fout = fopen (fileOut,"w");


	fprintf (fout,"%d %d\n",maxPenaltyId,maxPenalty);
	for (int i=0;i<ans.size();i++)
	{
		fprintf(fout,"%d\n",ans[i]+1);
	}
	fclose (fout);

	return 0;
}
