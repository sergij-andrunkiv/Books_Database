#include "config.h"

int calculate_total_value(FILE* local_database) {
	cout << "Specify the value to find its total number: \n";
	cout << "1 - Number of pages\n";
	cout << "2 - Weight\n";
	cout << "3 - Circulation\n";
	cout << "4 - Price\n\n";

	do {
		question = _getch();
		if(question == '1' || question == '2' || question == '3' || question == '4') {
			break;
		}
	} while(1);

	Book book;
	int total_value = 0, r;
	fseek(local_database, 0, 0);
	while(!feof(local_database)) {
		r = fread(&book, sizeof(book), 1, local_database);
		if(r < 1) {
			break;
		}
		switch(question) {
			case '1': total_value += book.number_of_pages; break;
			case '2': total_value += book.weight; break;
			case '3': total_value += book.count; break;
			case '4': total_value += book.price; break;
		}
	}
	switch(question) {
		case '1': cout << "Total number of pages in all books: " << total_value << endl << endl; break;
		case '2': cout << "Total weight of all books: " << total_value << endl << endl; break;
		case '3': cout << "Total circulation of all books: " << total_value << endl << endl; break;
		case '4': cout << "Total price of all books: " << total_value << endl << endl; break;
	}

	return 0;
}


int view_count_books_for_a_given_value(FILE* local_database) {
	cout << "Select a value to enter to find the number of books that contain this value: \n";
	cout << "1 - Title\t\t\t2 - Author\n";
	cout << "3 - Edition\t\t\t4 - Genre\n";
	cout << "5 - Language\t\t\t6 - Year of publication\n";
	cout << "7 - Number of pages\t\t8 - Weight\n";
	cout << "9 - Circulation\t\t\t0 - Price\n\n";

	do {
		question = _getch();
		if(question == '1' || question == '2' || question == '3' || question == '4' || question == '5') {
			char static_q = question;
			char value[50], input_string[50];
			cout << "Enter to search: "; fscanf(stdin, " "); fgets(value, 50, stdin);
			Book book;
			int counter = 0, r;
			fseek(local_database, 0, 0);
			while(!feof(local_database)) {
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
					counter++;
				}
			}
			cout << "Number of books for a given parameter: " << counter << " pcs." << endl << endl;
			return 0;
		}
		if(question == '6' || question == '7' || question == '8' || question == '9' || question == '0') {
			char static_q = question;
			int value, input_number;
			cout << "Enter to search: "; cin >> value;
			Book book;
			int counter = 0, r;
			fseek(local_database, 0, 0);
			while(!feof(local_database)) {
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
					counter++;
				}
			}
			cout << "Number of books for a given parameter: " << counter << " pcs." << endl << endl;
			return 0;
		}
	} while(1);
}


int view_books_with_max_value(FILE* local_database) {
	cout << "Specify the value to find the book with the largest value of this value: \n";
	cout << "1 - Year of publication\n";
	cout << "2 - Number of pages\n";
	cout << "3 - Weight\n";
	cout << "4 - Circulation\n";
	cout << "5 - Price\n\n";

	do {
		question = _getch();
		if(question == '1' || question == '2' || question == '3' || question == '4' || question == '5') {
			break;
		}
	} while(1);

	Book book;
	char static_q = question;
	int max_value = 0, r, counter = 0;
	fseek(local_database, 0, 2);
	int end_point = ftell(local_database);

	fseek(local_database, 0, 0);
	while(!feof(local_database)) {
		r = fread(&book, sizeof(book), 1, local_database);
		if(r < 1) {
			break;
		}
		switch(static_q) {
			case '1': if(max_value < book.year_of_publication) max_value = book.year_of_publication; break;
			case '2': if(max_value < book.number_of_pages) max_value = book.number_of_pages; break;
			case '3': if(max_value < book.weight) max_value = book.weight; break;
			case '4': if(max_value < book.count) max_value = book.count; break;
			case '5': if(max_value < book.price) max_value = book.price; break;
		}
	}
	switch(static_q) {
		case '1': cout << "Books with the greatest value of the year of publication " << max_value << ":" << endl; break;
		case '2': cout << "Books with the most pages " << max_value << ":" << endl; break;
		case '3': cout << "Books with the most weight " << max_value << " gram:" << endl; break;
		case '4': cout << "Books with the largest circulation " << max_value << ":" << endl; break;
		case '5': cout << "Books with the highest price " << max_value << " UAH:" << endl; break;
	}
	fseek(local_database, 0, 0);
	while(!feof(local_database)) {
		fread(&book, sizeof(book), 1, local_database);
		switch(static_q) {
			case '1': if(max_value == book.year_of_publication) { print_book(book); counter++; } break;
			case '2': if(max_value == book.number_of_pages) { print_book(book); counter++; } break;
			case '3': if(max_value == book.weight) { print_book(book); counter++; } break;
			case '4': if(max_value == book.count) { print_book(book); counter++; } break;
			case '5': if(max_value == book.price) { print_book(book); counter++; } break;
		}
		if(end_point == ftell(local_database)) {
			break;
		}
	}
	switch(static_q) {
		case '1': cout << "It was found " << counter << " books with the greatest value of the year of publication: " << max_value << endl << endl; break;
		case '2': cout << "It was found " << counter << " books with the most pages: " << max_value << endl << endl; break;
		case '3': cout << "It was found " << counter << " books with the most weight: " << max_value << endl << endl; break;
		case '4': cout << "It was found " << counter << " books with the largest circulation: " << max_value << endl << endl; break;
		case '5': cout << "It was found " << counter << " books with the highest price: " << max_value << endl << endl; break;
	}
	return 0;

}


int view_books_with_min_value(FILE* local_database) {
	cout << "Specify the value to find the book with the smallest value of this value: \n";
	cout << "1 - Year of publication\n";
	cout << "2 - Number of pages\n";
	cout << "3 - Weight\n";
	cout << "4 - Circulation\n";
	cout << "5 - Price\n\n";

	do {
		question = _getch();
		if(question == '1' || question == '2' || question == '3' || question == '4' || question == '5') {
			break;
		}
	} while(1);

	Book book;
	char static_q = question;
	int min_value;
	fseek(local_database, 0, 2);
	int end_point = ftell(local_database);

	fseek(local_database, 0, 0);
	while(!feof(local_database)) {
		fread(&book, sizeof(book), 1, local_database);
		switch(static_q) {
			case '1': min_value = book.year_of_publication; break;
			case '2': min_value = book.number_of_pages; break;
			case '3': min_value = book.weight; break;
			case '4': min_value = book.count; break;
			case '5': min_value = book.price; break;
		}
	}

	int r, counter = 0;

	fseek(local_database, 0, 0);
	while(!feof(local_database)) {
		r = fread(&book, sizeof(book), 1, local_database);
		if(r < 1) {
			break;
		}
		switch(static_q) {
			case '1': if(min_value > book.year_of_publication) min_value = book.year_of_publication; break;
			case '2': if(min_value > book.number_of_pages) min_value = book.number_of_pages; break;
			case '3': if(min_value > book.weight) min_value = book.weight; break;
			case '4': if(min_value > book.count) min_value = book.count; break;
			case '5': if(min_value > book.price) min_value = book.price; break;
		}
	}
	switch(static_q) {
		case '1': cout << "Books with the lowest value of the year of publication " << min_value << ":" << endl; break;
		case '2': cout << "Books with the fewest pages  " << min_value << ":" << endl; break;
		case '3': cout << "Books with the least weight " << min_value << ":" << endl; break;
		case '4': cout << "Books with the lowest circulation " << min_value << ":" << endl; break;
		case '5': cout << "Books with the lowest price " << min_value << ":" << endl; break;
	}
	fseek(local_database, 0, 0);
	while(!feof(local_database)) {
		fread(&book, sizeof(book), 1, local_database);
		switch(static_q) {
			case '1': if(min_value == book.year_of_publication) { print_book(book); counter++; } break;
			case '2': if(min_value == book.number_of_pages) { print_book(book); counter++; } break;
			case '3': if(min_value == book.weight) { print_book(book); counter++; } break;
			case '4': if(min_value == book.count) { print_book(book); counter++; } break;
			case '5': if(min_value == book.price) { print_book(book); counter++; } break;
		}
		if(end_point == ftell(local_database)) {
			break;
		}
	}
	switch(static_q) {
		case '1': cout << "It was found " << counter << " books with the lowest value of the year of publication: " << min_value << endl << endl; break;
		case '2': cout << "It was found " << counter << " books with the fewest pages: " << min_value << endl << endl; break;
		case '3': cout << "It was found " << counter << " books with the least weight: " << min_value << endl << endl; break;
		case '4': cout << "It was found " << counter << " books with the lowest circulation: " << min_value << endl << endl; break;
		case '5': cout << "It was found " << counter << " books with the lowest price: " << min_value << endl << endl; break;
	}

	return 0;
}