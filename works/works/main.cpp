#include <stdio>
#include <priority_queue>

class Job
{
private:
    int id_;
    int deadline_;
    int length_;
    int parents_;
    Job (int id, int deadline, int length):id_(id),deadline_(deadline),length_(length),parents_(0){}
    bool operator < (Job o)
    {
        if (this->parents_.size()<o.parents_.size()) return true;
        else
        {
            if (this->parents_.size()==o.parents_.size())
            {
                return this->deadline_<o.deadline_;
            }
        }
        return false;
    }
    bool operator > (Job o) {return ! operator < (o);}

    void setParents (int count) {parents_=count;}
    int getParents () {return parents_;}
    void incParents () {parents_++;}
    void decParents () {parents_--;}

};



struct Node
{
    Node* next;
    int value;
};


int main ()
{
    FILE* fin = fopen ("input.txt","r");
    int jobCount =0;
    fscanf (fin,"%d",&jobCount);
    Job* jobs = new Job[jobCount];
    Node* edges = new Node[jobCount];
    for (int i=0;i<jobCount;i++) edges[i]=NULL;
    for (int i=0;i<jobCount;i++)
    {
        int deadline =0;
        int length = 0;
        fscanf (fin,"%d %d",&length,&deadline);
        jobs[i] = Job(i+1,deadline,length);
    }
    int edges=0;
    fscanf (fin,"%d",&edges);
    for (int i=0;i<edges;i++)
    {
        int from =0;
        int to =0;
        fscanf (fin,"%d %d",&from,&to);
        Node* tmp = new Node;
        tmp->next = edges[from-1];
        tmp->value=to;
        edges[from-1] = tmp;
    }
    fclose (fin);
    delete[] edges;
    return 0;
}
