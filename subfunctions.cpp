#include "config.h"

char temp_for_title[50], temp_for_author[50], temp_for_edition[50], temp_for_genre[50], temp_for_language[50];
int temp_for_year_of_publication, temp_for_number_of_pages, temp_for_weight, temp_for_count, temp_for_price;
int temp_for_index;

Book input_book(FILE* local_database) {
	Book book;
	cout << "Enter data for the book: \n";
	cout << "Book title: "; fscanf(stdin, " "); fgets(book.title, 50, stdin);
	cout << "Book author: "; fscanf(stdin, " "); fgets(book.author, 50, stdin);
	cout << "Edition: "; fscanf(stdin, " "); fgets(book.edition, 50, stdin);
	cout << "Genre: "; fscanf(stdin, " "); fgets(book.genre, 50, stdin);
	cout << "Language: "; fscanf(stdin, " "); fgets(book.language, 50, stdin);
	cout << "Year of publication: "; cin >> book.year_of_publication;
	cout << "Number of pages: "; cin >> book.number_of_pages;
	cout << "Weight (gram): "; cin >> book.weight;
	cout << "Circulation: "; cin >> book.count;
	cout << "Price (UAH): "; cin >> book.price;
	return book;
}


int print_book(Book book) {
	cout << "-\n";
	cout << "Book title: " << book.title;
	cout << "Book author: " << book.author;
	cout << "Edition: " << book.edition;
	cout << "Genre: " << book.genre;
	cout << "Language: " << book.language;
	cout << "Year of publication: " << book.year_of_publication << endl;
	cout << "Number of pages: " << book.number_of_pages << endl;
	cout << "Weight: " << book.weight << endl;
	cout << "Circulation: " << book.count << endl;
	cout << "Price: " << book.price << endl << "-\n" << endl;
	return 0;
}


int change_book(FILE* local_database, Book book, int position) {
	cout << "Select an option to change: \n";
	cout << "1 - Title\t\t\t2 - Author\n";
	cout << "3 - Edition\t\t\t4 - Genre\n";
	cout << "5 - Language\t\t\t6 - Year of publication\n";
	cout << "7 - Number of pages\t\t8 - Weight(gram)\n";
	cout << "9 - Circulation\t\t\t0 - Price\n";
	cout << "* - Back to search\n\n";
	do {
		question = _getch();
		if(question == '1' || question == '2' || question == '3' || question == '4' || question == '5' ||
			question == '6' || question == '7' || question == '8' || question == '9' || question == '0') {
			switch(question) {
				case '1': cout << "New book title: "; fscanf(stdin, " "); fgets(book.title, 50, stdin); break;
				case '2': cout << "New book author: "; fscanf(stdin, " "); fgets(book.author, 50, stdin); break;
				case '3': cout << "New book edition: "; fscanf(stdin, " "); fgets(book.edition, 50, stdin); break;
				case '4': cout << "New book genre: "; fscanf(stdin, " "); fgets(book.genre, 50, stdin); break;
				case '5': cout << "New book language: "; fscanf(stdin, " "); fgets(book.language, 50, stdin); break;
				case '6': cout << "New year of publication: "; cin >> book.year_of_publication; break;
				case '7': cout << "New number of pages: "; cin >> book.number_of_pages; break;
				case '8': cout << "New book weight: "; cin >> book.weight; break;
				case '9': cout << "New book circulation: "; cin >> book.count; break;
				case '0': cout << "New book price: "; cin >> book.price; break;
			}
			cout << "\nChange another setting? (Y - Change / Any other key - Do not change):\n\n";
			question = _getch();
			if(question == 'Y' || question == 'y') {
				cout << "Select an option to change: \n";
				cout << "1 - Title\t\t\t2 - Author\n";
				cout << "3 - Edition\t\t\t4 - Genre\n";
				cout << "5 - Language\t\t\t6 - Year of publication\n";
				cout << "7 - Number of pages\t\t8 - Weight(gram)\n";
				cout << "9 - Circulation\t\t\t0 - Price\n";
				cout << "* - Back to search\n\n";
			}
			else {
				break;
			}
		}
		if(question == '*') {
			return 0;
		}
	} while(1);

	fseek(local_database, position, 0);
	fwrite(&book, sizeof(book), 1, local_database);
	return 0;
}


int delete_book(FILE* local_database, Book book, int position) {
	fseek(local_database, 0, 0);
	int count = 0;
	while(!feof(local_database)) {
		fread(&book, sizeof(book), 1, local_database);
		if(position != ftell(local_database)) {
			count++;
		}
	}
	fseek(local_database, 0, 2);
	int end_point = ftell(local_database);
	if(end_point == position) {
		count++;
	}

	Book* books = new Book[count];

	fseek(local_database, 0, 0);
	count = 0;
	while(!feof(local_database)) {
		fread(&book, sizeof(book), 1, local_database);
		if(position != ftell(local_database)) {
			books[count] = book;
			count++;
		}
	}
	fseek(local_database, 0, 2);
	end_point = ftell(local_database);
	if(end_point == position) {
		count++;
	}
	fclose(local_database);
	local_database = fopen(file_name, "wb+");
	for(int i = 0; i < count - 1; i++) {
		fwrite(&books[i], sizeof(books[i]), 1, local_database);
	}

	return 0;
}


int sort_block(Book* books, int* indexes, int j_index) {
	temp_for_index = indexes[j_index];
	indexes[j_index] = indexes[j_index + 1];
	indexes[j_index + 1] = temp_for_index;

	strcpy(temp_for_title, books[j_index].title);
	strcpy(books[j_index].title, books[j_index + 1].title);
	strcpy(books[j_index + 1].title, temp_for_title);

	strcpy(temp_for_author, books[j_index].author);
	strcpy(books[j_index].author, books[j_index + 1].author);
	strcpy(books[j_index + 1].author, temp_for_author);

	strcpy(temp_for_edition, books[j_index].edition);
	strcpy(books[j_index].edition, books[j_index + 1].edition);
	strcpy(books[j_index + 1].edition, temp_for_edition);

	strcpy(temp_for_genre, books[j_index].genre);
	strcpy(books[j_index].genre, books[j_index + 1].genre);
	strcpy(books[j_index + 1].genre, temp_for_genre);

	strcpy(temp_for_language, books[j_index].language);
	strcpy(books[j_index].language, books[j_index + 1].language);
	strcpy(books[j_index + 1].language, temp_for_language);

	temp_for_year_of_publication = books[j_index].year_of_publication;
	books[j_index].year_of_publication = books[j_index + 1].year_of_publication;
	books[j_index + 1].year_of_publication = temp_for_year_of_publication;

	temp_for_number_of_pages = books[j_index].number_of_pages;
	books[j_index].number_of_pages = books[j_index + 1].number_of_pages;
	books[j_index + 1].number_of_pages = temp_for_number_of_pages;

	temp_for_weight = books[j_index].weight;
	books[j_index].weight = books[j_index + 1].weight;
	books[j_index + 1].weight = temp_for_weight;

	temp_for_count = books[j_index].count;
	books[j_index].count = books[j_index + 1].count;
	books[j_index + 1].count = temp_for_count;

	temp_for_price = books[j_index].price;
	books[j_index].price = books[j_index + 1].price;
	books[j_index + 1].price = temp_for_price;

	return 0;
}


int search_book_with_parameter(FILE* local_database, char question, int parameter) {
	if(question == '1' || question == '2' || question == '3' || question == '4' || question == '5') {
		char static_q = question;
		char value[50], input_string[50];
		Book book;
		int counter = 0, r, position;
		cout << "Enter to search: "; fscanf(stdin, " "); fgets(value, 50, stdin);
		fseek(local_database, 0, 0);
		while(!feof(local_database)) {
			position = ftell(local_database);
			r = fread(&book, sizeof(book), 1, local_database);
			if(r < 1) {
				break;
			}
			switch(static_q) {
				case '1': strcpy(input_string, book.title); break;
				case '2': strcpy(input_string, book.author); break;
				case '3': strcpy(input_string, book.edition); break;
				case '4': strcpy(input_string, book.genre); break;
				case '5': strcpy(input_string, book.language); break;
			}
			if(strcmp(value, input_string) == 0) {
				print_book(book);
				counter++;
				if(parameter == 1) {
					cout << "Change data? (Y - Change / Any other key - Skip)\n\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						change_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n\n";
					}
				}
				else if(parameter == 2) {
					cout << "Delete item? (Y - Delete / Any other key - Skip)\n\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						position = ftell(local_database);
						delete_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n\n";
					}
				}
			}
		}
		if(counter == 0) {
			cout << "\nNO such book was found.\n\n";
			cout << "Which of the parameters to search for a book ?:\n";
			cout << "1 - By title\t\t\t2 - By the author\n";
			cout << "3 - By edition\t\t4 - By genre\n";
			cout << "5 - By language\t\t\t6 - By year of publication\n";
			cout << "7 - By number of pages\t8 - By weight\n";
			cout << "9 - By circulation\t\t\t0 - By the price\n";
			cout << "* - Exit to the main menu\n";
		}
		else {
			cout << "It was found " << counter << " books\n\n";
			cout << "Which of the parameters to search for a book ?:\n";
			cout << "1 - By title\t\t\t2 - By the author\n";
			cout << "3 - By edition\t\t4 - By genre\n";
			cout << "5 - By language\t\t\t6 - By year of publication\n";
			cout << "7 - By number of pages\t8 - By weight\n";
			cout << "9 - By circulation\t\t\t0 - By the price\n";
			cout << "* - Exit to the main menu\n";
		}
	}
	if(question == '6' || question == '7' || question == '8' || question == '9' || question == '0') {
		char static_q = question;
		int value, input_number;
		Book book;
		int counter = 0, r, position;
		cout << "Enter to search: "; cin >> value;
		fseek(local_database, 0, 0);
		while(!feof(local_database)) {
			position = ftell(local_database);
			r = fread(&book, sizeof(book), 1, local_database);
			if(r < 1) {
				break;
			}
			switch(static_q) {
				case '6': input_number = book.year_of_publication; break;
				case '7': input_number = book.number_of_pages; break;
				case '8': input_number = book.weight; break;
				case '9': input_number = book.count; break;
				case '0': input_number = book.price; break;
			}
			if(value == input_number) {
				print_book(book);
				counter++;
				if(parameter == 1) {
					cout << "Change data? (Y - Change / Any other key - Skip)\n\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						change_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n\n";
					}
				}
				else if(parameter == 2) {
					cout << "Delete item? (Y - Delete / Any other key - Skip)\n\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						position = ftell(local_database);
						delete_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n\n";
					}
				}
			}
		}
		if(counter == 0) {
			cout << "\nNO such book was found.\n\n";
			cout << "Which of the parameters to search for a book ?:\n";
			cout << "1 - By title\t\t\t2 - By the author\n";
			cout << "3 - By edition\t\t4 - By genre\n";
			cout << "5 - By language\t\t\t6 - By year of publication\n";
			cout << "7 - By number of pages\t8 - By weight\n";
			cout << "9 - By circulation\t\t\t0 - By the price\n";
			cout << "* - Exit to the main menu\n";
		}
		else {
			cout << "It was found " << counter << " books\n\n";
			cout << "Which of the parameters to search for a book ?:\n";
			cout << "1 - By title\t\t\t2 - By the author\n";
			cout << "3 - By edition\t\t4 - By genre\n";
			cout << "5 - By language\t\t\t6 - By year of publication\n";
			cout << "7 - By number of pages\t8 - By weight\n";
			cout << "9 - By circulation\t\t\t0 - By the price\n";
			cout << "* - Exit to the main menu\n";
		}
	}
	return 0;
}

int search_book_with_few_parameters(FILE* local_database, char question, int parameter) {
	if(question == '1' || question == '2' || question == '4') {
		char static_q = question;
		char value_1[50], value_2[50], input_string_1[50], input_string_2[50];
		Book book;
		int counter = 0, r, position;
		cout << "Enter the first parameter to search: "; fscanf(stdin, " "); fgets(value_1, 50, stdin);
		cout << "Enter the second parameter to search: "; fscanf(stdin, " "); fgets(value_2, 50, stdin);
		fseek(local_database, 0, 0);
		while(!feof(local_database)) {
			position = ftell(local_database);
			r = fread(&book, sizeof(book), 1, local_database);
			if(r < 1) {
				break;
			}
			switch(static_q) {
				case '1': strcpy(input_string_1, book.title); strcpy(input_string_2, book.author); break;
				case '2': strcpy(input_string_1, book.title); strcpy(input_string_2, book.edition); break;
				case '4': strcpy(input_string_1, book.genre); strcpy(input_string_2, book.language); break;
			}
			if((strcmp(value_1, input_string_1) == 0) && (strcmp(value_2, input_string_2) == 0)) {
				print_book(book);
				counter++;
				if(parameter == 1) {
					cout << "Change data? (Y/N)\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						change_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n";
					}
				}
				else if(parameter == 2) {
					cout << "Delete item? (Y/N)\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						position = ftell(local_database);
						delete_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n";
					}
				}
			}
		}
		if(counter == 0) {
			cout << "\nNO such book was found\n" << endl;
			cout << "Select a search mode by several options:\n";
			cout << "1 - By title and author\n";
			cout << "2 - By title and edition\n";
			cout << "3 - By title and price\n";
			cout << "4 - By genre and language\n";
			cout << "* - Exit to the main menu\n";
		}
		else {
			cout << "It was found " << counter << " books\n\n";
			cout << "Select a search mode by several options:\n";
			cout << "1 - By title and author\n";
			cout << "2 - By title and edition\n";
			cout << "3 - By title and price\n";
			cout << "4 - By genre and language\n";
			cout << "* - Exit to the main menu\n";
		}
	}

	if(question == '3') {
		char value_1[50], input_string[50];
		int value_2, input_number;
		Book book;
		int counter = 0, r, position;
		cout << "Enter the first parameter to search: "; fscanf(stdin, " "); fgets(value_1, 50, stdin);
		cout << "Enter the second parameter to search: "; cin >> value_2;
		fseek(local_database, 0, 0);
		while(!feof(local_database)) {
			position = ftell(local_database);
			r = fread(&book, sizeof(book), 1, local_database);
			if(r < 1) {
				break;
			}

			strcpy(input_string, book.title);
			input_number = book.price;

			if((strcmp(value_1, input_string) == 0) && (value_2 == input_number)) {
				print_book(book);
				counter++;
				if(parameter == 1) {
					cout << "Change data? (Y/N)\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						change_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n";
					}
				}
				else if(parameter == 2) {
					cout << "Delete item? (Y/N)\n";
					question = _getch();
					if(question == 'Y' || question == 'y') {
						position = ftell(local_database);
						delete_book(local_database, book, position);
						break;
					}
					else {
						cout << "Item skipped.\n";
					}
				}
			}
		}
		if(counter == 0) {
			cout << "\nNO such book was found\n" << endl;
			cout << "Select a search mode by several options:\n";
			cout << "1 - By title and author\n";
			cout << "2 - By title and edition\n";
			cout << "3 - By title and price\n";
			cout << "4 - By genre and language\n";
			cout << "* - Exit to the main menu\n";
		}
		else {
			cout << "It was found " << counter << " books\n\n";
			cout << "Select a search mode by several options:\n";
			cout << "1 - By title and author\n";
			cout << "2 - By title and edition\n";
			cout << "3 - By title and price\n";
			cout << "4 - By genre and language\n";
			cout << "* - Exit to the main menu\n";
		}
	}

	return 0;
}
