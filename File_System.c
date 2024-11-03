#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define File_Amount 5
#define Folder_Size 5
#define File_Name_Size 20
#define Folder_Name_Size 20
#define Text_Len 100

typedef struct file 
{
    char name[File_Name_Size];
    char Text[Text_Len];
    struct file *next;
} File;

typedef struct folder
{
    char name[Folder_Name_Size];
    File *files;
    struct folder* next;
} Folder;

void Create_Folder(Folder** new_folder, char name[]) //Allocating a space for a Folder  
{    
    *new_folder = malloc(sizeof(Folder));

    if (*new_folder == NULL) 
    {
        printf("\033[34m ALLOCATION FAILED\033[0m\n");
        exit(1);
    }

    strcpy((*new_folder)->name, name);
    (*new_folder)->files = NULL;
    (*new_folder)->next = NULL;
}

void Create_File(File** new_file)
{
    *new_file = malloc(sizeof(File));

    if (*new_file == NULL) 
    {
        printf("\033[34m ALLOCATION FAILED\033[0m\n");
        exit(1);
    }

    char file_name[File_Name_Size];

    printf("\033[34mwelcome_user\033[0m\033[36m@root$\033[0m Enter file name:\n");

    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if(fgets(file_name, sizeof(file_name), stdin) == NULL || strlen(file_name) <= 0)
    {
        printf("\033[34m INPUT ERROR\033[0m\n");
        exit(1);
    }

    file_name[strcspn(file_name, "\n")] = '\0'; // remove newline character
    strcpy((*new_file)->name, file_name);

    printf("\033[034mwelcome_user\033[0m\033[36m@root$\033[0m Enter file text below: \n");

    if (fgets((*new_file)->Text, sizeof((*new_file)->Text), stdin) == NULL)
    {
        printf("\033[34m SYSTEM ERROR!\033[0m\n");
        exit(1);
    }
    (*new_file)->next = NULL;
}

void Add_File(Folder* folder, File* new_file) 
{
    File* current = folder->files;
    size_t count = 0;

    if (current == NULL)
    {
        folder->files = new_file;
        return;
    }

    while (current->next != NULL)
    {
        current = current->next;
        count++;
    }

    if (count < File_Amount - 1) 
    {
        current->next = new_file;
    }

    else 
    {
        printf("\033[34m Folder is full\033[0m\n");
    }
}

void Delete_File(File** file) 
{
    if (*file == NULL) return;
    File* next_file = (*file)->next;
    free(*file);
    *file = next_file;
}

void Delete_Folder(Folder** folder) 
{
    if (*folder == NULL) return;
    while ((*folder)->files != NULL) 
    {
        Delete_File(&((*folder)->files));
    }
    free(*folder);
    *folder = NULL;
}

int main() 
{    
    Folder* folder = NULL;
    File* file = NULL;
    char folder_name[Folder_Name_Size];
    char c;
    int operation = 0;
    int operation2 = 0;
    int count  = 0 ;

    printf("----------------------------------------------------------------------\n");
    printf("                             MAIN MENU                                \n");
    printf("----------------------------------------------------------------------\n");
    printf("\033[34m                            FILE SYSTEM                         \033[0m\n");
    printf("\n$=To create a new folder enter (1):\n");
    printf("\n$=To delete a folder enter (2):\n");
    printf("\n$=To quit the file system enter(0):\n");
    printf("\n");
    printf("\033[34mwelcome_user\033[0m\033[36m@root$\033[0m:");

    if (scanf("%d", &operation) != 1) 
    {
        printf("\033[34m INPUT ERROR\033[0m\n");
        exit(1);
    }
    
    getchar();
    
    switch(operation)
    {
        case(1):

            {
                printf("\033[34mwelcome_user\033[0m\033[36m@root$\033[0m Enter folder name:");
                if (fgets(folder_name, sizeof(folder_name), stdin) == NULL || strlen(folder_name) <= 0) 
                {
                    printf("\033[34m INPUT ERROR\033[0m\n");
                    exit(1);
                }
                folder_name[strcspn(folder_name, "\n")] = '\0'; // remove newline character
                Create_Folder(&folder, folder_name);

                printf("\n$=Create a new file enter (1):\n");
                printf("\n$=Exit folder enter (2):\n");
                printf("\n$=Delete folder enter (3)\n");
                printf("\033[34mwelcome_user\033[0m\033[36m@root$\033[0m:");


                if (scanf("%d", &operation2) != 1) 
                {
                    printf("\033[34m INPUT ERROR\033[0m\n");
                    exit(1);
                }

                getchar();

                switch (operation2)
                {
                    case(2):
                        {
                            printf("Bye Bye XD\n");
                        }

                    case(1):
                        {
                            Create_File(&file);
                            Add_File(folder, file);

                            printf("$=Would you like to create another file?(y/n):");
                            if(scanf("%c",&c) != 1 || c > 'z' || c < 'A' && c != 'y' && c != 'Y' && c != 'n' && c != 'N')
                            {
                                printf("Sytem Error\n");
                                exit(1);
                            }

                            while(c == 'y' && count < 6)
                            {
                                count++;
                                Create_File(&file);
                                Add_File(folder, file);

                                printf("$=Would you like to create another file?(y/n):");
                                if(scanf("%c",&c) != 1 || c > 'z' || c < 'A' )
                                {
                                    printf("Sytem Error\n");
                                    exit(1);
                                }
                                if(c == 'n')
                                {
                                    printf("Okay :( \n");
                                    break;
                                }
                                if(count == 5)
                                {
                                    printf("\033[31mLimited to 5 files in a folder!\033[0m\n");
                                    printf("GET OUT OF MY SWAMP\n");
                                }
                            }
                        }
                        Delete_Folder(&folder);
                }
            }

        case(0):

            {
                Delete_Folder(&folder);
                break;
                return 1;
            }

        case(2):

            {
                printf("There are no folders to delete\n");
                Delete_Folder(&folder);
                break;
                return 1;
            }    
    }
    return 0;
}
