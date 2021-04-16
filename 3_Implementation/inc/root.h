#ifndef ROOT_H  
#define ROOT_H 

/*******************************************GLOBAL VARIABLES**********************************************************/
//ALl the globle variables and the composite data types will be declared here

#define CHARLEN 50 
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
typedef struct node* NODEPTR;   //represents a book

//Node that represents information about the Genre
struct hnode
{
    char genreName[CHARLEN];
    int bookCount;
    NODEPTR blink;
    struct hnode* glink;
};
typedef struct hnode* HNODEPTR;   ////represents a book genre



/*******************************************FUNCTION PROTOTYPE**********************************************************/
//function prototypes to be used
HNODEPTR fnGetHnode(void);                                //function to create a book genre node
NODEPTR fnGetNode(void);                                  //function to create a book node
HNODEPTR fnAddGenre(HNODEPTR,char []);                    //function to add a new genre to the library
HNODEPTR fnAddBooks(HNODEPTR);                            //function to add a new book to the library
HNODEPTR fnTakeBooks(HNODEPTR,char []);                   //functoin to remove a book from library permanenty
void fnDisplay(HNODEPTR);                                 //function to display books
HNODEPTR fnBorrow(HNODEPTR,unsigned int,char [],char []); //function to issue books 
HNODEPTR fnReturn(HNODEPTR,unsigned int);                 //function to return books 
void fnDisplayGenre(HNODEPTR,char []);                    //function the displays genre
void fnDisplayAdmin(HNODEPTR);                            //Detailed dsiplay about the books for admin
void freeMem(HNODEPTR);                                    //free dynaic memory at the end of the prgram

#endif






