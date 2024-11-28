#include <iostream>
#include <iomanip>
#include <string>
#include <fstream> // For file handling
#include <cstdlib> // For system("clear")
using namespace std;

// Node structure for singly linked list
struct Book {
    int id;
    string title;
    string author;
    Book* next; // Pointer to the next book
};

// Class to manage the book system
class BookManagementSystem {
private:
    Book* head; // Pointer to the first book in the list
    const string fileName = "books.txt"; // File name for storing book data

    // Save the current book list to a file
    void saveToFile() {
        ofstream outFile(fileName);
        Book* current = head;
        while (current != nullptr) {
            outFile << current->id << '\n' << current->title << '\n' << current->author << '\n';
            current = current->next;
        }
        outFile.close();
    }

public:
    // Constructor: Initialize and load data from file
    BookManagementSystem() : head(nullptr) {
        ifstream inFile(fileName);
        if (inFile) {
            int id;
            string title, author;
            while (inFile >> id) {
                inFile.ignore(); // Ignore leftover newline
                getline(inFile, title);
                getline(inFile, author);
                addBook(id, title, author, false); // Add without saving to avoid redundant writes
            }
        }
    }

    // Add a new book
    void addBook(int id, const string& title, const string& author, bool save = true) {
        Book* newBook = new Book{id, title, author, head};
        head = newBook; // Insert at the beginning
        if (save) {
            saveToFile(); // Save changes to file
            cout << "\n-------------------------------------------" << endl;
            cout << "     [SUCCESS] Book added successfully!     " << endl;
            cout << "-------------------------------------------" << endl;
        }
    }

    // Delete a book by ID
    void deleteBook(int id) {
        Book *current = head, *previous = nullptr;

        // Traverse the list to find the book
        while (current != nullptr && current->id != id) {
            previous = current;
            current = current->next;
        }

        // If the book is not found
        if (current == nullptr) {
            cout << "\n-------------------------------------------" << endl;
            cout << "  [ERROR] Book with ID " << id << " not found!" << endl;
            cout << "-------------------------------------------" << endl;
            return;
        }

        // Remove the book from the list
        if (previous == nullptr) {
            head = current->next; // Update head if the first book is removed
        } else {
            previous->next = current->next; // Skip the book to delete
        }

        delete current; // Free the memory
        saveToFile(); // Save changes to file
        cout << "\n-------------------------------------------" << endl;
        cout << "     Book deleted successfully!             " << endl;
        cout << "-------------------------------------------" << endl;
    }

    // Display all books
    void displayBooks() {
        if (head == nullptr) {
            cout << "\n-------------------------------------------" << endl;
            cout << "  [INFO] No books available in the system!" << endl;
            cout << "-------------------------------------------" << endl;
            return;
        }

        // Print table header
        cout << "\n===========================================" << endl;
        cout << "             List of Books                 " << endl;
        cout << "===========================================" << endl;
        cout << left << setw(10) << "Book ID" << setw(30) << "Title" << setw(30) << "Author" << endl;
        cout << string(70, '-') << endl;

        // Traverse the list and print book details
        Book* current = head;
        while (current != nullptr) {
            cout << left << setw(10) << current->id << setw(30) << current->title << setw(30) << current->author << endl;
            current = current->next;
        }
        cout << "-------------------------------------------" << endl;
    }

    // Search for a book by ID
    void searchBookByID(int id) {
        Book* current = head;
        while (current != nullptr) {
            if (current->id == id) {
                cout << "\n-------------------------------------------" << endl;
                cout << "Book Found:\n";
                cout << "Book ID: " << current->id << "\nTitle: " << current->title << "\nAuthor: " << current->author << endl;
                cout << "-------------------------------------------" << endl;
                return;
            }
            current = current->next;
        }
        cout << "\n-------------------------------------------" << endl;
        cout << "  [ERROR] Book with ID " << id << " not found!" << endl;
        cout << "-------------------------------------------" << endl;
    }

    // Count total books
    int countBooks() {
        int count = 0;
        Book* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    // Clear all books
    void clearAllBooks() {
        while (head != nullptr) {
            Book* temp = head;
            head = head->next;
            delete temp;
        }
        saveToFile(); // Save empty list to file
        cout << "\n-------------------------------------------" << endl;
        cout << "  All books have been cleared successfully!" << endl;
        cout << "-------------------------------------------" << endl;
    }

    // Destructor: Clean up memory
    ~BookManagementSystem() {
        clearAllBooks();
    }
};

// Function to display the main menu interface
void displayMenu() {
    system("clear"); // clear screen for fresh display
    cout << "\n===========================================" << endl;
    cout << "|       WELCOME TO BOOK MANAGEMENT       |" << endl;
    cout << "===========================================" << endl;
    cout << "| 1. Add Book                             |" << endl;
    cout << "| 2. Delete Book                          |" << endl;
    cout << "| 3. Display All Books                    |" << endl;
    cout << "| 4. Search Book by ID                    |" << endl;
    cout << "| 5. Count Total Books                    |" << endl;
    cout << "| 6. Clear All Books                      |" << endl;
    cout << "| 7. Exit                                 |" << endl;
    cout << "===========================================" << endl;
    cout << "\nEnter your choice (1-7): ";
}

// Function to add UI break for clarity
void addUIBreak() {
    cout << "\n-------------------------------------------\n" << endl;
}

// Main function
int main() {
    BookManagementSystem system;
    int choice;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                string title, author;
                addUIBreak();
                cout << "Enter Book Details:\n";
                cout << "Book ID: ";
                cin >> id;
                cin.ignore(); // Ignore leftover newline character
                cout << "Book Title: ";
                getline(cin, title);
                cout << "Author Name: ";
                getline(cin, author);
                system.addBook(id, title, author);
                break;
            }
            case 2: {
                int id;
                addUIBreak();
                cout << "Enter Book ID to delete: ";
                cin >> id;
                system.deleteBook(id);
                break;
            }
            case 3:
                addUIBreak();
                system.displayBooks();
                break;
            case 4: {
                int id;
                addUIBreak();
                cout << "Enter Book ID to search: ";
                cin >> id;
                system.searchBookByID(id);
                break;
            }
            case 5:
                addUIBreak();
                cout << "Total books in the system: " << system.countBooks() << endl;
                break;
            case 6:
                addUIBreak();
                system.clearAllBooks();
                break;
            case 7:
                cout << "\nGoodbye! Exiting the program." << endl;
                break;
            default:
                cout << "\n[ERROR] Invalid choice! Please try again." << endl;
        }

        addUIBreak();

    } while (choice != 7);

    return 0;
}
