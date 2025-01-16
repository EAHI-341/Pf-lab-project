#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_BOOKS = 200;         
const int MAX_TITLE_LENGTH = 100;  


int bookIDs[MAX_BOOKS];
string titles[MAX_BOOKS];
string authors[MAX_BOOKS];
int quantities[MAX_BOOKS];
int totalBooks = 0; 


void displayMenu();
void addBook();
void searchBook();
void displayAllBooks();
void updateBook();
void saveBooksToFile();
void loadBooksFromFile();
bool isBookIDExists(int id);
int getBookIndexByID(int id);
void displayBook(int index);
void deleteBook();


int main() {
    loadBooksFromFile();
    int choice;
    
   
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: 
                addBook();
                break;
            case 2: 
                searchBook();
                break;
            case 3: 
                displayAllBooks();
                break;
            case 4: 
                updateBook();
                break;
            case 5: 
                deleteBook();
                break;
            case 6: 
                saveBooksToFile();
                cout << "Books saved successfully!" << endl;
                break;
            case 7: 
                cout << "Exiting Library Management System. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7); 

    return 0;
}


void displayMenu() {
    cout << "\n--- Library Management System ---\n";
    cout << "1. Add a New Book\n";
    cout << "2. Search for a Book\n";
    cout << "3. Display All Books\n";
    cout << "4. Update Book Information\n";
    cout << "5. Delete a Book\n";
    cout << "6. Save Books to File\n";
    cout << "7. Exit\n";
}


void loadBooksFromFile() {
    ifstream file("library_books.txt");

    if (!file) {
        cout << "No previous data found. Starting fresh.\n";
        return;
    }

    while (file >> bookIDs[totalBooks]) {
        file.ignore();
        getline(file, titles[totalBooks]);
        getline(file, authors[totalBooks]);
        file >> quantities[totalBooks];
        totalBooks++;

        if (totalBooks >= MAX_BOOKS) {
            cout << "Book limit reached. Cannot load more books.\n";
            break;
        }
    }
    file.close();
    cout << "Books loaded from file successfully!\n";
}


void saveBooksToFile() {
    ofstream file("library_books.txt");

    for (int i = 0; i < totalBooks; ++i) {
        file << bookIDs[i] << "\n";
        file << titles[i] << "\n";
        file << authors[i] << "\n";
        file << quantities[i] << "\n";
    }

    file.close();
}


void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        cout << "Cannot add more books, library is full!\n";
        return;
    }

    int bookID;
    cout << "Enter Book ID: ";
    cin >> bookID;

    if (isBookIDExists(bookID)) {
        cout << "A book with this ID already exists. Try a different ID.\n";
        return;
    }

    cin.ignore(); 
    cout << "Enter Book Title: ";
    getline(cin, titles[totalBooks]);

    cout << "Enter Book Author: ";
    getline(cin, authors[totalBooks]);

    cout << "Enter Book Quantity: ";
    cin >> quantities[totalBooks];

    bookIDs[totalBooks] = bookID;
    totalBooks++;

    cout << "Book added successfully!\n";
}


bool isBookIDExists(int bookID) {
    for (int i = 0; i < totalBooks; ++i) {
        if (bookIDs[i] == bookID) {
            return true;
        }
    }
    return false;
}


void searchBook() {
    cin.ignore();
    cout << "Enter Book ID or Title to search: ";
    string query;
    getline(cin, query);

    bool found = false;
    for (int i = 0; i < totalBooks; ++i) {
      
        if (to_string(bookIDs[i]) == query || titles[i] == query) {
            displayBook(i);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "No book found with the given ID or Title.\n";
    }
}


void displayBook(int index) {
    cout << "\n--- Book Found ---\n";
    cout << "Book ID: " << bookIDs[index] << endl;
    cout << "Title: " << titles[index] << endl;
    cout << "Author: " << authors[index] << endl;
    cout << "Quantity: " << quantities[index] << endl;
    cout << "-----------------------\n";
}


void displayAllBooks() {
    if (totalBooks == 0) {
        cout << "No books to display.\n";
        return;
    }

    cout << "\n--- Displaying All Books ---\n";
    for (int i = 0; i < totalBooks; ++i) {
        displayBook(i);
    }
}


void updateBook() {
    int id;
    cout << "Enter the Book ID to update: ";
    cin >> id;

    int index = getBookIndexByID(id);
    if (index == -1) {
        cout << "No book found with the provided ID.\n";
        return;
    }

    cout << "Updating details for Book ID: " << id << endl;

    cin.ignore(); 
    cout << "Enter new Title: ";
    getline(cin, titles[index]);

    cout << "Enter new Author: ";
    getline(cin, authors[index]);

    cout << "Enter new Quantity: ";
    cin >> quantities[index];

    cout << "Book details updated successfully!\n";
}


int getBookIndexByID(int id) {
    for (int i = 0; i < totalBooks; ++i) {
        if (bookIDs[i] == id) {
            return i;
        }
    }
    return -1;
}
void deleteBook() {
    int id;
    cout << "Enter the Book ID to delete: ";
    cin >> id;

    int index = getBookIndexByID(id);
    if (index == -1) {
        cout << "No book found with the provided ID.\n";
        return;
    }

    for (int i = index; i < totalBooks - 1; ++i) {
        bookIDs[i] = bookIDs[i + 1];
        titles[i] = titles[i + 1];
        authors[i] = authors[i + 1];
        quantities[i] = quantities[i + 1];
    }

    totalBooks--;
    cout << "Book deleted successfully!\n";
}