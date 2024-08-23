#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"



void update_book_copies(const char* book_title, const char* book_author, int change)
{
    // Open books.csv for reading and writing
    char file_path_books[MAX_PATH_LENGTH];
    sprintf(file_path_books, "%s%s", folder_path_books, books_csv);
    FILE* book_file = fopen(file_path_books, "r+");
    if (book_file == NULL)
    {
        printf("Error opening books database\n");
        return;
    }

    // Create a temporary file to store the updated contents
    FILE* temp_file = fopen("temp.csv", "w");
    if (temp_file == NULL)
    {
        printf("Error creating temporary file\n");
        fclose(book_file);
        return;
    }

    // Iterate through each line in the file
    char line[256];
    while (fgets(line, sizeof(line), book_file))
    {
        char stored_title[100], stored_author[100];
        int copies;
        // Parse the line to extract title, author, and number of copies
        sscanf(line, "%[^,],%[^,],%d", stored_title, stored_author, &copies);
        // If the title and author match the book to be updated, adjust the number of copies
        if (strcmp(stored_title, book_title) == 0 && strcmp(stored_author, book_author) == 0)
        {
            copies += change; // Update the number of copies
            // Ensure the number of copies does not go below zero
            if (copies < 0) {
                printf("Error: Attempting to borrow more copies than available.\n");
                fclose(book_file);
                fclose(temp_file);
                remove("temp.csv"); // Remove temporary file
                return;
            }
            // Write the updated line to the temporary file
            fprintf(temp_file, "%s,%s,%d\n", stored_title, stored_author, copies);
        }
        else
        {
            // If the line does not match the book to be updated, simply copy it to the temporary file
            fprintf(temp_file, "%s", line);
        }
    }

    // Close both files
    fclose(book_file);
    fclose(temp_file);

    // Remove the original books.csv file
    remove(file_path_books);
    // Rename the temporary file to replace the original books.csv
    rename("temp.csv", file_path_books);
}
