
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define MAX_USERS 50
#define MAX_TITLE 100
#define MAX_AUTHOR 100
#define MAX_GENRE 50
#define MAX_NAME 50
#define MAX_PASSWORD 20
#define BOOK_FILE "library.txt"
#define USER_FILE "users.txt"

// Struct to represent a book
typedef struct {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    char genre[MAX_GENRE];
    int available; // 1 for available, 0 for issued
} Book;

// Struct to represent a user
typedef struct {
    char username[MAX_NAME];
    char password[MAX_PASSWORD];
    char role[10]; // "admin" or "user"
} User;

// Global variables
Book library[MAX_BOOKS];
int totalBooks = 0;
User users[MAX_USERS];
int totalUsers = 0;

// Function prototypes
void loadBooksFromFile();
void saveBooksToFile();
void loadUsersFromFile();
void saveUsersToFile();
int login();
void registerUser();
void mainMenu(char *role);
void addBook();
void viewBooks();
void issueBook();
void returnBook();
void searchBook();
void deleteBook();
void sortBooksByGenre();
void sortBooksByID();
void calculateDueDate(int bookID);

// Main function
int main() {
    loadBooksFromFile();
    loadUsersFromFile();

    printf("\n--- Welcome to the Library Management System ---\n");
    int choice;

    while (1) {
        printf("\n1. Login\n2. Register\n3. Exit\nEnter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        switch (choice) {
            case 1:
                if (login()) return 0;
                break;
            case 2:
                registerUser();
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                saveBooksToFile();
                saveUsersToFile();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to load books from file
void loadBooksFromFile() {
    FILE *file = fopen(BOOK_FILE, "r");
    if (!file) {
        printf("No library data found. Starting fresh.\n");
        return;
    }

    totalBooks = 0; // Reset book count before loading
    while (fscanf(file, "%d;%99[^;];%99[^;];%49[^;];%d\n",
                  &library[totalBooks].id,
                  library[totalBooks].title,
                  library[totalBooks].author,
                  library[totalBooks].genre,
                  &library[totalBooks].available) == 5) {
        totalBooks++;
    }

    fclose(file);
    printf("%d books loaded successfully from '%s'.\n", totalBooks, BOOK_FILE);
}


// Function to save books to file
void saveBooksToFile() {
    FILE *file = fopen(BOOK_FILE, "w");
    if (!file) {
        printf("Error: Unable to save library data.\n");
        return;
    }

    for (int i = 0; i < totalBooks; i++) {
        fprintf(file, "%d;%s;%s;%s;%d\n",
                library[i].id,
                library[i].title,
                library[i].author,
                library[i].genre,
                library[i].available);
    }
    fclose(file);
}

// Function to load users from file
void loadUsersFromFile() {
    FILE *file = fopen(USER_FILE, "r");
    if (!file) {
        printf("No user data found. Starting fresh.\n");
        return;
    }

    while (fscanf(file, "%49[^;];%19[^;];%9[^\n]\n",
                  users[totalUsers].username,
                  users[totalUsers].password,
                  users[totalUsers].role) == 3) {
        totalUsers++;
    }
    fclose(file);
}

// Function to save users to file
void saveUsersToFile() {
    FILE *file = fopen(USER_FILE, "w");
    if (!file) {
        printf("Error: Unable to save user data.\n");
        return;
    }

    for (int i = 0; i < totalUsers; i++) {
        fprintf(file, "%s;%s;%s\n",
                users[i].username,
                users[i].password,
                users[i].role);
    }
    fclose(file);
}

// Function for user login
int login() {
    char username[MAX_NAME], password[MAX_PASSWORD];
    getchar(); // Clear buffer
    printf("Enter username: ");
    fgets(username, MAX_NAME, stdin);
    username[strcspn(username, "\n")] = 0; // Remove newline

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD, stdin);
    password[strcspn(password, "\n")] = 0; // Remove newline

    for (int i = 0; i < totalUsers; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Login successful! Welcome, %s.\n", username);
            mainMenu(users[i].role);
            return 0;
        }
    }
    printf("Invalid credentials. Please try again.\n");
    return 0;
}

// Function to register a new user
void registerUser() {
    if (totalUsers >= MAX_USERS) {
        printf("User limit reached. Cannot register more users.\n");
        return;
    }

    User newUser;
    getchar(); // Clear buffer
    printf("Enter a username: ");
    fgets(newUser.username, MAX_NAME, stdin);
    newUser.username[strcspn(newUser.username, "\n")] = 0; // Remove newline

    printf("Enter a password: ");
    fgets(newUser.password, MAX_PASSWORD, stdin);
    newUser.password[strcspn(newUser.password, "\n")] = 0; // Remove newline

    printf("Enter role (admin/user): ");
    fgets(newUser.role, 10, stdin);
    newUser.role[strcspn(newUser.role, "\n")] = 0; // Remove newline

    users[totalUsers] = newUser;
    totalUsers++;
    saveUsersToFile(); // Save users immediately
    printf("User registered successfully!\n");
}

// Function to display the main menu
void mainMenu(char *role) {
    int choice;
    while (1) {
        printf("\n--- Library Management System (%s) ---\n", role);
        printf("1. Add Book\n");
        printf("2. View Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Search Book\n");
        printf("6. Delete Book\n");
        printf("7. Sort Books by Genre\n");
        printf("8. Sort Books by ID\n");
        printf("9. Logout\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear invalid input
            continue;
        }

        if (strcmp(role, "user") == 0 && (choice == 1 || choice == 6)) {
            printf("Permission denied. Only admins can perform this action.\n");
            continue;
        }

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                issueBook();
                break;
            case 4:
                returnBook();
                break;
            case 5:
                searchBook();
                break;
            case 6:
                deleteBook();
                break;
            case 7:
                sortBooksByGenre();
                break;
            case 8:
                sortBooksByID();
                break;
            case 9:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to add a book
void addBook() {
    if (totalBooks >= MAX_BOOKS) {
        printf("Library is full. Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.id = totalBooks + 1; // Auto-increment ID
    getchar(); // Clear buffer
    printf("Enter the title: ");
    fgets(newBook.title, MAX_TITLE, stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0; // Remove newline

    printf("Enter the author: ");
    fgets(newBook.author, MAX_AUTHOR, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0; // Remove newline

    printf("Enter the genre: ");
    fgets(newBook.genre, MAX_GENRE, stdin);
    newBook.genre[strcspn(newBook.genre, "\n")] = 0; // Remove newline

    newBook.available = 1; // Mark as available
    library[totalBooks++] = newBook;
    saveBooksToFile();
    printf("Book added successfully!\n");
}

// Function to view books
void viewBooks() {
    printf("\n--- Book List ---\n");
    if (totalBooks == 0) {
        printf("No books are currently in the library.\n");
        return;
    }
    for (int i = 0; i < totalBooks; i++) {
        printf("ID: %d, Title: %s, Author: %s, Genre: %s, Available: %s\n",
               library[i].id,
               library[i].title,
               library[i].author,
               library[i].genre,
               library[i].available ? "Yes" : "No");
    }
}

// Function to issue a book
void issueBook() {
    int id;
    printf("Enter book ID to issue: ");
        if (scanf("%d", &id) != 1 || id < 1 || id > totalBooks) {
        printf("Invalid Book ID.\n");
        while (getchar() != '\n'); // Clear invalid input
        return;
    }

    if (!library[id - 1].available) {
        printf("Book already issued.\n");
        return;
    }

    library[id - 1].available = 0;
    printf("Book issued successfully!\n");
    calculateDueDate(id - 1); // Display the due date

    saveBooksToFile(); // Save changes immediately
}

// Function to calculate and display the due date
void calculateDueDate(int bookID) {
    time_t now = time(NULL);
    struct tm dueDate = *localtime(&now);
    dueDate.tm_mday += 7; // Add 7 days to the current date
    mktime(&dueDate); // Normalize the time structure

    printf("The due date for returning the book '%s' is: %02d-%02d-%04d\n",
           library[bookID].title,
           dueDate.tm_mday,
           dueDate.tm_mon + 1,
           dueDate.tm_year + 1900);
}


// Function to return a book
void returnBook() {
    int bookID;
    printf("Enter book ID to return: ");
    if (scanf("%d", &bookID) != 1) {
        printf("Invalid input. Please enter a valid book ID.\n");
        return;
    }

    if (bookID <= 0 || bookID > totalBooks) {
        printf("Invalid book ID.\n");
        return;
    }

    if (library[bookID - 1].available == 1) {
        printf("This book was not issued.\n");
        return;
    }

    library[bookID - 1].available = 1; // Mark as available
    printf("Book '%s' has been returned.\n", library[bookID - 1].title);
}

// Function to search for a book by title or author
void searchBook() {
    char searchTerm[MAX_TITLE];
    getchar(); // Clear buffer
    printf("Enter title or author to search: ");
    fgets(searchTerm, MAX_TITLE, stdin);
    searchTerm[strcspn(searchTerm, "\n")] = 0; // Remove newline

    printf("\n--- Search Results ---\n");
    int found = 0;
    for (int i = 0; i < totalBooks; i++) {
        if (strstr(library[i].title, searchTerm) || strstr(library[i].author, searchTerm)) {
            printf("ID: %d, Title: %s, Author: %s, Genre: %s, Available: %s\n",
                   library[i].id,
                   library[i].title,
                   library[i].author,
                   library[i].genre,
                   library[i].available ? "Yes" : "No");
            found = 1;
        }
    }
    if (!found) {
        printf("No books found matching the search term.\n");
    }
}

// Function to delete a book
void deleteBook() {
    int bookID;
    printf("Enter book ID to delete: ");
    if (scanf("%d", &bookID) != 1) {
        printf("Invalid input. Please enter a valid book ID.\n");
        return;
    }

    if (bookID <= 0 || bookID > totalBooks) {
        printf("Invalid book ID.\n");
        return;
    }

    for (int i = bookID - 1; i < totalBooks - 1; i++) {
        library[i] = library[i + 1]; // Shift books to delete the one at bookID
    }
    totalBooks--;
    saveBooksToFile();
    printf("Book deleted successfully.\n");
}

// Function to sort books by genre
void sortBooksByGenre() {
    for (int i = 0; i < totalBooks - 1; i++) {
        for (int j = i + 1; j < totalBooks; j++) {
            if (strcmp(library[i].genre, library[j].genre) > 0) {
                // Swap books[i] and books[j]
                Book temp = library[i];
                library[i] = library[j];
                library[j] = temp;
            }
        }
    }
    printf("Books sorted by genre.\n");
}


// Function to sort books by ID
void sortBooksByID() {
    for (int i = 0; i < totalBooks - 1; i++) {
        for (int j = 0; j < totalBooks - i - 1; j++) {
            if (library[j].id > library[j + 1].id) {
                // Swap library[j] and library[j + 1]
                Book temp = library[j];
                library[j] = library[j + 1];
                library[j + 1] = temp;
            }
        }
    }
    printf("Books sorted by ID.\n");
}

