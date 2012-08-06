/*
Important Note:: Please be patient while running the program runs for n=100. It might seem like it
has crashed but it does not. It just takes a little longer to run for n=100; somewhat around a minute or two.
 Name- Ritwik Yadav
 Roll Number- 10CS30034
 Assignment 4- Random Graphs
 */
//importing necessary header files
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef int** graph; //defining the adjacency list graph type

//defining the node of a queue
typedef struct _node
{
  int i;
  struct _node* next;
}node;
typedef node* queue;

//this function enques the node p to q
queue enqueue(queue q, queue p) 
{
  if (q==NULL)
    return p;
  else 
    {
      queue trav;
      trav=q;
      while (trav->next!=NULL)
	trav=trav->next;
      trav->next=p;
      return q;
    }
}

//this function dequeues the given queue a
queue dequeue(queue a)
{
  if (a==NULL) return a;
  else
    {
      queue trav=a;
      trav=trav->next;
      free(a);
      return trav;
    }
}

//this function checks the connectivity of a graph with n nodes
int isConnect(graph g, int n)
{
  int idx;
  queue trav;
  int visit[n];
  for(idx=0; idx<n; idx++)
    visit[idx]=0;
  //applying the breadth first search technique to check connectivity of the graph
  queue q=(queue)malloc(sizeof(node));
  q->i=0;
  visit[0]=1;
  q->next=NULL;
  while(q!=NULL)
    {
      int u=q->i;
      q=dequeue(q);
      for(idx=1; idx<=g[u][0]; idx++)
	{
	  if (visit[g[u][idx]]==0)
	    {
	      queue nod=(queue)malloc(sizeof(node));
	      nod->i=g[u][idx];
	      nod->next=NULL;
	      q=enqueue(q, nod);
	      visit[g[u][idx]]=1; //updating the visited array
	    }
	}
    }
  for(idx=0; idx<n; idx++)
    if(visit[idx]==0) return -1; // graph is not connected
  return 1; //graph is connected

}

//this function gives the diameter of the graph g with n nodes
int giveDia(graph g, int n)
{
  int i,j,k;
    int D[n][n];
  for(i=0; i<n; i++)
    {
      for(j=0; j<n; j++)
		  if(i==j)
			  D[i][j]=0;
		else
			  D[i][j]=50000; //the initial value is set to a high value representing infinity.
      // For n=100, the diameter would never exceed say 100.
    }

  //Applying the APSP problem, with each edge cost=1
  for(i=0; i<n; i++)
    {
      for(j=1; j<=g[i][0]; j++)
	{
	  D[i][g[i][j]]=1; //setting the matrix for direct edges 
	}
    }

  //Using dynamic programming method to update the matrix D unless it gives the best possible path length at D[i][j] between i and j nodes
  for(k=0; k<n; k++)
    {
      for(i=0; i<n; i++)
	{
	  for(j=i+1; j<n; j++)
	    {
	      D[i][j]=(D[j][i]=(D[i][j]<(D[i][k]+D[k][j]))?D[i][j]:(D[i][k]+D[k][j]));
	    }
	}
    }
  k=-1;
  //Computing the maximum possible paths between two nodes in the graph.
  for(i=0; i<n; i++)
	{
	  for(j=i+1; j<n; j++)
	    {
	      if(D[i][j]>k) k=D[i][j];
	    }
	}
  return k;

}

//this function generates a graph of n nodes with the probability of each node being present=p
graph gen_graph(int n, double p)
{
  int i, j;
  double prob;
  graph G=(graph)malloc(sizeof(int*)*n); //allocating memory for the graph
  //initializing
  for(i=0; i<n; i++)
    {
      G[i]=(int*)malloc(n*sizeof(int));
      G[i][0]=0;
    }
  
  for (i=0; i<n; i++)
    {
      for(j=i+1; j<n; j++)
	{
	  prob=1.0*rand()/RAND_MAX;
	  //a random number is generated between zero and 1; and the edge is created accordingly
	  if(prob<=p)
	    {
	      //creating an edge
	      G[i][++G[i][0]]=j;
	      G[j][++G[j][0]]=i;
	    }
	}
      
      G[i]=(int*)realloc(G[i],(G[i][0]+1)*sizeof(int)); //freeing up unused memory
      
    }
  return G;
}

int main()
{
  int vertices;
  printf("Enter Number of vertices=");
  scanf("%d", &vertices);
  printf("\n");
  srand((unsigned int) time(NULL)); //seeding the random number generator
 
  double data[201][3]; //this matrix stores the data to be written in the file.
  //The first column has the local connectivity
  //The second column has the global connectivity
  //The third column has the average diameter
  int i,j;
  float p;
  graph G;
  int count, sumDia;
  j=0;

  //changing the value of p in appropriate step
  for(p=0; p<=1.0; p=p+0.0050)
    {
      count=0;
      sumDia=0;
      //generating 100 such graphs
      for(i=1; i<=100; i++)
	{
	  G=gen_graph(vertices, p);
	  if(isConnect(G, vertices)==1) 
	    {
	      count++; //stores the number of connected graphs
	      sumDia+=giveDia(G, vertices); //calculating the sum of the diameters of the connected graphs
	    }
	}
      data[j][0]=p;
      data[j][1]=1.0*count/100.0;
      if(count!=0)
	data[j][2]=1.0*sumDia/count; //calculating the average diameter
      else data[j][2]=1000000.0;
      printf("%f %f %f\n", data[j][0], data[j][1], data[j][2]);
      j++;
    }
  printf("\n");
  //writing the output to the file
  FILE *if1;
  if1=fopen("randgraph.dat", "w");
  for(i=0; i<201; i++)
    fprintf(if1, "%f %f %f\n", data[i][0], data[i][1], data[i][2]);
  printf("\nOutput successfully written to the file: randgraph.dat\n");
}
