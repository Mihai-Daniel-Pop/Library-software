#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"



void print_borrowed_books()
{
    // Open borrow.csv file
    char borrow_file_path[MAX_PATH_LENGTH];
    sprintf(borrow_file_path, "%s%s", folder_path_borrow, borrow_csv);
    FILE* borrow_file = fopen(borrow_file_path, "r");
    if (borrow_file == NULL)
    {
        printf("Error opening borrow.csv for reading.\n");
        return;
    }

    // Read each line of borrow.csv
    char line[256];
    while (fgets(line, sizeof(line), borrow_file))
    {
        // Extract username, book title, and book author from the line
        char stored_username[50], book_title[100], book_author[100];
        sscanf(line, "%[^,],%[^,],%[^\n]", stored_username, book_title, book_author);

        // Check if the username matches the currently logged-in user
        if (strcmp(stored_username, username) == 0)
        {
            printf("Book Title: %s, Author: %s\n", book_title, book_author);
        }
    }

    // Close the file
    fclose(borrow_file);
    printf("\n");
    menu();
}

void search_books()
{
    int option;
    printf("\n");
    printf("Choose how you want to search for a book:\n");
    printf("Remember, the format is as follows: To-Kill-a-Mockingbird,Harper-Lee\n");
    printf("1. By title\n");
    printf("2. By author\n");
    printf("3. By title and author\n");
    scanf("%d", &option);
    getchar(); // Clear input buffer

    char query[100];
    printf("Enter your query: ");
    scanf("%[^\n]", query);
    getchar(); // Clear input buffer

    if (option == 1)
        search_by_title(query);
    if (option == 2)
        search_by_author(query);
    if (option == 3)
    {
        char title[100], author[100];
        sscanf(query, "%[^,],%s", title, author);
        search_by_title_and_author(title, author);
    }
    else
    {
        printf("\n");
        menu();
    }
}

void search_by_title(const char* title)
{
    char file_path_books[MAX_PATH_LENGTH];
    sprintf(file_path_books, "%s%s", folder_path_books, books_csv);
    FILE* book_file = fopen(file_path_books, "r");
    if (book_file == NULL)
    {
        printf("Error opening books database\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), book_file))
    {
        char* token = strtok(line, ",");
        if (strstr(token, title) != NULL)
        {
            char* book_author = strtok(NULL, ","); // Extract the author from CSV
            int copies = atoi(strtok(NULL, ",")); // Extract the number of copies
            printf("Book: %s, Author: %s, Available Copies: %d\n", token, book_author, copies);
            found = 1;
        }
    }
    fclose(book_file);
    if (!found)
    {
        printf("No matching books found.\n");
    }
    printf("\n");
    menu();
}

void search_by_author(const char* author)
{
    char file_path_books[MAX_PATH_LENGTH];
    sprintf(file_path_books, "%s%s", folder_path_books, books_csv);
    FILE* book_file = fopen(file_path_books, "r");
    if (book_file == NULL)
    {
        printf("Error opening books database\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), book_file))
    {
        char* token = strtok(line, ",");
        char* book_author = strtok(NULL, ","); // Extract the author from CSV
        if (strstr(book_author, author) != NULL)
        {
            int copies = atoi(strtok(NULL, ",")); // Extract the number of copies
            printf("Book: %s, Author: %s, Available Copies: %d\n", token, book_author, copies);
            found = 1;
        }
    }
    fclose(book_file);
    if (!found)
    {
        printf("No matching books found.\n");
    }
    printf("\n");
    menu();
}

void search_by_title_and_author(const char* title, const char* author)
{
    char file_path_books[MAX_PATH_LENGTH];
    sprintf(file_path_books, "%s%s", folder_path_books, books_csv);
    FILE* book_file = fopen(file_path_books, "r");
    if (book_file == NULL)
    {
        printf("Error opening books database\n");
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), book_file))
    {
        char* token = strtok(line, ",");
        char* book_author = strtok(NULL, ","); // Extract the author from CSV
        if (strstr(token, title) != NULL && strstr(book_author, author) != NULL)
        {
            int copies = atoi(strtok(NULL, ",")); // Extract the number of copies
            printf("Book: %s, Author: %s, Available Copies: %d\n", token, book_author, copies);
            found = 1;
        }
    }
    fclose(book_file);
    if (!found)
    {
        printf("No matching books found.\n");
    }
    printf("\n");
    menu();
}
