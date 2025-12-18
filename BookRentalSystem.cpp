/*
* ---------- Group Members ----------
* Kidus Anteneh         RCD/0264/2017
* Eyuel Esubalew        RCD/1690/2017 
* Akbari Girma          RCD/0235/2017
* Birhanemedin Mulat    RCD/0242/2017
* -----------------------------------
*/

#include <iostream>
#include <string>

using namespace std;

struct date {
    int day = 0;
    string month = "NOV";
    int year = 2025;
};
struct customer {
    string CustomerName = "";
    int IDNumber = 0;
};
struct books {
    string BooksTitle;
    int BookCount = 0;
    int rentcount = 0;
    string ISBN;

};
struct rental_Node {
    customer Renter;
    books RentedBook;
    date DaysRented;
    bool Rented;
    rental_Node* next;
};


//function to create a new rental node
rental_Node* createNew(books b, customer c, date d) {
    rental_Node* node = new rental_Node;
    node->Renter = c;
    node->RentedBook = b;
    node->DaysRented = d;
    if (node->RentedBook.rentcount > 0) {
        node->Rented = true;
    }
    else {
        node->Rented = false;
    }
    node->next = nullptr;
    return node;
}

//function to check if customer already exists
bool customerCheck(customer list, bool& IsCorrect, int customerCount, rental_Node* head) {
    rental_Node* temp = head;
    while (temp != nullptr) {
        //check if customer ID matches any existing customer ID
        if (temp != nullptr && temp->Renter.IDNumber == list.IDNumber) {
            //check if customer name matches existing customer name
            if (temp->Renter.CustomerName == list.CustomerName) {
                cout << "Customer Name Matches ID.\n";
                cout << "Customer Found: " << temp->Renter.CustomerName << endl;
                IsCorrect = true;
                return false; //customer exists
            }
            //check if customer name matches any existing customer name under different ID
            else if (temp->Renter.IDNumber == list.IDNumber && temp->Renter.CustomerName != list.CustomerName) {
                cout << "Customer ID was Used by Another Customer Name.\n";
                IsCorrect = false;
                return false; //customer exists
            }
        }
        temp = temp->next;
    }

    //if no matching customer found, proceed to add new customer

    cout << "Customer Not Found. \nProceeding to add new customer.\n";
    IsCorrect = true;
    return true;
}

//function to check if customer has already rented a book
bool rentCheck(customer list, int customerCount, rental_Node* head) {
    rental_Node* temp = head;
    for (int i = 0; i < customerCount; i++) {
        if (temp != nullptr && temp->Renter.IDNumber == list.IDNumber) {
            cout << "Welcome Back " << temp->Renter.CustomerName << endl;
            break;//this is to stop the loop when the customer is found
        }
        temp = temp->next;
    }
    if (temp != nullptr) {
        if (temp->Rented == false) {
            cout << "You have no rented books currently." << endl;
            cout << "Proceeding to book selection." << endl;
            return false;
        }
        else {
            cout << "You have already rented a book: " << temp->RentedBook.BooksTitle << endl;
            cout << "You cannot rent another book until you return the current one." << endl;
            cout << "Returning to main menu." << endl;

        }
    }
    return true;
}

//function to delete rental node
void deleteNode(rental_Node*& head) {
    rental_Node* current = head;
    while (current != nullptr) {
        rental_Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    cout << "Memory cleared. Goodbye!\n";
}

//function to get rental date
date rentalDate(date d) {
    while (true) {
        int day;
        cout << "Enter Rental Day (DD): ";
        cin >> day;
        cin.ignore();
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid Month. Please try again.\n";
            continue;
        }
        if (day < 1 || day > 30) {
            cout << "Day must be between 1 and 31. Please try again.\n";
            continue;
        }
        else {
            d.day = day;
            break;
        }
        break;
    }
    return d;
}




//function to initialize book inventory
int BooksInventory(books bookList[]) {
    bookList[0].BooksTitle = "The Great Gatsby";
    bookList[0].BookCount = 1;
    bookList[0].ISBN = "9780743273565";
    bookList[1].BooksTitle = "To Kill a Mockingbird";
    bookList[1].BookCount = 8;
    bookList[1].ISBN = "9780061120084";
    bookList[2].BooksTitle = "1984";
    bookList[2].BookCount = 4;
    bookList[2].ISBN = "9780451524935";
    bookList[3].BooksTitle = "Atomic Habits";
    bookList[3].BookCount = 5;
    bookList[3].ISBN = "9780735211292";

    return 4;
}

//function to display the main menu and process user choice
int processMenu(int choice)
{
    while (true) {

        cout << "BOOK RENTAL SYSTEM\n";
        cout << "==================\n";
        cout << " Type 1 to Rent a Book\n";
        cout << " Type 2 to Display Rental Log\n";
        cout << " Type 3 to Return a Book\n";
        cout << " Type 4 to Exit\n";
        cout << "Enter your choice: ";
        //Accepts user input between 1-4 to navigate the menu
        cin >> choice;
        cin.ignore();

        //incase the user insert a wrong input clears the input and try again until a valid input is given
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "------------------------------------------------" << endl;
            cout << "Invalid choice.Please try again." << endl;
            cout << endl;
            continue;
        }
        return choice;
    }
}






//function to process the rental of a book
bool ProcessRental(customer list, bool newCustomer, int& customerCount, books b, int BCount, books bookList[], rental_Node*& head, date d)
{
    while (true) {
        
        bool isPassed = false;
        bool bookRented = true;
        //if customer exists proceed to book selection
        if (newCustomer == false) {

            bookRented = rentCheck(list, customerCount, head);
            if (bookRented == true) {
                return true;
            }
            
          
        }
        //if customer is new proceed to book selection
        else {
            bookRented = false;
        }

        while (bookRented == false) {
            int book;
            cout << "----------------Available books-----------------" << endl;



            //display available books
            for (int i = 0; i < BCount; i++) {
                cout << i + 1 << ". " << bookList[i].BooksTitle << "\nAvailable: { " << bookList[i].BookCount << " }" << endl;
            }
            cout << "------------------------------------------------" << endl;
            cout << "Choose The Book You Want: ";
            cin >> book;
            cin.ignore(10000, '\n');
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Enter A Correct Number" << endl;
                continue;
            }

            if (book < BCount + 1 && book > 0) {
                if (bookList[book - 1].BookCount > 0) {
                    book -= 1;
                    b = bookList[book];
                    cout << b.BooksTitle << "\n" << b.ISBN << "\nBook Selected Successfully" << endl;
                    b.rentcount += 1;
                    bookList[book].BookCount -= 1;
                    d = rentalDate(d);
                    cout << "------------------------------------------------" << endl;
                    cout << "Rental Date: " << d.day << "/" << d.month << "/" << d.year << endl;
                    isPassed = true;
                }
                else {
                    cout << "Sorry, this book is currently unavailable. Please select another book.\n";
                }
            }

            else {
                cout << "Invalid Book Selection. Please try again.\n";
                continue;
            }

            if (isPassed == true) {

                rental_Node* node = createNew(b, list, d);
                if (head == nullptr) {
                    head = node;
                }
                else {
                    rental_Node* temp = head; // Temporary pointer to traverse the list

                    // Append the new node at the end of the linked list
                    while (temp->next != nullptr) {
                        temp = temp->next; // Traverse to the end of the list
                    }
                    temp->next = node; // Append the new node at the end of the list
                }
                cout << "Rental Successful!\n"; // Confirmation message
                customerCount += 1;
                cout << "------------------------------------------------" << endl;
                cout << node->Renter.CustomerName << " rented \"" << node->RentedBook.BooksTitle << "\" on " << node->DaysRented.day << "/" << node->DaysRented.month << "/" << node->DaysRented.year << endl;
                return true;


            }


        }

    }
}

//function to add a new customer
bool AddCustomer(customer& list, int& customerCount, int& BCount, books bookList[], rental_Node*& head, date d)
{

    while (true) {
        bool IsCorrect = false;
        bool IsAdded = false;
        //flag to check if the customer is new or existing
        bool newCustomer = true;
        cout << endl;
        cout << "-------- ADD CUSTOMER / SEARCH CUSTOMER --------\n";
        cout << "Enter Customer Name: ";
        // to ignore the newline character after integer input
        getline(cin, list.CustomerName);
        // Input validation for ID Number
        cout << "Enter ID Number (4 digits): ";
        while (true) {
            cin >> list.IDNumber;

            // 1. Check if the input was actually a number
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input. Please enter a 4-digit number: ";
                continue;
            }

            // 2. Clear the buffer 
            cin.ignore(10000, '\n');

            // 3. Check the range (1000 to 9999)
            if (list.IDNumber >= 1000 && list.IDNumber <= 9999) {
                break; // Success! Exit the loop.
            }
            else {
                cout << "Error: ID must be exactly 4 digits (1000-9999). \nTry again: " << endl;
            }
        }
        cout << "------------------------------------------------" << endl;


        //check if customer already exists by calling customerCheck function
        newCustomer = customerCheck(list, IsCorrect, customerCount, head);

        if (newCustomer == false && IsCorrect == true) {
            cout << "Customer already exists. \nEnter Y to proceed to rental, \nEnter N to return to main menu" << endl;
            cout << "------------------------------------------------" << endl;
            cout << "Proceed to rental? (Y/N): ";
            char proceed;
            cin >> proceed;
            if (proceed == 'Y' || proceed == 'y') {
                books b;
                ProcessRental(list, newCustomer, customerCount, b, BCount, bookList, head, d);
                break;
            }
            else {
                continue;
            }
        }
        else if (newCustomer == true && IsCorrect == true)
        {

            cout << "------------------------------------------------" << endl;
            cout << "Adding New Customer: " << list.CustomerName << " with ID: " << list.IDNumber << endl;
            cout << "------------------------------------------------" << endl;
            books b;
            IsAdded = ProcessRental(list, newCustomer, customerCount, b, BCount, bookList, head, d);
            if (IsAdded == true) {
                break;
            }
        }
        else if (IsCorrect == false) {
            cout << "Customer ID was used by another user. Please try again with different ID.\n";
            continue;
        }


    }
    return true;

}


//function to process the return of a book
bool processReturn(books bookList[], int BCount, rental_Node* head)
{

    int id;
    cout << "Enter Customer ID for return: ";
    while (true) {
        cin >> id;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid ID Number. Please try again.\n";
            continue;
        }
        else {
            break;
        }
    }
    rental_Node* temp = head;
    while (temp != nullptr) {
        if (temp->Renter.IDNumber == id && temp->Rented) {
            temp->Rented = false;
            // Find the book in inventory to increment the count
            for (int i = 0; i < BCount; i++) {
                if (bookList[i].BooksTitle == temp->RentedBook.BooksTitle) {
                    bookList[i].BookCount++;
                    break;
                }
            }
            cout << "Book returned successfully: " << temp->RentedBook.BooksTitle << endl;
            return true;
        }
        temp = temp->next;
    }
    cout << "No active rental found for this ID.\n";
    return true;

}

//function to display rental log
void DisplayLog(int Count, rental_Node* head) {
    if (head == nullptr) {
        cout << "No rental records found.\n";
        return;
    }
    rental_Node* temp = head;
    cout << "\n--- RENTAL LOG ---\n";
    while (temp != nullptr) {

        cout << "Customer: " << temp->Renter.CustomerName
            << " | Book: " << temp->RentedBook.BooksTitle
            << " | Date: " << temp->DaysRented.day << "/" << temp->DaysRented.month << "/" << temp->DaysRented.year
            << " | Status: " << (temp->Rented ? "Rented" : "Returned") << endl;
        temp = temp->next;
    }
    cout << "------------------\n";
}

//function to display main menu and get user choice
int main()
{
    customer list; // customer list
    date d;
    rental_Node* head = nullptr; // head pointer for linked list
    books bookList[100]; // array to store book inventory
    int BCount = BooksInventory(bookList); // initialize book inventory
    int customerCount = 0;

    bool IsRunning = true;


    while (IsRunning) {

        int choice = 0;
        cout << endl;
        choice = processMenu(choice);

        if (choice == 4) {
            deleteNode(head);
            break;
        }
        else if (choice == 1) {

            IsRunning = AddCustomer(list, customerCount, BCount, bookList, head, d);
        }

        else if (choice == 2) {
            DisplayLog(customerCount, head);
        }
        else if (choice == 3) {
            customer c;
            books b;
            IsRunning = processReturn(bookList, BCount, head);
        }
        else {
            cout << "------------------------------------------------" << endl;
            cout << "Invalid choice. Please try again.\n";


        }
    }
    return 0;
}