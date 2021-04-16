#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/root.h"

int main()
{
    int i;
    unsigned int iD;
    char genre[CHARLEN],book[CHARLEN],author[CHARLEN];
    HNODEPTR head;
    head=NULL;

    char student_name[CHARLEN],usn[CHARLEN],ch;


    printf("\t\t\t------------------------------------------\n\t\t\t\"WHEN IN DOUBT COME TO THE LIBRARY\"\n\t\t\t------------------------------------------\n");
    printf("\nWelcome Admin(add a genere and a book)\n");                   
    printf("\nAdding a Genre->fantasy\n");
    strcpy(genre,"fantasy\0");
    head=fnAddGenre(head,genre);

    //adding a book -> GOT
    NODEPTR bookPtr = fnGetNode();
     strcpy(bookPtr->bookName,"Game Of Thrones");
    strcpy(bookPtr->author,"GR Martin");
    bookPtr->status=true;
    bookPtr->bookId=112;
    bookPtr->link=NULL;
    head->blink=bookPtr;

    //displaying
    fnDisplayAdmin(head);
    printf("\n---------------------------------------");

    

    printf("\n-----------------STUDENT----------------------");
    printf("\nName and USN respectively: Manu-1si17cs97\n");
    printf("\n----------------------------");
    printf("\n Book ID: 112 to borrow\n");
    head=fnBorrow(head,112,"manu\0","1si17cs97");
    printf("status after  borrowing a book\n-----------------------------------");
    fnDisplay(head);
    printf("\n------------------------------\nReturning the Book with ID->112\n");
    head=fnReturn(head,112);
    printf("status after  returning a book\n----------------------------------");
    fnDisplay(head);
    printf("\n---------------------------------------");

    return 0;
}