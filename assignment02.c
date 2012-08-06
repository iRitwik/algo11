/*
Name- Ritwik Yadav
Roll Number- 10CS30034
Assignment 2- Graphs, trees and heaps!
*/
//importing necessary header files
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
//defines the node of a binary tree which stores the binomial tree in the first child next sibling representation.
typedef struct _bintreenode
{
	int d;
	int nodenum;
	struct _bintreenode *left, *right;
}bnode;

//defines the heap node which stores the binomial heap
typedef struct _heapnode
{
	int val;
	struct _heapnode *next;
	bnode* bintree;
}hnode;

//insertion sort function to sort the array of degree sequences in decreasing order
void sort_ins(int* d, int n)
{
	int i,j,r;
	int k=0; //stores the index till where the array has been sorted.
	for(i=k+1; i<n; i++)
	{
		int ele=d[i];
		for(j=0; j<=k; j++)
		{
			if(ele>d[j])
				break;
		}
		for(r=k; r>=j; r--)
		{
			d[r+1]=d[r];
		}
		d[j]=ele;
		k++;
	}
}

//This function joins two binary trees
bnode* joinTree(bnode *a, bnode *b)
{
	bnode *c;
	if (a==NULL) return b;
	else if (b==NULL) return a;
	else 
	{
		if ((a->d)>(b->d))
		{
		if (a->left!=NULL)
		b->right=a->left;
		a->left=b;
		c=a;
		}
		else
		{
		if (b->left!=NULL)
		a->right=b->left;
		b->left=a;
		c=b;
		}
		return c;
	}
}

//this function merges two binomial heaps into one single binomial heap
hnode* mergeheap(hnode* a, hnode* b)
{
  int flag=-1; //flag is used to keep track of which heap is shorter
  int preval=-5; //this variable keeps track of the previous order of the tree encountered
  hnode *i,*j; bnode *c; //i and j are traversal variables. c stores the carry over
	
	if ((a->next==NULL) && (b->next==NULL)) return (hnode*)malloc(sizeof(hnode)); 
	//if both heaps are empty, we return an empty heap
	else
	{
	if(a->next!=NULL)
	{
		i=a->next;
	}
	else flag=0; //setting flag to 0 if heap1 is empty
	
	if(b->next!=NULL)
	{
		j=b->next;
	}
	else flag=1; //setting flag to 1 if heap2 is empty
	}
	c=NULL;
	hnode *res, *result; //stores the resultant heap
	res=(result=(hnode*)malloc(sizeof(hnode)));
	while(flag==-1)
	{
	  //this loop runs so long as either one or both heaps gets empty

		if(((i->val)>(preval+1)) && ((j->val)>(preval+1)) && (c!=NULL))
		{ //appropriately placing carryover in its correct position 
			res->next=(hnode*)malloc(sizeof(hnode));
			res=res->next;
			res->val=preval+1;
			res->bintree=c;
			c=NULL;
		}
		
			if((i->val)==(j->val))
			{
				if(c!=NULL)
				{
				res->next=(hnode*)malloc(sizeof(hnode));
				res=res->next;
				res->val=i->val;
				res->bintree=c; //placing carry resulting from previous addition
				c=joinTree((i->bintree), (j->bintree)); //updating carry
				preval=i->val; //updating preval
				i=i->next; //incrementing pointer
				j=j->next; //incrementing pointer
				}
				else
				{
				  c=joinTree((i->bintree), (j->bintree)); //updating carry
				  preval=i->val; //updating preval

				i=i->next; //incrementing pointer
				j=j->next; //incrementing pointer
				}
			}
			else if((i->val)<(j->val))
			{
				if(c==NULL)
				{
				  //if there was no carry from previous additions, creating a new node
					res->next=(hnode*)malloc(sizeof(hnode));
					res=res->next;
					res->val=i->val;
					res->bintree=i->bintree;
					preval=i->val; //updating preval
					i=i->next; //incrementing pointer
				}
				else 
				{
				  //otherwise the carry needs to be updated
				  c=joinTree(c,i->bintree); //updating carry
				  preval=i->val; //updating preval
				  i=i->next; //incrementing pointer
				}
			}
			else
			{
				if(c==NULL)
				{
				  //if there was no carry from previous additions, creating a new node
					res->next=(hnode*)malloc(sizeof(hnode));
					res=res->next;
					res->val=j->val;
					res->bintree=j->bintree;
					preval=j->val; //updating preval
					j=j->next; //incrementing pointer
				}
				else 
				{
				  //otherwise the carry needs to be updated
				c=joinTree(c,j->bintree);
				preval=j->val; //updating preval
				j=j->next; //updating pointer
				}
			}
			//setting value of flag according to which heap is shorter
		if(i==NULL) flag=0; 
		else if (j==NULL) flag=1;
		
	}
	
if (flag==0)
{
  //flag=0 implies heap1 is shorter
	while(j!=NULL)
	{
	  //adding the rest of the nodes in heap2 to the result
		if((j->val)==(preval+1))
		{
		if(c==NULL)
		{
			res->next=(hnode*)malloc(sizeof(hnode));
			res=res->next;
			res->val=j->val;
			res->bintree=j->bintree;
			preval=j->val;
			j=j->next;
		}
		else 
		{
			c=joinTree(c,j->bintree);
			preval=j->val;
			j=j->next;
		}
		}

		else if(c!=NULL)
		{
			res->next=(hnode*)malloc(sizeof(hnode));
			res=res->next;
			res->val=preval+1;
			res->bintree=c;
			preval++;
			c=NULL;
		}
		else preval++; //incrementing preval

	}
	
	if(c!=NULL)
	{
	  //if a carry over is still left, a new node is added to the end
		res->next=(hnode*)malloc(sizeof(hnode));
		res=res->next;
		res->val=preval+1;
		res->bintree=c;
	}
}
	
	
	if (flag==1)
	{
	  //flag=1 implies heap2 is shorter
		while(i!=NULL)
		  { //adding rest of the nodes of heap1 to the result
			if((i->val)==(preval+1))
			{
				if(c==NULL)
				{
					res->next=(hnode*)malloc(sizeof(hnode));
					res=res->next;
					res->val=i->val;
					res->bintree=i->bintree;
					preval=i->val;
					i=i->next;
				}
				else 
				{
					c=joinTree(c,i->bintree);
					preval=i->val;
					i=i->next;
				}
			}
			else if(c!=NULL)
			{
				res->next=(hnode*)malloc(sizeof(hnode));
				res=res->next;
				res->val=preval+1;
				res->bintree=c;
				preval++;
				c=NULL;
			}
			else preval++;
			
		}
		
		if(c!=NULL)
		{
		  //adding a new node to end if the carryover still exists
			res->next=(hnode*)malloc(sizeof(hnode));
			res=res->next;
			res->val=preval+1;
			res->bintree=c;
		}
	}
	
	res->next=NULL; //ending the result
	return result;
      }
	
hnode* makeheap(int *d_arr, int i, int j)
{
  //divide and conquer algorithm to create a heap from the degree sequences given
	int k;
	if(i==j)
	{
	  bnode *p=(bnode*)malloc(sizeof(bnode)); //creating a single node
		p->d=d_arr[i];
		p->nodenum=i;
		p->left=NULL;
		p->right=NULL;
		hnode *rr, *rrr;
		//creating an heap with just one node
		rrr=(rr=(hnode*)malloc(sizeof(hnode)));
		rr->next=(hnode*)malloc(sizeof(hnode));
		rr=rr->next;
		rr->val=0;
		rr->bintree=p;
		rr->next=NULL;
		return rrr;
	}
	
	k=(i+j)/2;
	hnode *h1, *h2;
	h1=makeheap(d_arr, i, k);
	h2=makeheap(d_arr, k+1, j);
	
	return mergeheap(h1,h2); //merging the two heaps with half nodes each to a single heap
}

//function to insert a node into a heap
hnode* insert(bnode *p, hnode *j)
{	
  //creates an empty heap with one node
	hnode *rr, *rrr;
	rr=(rrr=(hnode*)malloc(sizeof(hnode)));
	rr->next=(hnode*)malloc(sizeof(hnode));
	rr=rr->next;
		rr->val=0;
		rr->bintree=p;
		rr->next=NULL;

		return mergeheap(rrr,j); //merging it with the already existent heap
}

//this function returns the pointer to the heap node whose next node has the node with greatest degree

hnode* findmax(hnode *heap)
{
  int maxdeg=-1; //since degree is positive, we initially set degree to a negative value
	hnode *p=heap;
	if (heap->next==NULL) return heap; //if heap is empty, empty heap is returned
	heap=heap->next;

	while (heap->next!=NULL)
	{
	  //finding the node with the greatest degree
	  if ((heap->next->bintree->d)>maxdeg)
		{
			p=heap;
			maxdeg=p->next->bintree->d;
		}
		heap=heap->next;
	}
	
	return p;
}

//this function deletes the node with the maximum degree
hnode* delmax(hnode *heap)
{
  hnode *h=findmax(heap); //finding the address of the maximum degree node in the heap
  if (h->next==NULL) return heap; //if the heap is empty, there is nothing to delete
	hnode *h1=(hnode*)malloc(sizeof(hnode));
	hnode *h2=h1;
	int heval=h->next->val; //storing the degree of the tree
	bnode *b, *bd;
	b=(bd=h->next->bintree->left);
	int i,j;
	for(i=0; i<heval; i++)
	{
	  //storing the children of the root in another heap
		h1->next=(hnode*)malloc(sizeof(hnode));
		h1=h1->next; 
		h1->val=i;
		for(j=1; j<=(heval-i-2); j++)
			b=b->right;
		if(b->right!=NULL)
		h1->bintree=b->right;
		else h1->bintree=b;

		b->right=NULL;
		b=bd;
		
	}
	h1->next=NULL;
	h->next=h->next->next; //deleting the heapnode which has the root node with maximum degree
	return mergeheap(heap, h2); //merging the heap of children with the original heap and max. heapnode deleted
	
}


	
int main()
{
	int n, sum; //n is the number of vertices in the graph
	int *deg; //array which sotres the degree sequence
	int i,j,flag; //i, j are loop variables
	//flag is used to keep track if the degree sequence is graphic using Erdos Gallai criterion
	printf("Enter the number of vertices=");
	scanf("%d",&n);
	deg=(int*)malloc(n*sizeof(int));
	srand((unsigned int) time(NULL)); //seeding the random number generator with a time function
	for(i=0; i<n; i++)
	{
	  /* //uncomment this region and comment the line which follows to manually enter the degree sequence
	        printf("Enter Degree=");
		scanf("%d", &deg[i]);
		printf("\n");
	  */
		deg[i]=(int)rand()%n;
		sum+=deg[i];
	}
	sort_ins(deg, n); //sorting the degree sequence in descending order
	printf("\n+++ Sequence Generated:\n");
	
	for(i=0; i<n; i++)
	{
	  //printing the generated degree sequence
		if(i!=(n-1))
		printf("%d,",deg[i]);
		else
		printf("%d\n",deg[i]);
		
	}
	
	flag=0;
	//Applying the Erdos-Gallai criterion to check if the degree sequence is graphic
	if((sum%2)!=0)
	{
		flag=1;
	}
	
		for(i=0; i<n; i++)
		{
			int lsum=0;
			for(j=0; j<=i; j++)
			{
				lsum+=deg[j];
			}
			int rsum=i*(i+1);
			for(j=i+1; j<n; j++)
			{
				rsum+=(deg[j]<(i+1))?deg[j]:(i+1);
			}
			if (lsum>rsum)
			{
				flag=1;
				break;
			}
		}
	if (flag==1)
	{
		printf("\n*** Error: The sequence is not graphic...\n");
		exit(0); //exiting if the degree sequence is graphic
	}
	else printf("\n+++ Degree sequence is graphic...");
	
	//The Havel Hakimi algorithm is implemented here

	//initialising an empty graph
	int **graph=(int**)malloc(n*sizeof(int*));
	for(i=0; i<n; i++)
	{
		graph[i]=(int*)malloc(n*sizeof(int));
		for(j=0; j<n; j++)
		graph[i][j]=0;
	}
	
	hnode *h=makeheap(deg, 0, n-1); //creating the heap from the given degree sequence
	printf("\n+++ Degree sequence stored in heap...");
	hnode *dum;
	while(h->next!=NULL)
	{   
	        dum=findmax(h); ///finding the node with maximum degree.
		int d=dum->next->bintree->d;
		int u=dum->next->bintree->nodenum;
		
		h=delmax(h); //deleting node with maximum degree
		
		hnode *h1=(hnode*)malloc(sizeof(hnode));
		
		for(i=1; i<=d; i++)
		  {  // making d connections with other nodes
			hnode *maxh=findmax(h);
			int r=maxh->next->bintree->d;
			int v=maxh->next->bintree->nodenum;
			h=delmax(h);
			//updating the graph
			graph[u][v]=1;
			graph[v][u]=1;
			if(r>1)
			{
				bnode *bn=(bnode*)malloc(sizeof(bnode));
				bn->d=r-1;
				bn->nodenum=v;
				bn->left=NULL;
				bn->right=NULL;
				h1=insert(bn,h1);
			}
			
		}
		h=mergeheap(h,h1); //recreating the heap from which d elements were deleted to create the necessary connections in the graph 
	}
	printf("\n+++ Graph generated...");
	flag=0; //now the flag serves as a tool to check correctness of the graph
	
	//checking validity of the graph generated
	for(i=0; i<n; i++)
	{
		int rowsum=0;
		for(j=0; j<n; j++)
		{
			rowsum+=graph[i][j];
		}
		if (rowsum!=deg[i]) flag-=1; //each rowsum should match the corresponding degree of each node
		
	}
	if(flag!=0)
	{
		printf("+++ Graph generated is invalid...");
		printf("flag=%d",flag);
	}
		else printf("\n+++ Correctness verified...\n");
	 
}
