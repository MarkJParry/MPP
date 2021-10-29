# include <stdio.h>
# include <string.h>
# include <stdlib.h>

struct Module {
char name [50];
};

struct Student {
 struct Module modules[10];
 };

void printModule ( struct Module module )
{
 printf ("the module name is %s\n", module.name );
};

 int main ( void )
 {
 struct Module module = { "Multi - paradigm Programming " };
 printModule ( module );

 struct Student student = {};
 student.modules[0] = module ;

 struct Module module2 = { " Introduction to Programming " };
 student.modules[1] = module2 ;

 printModule ( student.modules[0]) ;
 printModule ( student.modules[1]) ;


 return 0;
 }
