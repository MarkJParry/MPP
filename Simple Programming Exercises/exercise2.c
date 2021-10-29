# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>

struct Module {
char name [50];
};

struct Student {
 struct Module modules[10];
 };
 
struct Employee {
int ID;
char name [50];
int age;
float salary;
int yearsWorked;
char jobTitle[50];
int reportsTo;
bool isManager;
};

struct Manager {
 struct Employee employees[10];
 };

void printModule ( struct Module module )
{
 printf ("the module name is %s\n", module.name );
};

void printEmployee ( struct Employee employee )
{
 printf ("employee name is %s\n", employee.name );
 printf (" ID is %d\n", employee.ID );
 printf (" age is %d\n", employee.age );
 printf (" salary is %.2f\n", employee.salary);
 printf (" years worked is %d\n", employee.yearsWorked );
 printf (" job title is %s\n", employee.jobTitle );
 printf (" reports to  %d\n", employee.reportsTo );
 printf (" is a manager is %s\n", employee.isManager ? "true" : "false" );
 printf ("--------------\n");

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
 
 struct Employee employee1;
			employee1.ID = 1;
			strcpy(employee1.name,"Dominic");
			employee1.age = 40;
			employee1.salary = 50000.00;
			employee1.yearsWorked = 10;
			strcpy(employee1.jobTitle,"Lecturer");
			employee1.reportsTo = 2;
			employee1.isManager = false;
 printEmployee( employee1 );
 
 struct Employee employee2;
 			employee2.ID = 2;
			strcpy(employee2.name ,"Mark");
			employee2.age = 63;
			employee2.salary = 65000.00;
			employee2.yearsWorked = 12;
			strcpy(employee2.jobTitle,"Manager");
			employee2.reportsTo = 2;
			employee2.isManager = true;
 printEmployee ( employee2);


 struct Manager manager = {};
 manager.employees[0] = employee1 ;


 manager.employees[1] = employee2 ;

 printEmployee ( manager.employees[0]) ;
 printEmployee ( manager.employees[1]) ;

 return 0;
 }
