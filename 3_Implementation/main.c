#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "./inc/root.h"


int main()
{
    int i=0,iChoice;
    unsigned int iD;
    char genre[CHARLEN],book[CHARLEN],author[CHARLEN];
    HNODEPTR head;
    head=NULL;

    char student_name[CHARLEN],usn[CHARLEN],ch;


    label:
    printf("\t\t\t------------------------------------------\n\t\t\t\"WHEN IN DOUBT COME TO THE LIBRARY\"\n\t\t\t------------------------------------------\n");
    printf("\n1.Admin\n2.Student\n");
    printf("Enter your choice(1 or 2):\n");
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