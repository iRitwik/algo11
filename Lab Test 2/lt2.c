/*
Algorithms I
Lab Test 2: Graphs, Trees and Heaps
Name:Ritwik Yadav
Roll Number: 10CS30034
PC Number: 43
 */
//including the necessary libraries
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
static int flag=0; //this varaible keeps track if the search is successful
//for the key to be searched.

/* 
This function takes the array A, the number of elements n and 
the key to be searched as input. It then returns the number of 
elements that are either less than or equal to the key.
The binary search technique(log n) is applied but instead 
of reporting the first ever occurence of the key we can lay our 
hands upon, we make a search again in the latter part of the array
to ensure we find the last occurence of the key in the array. 
If the search fails, we return the last index(l) of the subarray 
we were searching in. This ensures we get the last possible 
occurence of x, if any. 
 */
int binsearch(int A[], int n, int x)
{
  int f=0;
  int l=n-1;
  int m;
  while(f<=l)
    {
      int m=(f+l)/2;
      if (A[m]<x)
	f=m+1;
      else if (A[m]>x)
	l=m-1;
      else
	{
	  flag=1; //updating flag to indicate that the search
	  //was successful
	  f=m+1;
  
	}
    }
 
  return (l+1);

}

int main()
{
  srand((unsigned int)time(NULL)); //seeding the random number geerator
  int i; //loop variable
  int n; //stores the number of elements in the array
  int x; //stores the key to be searched for
  int occur; //stores the occurences of the key
  int *A; //random sorted array of integers
  double p1, p2; //probability deciding variables
  int n1, n2, n3, n4; 
  printf("n=");
  scanf("%d", &n);
  printf("\n");
  A=(int*)malloc(n*sizeof(int)); //dynamically allocating memory for the array
  // A[0]=rand()%(RAND_MAX-2);
  A[0]=rand()%11; //generating the value of A[0]

  printf("%d\t", A[0]);
  //generating the rest of the array elements and printing them
  for(i=1; i<n; i++)
    {
      p1=1.0*rand()/RAND_MAX;
      if(p1<=0.5)
	A[i]=A[i-1];
      else
	{
	 p2=1.0*rand()/RAND_MAX;
	 if(p2<=(1.0/3.0))
	   A[i]=A[i-1]+1;
	 else if(p2<=(2.0/3.0))
	   A[i]=A[i-1]+2;
	 else
	   A[i]=A[i-1]+3;
	}
      printf("%d\t", A[i]);
    }
  printf("\n");
  printf("x="); //reaing the key to be searched for
  scanf("%d", &x);
  
  /*
We calculate the occurences by calculating the occurences of key by
calculating the number of elements less than or equal to 
the immediate predecessor and substracting.
   */
  n1=binsearch(A, n, x); 
  if(flag==1)
    {
      n2=binsearch(A, n, x-1)-n1;
      
      n3=binsearch(A, n, x-2)-n1;
      n4=binsearch(A, n, x-3)-n1;
      if (n2!=0) occur=-n2;
      else if (n3!=0) occur=-n3;
      else occur=-n4;
    }
  else occur=0;
  printf("Number of elements less than or equal to %d is %d\n", x, n1);
  printf("Number of occurences of %d is %d\n", x, occur);
}


