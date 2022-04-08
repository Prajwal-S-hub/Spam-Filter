#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack *stckptr;
typedef struct stack{
    char  *data;
    stckptr *link;

};

stckptr top=NULL;
int failure[40];

//email structure
typedef struct
{
    char sender[30];
    char sub[30];
    char body[30];
    int score;
}email;



//search function
//kmp
void fail(char *pat)
{
	int i,j;
	int n=strlen(pat);
	failure[0]=-1;
	for(j=1;j<n;j++)
	{
		i=failure[j-1];
		while((pat[j]!=pat[i+1])&&(i>0))
			i=failure[i];
		if(pat[j]==pat[i+1])
			failure[j]=i+1;
		else
			failure[j]=-1;
	}
}
int search(char *pat,char *string)
{
	int i=0,j=0;
	int lens=strlen(string);
	int lenp=strlen(pat);
	while(i<lens&&j<lenp)
	{
		if(string[i]==pat[j])
		{
			i++;
			j++;
		}
		else if(j==0)
			i++;
		else
			j=failure[j-1]+1;
	}
	return((j==lenp)?(i-lenp):-1);
}
//Read an email from user
void read_email()
{
    //function to read the email from user
      email t1;
    printf("\nEnter the name of the sender: ");
    gets(t1.sender);
    printf("\nEnter the subject of the email: ");
    gets(t1.sub);
    printf("\nEnter the body of the email: ");
    gets(t1.body);
   linked_list(t1);
}




void push(char *item)
{
    stckptr temp;
    temp = (stckptr)malloc(sizeof(*temp));
    temp->data = item;
    temp->link = top;
    top = temp;
    //free(temp);
}



char* pop()
{
    stckptr temp=top;
    char *item;
    if(temp==NULL)
    {
        item = "";
        return item;
    }
    else
    {
        item=top->data;
        top=top->link;
        free(temp);
        return item;
    }
}
//search
void linked_list(email t1)
{
    email t2=t1;
    t2.score=0;
    char *last_node;
    last_node="abc";
    fail(t2.sender);
    fail(t2.sub);
    fail(t2.body);
    while(last_node!="")
    {
        last_node=pop();
        //printf("%s\n",last_node);
        if(search(last_node,t2.sender)!=-1)
        {
            t2.score+=10;
        }
        else if(search(last_node,t2.sub)!=-1)
        {
            t2.score+=7;
        }
        else if(search(last_node,t2.body)!=-1)
                {
                    t2.score+=3;
                }
    }

        printf("\nScore: %d",t2.score);

        if(t2.score>15)
        {
            printf("\nThe mail is spam!");
        }
        else if(t2.score>10)
        {
            printf("\nThe mail is ham.");
        }
        else
        {
            printf("\nThe mail is in primary inbox.");
        }
}



//spam directory
void spam()
{
    push("noname");
    push("nosubject");
    push("ola");
    push("uber");
    push("zomato");
    push("swiggy");
    push("airtel");
    push("bharat matrimony");
    push("rummycircle");
    push("cricbuzz");
    push("bookmyshow");
    push("naukari.com");
    push("admissions");
    push("lottery");
    push("discount");
    push("won");
    push("recharge");
    push("want to lose weight");
    push("sale");
    push("free");
    push("dear customer");
}

void main()
{
    spam();
    read_email();
}
