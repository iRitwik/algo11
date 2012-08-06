/*
Important Note:: The file wordlist.txt should be present in the same directory as this program for it to work correctly!
 Name- Ritwik Yadav
 Roll Number- 10CS30034
 Assignment 3- Dictionary
 */
//importing necessary header files
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include <string.h>
//defining the tree node
typedef struct _treenode 
{
  char *word; //stores the word
  struct _treenode *left; //stores the left child
  struct _treenode *right; //stores the right child
  struct _treenode *parent; //stores the parent pointer
  int balancefactor; //stores the balance factor
} AVLtreenode;

typedef AVLtreenode* AVLtree; //stores the root of the AVLtree

typedef AVLtree* dictionary; //The AVL Forest

int calcht(AVLtree a)
{
  //this function calculates and returns the height of the AVLtree whose root node is a
  if(a==NULL) return -1;
  else if (a->balancefactor>=0)
    return 1+calcht(a->right);
  else return 1+calcht(a->left);
}

void rotcl(dictionary d, AVLtree node, int l)
{
  //this function causes a clockwise rotation at the node
  AVLtree node_l, node_p;
  node_l=node->left; //stores the left node 
  node_p=node->parent; //stores the parent of the node
  //making the necessary pointer adjustments
  if(node_l->right!=NULL)
    {
      node->left=node_l->right;
      node->left->parent=node;
    }
  else
    node->left=NULL;

  node_l->right=node;
  node->parent=node_l;

  node_l->parent=node_p;
  if(node_p!=NULL)
    {
      if(strncmp(node_p->word,node->word,l)>0)
	node_p->left=node_l;
      else
	node_p->right=node_l;
    }
  else d[l-2]=node_l;
  //updating balance factors of the node
  node->balancefactor=calcht(node->right)-calcht(node->left);
  node_l->balancefactor=calcht(node_l->right)-calcht(node_l->left);

}

void rotanticl(dictionary d, AVLtree node, int l)
{
  //this function causes an anti-clockwise rotation at the node
  AVLtree node_r, node_p;
  node_r=node->right; //stores the right node
  node_p=node->parent; //stores the parent of the node
  //making the necessarhy pointer adjustments
  if(node_r->left!=NULL)
    {
      node->right=node_r->left;
      node->right->parent=node;
    }
  else
    node->right=NULL;

  node_r->left=node;
  node->parent=node_r;

  node_r->parent=node_p;
  if(node_p!=NULL)
    {
      if(strncmp(node_p->word,node->word,l)>0)
	node_p->left=node_r;
      else
	node_p->right=node_r;
    }
  else d[l-2]=node_r;
  //updating the balance factors of the node
  node->balancefactor=calcht(node->right)-calcht(node->left);
  node_r->balancefactor=calcht(node_r->right)-calcht(node_r->left);
}

void balme(dictionary d, AVLtree node, int l)
{
  //this function adjusts the balance factor after the node  
  //has been inserted in the AVLtree
  AVLtree par;
  if (node->balancefactor==0) return;
  //if the balance factor changes to 0 from +1 or -1 the change is absorbed 
  else
    {
      if (node->parent!=NULL)
	{
	  while(node->parent!=NULL)
	    {
	      par=node->parent;
	      int i=strncmp(par->word,node->word,l);
	      if(i>0)
		(par->balancefactor)+=-1;
	      else
		(par->balancefactor)+=1;
	      if(par->balancefactor==0) return; //if the balance factor changes to 0 from +1 or -1 the change is absorbed 
	      else if(abs(par->balancefactor)==1) node=par;
	      //if the balance factor changes to +1 or -1, we go to the parent
	      else if(par->balancefactor==2)
		{
		  if(node->balancefactor==1)
		    {
		      //same sign, only one rotation required
		      rotanticl(d, par,l);
		      return;
		    }
		  else
		    {
		      //opposite sign, double roation carried out
		      rotcl(d, node,l);
		      rotanticl(d, par,l);
		      return;
		    }
		}
	      else if(par->balancefactor==-2)
		{
		  if(node->balancefactor==-1)
		    {
		      //same sign, one rotation required
		      rotcl(d, par,l);
		      return;
		    }
		  else
		    {
		      //opposite sign, double rotation required
		      rotanticl(d,node,l);
		      rotcl(d,par,l);
		      return;
		    }
		}
	    }

	}
    }
}

dictionary insert(dictionary d, AVLtree node, int length)
{
  //this function causes insertion in the AVLtree
  int compare; //this variable stores the comparison results of string
  int flag=0; //this variable serves an indication where the insertion has taken place
  char *str1=(char*)malloc(length*sizeof(char));
  char *str2=(char*)malloc(length*sizeof(char));
  str2=strcpy(str2, node->word);
  AVLtree nodin,trav;
  if (length>=2 && length<=8)
    {
      trav=(nodin=d[length-2]); //choosing the correct tree for insertion
      
      if(nodin==NULL)
	{
	  d[length-2]=node; //insering if the tree is empty
	  return d;
	}
       
       while(trav!=NULL)
	{
	  str1=strcpy(str1, trav->word);
	  compare=strncmp(str1,str2,length);
	  //updating the trav pointer and the flag variable
	  if (compare==0)
	    {
	      flag=0;
	      break;
	    }
	  else if(compare>0) 
	    {
	      nodin=trav;
	      trav=trav->left;
	      flag=-1;
	    }
	  else
	    {
	      nodin=trav;
	      trav=trav->right;
	      flag=1;
	    }
	}

       //inserting the new node at its correct position
       //followed by a balancing the tree      
     if(flag==-1)
	{
	  nodin->left=node;
	  node->parent=nodin;
	  (nodin->balancefactor)+=flag;
	  balme(d, nodin, length);
	}
      else if (flag==1)
	{
	  nodin->right=node;
	  node->parent=nodin;
	  (nodin->balancefactor)+=flag;
	  balme(d, nodin, length);
	}
      else if(flag==0)
	{ 
	  //  printf("\nWord already present in the tree!\n");
	}
    }
  else
    {
      printf("\nError: The length of a Funglish word should be between 2 to 8 (limits inclusive)!\n");
    }
  return d;
}

int isVowel(char ch)
{
  //this function give a positive value if the character input is a vowel
  if(ch=='A' || ch=='E' || ch=='I' || ch=='O' || ch=='U')
    return 1;
  else return -1;
}

int search(dictionary d, char* ch)
{
  //this function seraches for a given word in the dictionary 
  int compare; //stores comparison results of a string
  int flag=-1; //stores the search result
  AVLtree a;
  int length=(int)strlen(ch);
  a=d[length-2];
  while(a!=NULL)
    {
      compare=strncmp(a->word, ch, length);
      if(compare==0)
	{
	  flag=1;
	  break;
	}
      else if (compare>0)
	a=a->left;
      else 
	a=a->right;
    }
  return flag;
}

void generate(char* rand_lett, dictionary d)
{
  //this function generates a random word of random length
  int i,j,k,p; //loop variables
  char prev, next; 
  int prob; //the probability variable
 
  int length=2+(rand()%7); //the length of the string generated
  //int length=7;
  char* ch=(char*)malloc(sizeof(char)*length);
  
    for(i=0; i<length; i++)
    {
      if(i!=0) 
	{
	  prev=ch[i-1]; //storing the previous character
	  prob=rand()%10;
	  next=rand_lett[rand()%100]; //choosing a random element from the array
	  //only if prob is 0, can two consonants and vowels may occur together which has 10% probability
	  while(isVowel(prev)*isVowel(next)*prob>0)
	    next=rand_lett[rand()%100]; //generating the next character
	  ch[i]=next; //storing the next character
	}
      else
	ch[i]=rand_lett[rand()%100];
     }
  
  //ch=strcpy(ch, "ELDIRIT");
  printf("\nSearching for word \"%s\"\t: ",ch);
  if(search(d, ch)==1) printf("Found\n");
  else 
    {
      printf("Not Found\n");
      printf("Spell Check Suggestions:\n");
      //Generating Spell Check Suggestions
    
      //Group 1-Delete one letter
      printf("Group 1:");
      for(i=0; i<length; i++)
	{
	  p=0;
	  char *sug=(char*)malloc((length-1)*sizeof(char));
	  for(j=0; j<length; j++)
	    if(i!=j) sug[p++]=ch[j];
	  if(search(d, sug)==1)
	  printf("%s ",sug);
	  
	}

      //Group 2-Add one letter
      printf("\nGroup 2:");
      for(i=0; i<=length; i++)
	{
	  for(k=0; k<26; k++)
	    {
	      p=0;
	      char addit=(char)(65+k);
	      char *sug=(char*)malloc((length+1)*sizeof(char));
	      sug[i]=addit;
	      for(j=0; j<length; j++)
		{
		  if(p!=i) 
		    sug[p++]=ch[j];
		  else 
		    {
		      p++;
		      sug[p++]=ch[j];
		    }
		}
	      if(search(d, sug)==1)
		printf("%s ", sug);
	    }
	}


      //Group 3-Change a letter
      printf("\nGroup 3:");
      for(i=0; i<length; i++)
	{
	  for(j=0; j<26; j++)
	    {
	      p=0;
	      char addit=(char)(65+j);
	      char *sug=(char*)malloc(length*sizeof(char));
	      sug[i]=addit;
	      for(k=0; k<length; k++)
		if(i!=k) sug[k]=ch[k];
	      if(search(d, sug)==1)
		printf("%s ", sug);
	    }
	}

      
      //Group 4-Swap any two
      printf("\nGroup 4:");
      char *c=(char*)malloc(length*sizeof(char));
      c=strcpy(c, ch);
      for(i=0; i<length; i++)
	{
	  for(j=i; j<length; j++)
	    {
	      char c1=c[i];
	      c[i]=c[j];
	      c[j]=c1;
	      if(search(d, c)==1)
		printf("%s ", c);
	      c=strcpy(c, ch);
	    }
	}
      printf("\n");


    }
  
}
void destroy_tree(AVLtree a)
{
  if(a==NULL) return;
  else 
    {
      destroy_tree(a->left); //recursively destroying the left subtree
      destroy_tree(a->right); //recursively destroying the right subtree
      free(a->word); //freeing space allocated for the word stored
      free(a); //freeing space for the node
      return;
    }
}
void destroy(dictionary d)
{
  int i=0;
  AVLtree a;
  for(i=0; i<=6; i++)
    {
      a=d[i];
      destroy_tree(a); //destroying each single tree in the forest
    }
  free(d);
} 

int main()
{
  srand((unsigned int) time(NULL)); //seeding the random number generator
  FILE *if1; //the file pointer
  int i,j,p;
  if1=fopen("wordlist.txt", "r"); //initializing the file pointer
  //if1=fopen("wordlist-sorted-nodup.txt", "r");
  
  dictionary d1; //creating the dictionary
  d1=(dictionary)malloc(7*sizeof(AVLtree)); //initialising the dictionary
  char* ch=(char*)malloc(8*sizeof(char));
  
  while(!feof(if1))
    {
      //reading file till end of file is encountered
      fscanf(if1,"%s",ch); //reading a word
      int length=(int)strlen(ch);
      //creating a node
      AVLtree add=(AVLtree)malloc(sizeof(AVLtreenode));
      add->word=(char*)malloc(sizeof(char)*length);
      add->word=strcpy((add->word),ch);
      add->left=(add->right=(add->parent=NULL));
      d1=insert(d1, add, length); //inserting the word in the appropriate tree
      // printf("%s\n", add->word);
    }
  for(i=0; i<=6; i++)
    printf("Height of D[%d] = %d\n",(i+2),calcht(d1[i])); //displaying the heights of the tree
  
  //generating an array of characters
  //each characters frequency is dependent on the probability of its occurence
  int freq[26]={9,2,2,6,11,4,3,2,9,1,1,4,2,4,8,2,1,6,5,6,4,2,2,1,2,1};
  char rand_letter[100];
  p=0;
  for(i=0; i<26; i++)
    {
      for(j=0; j<freq[i]; j++)
	{
	  rand_letter[p++]=(char)(65+i);
	}
    }
  for(i=0; i<8; i++)
    generate(rand_letter, d1); //generating 8 random words and displaying spell check suggestions
  destroy(d1); //destroying the dictionary
}
