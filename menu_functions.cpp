#include "config.h"

char sort_file_name[30];

int add_book(FILE* local_database) {
	Book book;
	book = input_book(local_database);
	fseek(local_database, 0, 2);
	fwrite(&book, sizeof(book), 1, local_database);
	return 0;
}

int search_control(FILE* local_database, int parameter) {
	cout << "Search a book by one (1) or complex (2) criteria ?:\n* - Exit to the main menu\n";
	do {
		question = _getch();
		if(question == '1') {
			cout << "\nWhich of the parameters to search for a book ?:\n";
			cout << "1 - By title\t\t\t2 - By the author\n";
			cout << "3 - By edition\t\t4 - By genre\n";
			cout << "5 - By language\t\t\t6 - By year of publication\n";
			cout << "7 - By number of pages\t8 - By weight\n";
			cout << "9 - By circulation\t\t\t0 - By the price\n";
			cout << "* - Exit to the main menu\n\n";
			do {
				question = _getch();
				if(question == '1' || question == '2' || question == '3' || question == '4' || question == '5' ||
					question == '6' || question == '7' || question == '8' || question == '9' || question == '0') {
					search_book_with_parameter(local_database, question, parameter);
				}
				else if(question == '*') {
					return 0;
				}
			} while(1);
		}
		else if(question == '2') {
			cout << "\nSelect a search mode by several options:\n";
			cout << "1 - By title and author\n";
			cout << "2 - By title and edition\n";
			cout << "3 - By title and price\n";
			cout << "4 - By genre and language\n";
			cout << "* - Exit to the main menu\n\n";
			do {
				question = _getch();
				if(question == '1' || question == '2' || question == '3' || question == '4') {
					search_book_with_few_parameters(local_database, question, parameter);
				}
				else if(question == '*') {
					return 0;
				}
			} while(1);
		}
		else if(question == '*') {
			return 0;
		}
	} while(1);
}

int print_all(FILE* local_database) {
	Book book;
	int counter = 0, r;
	fseek(local_database, 0, 0);
	while(!feof(local_database)) {
		r = fread(&book, sizeof(Book), 1, local_database);
		if(r < 1) {
			break;
		}
		counter++;
		print_book(book);
	}
	cout << counter << " books from the database were found and published.\n\n";
	return 0;
}

int sort_books(FILE* local_database) {
	// determine the size of the database
	fseek(local_database, 0, 2);
	int size = ftell(local_database);
	fseek(local_database, 0, 0);
	size /= sizeof(Book);

	// Allocate memory for arrays for sorted data and create a file variable for the sorted file
	Book book;
	Book* books = new Book[size];
	int* indexes = new int[size];
	fseek(local_database, 0, 0);
	int count = 0;
	while(count < size) {
		fread(&book, sizeof(book), 1, local_database);
		books[count] = book;
		indexes[count] = count;
		count++;
	}
	count--;
	FILE* sort_database = NULL;

	// Everything below is the process of sorting and writing the relevant data to files
	cout << "1 - Sort all information about the data into a new binary file.\n";
	cout << "2 - Sort all information about the data into a new text file.\n";
	cout << "3 - Sort only data indexes to a new file.\n\n";
	do {
		do {
			question = _getch();
			if(question == '1' || question == '2' || question == '3') {
				break;
			}
		} while(1);

		char static_q = question;

		cout << "Which of the parameters to sort?\n";
		cout << "1 - By year of publication\n";
		cout << "2 - By number of pages\n";
		cout << "3 - By weight\n";
		cout << "4 - By circulation\n";
		cout << "5 - By the price\n";
		cout << "* - Exit to the main menu\n\n";

		do {
			question = _getch();
			if(question == '1' || question == '2' || question == '3' || question == '4' || question == '5') {
				break;
			}
			else if(question == '*') {
				return 0;
			}
		} while(1);

		for(int i = 0; i < size; i++) {
			for(int j = 0; j < size - i - 1; j++) {
				if(question == '1') {
					if(books[j].year_of_publication > books[j + 1].year_of_publication) {
						sort_block(books, indexes, j);
					}
				}
				else if(question == '2') {
					if(books[j].number_of_pages > books[j + 1].number_of_pages) {
						sort_block(books, indexes, j);
					}
				}
				else if(question == '3') {
					if(books[j].weight > books[j + 1].weight) {
						sort_block(books, indexes, j);
					}
				}
				else if(question == '4') {
					if(books[j].count > books[j + 1].count) {
						sort_block(books, indexes, j);
					}
				}
				else if(question == '5') {
					if(books[j].price > books[j + 1].price) {
						sort_block(books, indexes, j);
					}
				}
			}
		}

		switch(static_q) {
			case '1': cout << "Enter a name (in .bin format): "; break;
			case '2': cout << "Enter a name (in .txt format): "; break;
			case '3': cout << "Enter a name (in .txt format): "; break;
		}
		do {
			cin >> sort_file_name;
			if(static_q == '1') {
				if((sort_database = fopen(sort_file_name, "rb+")) == NULL) {
					if((sort_database = fopen(sort_file_name, "wb+")) == NULL) {
						cout << "Error.\n";
					}
					break;
				}
				else {
					cout << "The file with the specified name already exists. Replace it? Y/N\n* - Exit\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						sort_database = fopen(sort_file_name, "wb+");
						break;
					}
					else if(question == 'N' || question == 'n') {
						cout << "Enter a NEW file name (in .bin format): ";
					}
					else if(question == '*') {
						return 0;
					}
				}
			}
			else if(static_q == '2' || static_q == '3') {
				if((sort_database = fopen(sort_file_name, "rt+")) == NULL) {
					if((sort_database = fopen(sort_file_name, "wt+")) == NULL) {
						cout << "Error.\n";
					}
					break;
				}
				else {
					cout << "The file with the specified name already exists. Replace it? Y/N\n* - �����\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						sort_database = fopen(sort_file_name, "wt+");
						break;
					}
					else if(question == 'N' || question == 'n') {
						cout << "Enter a NEW file name (in .txt format): ";
					}
					else if(question == '*') {
						return 0;
					}
				}
			}
		} while(1);

		fseek(sort_database, 0, 0);
		for(int i = 0; i < size; i++) {
			switch(static_q) {
				case '1': fwrite(&books[i], sizeof(books[i]), 1, sort_database); break;
				case '2': fprintf(sort_database, "Book title: %sBook author: %sEdition: %sGenre: %sLanguage: %sYear of publication: %d\nNumber of pages: %d\nWeight: %d gram\nCirculation: %d pcs.\nPrice: %d UAH\n\n", books[i].title, books[i].author, books[i].edition, books[i].genre, books[i].language, books[i].year_of_publication, books[i].number_of_pages, books[i].weight, books[i].count, books[i].price); break;
				case '3': fprintf(sort_database, "%d\n", indexes[i]); break;
			}
		}
		fclose(sort_database);

		cout << "\nSort more?\n";
		cout << "Y - Sort\tN - Exit the menu\n\n";
		do {
			question = _getch();
			if(question == 'N' || question == 'n') {
				delete[] books;
				return 0;
			}
			else if(question == 'Y' || question == 'y') {
				cout << "1 - Sort all information about the data into a new binary file.\n";
				cout << "2 - Sort all information about the data into a new text file.\n";
				cout << "3 - Sort only data indexes to a new file.\n\n";
				break;
			}
		} while(1);
	} while(1);
}

int calculate(FILE* local_database) {
	cout << "What calculations do I need to perform ?:\n";
	cout << "1 - Calculate the total amount of the specified value\n";
	cout << "2 - Print the number of books for a given value\n";
	cout << "3 - Find the book of greatest value\n";
	cout << "4 - Find the book by the least value\n";
	cout << "* - Exit to the main menu\n\n";
	do {
		question = _getch();
		if(question == '1' || question == '2' || question == '3' || question == '4' || question == '*') {
			switch(question) {
				case '1': calculate_total_value(local_database); break;
				case '2': view_count_books_for_a_given_value(local_database); break;
				case '3': view_books_with_max_value(local_database); break;
				case '4': view_books_with_min_value(local_database); break;
				case '*': return 0;
			}
			cout << "What calculations do I need to perform ?:\n";
			cout << "1 - Calculate the total amount of the specified value\n";
			cout << "2 - Print the number of books for a given value\n";
			cout << "3 - Find the book of greatest value\n";
			cout << "4 - Find the book by the least value\n";
			cout << "* - Exit to the main menu\n\n";
		}
	} while(1);
}


int open_database(FILE* local_database) {
	fclose(local_database);
	cout << "Enter the name of an existing or new database file: ";
	cin >> file_name;
	if((local_database = fopen(file_name, "rb+")) == NULL) {
		if((local_database = fopen(file_name, "wb+")) == NULL) {
			cout << "Unknown file creation error.\n";
		}
		cout << "A new database file named: " << file_name << endl;
	}
	else {
		cout << "Opened an existing file " << file_name << endl << endl;
	}

	return 0;
}


int clear_all(FILE* local_database) {
	cout << "WARNING!!! You really want to clear all data from the file " << file_name << "?\n";
	cout << "Y - Clean up\tN - Cancel\n\n";
	do {
		question = _getch();
		if(question == 'Y' || question == 'y') {
			fclose(local_database);
			if((local_database = fopen(file_name, "wb+")) == NULL)
			{
				cout << "An error has occurred!" << endl;
				return -1;
			}
			cout << "The file has been cleared.\n";
			break;
		}
		else if(question == 'N' || question == 'n') {
			cout << "Cleaning canceled.\n";
			break;
		}
	} while(1);

	return 0;
}
