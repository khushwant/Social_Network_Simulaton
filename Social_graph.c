#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include <stdbool.h>
#include<string.h>
struct Hnode
{
	char Username[20];
	char first_name[20];
	char last_name[20];
	struct Hnode *LINK;
	struct Node *ALINK;
};
struct Node
{
	int id;
	char requestee[20];
	bool accepted;
	struct Node *Next;	
};
typedef struct Hnode Hnode;
typedef struct Node Node;
int id=0;
Hnode *start, *LOC;
void init(Hnode** start)
{
	start=NULL;
}
Hnode* node_search(Hnode**start,char* item)
{
	Hnode* Temp;
	LOC=NULL;
	Temp=*start;
	while(Temp!=NULL){
		if(!strcmp(Temp->Username, item))
		{
			LOC=Temp;
			return LOC;
		}
		else
		Temp=Temp->LINK;
	}
	return LOC;
} 
Node* edge_search(char *src, char *dst){
	Node* Atemp;
	Hnode *LocSrc, *LocDst;
	LocSrc= node_search(&start, src);
	LocDst= node_search(&start, dst);
        Atemp= LocSrc->ALINK;
        if(LocSrc==NULL || LocDst==NULL)
        {
        	printf("\nUser not found\n");
            return NULL;
        }
        else
        {
            while(Atemp!=NULL)
            {
                if(!strcmp(Atemp->requestee, dst))
                {
                    return Atemp;
                }
                else
                {
                    Atemp= Atemp->Next;
                }
            }
        }
        return NULL;
}
void createUser(Hnode** start)
{
	Hnode *temp1, *temp2;
	temp1= (struct Hnode*)malloc(sizeof(struct Hnode));
	printf("\n Enter Details for creating user:\n");
	printf("\tUsername: ");
	scanf("%s",temp1->Username);
	printf("\n\tFirst name: ");
	scanf("%s",temp1->first_name);
	printf("\n\tLast name: ");
	scanf("%s",temp1->last_name);
	temp1->LINK= NULL;
	temp1->ALINK= NULL;
	if((*start)==NULL)
	{
		*start=temp1;
	}
	else
	{
		temp2= *start;
		while((temp2->LINK)!= NULL)
		{
			temp2=temp2->LINK;
		}
		temp2->LINK=temp1;
	}
}
void createFriendship(Hnode** start)
{
	Hnode *LocSrc, *LocDst;
	Node *temp1, *temp2;
	char src[20];
	temp1= (struct Node*)malloc(sizeof(struct Node));
	printf("\nEnter the info for friendship request:\n");
	printf("\tEnter Requester's username: ");
	scanf("%s",src);
	printf("\tEnter Requestee's username: ");
	scanf("%s",temp1->requestee);
	temp1-> id= ++id;
	temp1-> Next= NULL;
	LocSrc= node_search(start, src);
	LocDst= node_search(start, temp1->requestee);
	if(LocSrc== NULL|| LocDst== NULL)
	{
		printf("Src or Dst not found");
		exit(0);
	}
	if((LocSrc->ALINK)== NULL)
	{
		LocSrc->ALINK= temp1;
	}
	else
	{
		temp2=LocSrc->ALINK;
		while((temp2->Next)!= NULL)
		{
			temp2= temp2->Next;
		}
		temp2->Next=temp1;
	}
	temp2=edge_search(temp1->requestee,src);
	if(temp2!=NULL){
		temp1->accepted=true;
		temp2->accepted=true;
	}
	else{
		temp1->accepted=false;
	}
}
int degree_user(char *user1, char *user2){
	int deg=0;
	if(edge_search(user1,user2)!=NULL)
	{
		deg++;
	}
	if(edge_search(user2,user1)!=NULL)
	{
		deg++;
	}
	return deg;
}
void display(Hnode **start)
{
	Hnode*temp;
	struct Node*temp1;
	int i=0;
	temp=*start;
	while(temp!=NULL)
	{
		printf("\n Node : %dth info: %s",++i,temp->Username);
		if(temp->ALINK!=NULL)
		{
			printf("\nedges are:");
			temp1=temp->ALINK;

			while(temp1!=NULL)
			{
				printf("\t%d %s %s",temp1->id, temp1->requestee, temp1->accepted?"true":"false");
				temp1=temp1->Next;
			}
		}
		temp=temp->LINK;
	}
}

int main()
{
	Hnode *pos;
	init(&start);
/*	createUser(&start);
	createUser(&start);
	createUser(&start);
	createUser(&start);
	createUser(&start);
	createFriendship(&start);
	display(&start);
	createFriendship(&start);
	display(&start);
	insert_e(&start,"a","e");
	insert_e(&start,"b","a");
	insert_e(&start,"b","d");
	insert_e(&start,"c","a");
	insert_e(&start,"c","d");
	insert_e(&start,"e","d");
	
	pos=node_search(&start,"khush12");
	
	if(pos==NULL)
		printf("\nnode not found");
	else
	{
		printf("\n node found \n out going edges are:");
		pos1=pos->ALINK;
		while(pos1!=NULL)
		{
			printf("(%s,%s)",pos->Username,pos1->requestee);
			pos1 = pos1->Next;
		}
	}
	pos1= edge_search("a", "e");
	if(pos1==NULL)
	{
		printf("\nEdge not found");
	}
	else
	{
		printf("\nEdge found at Location: %s", pos1->AINFO);
	}
*/
	int ch;
	char choice='y';
	while(choice=='y'||choice=='Y')
	{	
		printf("\n\t\t\t\tSocial Network\n");
		printf("\n\t1.Create User.");
		printf("\n\t2.Create Friendship.");
		printf("\n\t3.Check degree of connection.");
		printf("\n\t\tEnter your Choice\n");
		scanf("%d",&ch);
		switch(ch){
			case 1: createUser(&start);
					display(&start);
						break;
			case 2: createFriendship(&start);
					display(&start);
						break;
			case 3: printf("Enter Usernames for checking degree:");
					char a[20],b[20];
					printf("Enter 1st username");
					scanf("%s",a);
					printf("Enter 2nd username");
					scanf("%s",b);
					printf("\ndegree of connection:%d",degree_user(a,b));
					display(&start);
		}
		printf("\n want to continue?(y/n)");
		scanf("%c",&choice);
	}
}
