# Library Management System

## Overview
The **Library Management System (LMS)** is a command-line application built in C for managing books and user data in a library. It provides features for users to interact with the system, including registering, logging in, viewing books, issuing and returning books, searching, and sorting. The system uses file handling to store books and user information persistently.

## Key Features

### User Management
- **`login()`**: Allows users to log into the system.
- **`registerUser()`**: Enables users to register for an account.

### Book Management
- **`addBook()`**: Adds a new book to the library database.
- **`viewBooks()`**: Displays all books in the library.
- **`issueBook()`**: Issues a book to a registered user.
- **`returnBook()`**: Handles the return process for borrowed books.
- **`searchBook()`**: Searches for a book by title, author, or genre.
- **`deleteBook()`**: Deletes a book from the system.

### Book Sorting
- **`sortBooksByGenre()`**: Sorts books based on their genre.
- **`sortBooksByID()`**: Sorts books by their unique ID.

### Due Date Management
- **`calculateDueDate()`**: Calculates the due date for a borrowed book based on its ID.

### File Handling
- **`loadBooksFromFile()`**: Loads book data from a file into the system.
- **`saveBooksToFile()`**: Saves the current book data back to the file.
- **`loadUsersFromFile()`**: Loads user data from a file.
- **`saveUsersToFile()`**: Saves the current user data back to the file.

## Project Structure
The project contains the following files:

- **`screenshots/`**
  - Contains screenshots of the application's output, demonstrating various functionalities such as book management, user login, and file handling.

- **`src/`**
  - **`library.c`**: Implements book-related functionalities such as adding, deleting, and viewing books, as well as sorting and calculating due dates.
  - **`user.c`**: Manages user-related functionalities, including registration, login, and issuing books.

- **`docs/`**
  - **`LibraryManagementSystem_Presentation.pptx`**: PowerPoint presentation describing the project and its features.

- **`README.md`**: Project documentation (this file).

## Requirements
- A **C compiler** (e.g., GCC) to compile the source code.
- Operating system: **Linux, Windows, or macOS**.

## Installation and Usage

1. **Clone the Repository**
   ```bash
   git clone https://github.com/JayHire06/LibraryManagementSystem.git

## Team Members
- **Jay** (202452323)
- **Rashi** (20241142)
- **Tanmay** (202452334)
