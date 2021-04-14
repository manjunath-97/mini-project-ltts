#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define CHARLEN 50    //Max. length of a string


//Node that represents information about the book
struct node
{
    bool status;
    unsigned int bookId;
    char bookName[CHARLEN];
    char author[CHARLEN];
    char borrower_name[CHARLEN];
    char borrower_usn[CHARLEN];
    struct node* link;
};
typedef struct node* NODEPTR;

//Node that represents information about the Genre
struct hnode
{
    char genreName[CHARLEN];
    int bookCount;
    NODEPTR blink;
    struct hnode* glink;
};
typedef struct hnode* HNODEPTR;


//Function prototypes
HNODEPTR fnGetHnode(void);
NODEPTR fnGetNode(void);
HNODEPTR fnAddGenre(HNODEPTR,char []);
HNODEPTR fnAddBooks(HNODEPTR);
HNODEPTR fnTakeBooks(HNODEPTR,char []);
void fnDisplay(HNODEPTR);
HNODEPTR fnBorrow(HNODEPTR,unsigned int,char [],char []);
HNODEPTR fnReturn(HNODEPTR,unsigned int);
void fnDisplayGenre(HNODEPTR,char []);
void fnDisplayAdmin(HNODEPTR);

int main()
{
    int i=0,iChoice;
    unsigned int iD;
    char genre[CHARLEN],book[CHARLEN],author[CHARLEN];
    HNODEPTR head;
    head=NULL;

    char password[CHARLEN],entered_pass[CHARLEN],student_name[CHARLEN],usn[CHARLEN],ch;
    password[0]='\0';

    label:
    printf("\t\t\t------------------------------------------\n\t\t\t\"WHEN IN DOUBT COME TO THE LIBRARY\"\n\t\t\t------------------------------------------\n");
    printf("\n1.Admin\n2.Student\n");
    printf("Enter your choice:\n");
    scanf("%d",&iChoice);

    switch(iChoice)
    {
        case 1:     printf("\nWelcome Admin\n");
                    for(;;)
                    {
                        
                        printf("\n----------------------------");
                        printf("\n1.Add Genre\n2.Add Book\n3.Take book\n4.Display\n5.Go to home\n6.Exit\n");
                        printf("\n----------------------------");
                        printf("\nEnter your choice:\t");
                        scanf("%d",&iChoice);

                        switch(iChoice)
                        {
                            case 1:printf("\nEnter the Genre Name:\n");
                                    scanf("%s",genre);
                                    head=fnAddGenre(head,genre);
                                    break;
                            case 2:head=fnAddBooks(head);
                                    break;
                            case 3:printf("\nEnter name of the Book you want to take:\n");
                                    scanf("%s",book);
                                    head=fnTakeBooks(head,book);
                                    break;
                            case 4:fnDisplayAdmin(head);
                                    break;
                            case 5: printf("\n----------------------------");
                                    printf("\nBack in the Home Page!\n");
                                    goto label;
                                    break;
                            case 6:exit(100);

                            default:printf("\nInvalid Choice!\n");printf("\n----------------------------");
                            break;

                        }

                    }
                

        case 2: printf("\nEnter Name and USN respectively:\n");
                scanf("%s",student_name);
                scanf("%s",usn);
                printf("\nName : %s\tUSN : %s\n\n",student_name,usn);
                for(;;)
                {
                    printf("\nWelcome %s!\n\n",student_name);
                    printf("\n----------------------------");
                    printf("\n1.Borrow book\n2.Return book\n3.Display All books available\n4.Go to home\n5.Exit\n");
                    printf("\n----------------------------");
                    printf("\nEnter your choice:\t");
                    scanf("%d",&iChoice);

                    switch(iChoice)
                    {
                        case 1:printf("\nEnter the Book ID:\n");
                                scanf("%u",&iD);
                                head=fnBorrow(head,iD,student_name,usn);
                                break;
                        case 2:printf("\nEnter the Book ID:\n");
                                scanf("%u",&iD);
                                head=fnReturn(head,iD);
                                break;
                        case 3:fnDisplay(head);
                                break;
                        case 4: printf("\n----------------------------");
                                printf("\nBack in the Home Page!\n");
                                goto label;
                                    break;
                        case 5:exit(100);

                        default: printf("\nInvalid Choice!\n");printf("\n----------------------------");
                                break;
                    }
                }
                break;
        default:printf("\nInvalid Choice!\n");
                    goto label;
                    break;
    }
    return 0;
}

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