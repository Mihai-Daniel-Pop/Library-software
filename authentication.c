#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

char username[50] = "";
char folder_path[] = "C:/Users/Click/OneDrive/Desktop/C C++/Library v3/";
char folder_path_books[] = "C:/Users/Click/OneDrive/Desktop/C C++/Library v3/";
char folder_path_borrow[] = "C:/Users/Click/OneDrive/Desktop/C C++/Library v3/";
char books_csv[] = "books.csv";
char people_csv[] = "people.csv";
char borrow_csv[] = "borrow.csv";

void menu()
{
    int step;
    printf("To see your loans press 1 and enter.\n");
    printf("To search for a book press 2 and enter.\n");
    printf("To borrow a book press 3 and enter.\n");
    printf("To return a book, press 4 and enter:\n");
    printf("To donate a book, press 5 and enter:\n");
    printf("To exit, press 6 and enter:\n"); // Option to exit
    scanf("%d", &step);
    if (step == 1)
        print_borrowed_books();
    if (step == 2)
        search_books();
    if (step == 3)
        borrow_book();
    if (step == 4)
    {
        char title[100];
        printf("Enter the title of the book you want to return: ");
        scanf("%s", title);
        return_book(username, title); // Pass the username and title as arguments
    }
    if (step == 5)
        donate_book();
    if (step == 6)
        exit_program(); // Call the exit function
}

void exit_program()
{
    exit(0); // Terminate the program with successful termination
}

void create_account()
{
    int step;
    char new_user[50];
    char new_password[50];
    printf("Enter your new username:\n");
    scanf("%[^\n]%*c", new_user);
    printf("Enter your new password:\n");
    scanf("%[^\n]%*c", new_password);

    char file_path[MAX_PATH_LENGTH];
    sprintf(file_path, "%s%s", folder_path, people_csv);

    // Attempt to open the file in append mode
    FILE* file = fopen(file_path, "a");
    if (file != NULL)
    {
        // Write the new user information to the file
        fprintf(file, "%s,%s\n", new_user, new_password);
        fclose(file);
        printf("Account created successfully.\n");
    }
    else
    {
        printf("Failed to create the account.\n");
    }

    printf("A restart is required, in order to update your login detail.\n");
    exit_program();
}

void login()
{
    char password[50];
    int attempts = 5; // Number of attempts allowed
    int step;
    printf("Enter your name and surname: ");
    scanf("%[^\n]%*c", username); // Update the global username variable directly

    char file_path[MAX_PATH_LENGTH];
    sprintf(file_path, "%s%s", folder_path, people_csv);

    // Check if the file exists
    FILE* file = fopen(file_path, "r");
    if (file != NULL)
    {
        char line[256];
        while (fgets(line, sizeof(line), file))
        {
            char stored_username[50], stored_password[50];
            if (sscanf(line, "%[^,],%s", stored_username, stored_password) == 2)
            {
                if (strcmp(stored_username, username) == 0)
                {
                    do
                    {
                        printf("Enter your password (Attempts left: %d): ", attempts);
                        scanf("%[^\n]%*c", password);
                        if (strcmp(password, stored_password) == 0)
                        {
                            printf("Welcome, %s\n", username);
                            menu(); // Display the menu
                            fclose(file);
                            return; // Exit the function after displaying the menu
                        }
                        else
                        {
                            printf("Password is incorrect.\n");
                            attempts--;
                        }
                    }
                    while (attempts > 0);
                    printf("You have exceeded the maximum number of attempts. Exiting...\n");
                    fclose(file);
                    exit_program(); // Exit the program
                }
            }
        }
        fclose(file);
    }
    else
    {
        printf("Error opening people database.\n");
    }

    printf("There is no account under this name.\n");
    printf("If you would like to register a new account, type 1 and press Enter:\n");
    printf("If you would like to go back to the login menu, type 2 and press Enter:\n");
    scanf("%d", &step);
    getchar();
    if (step == 1)
        create_account();
    if (step == 2)
        login();
    else
        exit_program();
}
