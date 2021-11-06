10

You pass structures to functions like this, don't do it in any other way:

typedef struct    // use typedef for convenience, no need to type "struct" all over the place
{
  int x;
  int y;
} Data_t;


void function (Data_t* data); // function declaration

int main()
{
  Data_t something = {1, 1};  // declare a struct variable and initialize it
  printf("%d %d\n", something.x, something.y);

  function (&something); // pass address of "something" to the function

  /* since it was passed through a pointer (by reference), 
     the original "something" struct is now modified */

  printf("%d %d\n", something.x, something.y);
}

void function (Data_t* data)  // function definition
{
  data->x = 2; // access a struct member through a pointer using the -> operator
  data->y = 2;
}