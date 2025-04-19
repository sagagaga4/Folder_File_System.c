#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constants to limit folder and file attributes
#define File_Amount 5
#define Folder_Size 5
#define File_Name_Size 20
#define Folder_Name_Size 20
#define Text_Len 100

// Struct definition for a file
typedef struct file 
{
    char name[File_Name_Size];   // File name
    char Text[Text_Len];         // Content of the file
    struct file *next;           // Pointer to the next file in the list
} File;

// Struct definition for a folder
typedef struct folder
{
    char name[Folder_Name_Size]; // Folder name
    File *files;                 // Head pointer to the file list
    struct folder* next;         // Pointer to the next folder in the list (not used in current program)
} Folder;

// Function to allocate and initialize a folder
void Create_Folder(Folder** new_folder, char name[]) 
{    
    *new_folder = malloc(sizeof(Folder));
    if (*new_folder == NULL) 
    {
        printf("\033[34m ALLOCATION FAILED\033[0m\n");
        exit(1);
    }

    strcpy((*new_folder)->name, name); // Set folder name
    (*new_folder)->files = NULL;       // Initialize file list to NULL
    (*new_folder)->next = NULL;        // Initialize next folder to NULL
}

// Function to create a new file and get user input
void Create_File(File** new_file)
{
    *new_file = malloc(sizeof(File));
    if (*new_file == NULL) 
    {
        printf("\033[34m ALLOCATION FAILED\033[0m\n");
        exit(1);
    }

    char file_name[File_Name_Size];

    // Prompt user for file name
    printf("\033[34mwelcome_user\033[0m\033[36m@root$\033[0m Enter file name:\n");

    // Clear input buffer
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);

    if(fgets(file_name, sizeof(file_name), stdin) == NULL || strlen(file_name) <= 0)
    {
        printf("\033[34m INPUT ERROR\033[0m\n");
        exit(1);
    }

    file_name[strcspn(file_name, "\n")] = '\0'; // Remove newline character
    strcpy((*new_file)->name, file_name);       // Set file name

    // Prompt user for file text
    printf("\033[034mwelcome_user\033[0m\033[36m@root$\033[0m Enter file text below: \n");

    if (fgets((*new_file)->Text, sizeof((*new_file)->Text), stdin) == NULL)
    {
        printf("\033[34m SYSTEM ERROR!\033[0m\n");
        exit(1);
    }

    (*new_file)->next = NULL; // Initialize next pointer
}

// Function to add a file to a folder
void Add_File(Folder* folder, File* new_file) 
{
    File* current = folder->files;
    size_t count = 0;

    // If file list is empty, add as first file
    if (current == NULL)
    {
        folder->files = new_file;
        return;
    }

    // Traverse to the end of the file list
    while (current->next != NULL)
    {
        current = current->next;
        count++;
    }

    // Check file limit in folder
    if (count < File_Amount - 1) 
    {
        current->next = new_file;
    }
    else 
    {
        printf("\033[34m Folder is full\033[0m\n");
    }
}

// Function to delete a single file
void Delete_File(File** file) 
{
    if (*file == NULL) return;

    File* next_file = (*file)->next;
    free(*file);         // Free file memory
    *file = next_file;   // Move pointer to next file
}

// Function to delete a folder and all its files
void Delete_Folder(Folder** folder) 
{
    if (*folder == NULL) return;

    while ((*folder)->files != NULL) 
    {
        Delete_File(&((*folder)->files)); // Delete files one by one
    }

    free(*folder);   // Free folder memory
    *folder = NULL;
}

// Main menu to interact with the file system
int main() 
{    
    Folder* folder = NULL;
    File* file = NULL;
    char folder_name[Folder_Name_Size];
    char c;
    int operation = 0;
    int operation2 = 0;
    int count = 0;

    // Main Menu
    printf("----------------------------------------------------------------------\n");
    printf("                             MAIN MENU                                \n");
    printf("----------------------------------------------------------------------\n");
    printf("\033[34m                            FILE SYSTEM                         \033[0m\n");
    printf("\n$=To create a new folder enter (1):\n");
    printf("\n$=To delete a folder enter (2):\n");
    printf("\n$=To quit the file system enter(0):\n");
    printf("\n\033[34mwelcome_user\033[0m\033[36m@root$\033[0m:");

    // Get user operation input
    if (scanf("%d", &operation) != 1) 
    {
        printf("\033[34m INPUT ERROR\033[0m\n");
        exit(1);
    }

    getchar(); // Clear newline from input buffer

    switch(operation)
    {
        case(1): // Create folder
        {
            printf("\033[34mwelcome_user\033[0m\033[36m@root$\033[0m Enter folder name:");

            if (fgets(folder_name, sizeof(folder_name), stdin) == NULL || strlen(folder_name) <= 0) 
            {
                printf("\033[34m INPUT ERROR\033[0m\n");
                exit(1);
            }

            folder_name[strcspn(folder_name, "\n")] = '\0'; // Remove newline
            Create_Folder(&folder, folder_name);

            // Inner menu
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
                case(2): // Exit
                {
                    printf("Bye Bye XD\n");
                    break;
                }

                case(1): // Create files
                {
                    Create_File(&file);
                    Add_File(folder, file);

                    // Ask if the user wants to create more files
                    printf("$=Would you like to create another file?(y/n):");
                    if(scanf("%c", &c) != 1 || c > 'z' || c < 'A') 
                    {
                        printf("Sytem Error\n");
                        exit(1);
                    }

                    // Loop to create additional files
                    while(c == 'y' && count < 6)
                    {
                        count++;
                        Create_File(&file);
                        Add_File(folder, file);

                        printf("$=Would you like to create another file?(y/n):");
                        if(scanf(" %c", &c) != 1 || c > 'z' || c < 'A')
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
                    break;
                }

                case(3): // Delete folder
                {
                    Delete_Folder(&folder);
                    break;
                }
            }
            break;
        }

        case(0): // Exit program
        {
            Delete_Folder(&folder);
            break;
        }

        case(2): // Attempt to delete non-existing folder
        {
            printf("There are no folders to delete\n");
            Delete_Folder(&folder);
            break;
        }
    }

    return 0;
}
