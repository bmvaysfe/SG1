/*
    07.12.12
    List.c
    Sorted single linked list.
*/    


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>


int max_alias_size = 0;

struct Node {
/*    char data[10];    */
    int data;  /* For testing only */
    struct Node *next;
};
typedef struct Node Node;    

Node* getNode(void)
{
    Node *p = (Node *)malloc(sizeof(Node));
    if(!p) {
        puts("Allocation failed\n");
    }        
    memset(p, 0, sizeof(Node));
    p->next = NULL;
    return p;
}    

/* Insert data in sorted order */

/* TO DO: Insert into alphabetically sorted list */
void insert(Node **head, int data)  
{
    Node *np = NULL;
	Node *q = NULL;
    Node *p = *head;
    
    puts("In insert()!\n");
    
    /* Create new node and fill info */
    np = getNode();  
    np->data = data;
    
    /* Use strcpy() to handle char strings 
       instead of < operator in data comparison. */
    while(p && ( p->data< data)) {            
                q = p;
                p = p->next;
    }                
    
    if(q) { /* insert after q */
            np->next = q->next;
            q->next = np;
    }                
    else {  /* 1st node, insert front */
            /* insert in front of p /*/
        np->next = *head;
        *head = np;
    }
    
}    



void print_list(Node **head)
{
    Node *p = *head;
    puts("In print_list()!");
    while(p) {
/*        puts(p->data);    */ /* for char[10] data only */
        printf("%d\t", p->data);
        p = p->next;
    }
}        



void print_recursively(Node *n)
{
        if(n) {
            printf("%d ", n->data);
            print_recursively(n->next);            
        }
}


/* Print list in reverse order */
void print_reverse(Node *n)        
{
        if(n) {
            print_reverse(n->next);
            printf("%d ", n->data);
        }
}


    
void clean_up(Node ** head)
{
    Node *p = *head;
    Node *q = *head;
    if(!*head) return; /* List is empty already */
    
    while(p) {
        q = p;
        p = p->next;
        free(q);
        q = NULL;
    }        
    *head=NULL;
}

/*
Recursive Method:

   1) Divide the list in two parts - first node and rest of the linked list.
   2) Call reverse for the rest of the linked list.
   3) Link rest to first.
   4) Fix head pointer
   
   Time Complexity: O(n)
	Space Complexity: O(1)
*/

void recursiveReverse(Node** head_ref)
{
    Node* first;
    Node* rest;
      
    /* empty list */
    if (*head_ref == NULL)
       return;   
 
    /* suppose first = {1, 2, 3}, rest = {2, 3} */
    first = *head_ref;  
    rest  = first->next;
 
    /* List has only one node */
    if (rest == NULL)
       return;   
 
    /* reverse the rest list and put the first element at the end */
    recursiveReverse(&rest);
    first->next->next  = first;  

    /* tricky step -- see the diagram */
    first->next  = NULL;          
 
    /* fix the head pointer */
    *head_ref = rest;              
}

    
#define NUM_TEST_CASES 20

int countNodes(Node **head)
{
    int count=0;
    Node *p=*head;
    
    while(p) {
        ++count;
        p=p->next;
    }
    return count;
}            

int countNodes_Recursively(Node *n)
{
    if(!n) return 0;
    return 1+countNodes_Recursively(n->next);
}    



/* In-place list reverse */
void reverse(Node **head)
{
    Node *temp1=*head;
    Node *temp2=NULL;
    Node *temp3=NULL;
    
    while(temp1) {
        *head=temp1;
        temp2=temp1->next;
        temp1->next=temp3;
        temp3=temp1;
        temp1=temp2;
    }        
}

/* Get middle node of the list  */
Node * getMiddle(Node **head)
{
    Node *p1=*head;
    Node *p2=*head;
    if(!*head) {
        puts("The list is empty!");
		return NULL;
    }
    
    
    
    while(p2)
    {
        p1=p1->next;
        p2=p2->next;
        if(!p2) break;
        else p2=p2->next;  
//      if(p2) p2=p2->next;  // 05.06.10, more elegant than 2 lines above.
    }        
    return p1;
}    
    
    
Node * getMthFromRear(Node **head, int m)
{
    Node *current=*head;
	Node *Mth=current;

	int i;
    if(!*head) {
     		puts("The list is empty!");
			return NULL;
  	} 			 
  		
    if(m<=0) {
		 printf("m = %d\n", m);
		 return NULL;
  	} 			            

	
			
	for(i=0; i<m && current; i++) {
			 current=current->next;
	}

    if(!current) return NULL;
                  
	while(current) {
	   current=current->next;
	   Mth=Mth->next;
    }
    return Mth;                
}        
    
    
void deleteMthFromRear(Node **head, int m)
{
    Node *q = *head;
    Node *c=*head;
    Node *p = NULL;
    
    if(!*head || m<=0) return;
    
    p = getMthFromRear(head, m);
    if(!p) return;
    
    
    while(c!=p) {
        q=c;
        c=c->next;
    }        
    
    q->next=p->next;
    if(p==*head) *head=p->next;
    
    free(p);
    p=NULL;
}        
    
int main(int argc, char**argv)
{
    Node *list_head=NULL;
    Node *pHead = list_head;
#if 0
    char *data[NUM_TEST_CASES] = { "Alex, Vova, Bill, Core, Janet"};
#endif     
    int data[] = {5, 3
					/*	, 1, 0, -2, 
                  -10, 260, 2140, -9430, 8718,				  
                  2020, 131, -8718, -10000, 12345, 
                  2222 , 75131, 67700, -260, 8448	
                  */
    
    };
    int i=0;
    
    puts("Start!\n");
    printf("List now has %d nodes.\n", countNodes(&list_head));
    printf("List now has %d nodes.\n", countNodes_Recursively(pHead));
    
    /* 1. Insert data */
    for(i=0; i < sizeof(data)/sizeof(data[0]); i++)
    {
        insert(&list_head, data[i]);
    }
    puts("Done with insert()!\n");
    
    /* 2. Print sorted data */
    pHead=list_head;
    print_list(&list_head);
    pHead=list_head;
    
    puts("\n\nRecursive printing");        
    print_recursively(pHead);
    
    puts("\n\nReverse Printing");
    pHead=list_head;
    print_reverse(pHead);
    puts("\nDone with print()!\n");
    
    printf("Before clean_up(): list has %d nodes.\n", countNodes(&list_head));
    pHead=list_head;
    printf("Before clean_up(): list has %d nodes.\n", countNodes_Recursively(pHead));
    
    /* 3. Reverse list in place and print it. */
    puts("\nList is reversed now:");
//    reverse(&list_head);
	recursiveReverse(&list_head);
    pHead=list_head;
    print_recursively(pHead);
    
    /* 4. Clean up */
    clean_up(&list_head);
    puts("\n\nDone with clean()!\n");
    
    printf("List now has %d nodes.\n", countNodes(&list_head));
    pHead=list_head;
    printf("List now has %d nodes.\n", countNodes_Recursively(pHead));
    return 0;
}
