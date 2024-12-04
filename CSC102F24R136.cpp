#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>

using namespace std;

const int MAX_BOOKS = 100;
double totalSalesAmount = 0;
struct Book {
    string title;
    string author;
    double price;
    int stock;
};
void menu();
void adminOptions();
void userOptions();
void addbook(Book book[], int &bookCount);
void viewAllBooks(const Book book[], const int bookCount);
void editBook(Book book[], int bookCount);
void deleteBook(Book book[], int bookCount);
void generateReport(const Book book[], int bookCount);
void searchBook(const Book books[], int bookCount);
void salesEntry(Book books[], int bookCount);
void checkPrice(const Book books[], int bookCount);
void checkStock(const Book books[], int bookCount);
void saveBooks(const Book books[], int bookCount);
void savetotalSales();
void loadBooks(Book books[], int &bookCount);
int main()
{
    string name;
    string pwd;
    string user;
    int input1, input2, input3;
    int loggedInUserType = -10;
    Book books[MAX_BOOKS];
    int bookCount = 0;
    cout << " *********************************************************************                              " << endl;
    cout << "                               " << endl;
    cout << "                       BOOKS HUB                             " << endl;
    cout << "                               " << endl;
    cout << " *********************************************************************                              " << endl;
    loadBooks(books,bookCount);

    do
    {
        menu();

        // Input validation for main menu option
        while (true)
        {
            cout << "\tChoose an option: ";
            cin >> input1;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a valid integer." << endl;
            }
            else
            {
                cin.ignore(10000, '\n');
                break;
            }
        }

        switch (input1)
        {
        case 1:
            cout << "Enter the username: ";
            cin >> user;

            cout << "Enter Password: ";
            cin >> pwd;

            if (user == "Manager" && pwd == "book123")
                loggedInUserType = 1;
            else
                cout << "Invalid credentials" << endl;
            break;
        case 2:
            loggedInUserType = 2;
            break;
        case 0:
            loggedInUserType = -10;
            cout << "Thank you for using the system;" << endl;
            break;
        default:
            cout << "Invalid choice!!!" << endl;
            break;
        }

        if (loggedInUserType == 1)
        {
            do
            {
                adminOptions();

                // Input validation for admin options
                while (true)
                {
                    cout << "\tChoose an option: ";
                    cin >> input2;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input. Please enter a valid integer." << endl;
                    }
                    else
                    {
                        cin.ignore(10000, '\n');
                        break;
                    }
                }

                switch (input2)
                {
                case 1:
                    cout << "Total Sales:" << totalSalesAmount << endl;
                    break;
                case 2:
                    addbook(books, bookCount);
                    break;
                case 3:
                    deleteBook(books, bookCount);
                    break;
                case 4:
                    editBook(books, bookCount);
                    break;
                case 5:
                    generateReport(books, bookCount);
                    break;
                case 6:
                    viewAllBooks(books, bookCount);
                    break;
                case 0:
                    cout << "Logged out" << endl;
                    saveBooks(books, bookCount);
                    
                    loggedInUserType = -10;
                    break;
                default:
                    cout << "Invalid choice" << endl;
                    break;
                }
            } while (input2 != 0);
        }

        if (loggedInUserType == 2)
        {
            do
            {
                userOptions();

                // Input validation for user options
                while (true)
                {
                    cout << "\tChoose an option: ";
                    cin >> input3;

                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input. Please enter a valid integer." << endl;
                    }
                    else
                    {
                        cin.ignore(10000, '\n');
                        break;
                    }
                }

                switch (input3)
                {
                case 1:
                    searchBook(books, bookCount);
                    break;
                case 2:
                    checkPrice(books, bookCount);
                    break;
                case 3:
                    checkStock(books, bookCount);
                    break;
                case 4:
                    salesEntry(books, bookCount);
                    break;
                case 0:
                    cout << "Logged out" << endl;
                    savetotalSales();
                    loggedInUserType = -10;
                    break;
                default:
                    cout << "Invalid choice" << endl;
                    break;
                }

            } while (input3 != 0);
        }

    } while (input1 != 0);
    return 0;
}
// Main menu
void menu()
{
    cout << endl;
    cout << "Choose the desired option\n";
    cout << left << setw(10) << "\t"
         << setw(25) << "1. Manager "
         << setw(25) << "2. Seller "
         << setw(25) << "0. Exit";
    cout << endl;

    cout.unsetf(ios::left);
    cout.unsetf(ios::right);

    cout << "\tChoose an option: ";
}
// Admin options
void adminOptions()
{
    cout << "Choose the desired option\n";

    cout << setw(15) << "1. Total sales"
         << setw(15) << "2. Add book"
         << setw(20) << "3. Delete book"
         << setw(20) << "4. Edit Book"
         << endl;

    cout << setw(20) << "5. Generate Stock Report"
         << setw(20) << "6. View All Books"
         << setw(20) << "0. Logout"
         << endl;

    cout.unsetf(ios::left);
    cout.unsetf(ios::right);

    cout << "\tChoose an option: ";
}

// User options
void userOptions()
{
    cout << endl;
    cout << "Choose the desired option\n";

    cout << setw(15) << "1. Search"
         << setw(15) << "2. Check price"
         << setw(15) << "3. Check Stock"
         << setw(20) << "4. Sale entry"
         << endl;

    cout << setw(15) << "0. Exit"
         << endl;
}

void addbook(Book books[],int &bookCount)
{
    char choice;

    do
    {
        if (bookCount >= MAX_BOOKS)
        {
            cout << "Cannot add more books. Maximum limit reached." << endl;
            return;
        }

        string title, author;

        while (true)
        {
            cout << "Enter book title : ";

            getline(cin, title);

            if (title.empty())
            {
                cout << "Book title cannot be empty." << endl;
            }
            else if (title.length() > 25)
            {
                cout << "Book title cannot exceed 25 characters." << endl;
            }
            else
            {
                books[bookCount].title = title;
                break;
            }
        }

        while (true)
        {
            cout << "Enter book author : ";
            getline(cin, author);

            if (author.empty())
            {
                cout << "Book author cannot be empty." << endl;
            }
            else if (author.length() > 25)
            {
                cout << "Book author cannot exceed 25 characters." << endl;
            }
            else
            {
                books[bookCount].author = author;
                break;
            }
        }

        while (true)
        {
            cout << "Enter book price: ";
            cin >> books[bookCount].price;

            if (cin.fail() || books[bookCount].price < 0)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a valid positive number for the price." << endl;
            }
            else
            {
                cin.ignore(10000, '\n');
                break;
            }
        }
        while (true)
        {
            cout << "Enter total stock of book :";
            cin >> books[bookCount].stock;
            if (cin.fail() || books[bookCount].stock < 0)
            {
                cout << "Please enter a valid number.";
                cin >> books[bookCount].stock;
            }
            else
            {
                break;
            }
        }
        bookCount++;
        cout << "Book added successfully!" << endl;

        while (true)
        {
            cout << "Do you want to add another book? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N')
            {
                break;
            }
            else
            {
                cout << "Invalid input. Please enter 'y' for yes or 'n' for no." << endl;
            }
        }

    } while (choice == 'y' || choice == 'Y');

    cout << "Exiting addBook function." << endl;
}
void viewAllBooks(const Book books[], const int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available." << endl;
        return;
    }

    cout << left << setw(30) << "Title"
         << setw(30) << "Author"
         << setw(10) << "Price" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < bookCount; i++)
    {
        cout << setw(30) << books[i].title
             << setw(30) << books[i].author
             << setw(10) << fixed << setprecision(2) << books[i].price << endl;
    }
}
void editBook(Book books[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available to edit." << endl;
        return;
    }

    int bookIndex;
    cout << "Enter the index of the book you want to edit : ";
    cin >> bookIndex;

    while (cin.fail() || bookIndex < 0 || bookIndex >= bookCount)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid index. Please enter a valid index (0 to " << bookCount - 1 << "): ";
        cin >> bookIndex;
    }

    cout << "Current details of the book:" << endl;
    cout << "Title: " << books[bookIndex].title << endl;
    cout << "Author: " << books[bookIndex].author << endl;
    cout << "Price: " << fixed << setprecision(2) << books[bookIndex].price << endl;

    cout << "Enter new title : ";
    cin.ignore();
    string newTitle;
    getline(cin, newTitle);
    if (!newTitle.empty())
    {
        books[bookIndex].title = newTitle;
    }

    cout << "Enter new author : ";
    string newAuthor;
    getline(cin, newAuthor);
    if (!newAuthor.empty())
    {
        books[bookIndex].author = newAuthor;
    }

    double newPrice;
    cout << "Enter new price: ";
    cin >> newPrice;
    if (cin.fail() || newPrice < 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Keeping current price: " << fixed << setprecision(2) << books[bookIndex].price << endl;
    }
    else
    {
        books[bookIndex].price = newPrice;
    }

    cout << "Book details updated successfully!" << endl;
}
void deleteBook(Book books[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available to edit." << endl;
        return;
    }

    int bookIndex1;
    cout << "Enter the index of the book you want to delete : ";
    cin >> bookIndex1;

    while (cin.fail() || bookIndex1 < 0 || bookIndex1 >= bookCount)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid index. Please enter a valid index : ";
        cin >> bookIndex1;
    }

    cout << "Selected book:" << endl;
    cout << "Title: " << books[bookIndex1].title << endl;
    cout << "Author: " << books[bookIndex1].author << endl;
    cout << "Price: " << fixed << setprecision(2) << books[bookIndex1].price << endl;
    for (int i = bookIndex1; i < bookCount - 1; i++)
    {
        books[i].title = books[i].title;
        books[i].author = books[i+1].author;
        books[i].price = books[i+1].price;
    }
    bookCount--;
    cout << "Book Deleted Successfuly" << endl;
}
void generateReport(const Book books[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available to generate a report." << endl;
        return;
    }

    double totalValue = 0.0;

    cout << "==================== Book Report ====================" << endl;
    cout << left << setw(30) << "Title"
         << setw(30) << "Author"
         << setw(10) << "Price" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < bookCount; i++)
    {
        cout << setw(30) << books[i].title
             << setw(30) << books[i].author
             << setw(10) << fixed << setprecision(2) << books[i].price << endl;
        totalValue +=books[i].price;
    }

    cout << string(70, '-') << endl;
    cout << "Total number of books: " << bookCount << endl;
    cout << "Total value of books: " << fixed << setprecision(2) << totalValue << endl;
    cout << "====================================================" << endl;
}
void searchBook(const Book books[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available ." << endl;
        return;
    }
    bool found = false;
    string searchedBook;
    cout << "Enter the Title of the Book" << endl;
    cin.ignore();
    getline(cin, searchedBook);

    cout << left << setw(30) << "Title"
         << setw(30) << "Author"
         << setw(10) << "Price" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < bookCount; i++)
    {
        if (searchedBook == books[i].title)
        {
            cout << setw(30) << books[i].title
                 << setw(30) << books[i].author
                 << setw(10) << fixed << setprecision(2) << books[i].price << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No books found" << endl;
    }
}
void salesEntry( Book books[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available for sale." << endl;
        return;
    }
    cout << "Available Books" << endl;
    cout << left << setw(30) << "Title"
         << setw(30) << "Author"
         << setw(10) << "Price" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < bookCount; i++)
    {
         cout << setw(30) << books[i].title
             << setw(30) << books[i].author
             << setw(10) << fixed << setprecision(2) << books[i].price << endl;
    }
    int bookIndex;
    int quantity;
    cout << "Enter the index of the book you want to sell  ";
    cin >> bookIndex;

    while (cin.fail() || bookIndex < 0 || bookIndex >= bookCount)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid index. Please enter a valid index  ";
        cin >> bookIndex;
    }
    cout << "Enter the quantity sold: ";
    cin >> quantity;

    while (cin.fail() || quantity <= 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid quantity. Please enter a positive integer: ";
        cin >> quantity;
    }
    if (quantity > books[bookIndex].stock)
    {
        cout << "Not enough stock available. Only " << books[bookIndex].stock << " available." << endl;
    }
    else
    {
        books[bookIndex].stock -= quantity;
        double totalSales = books[bookIndex].price * quantity;
        totalSalesAmount += totalSales;
        cout << "Sales record updated successfully." << endl;
    }
}
void checkPrice(const Book books[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available ." << endl;
        return;
    }
    bool found = false;
    string searchedBook;
    cout << "Enter the Title of the Book" << endl;
    cin.ignore();
    getline(cin, searchedBook);

    cout << left << setw(30) << "Title"

         << setw(30) << "Price" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < bookCount; i++)
    {
        if (searchedBook == books[i].title)
        {
            cout << setw(30) << books[i].title

                 << setw(30) << fixed << setprecision(2) << books[i].price << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No books found" << endl;
    }
}
void checkStock(const Book books[], int bookCount)
{
    if (bookCount == 0)
    {
        cout << "No books available ." << endl;
        return;
    }
    bool found = false;
    string searchedBook;
    cout << "Enter the Title of the Book" << endl;
    cin.ignore();
    getline(cin, searchedBook);

    cout << left << setw(30) << "Title"

         << setw(30) << "Stock" << endl;
    cout << string(70, '-') << endl;
    for (int i = 0; i < bookCount; i++)
    {
        if (searchedBook == books[i].title)
        {
            cout << setw(30) << books[i].title

                 << setw(30) << fixed << setprecision(2) << books[i].stock << endl;
            found = true;
        }
    }
    if (!found)
    {
        cout << "No books found" << endl;
    }
}
void saveBooks(const Book books[], int bookCount)
{
    ofstream fout;
    fout.open("Books.txt");
    if (!fout.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    for (int i = 0; i < bookCount; i++)
    {
        fout << books[i].title << "," << books[i].author << "," << books[i].price << "," << books[i].stock << endl;
    }
    fout.close();
}
void savetotalSales()
{
    ofstream fout;
    fout.open("Sales.txt");
    if (!fout.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    fout << totalSalesAmount << endl;
}
void loadBooks(Book books[], int &bookCount)
{
    ifstream fin;
    fin.open("Books.txt");
    if (!fin.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    bookCount = 0;
    while (bookCount < MAX_BOOKS && fin.good())
    {
        getline(fin, books[bookCount].title, ',');
        getline(fin, books[bookCount].author, ',');
        fin >> books[bookCount].price;
        fin.ignore();
        fin >> books[bookCount].stock;
        fin.ignore();

        if (fin.fail())
        {
            break;
        }
        bookCount++;
    }
    fin.close();
}
