#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#define MAX_PATH_LENGTH 256

extern char username[50];
extern char folder_path[];
extern char folder_path_books[];
extern char folder_path_borrow[];
extern char books_csv[];
extern char people_csv[];
extern char borrow_csv[];

void login();
void create_account();
void menu();
void print_borrowed_books();
void search_books();
void borrow_book();
void return_book(const char* username, const char* title);
void donate_book();
int search_by_title_and_author1(const char* title, const char* author);
void update_book_copies(const char* book_title, const char* book_author, int change);

#endif // LIBRARY_H_INCLUDED
