#include<stdio.h>
#include<string.h>

/*
structure is defined above all functions so it is global.
*/

struct student
{
    char name[20];
    int roll_no;
    int marks;
};
struct class
{
    char name[20];
};



void print_struct(struct student s);

struct student add_student(struct class c)
{   
    printf("Class: %s\n",c.name);
    struct student stu = {"Tim", 1, 78};
    return stu;
}


int main()
{
    //struct student stu = add_student();  
    //print_struct(stu);
    struct class c = {"physics"};
    int a = 0;
    if (a ==0){
        //struct class c;
        struct student stu = add_student(c); 
        print_struct(stu);
    }
    struct student stu;
    print_struct(stu);
 



    return 0;
}

void print_struct(struct student s)
{
    printf("Name: %s\n", s.name);
    printf("Roll no: %d\n", s.roll_no);
    printf("Marks: %d\n", s.marks);
}
