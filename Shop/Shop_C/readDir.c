/*
https://c-for-dummies.com/blog/?p=3246

To access a directory, use the opendir() function. It’s prototyped in the dirent.h header file as:

DIR *opendir(const char *filename);


https://www.tutorialspoint.com/c_standard_library/c_function_perror.htm

The C library function void perror(const char *str) prints a descriptive error message to stderr. 
First the string str is printed, followed by a colon then a space.
*/

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

struct data_File {
    int f_number;
	char* f_name;
};

struct csv_Folder {
	struct data_File data_file[20];
	int index;
};

struct csv_Folder get_files()
{
    DIR *folder;
    struct dirent *entry;
    int files = 0; 
    struct csv_Folder csv_folder = {};

    folder = opendir("../Data");
    if(folder == NULL)
    {
        perror("Unable to read directory");
        return csv_folder;
    }
   

    while( (entry=readdir(folder)) )
    {

        if(strstr(entry->d_name,"cust") != NULL)
            {
            files++;
            //printf("File %3d: %s\n", files, entry->d_name);
            struct data_File data_file ={};
            data_file.f_number= files;
            data_file.f_name = entry->d_name;
            csv_folder.data_file[csv_folder.index++] = data_file;

            }
    }

    closedir(folder);

    return csv_folder;
}

int validate_input(int choice,int min,int max){
    //printf("Input:%d Min:%d Max:%d\n",choice,min,max);
    int validated = 0;
    if((choice >= min)&&(choice <= max)){
        
        validated = 1;
    }
    else{

        validated = 0;
    }
    return validated;
}

int get_input(){
	char input[4];
	
	fgets(input,4,stdin);
	int choice = atoi(input);
    return choice;
    
}

int main(){
    struct csv_Folder csv_folder = get_files();
    if (csv_folder.index > 0)
        {
        printf("The data folder contains the following files:\n");
        for(int i = 0;i < csv_folder.index; i++)
            {
            printf("File %3d: %s\n",csv_folder.data_file[i].f_number,csv_folder.data_file[i].f_name);
            }
        printf("Please choose a file to upload by inputting its number or enter -1 to exit\n");
        int choice = 0;
        while (choice != -1)
            {
            int choice = get_input();
            //printf("Chosen:%d\n",choice);
            if (choice == -1)
                {
                break;
                }
            int validated = validate_input(choice,1,csv_folder.index);
            if (validated == 1)
                {
                int idx = choice -1;
                printf("You have chosen to upload %s\n",csv_folder.data_file[idx].f_name);
                break;
                }
            else
                {
                printf("Please enter a valid file number\n");
                }
            }
        }
    else
        {
        printf("The data folder is empty - please add an order file in csv format to the folder\n");   
        }

    return(0);
}