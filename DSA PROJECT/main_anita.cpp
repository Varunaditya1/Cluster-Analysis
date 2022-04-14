#include <iostream>
#include<math.h>
using namespace std;
#define r 5
#define pos 10
int rear[pos+2]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int head[pos+2]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int MAX =5000;
int queue_bsf[500];
void display(int queue_array[], int i)
{
if(head[i] == -1)
printf("Queue is empty \n");
else
{
printf("Queue[%d] is : \n",i);
for(int j = head[i]; j <= rear[i]; j++)
{printf("%d",queue_array[j]);}
}
printf("\n");
}
void enqueue(int item , int queue_array[],int i)
{
if(rear[i] == MAX-1)
printf("Queue Overflow \n");
else
{
if(head[i]== -1)
{head[i] = 0;}
rear[i] = rear[i]+1;
queue_array[rear[i]] = item;
}
}
int dequeue(int queue_array[], int i)
{
if(head[i] == -1 || head[i] > rear[i])
{
printf("Queue Underflow \n");
}
if(head[i]!=-1)
{
int k = queue_array[head[i]];
head[i] = head[i]+1 ;
return k;
}
}

struct vertex {
    int x;
    int y;
};
struct points {
    int coord_1;
    int coord_2;
    double weight;
};
struct neighbours {
    int neigh[r-1];
};
struct mst{
struct points p[r-1];
};
struct vertex node_list[r];
struct points edges[pos];
struct neighbours neighbour[r-1];
struct mst mt;
int bfs(struct neighbours n[], int coord_1, int coord_2)
{
    if(head[coord_1]!=-1)
    {int temp = coord_1;
    int dist[r];
    for (int i = 0 ; i<r;i++)
    {
        dist[i]=989;
    }
    int v=0;
    enqueue(temp,queue_bsf,pos);
    while(head[pos]<=rear[pos] && head[pos]!=-1)
    {

        v = dequeue(queue_bsf,pos);
        int i = 0;
        int j;
        int temp_1[500];
        int l =0;
        while(l<=rear[temp])
    {
        enqueue(n[temp].neigh[l],temp_1,pos+1);
        l++;
    }
        while(i<l)
        {
            j = dequeue(temp_1,pos+1);
            dist[v]=v;
            if(dist[j]!=j)
            {enqueue(j,queue_bsf,pos);
            temp = j;}
            i++;
        }

    }

    if (dist[coord_2]==989)
    {
        return 0;
    }
    else
        {

        return 1;}}
        else
            return 0;


}
void form_mst(struct points p1[],struct neighbours n[], struct mst m)
{
    int k = 0;
  for (int i = 0 ; i<pos;i++)
  {

      if(k>r-2)
      {
          break;
      }
      else
      {if (i == 0 || i ==1)
      {
          enqueue(p1[i].coord_2,n[p1[i].coord_1].neigh,p1[i].coord_1);
          enqueue(p1[i].coord_1,n[p1[i].coord_2].neigh,p1[i].coord_2);
          m.p[k].coord_1= p1[i].coord_1;
          m.p[k].coord_2= p1[i].coord_2;
          m.p[k].weight= p1[i].weight;
         k++;
      }
      else
      {
         if(bfs(n,p1[i].coord_1,p1[i].coord_2)==0)
         {
             enqueue(p1[i].coord_2,n[p1[i].coord_1].neigh,p1[i].coord_1);
             enqueue(p1[i].coord_1,n[p1[i].coord_2].neigh,p1[i].coord_2);
             m.p[k].coord_1= p1[i].coord_1;
             m.p[k].coord_2= p1[i].coord_2;
             m.p[k].weight= p1[i].weight;
             k++;
         }

      }
      }
  }

  for (int i = 0 ; i <r-1;i++)
  {
      {
          printf("%d-%d\n",m.p[i].coord_1,m.p[i].coord_2);
      }
  }


}

void swap (struct points *p1, struct points *p2)
 {
    struct points temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

double euclid (struct vertex node1, struct vertex node2) {
    int temp_x;
    int temp_y;
    double dist;
    temp_x = pow(abs(node1.x - node2.x), 2);
    temp_y = pow(abs(node1.y - node2.y), 2);
    dist = sqrt(temp_x + temp_y);
    return dist;
}

int main() {


    int vertex1[r] = {0, 2, 1, 0,0};
    int vertex2[r] = {0, 2, 1, 2,3};
    int len = sizeof(vertex1)/sizeof(vertex1[0]);

    for (int i = 0; i < len; i++) {
        node_list[i].x = vertex1[i];
        node_list[i].y = vertex2[i];
    }
    int no_edges = 0;
    for (int i = 0; i < r; i++) {
        for (int j = i+1; j < r; j++) {
            edges[no_edges].coord_1 = i;
            edges[no_edges].coord_2 = j;
            edges[no_edges].weight = euclid(node_list[i], node_list[j]);
            no_edges++;
        }
    }

    for (int i = 0; i < no_edges; i++) {
        for (int j = i-1; j >= 0; j--) {
            if (edges[j].weight >= edges[j+1].weight) {
                swap(&edges[j], &edges[j+1]);
            }
        }
    }
    for (int i = 0 ; i<r;i++)
    {
        printf("coord[%d] = (%d, %d)\n", i, node_list[i].x,node_list[i].y);
    }

    for (int i = 0; i < no_edges; i++) {
        printf("Edge[%d] - %d - %d - %.2lf\n",
               i, edges[i].coord_1,
               edges[i].coord_2, edges[i].weight);
    }

    cout<<endl;
    form_mst(edges,neighbour,mt);
    return 0;
}
