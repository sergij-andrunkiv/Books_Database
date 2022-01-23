#include "config.h"

char file_name[30], question;

int main()
{
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   cout << "Enter a name for the new or existing file: ";
   cin >> file_name;
   FILE* database;
   if((database = fopen(file_name, "rb+")) == NULL) {
      if((database = fopen(file_name, "wb+")) == NULL) {
         cout << "Unknown file creation error.\n";
      }
      cout << "A new database file has been created with name: " << file_name << endl;
   }

   do {
      cout << "\n-----------------------------------------------------------------\n";
      cout << "LIST OF CHOICE OF OPERATING MODES\nChoose an action:\n";
      cout << "-----------------------------------------------------------------\n";
      cout << "1 - Add a book\n";
      cout << "2 - Find a book and print it\n";
      cout << "3 - Find a book and change the data\n";
      cout << "4 - Find a book and delete\n";
      cout << "5 - Display all books on the screen\n";
      cout << "6 - Sort books\n";
      cout << "7 - Perform calculations\n";
      cout << "8 - Open another database file\n";
      cout << "9 - Clear the current database\n";
      cout << "0 - Shut down the database processing program\n";
      cout << "-----------------------------------------------------------------\n\n";
      question = _getch();
      switch(question) {
         case '1': add_book(database); break;
         case '2': search_control(database, 0); break;
         case '3': search_control(database, 1); break;
         case '4': search_control(database, 2); break;
         case '5': print_all(database); break;
         case '6': sort_books(database); break;
         case '7': calculate(database); break;
         case '8': open_database(database); break;
         case '9': clear_all(database); break;
         case '0': cout << "\nThe program is completed\n"; return 0;
      }
   } while(1);
   fclose(database);

   system("pause");
   return 0;
}
