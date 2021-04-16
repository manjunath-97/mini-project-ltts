#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/root.h"

HNODEPTR fnGetHnode(void)
{
    HNODEPTR temp;
    temp=(HNODEPTR)malloc(sizeof(struct hnode));
    return temp;
}


NODEPTR fnGetNode(void)
{
    NODEPTR temp;
    temp=(NODEPTR)malloc(sizeof(struct node));
    return temp;
}

HNODEPTR fnAddGenre(HNODEPTR head,char genre[])
{

    HNODEPTR htemp,cur;

    htemp=fnGetHnode();
    strcpy(htemp->genreName,genre);
    htemp->glink=NULL;
    htemp->bookCount=0;
    htemp->blink=NULL;

    if(head==NULL)
    {
        htemp->blink=NULL;
        head=htemp;
        printf("\nGenre added successfully!\n");
        return head;
    }
    cur=head->glink;
    head->glink=htemp;
    htemp->glink=cur;
    printf("\nGenre added successfully!\n");
    return head;
}

HNODEPTR fnAddBooks(HNODEPTR head)
{
    HNODEPTR htrack;
    NODEPTR btemp,btrack;

    unsigned int id;
    char genre[CHARLEN],book[CHARLEN],author[CHARLEN];

    printf("\nEnter genre name,ID,Book name and Author Name\n");
    scanf("%s",genre);
    scanf("%u",&id);
    scanf("%s",book);
    scanf("%s",author);

    int flag=true;
    htrack=head;
    while(htrack!=NULL)
    {
        btrack=htrack->blink;
        while(btrack!=NULL)
        {
            if(btrack->bookId==id)
            {
                flag=false;
                break;
            }
            btrack=btrack->link;
        }
        if(flag==false)
            break;
        else
            htrack=htrack->glink;
    }

    if(flag==false)
    {
        printf("\nDuplicate ID not allowed!\n");
        return head;
    }
    btemp=fnGetNode();
    strcpy(btemp->bookName,book);
    strcpy(btemp->author,author);
    btemp->status=true;
    btemp->bookId=id;

    htrack=head;
    while((htrack!=NULL)&&(strcmp(htrack->genreName,genre)))
    {
        htrack=(HNODEPTR)htrack->glink;
    }
    if(htrack==NULL)
    {
        printf("\nNo matches for entered Genre!\n");
        return head;
    }
    if(!strcmp(genre,htrack->genreName))
    {
        if(htrack->bookCount==0)
        {
            btemp->link=NULL;
            htrack->blink=btemp;
            htrack->bookCount=htrack->bookCount+1;
            printf("\nBook added successfully!\n");
            return head;
        }

        btrack=htrack->blink;
        btemp->link=(NODEPTR)btrack;
        htrack->blink=btemp;
        htrack->bookCount=htrack->bookCount+1;
        return head;
    }

    printf("\nGenre not found!\n");
    return head;
}

void fnDisplay(HNODEPTR head)
{
    HNODEPTR htrack;
    NODEPTR btrack;

    if(head==NULL)
    {
        printf("\nNo books to display!\n");
        return;
    }

    for(htrack=head;htrack!=NULL;htrack=htrack->glink)
    {

            printf("\nGenre %s\nNo of books %d\n",htrack->genreName,htrack->bookCount);
            for(btrack=htrack->blink;btrack!=NULL;btrack=btrack->link)
            {
                printf("\nBook ID : %u\nBook Name:\t%s\nAuthor Name:\t%s\n",btrack->bookId,
			btrack ->bookName,btrack->author);
                if(btrack->status==false)
                {
                    printf("The book has already been issued!\n");
                }
                else
                {
                    printf("Book is not issued!\n");
                }

            }

    }
    return;
}

HNODEPTR fnTakeBooks(HNODEPTR head,char book[])
{
    HNODEPTR htrack;
    NODEPTR bprev,btrack;


    htrack=head;

    if(head==NULL)
    {
        printf("\nBook shelf is Empty!! Add some books\n");
        return head;
    }

    while(htrack!=NULL)
    {
        bprev=NULL;
        btrack=htrack->blink;

        while((btrack!=NULL)&&(strcmp(btrack->bookName,book)))
        {
            bprev=btrack;
            btrack=btrack->link;
        }

        if(btrack==NULL)
        {
            htrack=htrack->glink;
            continue;
        }
        if(!(strcmp(btrack->bookName,book)))
        {
printf("\nBook %s is found at Genre %s and taken out successfully\n",btrack->bookName,htrack->genreName);

            if(htrack->blink==btrack)
            {
                htrack->blink=btrack->link;
                htrack->bookCount=htrack->bookCount-1;
                free(btrack);
                return head;
            }
            bprev->link=btrack->link;
            htrack->bookCount=htrack->bookCount-1;

            free(btrack);

            return head;
        }
        htrack=htrack->glink;
    }
    printf("\nBook is not found!\n");
    return head;
}


HNODEPTR fnBorrow(HNODEPTR head,unsigned int id,char student_name[],char usn[])
{
    HNODEPTR htrack;
    NODEPTR bprev,btrack;


    htrack=head;

    if(head==NULL)
    {
        printf("\nBook shelf is Empty!\n");
        return head;
    }

    while(htrack!=NULL)
    {
        bprev=NULL;
        btrack=htrack->blink;

        while((btrack!=NULL)&&btrack->bookId!=id)
        {
            bprev=btrack;
            btrack=btrack->link;
        }

        if(btrack==NULL)
        {
            htrack=htrack->glink;
            continue;
        }
        if(btrack->bookId==id)
        {
            if(btrack->status==false)
            {
                printf("Book %s with ID %u is found at Genre %s and the book has already been issued!\n",btrack->bookName,btrack->bookId,htrack->genreName);
                return head;
            }
            printf("\nBook %s with ID %u is found at Genre %s and issued successfully\n",btrack->bookName,btrack->bookId,htrack->genreName);
            strcpy(btrack->borrower_name,student_name);
            strcpy(btrack->borrower_usn,usn);
            btrack->status=false;
            return head;
        }
        htrack=htrack->glink;
    }

    printf("\nBook is not found!\n");
    return head;

}




HNODEPTR fnReturn(HNODEPTR head,unsigned int id)
{
    HNODEPTR htrack;
    NODEPTR bprev,btrack;


    htrack=head;
    if(head==NULL)
    {
        printf("\nBook shelf is Empty!\n");
        return head;
    }

    while(htrack!=NULL)
    {
        bprev=NULL;
        btrack=htrack->blink;

        while((btrack!=NULL)&&btrack->bookId!=id)
        {
            bprev=btrack;
            btrack=btrack->link;
        }

        if(btrack==NULL)
        {
            htrack=htrack->glink;
            continue;
        }
        if(btrack->bookId==id)
        {
            printf("\nBook %s is found at Genre %s and recieved successfully\n",btrack->bookName,
htrack->genreName);

            if(btrack->status==true)
            {
                printf("This book has not been issued!\n");
                return head;
            }

            btrack->status=true;
            return head;
        }
        htrack=htrack->glink;
    }
    printf("\nBook is not found!\n");
    return head;
}

void fnDisplayGenre(HNODEPTR head,char genre[])
{
    HNODEPTR htrack;
    NODEPTR btrack;

    if(head==NULL)
    {
        printf("\nNo books to display!\n");
        return;
    }

    for(htrack=head;htrack!=NULL;htrack=htrack->glink)
    {
            if(!strcmp(htrack->genreName,genre))
            {
                printf("\nGenre %s\nNo of books %d\n",htrack->genreName,htrack->bookCount);
                for(btrack=htrack->blink;btrack!=NULL;btrack=btrack->link)
                {
                    printf("\nBook ID : %d\nBook Name:\t%s\nAuthor Name:\t%s\n",btrack->bookId,
btrack->bookName,btrack->author);
                    if(btrack->status==false)
                    {
                        printf("The Book has already been issued!\n");
                    }
                    else
                    {
                        printf("Book is available for issue!\n");
                    }
                }
            }

    }
    return;
}
void fnDisplayAdmin(HNODEPTR head)
{
    HNODEPTR htrack;
    NODEPTR btrack;

    if(head==NULL)
    {
        printf("\nNo books to display!\n");
        return;
    }

    for(htrack=head;htrack!=NULL;htrack=htrack->glink)
    {

            printf("\nGenre %s\nNo of books %d\n",htrack->genreName,htrack->bookCount);

            for(btrack=htrack->blink;btrack!=NULL;btrack=btrack->link)
            {
                printf("\nBook ID : %u\nBook Name:\t%s\nAuthor Name:\t%s\n",btrack->bookId, btrack->bookName,btrack->author);
                if(btrack->status==false)
                {
                    printf("The book has already been issued to\n");
                    printf("Name : %s\t\tUSN : %s\n",btrack->borrower_name,btrack->borrower_usn);
                }
                else
                {
                    printf("Book is available for issue\n");
                }

            }

    }
    return;
}
void freeMem(HNODEPTR head){
    HNODEPTR htrack;
    NODEPTR btrack;

    if(head==NULL)
    {
        printf("\nNo books to display!\n");
        return;
    }
    HNODEPTR ptr;
    htrack=head;
    while(htrack!=NULL)
    {
            NODEPTR hptr;
            btrack=htrack->blink;
            htrack->blink = NULL;
            while(btrack!=NULL)
            {
                hptr = btrack;
                btrack=btrack->link;
                free(hptr);
            }
            ptr = htrack;
            htrack=htrack->glink;
            free(ptr);
    }
    return;
}