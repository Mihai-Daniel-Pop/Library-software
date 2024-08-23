#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

void donate_book()
{
    char title[100], author[100];

    // Prompt the user to enter the book title and author in the specified format
    printf("Enter the book title and author in the format 'Title,Author' (e.g., To-Kill-a-Mockingbird,Harper-Lee):\n");

    // Prompt the user to enter the book title
    printf("Enter the book title: ");
    scanf("%s", title);

    // Prompt the user to enter the author
    printf("Enter the author: ");
    scanf("%s", author);

    // Open the books.csv file
    char file_path_books[MAX_PATH_LENGTH];
    sprintf(file_path_books, "%s%s", folder_path_books, books_csv);
    FILE* book_file = fopen(file_path_books, "r+");
    if (book_file == NULL)
    {
        printf("Error opening books database\n");
        return;
    }

    // Search for the book in the books.csv file
    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), book_file))
    {
        char stored_title[100], stored_author[100];
        int copies;
        sscanf(line, "%[^,],%[^,],%d", stored_title, stored_author, &copies);
        if (strcmp(stored_title, title) == 0 && strcmp(stored_author, author) == 0)
        {
            // Book found, increment the number of copies available
            copies++;
            fseek(book_file, -strlen(line), SEEK_CUR); // Move file pointer back to the beginning of the line
            fprintf(book_file, "%s,%s,%d\n", stored_title, stored_author, copies); // Write the updated line
            found = 1;
            break;
        }
    }

    // If book not found, append a new entry to books.csv
    if (!found)
    {
        fseek(book_file, 0, SEEK_END); // Move file pointer to the end of the file
        fprintf(book_file, "%s,%s,1\n", title, author); // Append new entry with one copy available
    }

    // Close the books.csv file
    fclose(book_file);

    printf("Book donated successfully.\n");
    printf("\n");
    menu(); // Return to the menu
}

void return_book(const char* username, const char* title)
{
    // Open the borrow.csv file for reading
    char borrow_file_path[MAX_PATH_LENGTH];
    sprintf(borrow_file_path, "%s%s", folder_path_borrow, borrow_csv);
    FILE* borrow_file = fopen(borrow_file_path, "r");
    if (borrow_file == NULL)
    {
        printf("Error opening borrow.csv\n");
        return;
    }

    // Create a temporary file to store the updated contents
    FILE* temp_file = fopen("temp.csv", "w");
    if (temp_file == NULL)
    {
        printf("Error creating temporary file\n");
        fclose(borrow_file);
        return;
    }

    char line[256];
    int found = 0;
    while (fgets(line, sizeof(line), borrow_file))
    {
        char stored_username[50], book_title[100], book_author[100];
        sscanf(line, "%[^,],%[^,],%[^\n]", stored_username, book_title, book_author);
        if (strcmp(stored_username, username) == 0 && strcmp(book_title, title) == 0)
        {
            found = 1;
            printf("Book returned successfully.\n");
        }
        else
        {
            fprintf(temp_file, "%s\n", line);
        }
    }

    fclose(borrow_file);
    fclose(temp_file);

    remove(borrow_file_path); // Delete the original borrow.csv file
    rename("temp.csv", borrow_file_path); // Rename the temporary file to borrow.csv
    printf("\n");
    menu();
    if (!found)
    {
        printf("Book not found in the borrow records.\n");
        printf("\n");
        menu();
    }
}

void borrow_book()
{
    printf("\n");
    printf("How to search for a book:\n");
    printf("By title and author: title,author\n");
    printf("This is an example: To-Kill-a-Mockingbird,Harper-Lee\n");
    char query[100];
    printf("Enter your query: ");
    scanf("%s", query);
    getchar(); // Clear input buffer

    char title[100] = "", author[100] = ""; // Initialize title and author variables
    sscanf(query, "%[^,],%s", title, author); // Extract both title and author from the query

    int borrowed = search_by_title_and_author1(title, author);

    if (borrowed)
    {
        // Prompt the user to confirm borrowing
        int confirm;
        printf("Do you want to borrow this book? (1 for Yes, 0 for No): ");
        scanf("%d", &confirm);
        getchar(); // Clear input buffer

        if (confirm)
        {
            // Append borrowing information to borrow.csv
            char borrow_file_path[MAX_PATH_LENGTH];
            sprintf(borrow_file_path, "%s%s", folder_path_borrow, borrow_csv);
            FILE* borrow_file = fopen(borrow_file_path, "a");
            if (borrow_file != NULL)
            {
                // Add the borrowing information: username, title, author
                fprintf(borrow_file, "%s,%s,%s\n", username, title, author);
                fclose(borrow_file);
                printf("Book borrowed successfully.\n");
                // Update book copies only if the book is borrowed
                update_book_copies(title, author, -1); // Decrement the number of available copies
                menu();
            }
            else
            {
                printf("Error opening borrow.csv for writing.\n");
                printf("\n");
                menu();
            }
        }
        else
        {
            printf("Book not borrowed.\n");
            printf("\n");
            menu();
        }
    }
    else
    {
        printf("No matching books found.\n");
        menu(); // Return to the menu if the book is not found
    }
}

int search_by_title_and_author1(const char* title, const char* author)
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
    return found;
}
