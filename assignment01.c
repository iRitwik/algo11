/*
Assignment 1
----------------
Problem Statement: To obtain the solution of -Travelling Salesman Problem- using exact method (generating all permutations), divide and conquer method,
Greedy method and Bellman-Held-Karp Dynamic Programming Algorithms.

Developed By-
Name: Ritwik Yadav
Roll Number: 10CS30034

Note: To measure the actual time taken by each of the algorithms, certain statements at the end of each definition maybe uncommented.
The Divide and Conquer Algorithm may work better than what is mentioned in the instructions for this assignment since both clockwise and counter-clockwise loops for the latter loop are considered. 
*/

//Importing Necessary Libraries
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

//Defining a structure datatype to store the x and y co-ordinates of a city.
typedef struct
{
	int x;
	int y;
} City;

//These static variables are used in the exact algorithm, which recursively generates permutations.
//To avoid declaration and allocation at each recursive call, they are statically maintained.
static int** Paths; //This 2D array stores all the possible permutations of the cities
static int* Ex_Cost; //This array stores the exact cost corresponding to each path stored in Paths
static int st_k=0; 

//This function swaps the values stored in the respective variables.
void swap (int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

//This function uses quick sort algorithm to sort the array of City structures in increasing order of their x-coordinate.
void sort_qu(City* Cities, int n)
{
	int i,j,r;
	//Sorting the cities with respect to x coordinates
	int k=0; //stores the index till where the array has been sorted.
	for(i=k+1; i<n; i++)
	  {
		int ele=Cities[i].x;
		int ele1=Cities[i].y;
		for(j=0; j<=k; j++)
		{
			if(ele<Cities[j].x)
				break;
		}
		for(r=k; r>=j; r--)
		{
			Cities[r+1].x=Cities[r].x;
			Cities[r+1].y=Cities[r].y;
		}
		Cities[j].x=ele;
		Cities[j].y=ele1;
		k++;
	  }
}

//The permute() function recursively generates all possible permutations of the order in which the cities can be visited.
void permute(int** table, int *a, int i, int n)
{
	int j;
	
	if (i == n)
	{
		
		//Code for Displaying all possible paths
		for(j=0; j<=n;j++)
		{
		  Paths[st_k][j]=a[j]; //storing the path in the Paths array
		}
		
		for(j=0; j<n;j++)
		{
			Ex_Cost[st_k]+=table[a[j]][a[j+1]];
		}
		Ex_Cost[st_k]+=table[a[n]][a[0]]; //storing the cost incurred corresponding to the path generated in the Ex_Cost array.
		st_k++;  
	}
	else
	{
	  //recursively generating the permutations.
	  /* 
	     This algorithm acts on the basis of the following procedure:
	     It chooses a first element out of the given possibilities. 
	     It recursively generates the permutations of the remaining elements after the first element has been set.
	  */
	 
        for (j = i; j <= n; j++)
		{
			swap((a+i), (a+j));
			permute(table, a, i+1, n);
			swap((a+i), (a+j)); //This statement generates the array which was changed before.
		}
	}
}


// The following function dnctsp() uses the Divide and Conquer Algorithm for solving the Travelling Salesman Problem.
void dnctsp(int* order, int i, int j, int **dist)
{
  int min=6000; //The minimum variable has been set to a safe upper value which cannot be attained even in the most favorable trade-off that occurs in this algorithm.
  int l,n,fl1,fl2,fl3,fl4; //l and n are used as loop variables. fl1, fl2, fl3 and fl4 are used as flag variables to store where the two separate paths are to be joined.

  if ((j-i)==1 || (j-i)==2) //If the total number of cities is 2 or 3, nothing needs to be done as only one path exists through 3 or lesser cities.
		return;
	else
	  {
	    int m=(i+j)/2; // m is computed to divide the cities into roughly two equal halves
	    dnctsp(order, i, m, dist); //the dnctsp is called on the first half of the cities.
	    dnctsp(order, m+1, j, dist); //the dnctsp is called on the second half of the cities.

	    //After getting two loops. The best possible trade-of is considered for joining the two loops into one.
	    for(l=i; l<=m; l++)
		{
			for(n=m+1; n<=j; n++)
			{
				int a,b,c,d,e;
				a=l;
				b=l+1;
				c=n;
				d=n+1;

				//Maintaining the circular nature of the loop.
				if(l==m) b=i;
				if(n==j) d=m+1;
				
				//Checking whether joining 'a to c' & 'b to d' would be a better trade-of or joining 'a to d' & 'b to c'.
				if((dist[order[a]][order[d]]+dist[order[b]][order[c]])<(dist[order[a]][order[c]]+dist[order[b]][order[d]]))
				{
					//If joining 'a to d' & 'b to c' is a better trade-off, switching values c and d.
				       //This switch is done to avoid any other confusions. After this switch, it is certain that a will be joined to c and 'b to d'.
					int dum=c;
					c=d;
					d=dum;
				}
				e=-dist[order[a]][order[b]]-dist[order[c]][order[d]]+(dist[order[a]][order[c]]+dist[order[b]][order[d]]); //computing the trade-off
				//printf("\n e=%d \n",e);
				if(e<min)
				{
				  //Computing the minimum trade-off possible and storing the corresponding indexes in the flag variables.
					min=e;
					fl1=a;
					fl2=b;
					fl3=c;
					fl4=d;
				}
			}
		}
		
		//Shifting the first half of the array to the right until 'fl1' (corresponding to 'a') acquires the mid position.
		if(fl1!=m)
		{
			for(l=1; l<=(m-fl1); l++)
			{
				int dum=order[m];
				for(n=m; n>i; n--)
				{
					order[n]=order[n-1];
				}
				order[i]=dum;
			}
		}
		
		//Similarly, shifting the latter part of the array until 'fl3' (corresponding to 'c') acquires the post-mid position without changing the order of the cities.
		if(fl3!=(m+1))
		{
			int limit=(fl3>fl4)?(fl3-m-1):(fl3-m);
			for(l=1; l<=limit; l++)
			{
				int dum=order[m+1];
				for(n=m+1; n<j; n++)
				{
					order[n]=order[n+1];
				}
				order[j]=dum;
			}
			//If 'fl4' (corresponding to 'd') is greater than 'fl3' one more shif to the left is executed and the order is reversed before joining.
			if(fl3<fl4)
			{
				for(n=m+1; n<=((m+j+1)/2); n++)
				{
					swap(&order[n],&order[j-n+m+1]);
				}
			}
			
			
		}
		
    }//end of else
} 
 
//The following function greedy() implements the greedy algorithm to solve the travelling salesman problem.
void greedy(int** table, int *a, int n)
{
	int i,j,k;
	k=0;  // k represents the index till which the cities have been incorporated in the loop
	
	//u,v stores the edge where the new city w has to be incorporated. 'mincost' sotres the cost incurred when city 'w' is inducted in the loop by breaking the edge u-v.  
	int u,v,w,cost,u1,v1,w1, mincost;
	while(k!=n)
	{
		mincost=6000;  //The minimum variable has been set to a safe upper value which cannot be attained even in the most favorable trade-off that occurs in this algorithm.
		for(i=0; i<=k; i++)
		{
			for(j=k+1; j<=n; j++)
			{
				u1=i; 
				v1=(i==k)?0:i+1; //maintaining the circular nature of the loop 
				w1=j;
				cost=-table[a[u1]][a[v1]]+table[a[u1]][a[w1]]+table[a[w1]][a[v1]]; //computing the trade-off for this particular induction
				
				//Computing the minimum cost incurred for induction of one of the remaining cities.
				if(cost<mincost)
				{
					mincost=cost;
					u=u1;
					v=v1;
					w=w1;
				}
			}
		}

		//if the city to be inducted at the last position, only a swap is required
		if(v==0)
		{
			int dum=a[k+1];
			a[k+1]=a[w];
			a[w]=dum;
			k++;
		}
		//otherwise the elements are shifted before adding that city to its correct position.
		else 
		{
			int dum=a[k+1];
			a[k+1]=a[w];
			a[w]=dum;
			dum=a[k+1];
			for(i=k; i>=v; i--)
			  a[i+1]=a[i]; //shifting elements
			a[v]=dum;
			k++;
		}
		
	}		
}



int main()
{
        
        clock_t t1, t2;    /* Time variables */
        float timeTaken;   /* Total time taken */

	int i,j,k; //loop variables
	int n; //number of cities
	int **dist_tab; //stores the distance table between cities
	//and since the cost is directly proportional to the distance, we can use total distance as a qualitative measurement for cost.
	
	//Inputting from the User
	printf("\nEnter the number of cities=");
	scanf("%d", &n);
	
	City* arr_Cities=(City*)malloc(n*sizeof(City)); //creating an array of cities
	
	dist_tab=(int**)malloc(n*sizeof(int*)); //allocating space for distance table
	for(i=0; i<n; i++)
	  {
		dist_tab[i]=(int*)malloc(n*sizeof(int));
	  }
	srand((unsigned int) time(NULL)); //seeding the random number generator with a time function
	
	//Generating Cities
	printf("\nCity List::\n");
	for(i=0; i<n; i++)
	  {
             /*	
		//This region if uncommented can be used to input city data without using random number generation
		printf("\n Enter X and Y \n");
		scanf("%d",&arr_Cities[i].x);
		scanf("%d",&arr_Cities[i].y);
             */
		arr_Cities[i].x=(int)rand()%1000;
		arr_Cities[i].y=(int)rand()%1000;
		//printf("(%d,%d) ", arr_Cities[i].x, arr_Cities[i].y);
	  }
	
	//Sorting the cities
	sort_qu(arr_Cities, n);
	printf("\n");

	  for(i=0; i<n; i++)
	  {
	    printf("(%d,%d) ", arr_Cities[i].x, arr_Cities[i].y); //printing the sorted city list
	  }
	
	//Generating Distance Table
	//printf("\nDistance Table::\n");
	  for(i=0; i<n; i++)
	  {
		for(j=0; j<n; j++)
		{
			dist_tab[i][j]=sqrt(pow((arr_Cities[i].x-arr_Cities[j].x),2)+pow((arr_Cities[i].y-arr_Cities[j].y),2));
			//printf("%d\t\t", dist_tab[i][j]);
		}
		      //printf("\n");
	  }
	
	
	//The Exact Solution
	t1 = clock();
	printf("\nExact TSP:\n");
	int fact=1;
	//total number of permutations will be (n-1)!
	for(i=1; i<n; i++)
		fact*=i;
	Ex_Cost=(int*)malloc(fact*sizeof(int)); //stores the cost of each path
	
	Paths=(int**)malloc(fact*sizeof(int*)); //stores the path for each permutation
	for(i=0; i<fact; i++)
		Paths[i]=(int*)malloc(n*sizeof(int));
	
	//perms array is used to generate all possible paths 
	int *perms=(int*)malloc(n*sizeof(int));
	
	for(i=0; i<n; i++)
		perms[i]=i;
	permute(dist_tab, perms,1,n-1);
	
	int min=Ex_Cost[i],flag=0;
	//printf("Cost tab:");
	for(i=0; i<fact; i++)
        {
	  //printf("%d,",Ex_Cost[i]);
		if (min>Ex_Cost[i])
		{
		  min=Ex_Cost[i]; //computing the minimum possible cost
			flag=i;
		}
       }
	//	printf("Cost tab:\n");
	for(i=0; i<n; i++)
	  {
	    printf("%d-",Paths[flag][i]); //displaying the path with the minimum cost
	  }
	printf("Minimum Cost=%d\n", min);
	
	t2 = clock();     /* Record the time after the block exits */

	/* Compute the time taken per execution of the block */
	timeTaken = ( (float)(t2 - t1) / (float)CLOCKS_PER_SEC);
	//	printf("Time taken = %f seconds\n", timeTaken);

	
	//DNC Approach
	t1 = clock();
	printf("Divide and Conquer:\n");
	int dnccost=0;
	//regenerating perms array
	for(i=0; i<n; i++)
		perms[i]=i;
	dnctsp(perms,0,n-1,dist_tab);
	  for(i=0; i<n; i++)
	  {
	    printf("%d-",perms[i]); //displaying the path attained by divide and conquer technique
		if(i!=(n-1))
		  dnccost+=dist_tab[perms[i]][perms[i+1]]; //computing the cost of that path
	  }
	dnccost+=dist_tab[perms[n-1]][perms[0]];
	printf("Cost=%d\n",dnccost);
	t2 = clock();     /* Record the time after the block exits */

	/* Compute the time taken per execution of the block */
	timeTaken = ( (float)(t2 - t1) / (float)CLOCKS_PER_SEC);
	//	printf("Time taken = %f seconds\n", timeTaken);	


	//The Greedy Algorithm
	t1 = clock();
	int gcost=0;
	printf("Greedy:\n");
	//regenerating perms array
	for(i=0; i<n; i++)
		perms[i]=i;
	greedy(dist_tab, perms, n-1);
	for(i=0; i<n; i++)
        {
		printf("%d-",perms[i]); //displaying the path attained by divide and conquer technique
		if(i!=(n-1))
			gcost+=dist_tab[perms[i]][perms[i+1]];  //computing the cost of that path
        }
	gcost+=dist_tab[perms[n-1]][perms[0]];
	printf("Cost=%d\n",gcost);
	t2 = clock();     /* Record the time after the block exits */

	/* Compute the time taken per execution of the block */
	timeTaken = ( (float)(t2 - t1) / (float)CLOCKS_PER_SEC);
	//	printf("Time taken = %f seconds\n", timeTaken);

	//The Dynamic Programming Approach.
	t1 = clock();
	printf("Dynamic Program TSP:\n");
	/*
	  Array B and L are 2D arrays of size [2^(n-1)] X [n-1]
	  The row index denotes the set X of the Bellman-Herd-Karp Dynamic Programming Algorithm
	  The start city is assumed to be 0. The tour is supposed to end on the (j+1) city. Here j is the column index.
	  The row number, if expressed in binary, denotes the cities which are included in the set X.
	  A zero indicates that the city is not present in set X and one indicates it is present.
	  The least significant bit represents City 1, the second least bit represents City 2 and so on.
	  Similarly, the most significant bit represents (n-1)th City.
	  B stores the minimum possible cost of travelling from 0 to (j+1)th city visiting each city in X once and back to 0.
	  L stores the previous city which was visited before travelling to the (j+1) city, thereby giving us a trail to the actual path taken. 
	 */
	int** B=(int**)malloc((int)pow(2,n-1)*sizeof(int*));
	int** L=(int**)malloc((int)pow(2,n-1)*sizeof(int*));
	for(i=0; i<(int)pow(2,n-1); i++)
	{
		B[i]=(int*)malloc((n-1)*sizeof(int));
		L[i]=(int*)malloc((n-1)*sizeof(int));
	}
	
	for(j=0; j<n-1; j++)
	{
	  B[0][j]=dist_tab[0][j+1]; //for the first row, the set X is empty
	  L[0][j]=0; //the previous visited city is 0 in such a case
	}
	for(i=0; i<(int)pow(2,n-1); i++)
	{
		for(j=0; j<n-1; j++)
		{
			
			if((i&(1<<j))!=0)
			{
			  B[i][j]=-1; //for invalid values of Set X, -1 is stored in the matrix
			  L[i][j]=-1; //by invalid, I mean set X such that it contains destination city bit set to 1
			}
		}
	}
	
	
	for(i=1; i<(int)pow(2,n-1); i++)
	{
		for(j=0; j<n-1; j++)
		{
			if(B[i][j]!=-1)
			{
				min=-1;
				for(k=0; k<n-1; k++)
				{
				  if(((1<<k)&i)!=0) //checking if the kth bit of i is one
					{
					  //if the kth bit is 1, we set it to zero and compute the minimum using the values in the previous rows.
						int remcost=B[i-(int)pow(2,k)][k]+dist_tab[k+1][j+1];
						if((min==-1) || (min>remcost))
						{
							min=remcost;
							L[i][j]=k+1; //once the minimum is obtained, the previously visited city is stored in matrix L
						}
					}
					
				}//end fr k
				B[i][j]=min;
				
			}//end if1
			
		}//end fr2
		
	}//end fr1
	
	/*
	 //Display
	 for(i=0; i<(int)pow(2,n-1); i++)
	 {
	 for(j=0; j<n-1; j++)
	 {
	 printf("%d\t\t", B[i][j]);
	 }
	 printf("\n");
	 }
	 printf("\n");
	 printf("\n");
	 for(i=0; i<(int)pow(2,n-1); i++)
	 {
	 for(j=0; j<n-1; j++)
	 {
	 printf("%d\t\t", L[i][j]);
	 }
	 printf("\n");
	 }
	 
	 //Display
	 */
	int leg_min=-1;
	min=-1;
	
	for(i=0; i<n-1; i++)
	{
		int mincost=B[(int)(pow(2,n-1)-pow(2,i))-1][i]+dist_tab[i+1][0];
		if((mincost<min) || (min==-1))
		{
		  min=mincost; //computing the overall minimum cost by setting each possible city as the last visited city
		  leg_min=i+1; //leg_min stores the city which was visited last for the minimum tour in question
		}
	}
	
	//printf("%d\n",leg_min);
	
	int set_min=(int)pow(2,n-1)-1-(int)pow(2,leg_min-1);
	printf("0-");
	while(leg_min!=0)
	{
		printf("%d-",leg_min);
		leg_min=L[set_min][leg_min-1]; //updating leg_min to keep track of the route taken to obtain the minimum.
		set_min-=(int)pow(2,leg_min-1);
	}
	printf("Minimum Cost=%d\n",min);
	
	t2 = clock();     /* Record the time after the block exits */

	/* Compute the time taken per execution of the block */
	timeTaken = ( (float)(t2 - t1) / (float)CLOCKS_PER_SEC);
	//	printf("Time taken = %f seconds\n", timeTaken);	
	
}
