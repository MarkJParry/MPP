//https://www.tutorialspoint.com/cprogramming/c_structures.htm
#include <stdio.h>
#include <string.h>
 
struct Books {
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
};

/* function declaration */
void printBook( struct Books book );
void searchBook( struct Books book );

int main( ) {

   struct Books Book[10];        /* Declare an array Book[] of type Book */
   int idx = 0; 
   /* book 1 specification */
   strcpy( Book[idx].title, "C Programming");
   strcpy( Book[idx].author, "Nuha Ali"); 
   strcpy( Book[idx].subject, "C Programming Tutorial");
   Book[idx].book_id = 6495407;

   idx++;

   /* book 2 specification */
   strcpy( Book[idx].title, "Telecom Billing");
   strcpy( Book[idx].author, "Zara Ali");
   strcpy( Book[idx].subject, "Telecom Billing Tutorial");
   Book[idx].book_id = 6495700;
   
   idx++;

    /* book 3 specification */
   strcpy( Book[idx].title, "Jabberwocky");
   strcpy( Book[idx].author, "Louise Carroll");
   strcpy( Book[idx].subject, "Monty Pythons Version");
   Book[idx].book_id = 6495710;
   idx++;
 
   /* print Book info */
   for (int i = 0; i < idx; i++)
        {printBook( Book[i] );}

    //search for detais given id
    int input;
    printf("Enter book_id to search for its details:\n");
    scanf("%d", &input); 
    int found = 0;

    for (int i = 0; i < idx; i++)
    {
        if (Book[i].book_id == input)
            {printBook( Book[i] );
            found = 1;
            break;
            }
    }
    if (found == 0)
        {printf("Book details not found\n");}
    

   return 0;
}

void printBook( struct Books book ) {

   printf( "Book title : %s\n", book.title);
   printf( "Book author : %s\n", book.author);
   printf( "Book subject : %s\n", book.subject);
   printf( "Book book_id : %d\n", book.book_id);
}

