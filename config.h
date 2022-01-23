#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
using namespace std;

typedef struct {
	char title[50], author[50], edition[50], genre[50], language[50];
	int year_of_publication, number_of_pages, weight, count, price;
} Book;

extern char file_name[30], sort_file_name[30], question;
// Global variables for temporary storage of fields (used for sorting)
extern char temp_for_title[50], temp_for_author[50], temp_for_edition[50], temp_for_genre[50], temp_for_language[50];
extern int temp_for_year_of_publication, temp_for_number_of_pages, temp_for_weight, temp_for_count, temp_for_price;
extern int temp_for_index;

// Prototypes of main functions
int add_book(FILE*);
int search_control(FILE*, int);
int print_all(FILE*);
int sort_books(FILE*);
int calculate(FILE*);
int open_database(FILE*);
int clear_all(FILE*);

// Prototypes of subfunctions
Book input_book(FILE*);
int print_book(Book);
int change_book(FILE*, Book, int);
int delete_book(FILE*, Book, int);
int sort_block(Book*, int*, int);
int search_book_with_parameter(FILE*, char, int);
int search_book_with_few_parameters(FILE*, char, int);

// Prototypes of processing functions
int calculate_total_value(FILE*);
int view_count_books_for_a_given_value(FILE*);
int view_books_with_max_value(FILE*);
int view_books_with_min_value(FILE*);