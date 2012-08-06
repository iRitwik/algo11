/*
Lab Test 1 Program
-------------------
Name: Ritwik Yadav
Roll Number: 10CS30034
PC Number: 61(Odd)
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//defining a node of the binary tree
typedef struct _node
{
  int id; //stores id
  struct _node *l,*r; //stores pointers to left and right child respectively
}Node;

static int lmax=0; //statically maintaining the maximum level at which a leaf occurs

// This function creates the binary tree and returns a pointer to the root of the tree.

Node* createBtree()
{
  int i; //loop variable
  int n; //n stores the number of nodes in tree
  int *rt; //rt is a 1D array used to detect the root of the binary tree during its creation
  scanf("%d",&n);

  Node *arr, *root; 
  //arr is an array of nodes which occur in the binary tree
  arr=(Node*)malloc(n*sizeof(Node));
  rt=(int*)malloc(n*sizeof(int));
  for(i=0; i<n; i++)
    {
      
      rt[i]+=i; //storing the respective id's
      scanf("%d",&(arr[i].id));
      int l,r; //l and r store the id's of the left ad the right child respectively
      scanf("%d",&l); 
      scanf("%d",&r);
  
      //creating appropriate pointer realtions
      /* To detect the root the following method is used. An array is maintained which stores the id of all the nodes which occur in the binaryh tree. The root is not the child of any of the other nodes which occur in tree. Therefore, whenever an id is listed as a child of particular node, its id is subtracted from itself. Hence, all such nodes which are children of some node in the binary tree have zero stored against them in the array rt except for the root.
       */
      if(l!=-1)
	{	
	  arr[i].l=arr+l;
	  if(l!=0)
	    rt[l]-=l;
	  else
	    rt[l]=-1;
	}
      else 
	arr[i].l=NULL;
      if(r!=-1)
	{	
	  arr[i].r=arr+r;
	  if(r!=0)
	    rt[r]-=r;
	  else 
	    rt[0]=-1;
	}
      else 
	arr[i].r=NULL;
    }

  for(i=0; i<n; i++)
    {
      if(rt[i]==i) break; //detecting where the root occurs
    }
   root=arr+i;
   printf("Id of root = %d\n",root->id);
   return root;

}

//The finLeaf function takes a node and recursively checks the left and right subtree for leaves.
//It also keeps a track of the level at which a particular leaf occurs.
void findLeaf(Node *node, int level)
{
  Node *L,*R;
  L=node->l; //stores the left subtree
  R=node->r; //stores the right subtree
  if(L==NULL && R==NULL)
    {
      printf("%d\t", node->id); //printing the id of the node that that has no children
      lmax=(lmax>level)?lmax:level; //updating the maximum level at which a leaf occurs
    }
  if(L!=NULL)
    findLeaf(L, level+1); //scanning the left subtree for leaves
  if(R!=NULL)
    findLeaf(R, level+1); //scanning the right subtree for leaves
}

void printMaxLeaves(Node *node, int level, int max_level)
{
  Node *L,*R;
  L=node->l; //stores the left subtree
  R=node->r; //stores the right subtree
  if(L==NULL && R==NULL)
    {
      if(level==max_level) //if the leaf occurs at maximum level, printing it
	printf("%d\t", node->id);
    
    }
  if(L!=NULL)
    printMaxLeaves(L, level+1, max_level);
  if(R!=NULL)
    printMaxLeaves(R, level+1, max_level);
}



int main()
{
  Node *root=createBtree();
  printf("Leaves in the tree are\n");
  findLeaf(root, 0);
  printf("\n");
  printf("Maximum level of a leaf in T is %d\n", lmax);
  printf("Leaves at maximum level are ");
  printMaxLeaves(root, 0, lmax);
  printf("\n");
}
