// Karina Rios
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "person.cpp"
#include "book.cpp"

using namespace std;

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

// You are not obligated to use these function declarations - they're just given as examples
void readBooks(vector<Book *> & myBooks) {
  string title,author,cat,trash;
  int id;
  ifstream Data;
  Data.open("books.txt");
  while(!Data.eof()){
    Data >> id;
    getline(Data,trash);
    getline(Data,title);
    getline(Data,author);
    getline(Data,cat);
    getline(Data,trash);
    myBooks.push_back(new Book(id,title,author,cat));
  }
  Data.close();
}

int readPersons(vector<Person *> & myCardholders) {
  int max = 0;
  int id;
  bool active;
  string fname,lname,trash;
  ifstream people;
  people.open("persons.txt");
  while(!people.eof()){
    people >> id >> active >> fname >> lname;
    getline(people,trash);
    myCardholders.push_back(new Person(id,active,fname,lname));
    if(max < id){
      max = id;
    }
  }
  people.close();
  return max+1;
}

void readRentals(vector<Book *> myBooks, vector<Person *> myCardholders){
  int bookID, cardID;
  string trash;
  ifstream Rental;
  Rental.open("rental.txt");
  while(!Rental.eof()){
    Rental >> bookID >> cardID;
    getline(Rental,trash);
    for(int i = 0; i < myBooks.size(); i++){
      for(int j = 0; i < myCardholders.size(); j++)
	if(myBooks.at(i)->getId() == bookID && myCardholders.at(i)->getId() == cardID){
	  myBooks.at(i)->setPersonPtr(myCardholders.at(i));
      }
    }
  }
  Rental.close();
}

void checkout(vector<Book *> myBooks, vector<Person *> myCardholders){
  int cardID,bookID;

  cout << "Please enter the card ID: " ;
  cin >> cardID;

  for(int i = 0; i < myCardholders.size(); i++){
    if(myCardholders.at(i)->getId() == cardID && myCardholders.at(i)->isActive() == true){
      cout << "\nCardholder: " << myCardholders.at(i)->fullName() << endl;
      cout << "Please enter the book ID:";
      cin >> bookID;
      for(int j = 0; j < myBooks.size(); j++){
	if(myBooks.at(j)->getId() == bookID && myBooks.at(j)->getPersonPtr() == nullptr){
	  cout << "\nTitle: " << myBooks.at(j)->getTitle() << endl;
	  return;
	}
      }
      cout << "\nBook already checked out";
      return;
    }
  }
  cout << "\nCard ID not found" << endl;
}

void returnBook(vector<Book *> & myBooks){
  int bookID;
  cout << "Please enter the book ID to return: ";
  cin >> bookID;

  for(int i = 0; i < myBooks.size(); i++){
    if(myBooks.at(i)->getId() == bookID){
      cout << "\nTitle: " << myBooks.at(i)->getTitle() << endl;
      myBooks.at(i)->setPersonPtr(nullptr);
      cout << "Return Complete\n";
      return;
    }
  }
  cout << "Book ID not found\n";
}
 

void openCard(vector<Person *> & myCardholders, int nextID) {
  string firstName, lastName;
  cout<< "Please enter the first name: ";
  cin >> firstName;
  cout << "\nPlease enter the last name: ";
  cin >> lastName;

  myCardholders.push_back(new Person(nextID,true,firstName,lastName));
  cout << "\nCard ID: " << nextID << " active" << endl;
  cout << "Cardholder: " << myCardholders.back()->fullName();
}

void closeCard(vector<Person *> myCardholders){
  int cardID;
  char option;
  cout << "Please enter the card ID: ";
  cin >> cardID;

  for(int i = 0; i < myCardholders.size(); i++){
    if(myCardholders.at(i)->getId() == cardID){
      cout << "Cardholder: " << myCardholders.at(i)->fullName() << endl;
      if(myCardholders.at(i)->isActive() == false){
	cout << "Card ID is already inactive" << endl;
	return;
      }
      cout << "Are you sure you want to deactivate card (y/n)? ";
      cin >> option;
      if(option == 'y'){
	myCardholders.at(i)->setActive(false);
	cout << "Card ID deactivated" << endl;
	return;
      }
      return;
    }

    cout << "Card ID not found" << endl;
  }
}

void searchBook(vector<Book *> myBooks){
  int count = 0;
  for(int i = 0; i < myBooks.size(); i++){
    if(myBooks.at(i)->getPersonPtr() == nullptr){
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle()<< endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
      cout << "Category: " << myBooks.at(i)->getCategory() << endl;
      ++count;
    }
  }
  
  if(count == 0){
    cout << "No available books\n";
  }
}

void searchRentals(vector<Book *> myBooks){
 int count = 0;
  for(int i = 0; i < myBooks.size(); i++){
    if(myBooks.at(i)->getPersonPtr() != nullptr){
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle()<< endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
      cout << "Cardholder: " << myBooks.at(i)->getPersonPtr()->fullName() << endl;
      cout << "Card ID: " << myBooks.at(i)->getPersonPtr()->getId() << endl;
      ++count;
    }
  }
  
  if(count == 0){
    cout << "No available books\n";
  }
}

void bookrentals(vector<Book *> myBooks){
  int card;
  int count = 0;
  cout << "Please enter the card ID: ";
  cin >> card;

  for(int i = 0; i < myBooks.size(); i++){
    if(myBooks.at(i)->getPersonPtr()->getId() == card){
      cout << "\nCardholder: " << myBooks.at(i)->getPersonPtr()->fullName() << endl;
    }
    if(myBooks.at(i)->getPersonPtr()->isActive() == true){
      cout << "Book ID: " << myBooks.at(i)->getId() << endl;
      cout << "Title: " << myBooks.at(i)->getTitle() << endl;
      cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
      cout << endl;
      ++count;
    }
  }

  if(count == 0){
    cout << "No books currently checked out" << endl;
  }
}

void update(vector<Book *> myBooks, vector<Person *> myCardholders){
  ofstream Rental;
  Rental.open("rental.txt");
  ofstream Data;
  Data.open("books.txt");
  for(int i = 0; i < myBooks.size(); i++){
    Data << myBooks.at(i)->getId() << endl;
    Data << myBooks.at(i)->getTitle() << endl;
    Data << myBooks.at(i)->getAuthor();
    Data << myBooks.at(i)->getCategory();
    if(myBooks.at(i)->getPersonPtr() != nullptr){
      Rental << myBooks.at(i)->getId() << " " << myBooks.at(i)->getPersonPtr()->getId() << endl;
  }
  }
  Data.close();
  Rental.close();

  ofstream people;
  people.open("persons.txt");
  for(int j = 0; j < myCardholders.size(); j++){
    people << myCardholders.at(j)->getId() << " " << myCardholders.at(j)->isActive() << " "
						 << myCardholders.at(j)->fullName() << endl;
  }
  people.close();
}


int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;
    int newID;
    
    readBooks(books);
    newID = readPersons(cardholders);
    readRentals(books,cardholders);
    
    int choice;
    int person,bookid;
    string trash;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that 
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
	      checkout(books,cardholders);
              break;

            case 2:
	      returnBook(books);
	      break;

            case 3:
	      searchBook(books);
                break;

            case 4:
	      searchRentals(books);
                break;

            case 5:
	      bookrentals(books);
                break;

            case 6:
	      openCard(cardholders,newID);
                break;

            case 7:
	      closeCard(cardholders);
                break;
                
            case 8:
	      update(books, cardholders);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8);
      return 0;
}
