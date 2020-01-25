#include "Genre.h"
#include <iostream>
#include <algorithm>

Genre::Genre(const string gname) : genreName(""), head(NULL) {
}

Genre::~Genre() {
	if (head != NULL) {
		BookNode* ptr = head;
		while (ptr != NULL) {
			BookNode* toBeDeleted = ptr;

			ptr = ptr->next;

			toBeDeleted->next = NULL;
			delete toBeDeleted;
			toBeDeleted = NULL;
		}
	}
}

Genre::Genre(const Genre& genreToCopy) {
	genreName = genreToCopy.genreName;
	
	if (genreToCopy.head == NULL) {
		head = NULL;
	}
	else {
		head = new BookNode;
		head->a = genreToCopy.head->a;

		BookNode* newPtr = head;

		for (BookNode* origPtr = genreToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new BookNode;
			newPtr = newPtr->next;
			newPtr->a = origPtr->a;
		}
		newPtr->next = NULL;
	}
}

void Genre::operator=(const Genre& right) {
	genreName = right.genreName;

	if (right.head == NULL) {
		head = NULL;
	}
	else {
		head = new BookNode;
		head->a = right.head->a;

		BookNode* newPtr = head;

		for (BookNode* origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new BookNode;
			newPtr = newPtr->next;
			newPtr->a = origPtr->a;
		}
		newPtr->next = NULL;
	}
}

string Genre::getGenreName() const {
	return genreName;
}

void Genre::setGenreName(const string gName) {
	genreName = gName;
}

void Genre::displayAllBooks(){
	if (head == NULL) {
		cout << "No Books exist" << endl;
		cout << "	No Authors exist" << endl;
	}		
	else {
		BookNode* newPtr;
		for (newPtr = head; newPtr != NULL; newPtr = newPtr->next) {
			cout << "Book " << newPtr->a.getName() << endl;
			newPtr->a.displayAuthors();
		}
			
	}

}

void Genre::addBook(string bookName){
	bool flag = true;
	for (BookNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->a.getName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		
		if (s1 == s2)
			flag = false;		
	}

	if (flag) {
		if (head == NULL) {
			head = new BookNode;
			head->a.setName(bookName);
			head->next = NULL;				
		}
		else {
			BookNode* newPtr;
			for (newPtr = head; newPtr->next != NULL; newPtr = newPtr->next);

			newPtr->next = new BookNode;
			newPtr = newPtr->next;
			newPtr->a.setName(bookName);			
			newPtr->next = NULL;			
		}
	}
	else
		cout << "Same book is already added" << endl;
}

void Genre::removeBook(string bookName){
	bool flag = false;	
	if (head == NULL) {
		cout << "No book is present in this genre" << endl;
	}
	else {
		BookNode* prev = NULL;
		for (BookNode* ptr = head; ptr != NULL; ptr = ptr->next) {
			string s1 = ptr->a.getName();
			string s2 = bookName;
			transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
			transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
			if (s1 == s2) {
				if (prev == NULL) {					
					BookNode* toBeDeleted = head;
					head = head->next;

					toBeDeleted->next = NULL;
					delete toBeDeleted;
					toBeDeleted = NULL;
					
					flag = true;
					break;
				}
				else {					
					prev->next = ptr->next;

					ptr->next = NULL;
					delete ptr;
					ptr = NULL;
					
					flag = true;
					break;
				}			
			}
			prev = ptr;
		}
	}	

	if (!flag)
		cout << "Could not find the specified book name ->" << bookName << endl;
}

void Genre::addAuthor(string bookName, int authorID, string authorName){
	
	bool flag = false;
	for (BookNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->a.getName();
		string s2 = bookName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
		
		if (s1 == s2) {
			ptr->a.addAuthor(authorID, authorName);
			flag = true;
		}	
	}
	if (!flag)
		cout << "Genre is correct but book is not found-> " << bookName << endl;
}

void Genre::removeAuthor(string bookName, int authorID){
	bool flag = false;
	for (BookNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->a.getName();
		string s2 = bookName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2) {
			ptr->a.removeAuthor(authorID);
			flag = true;
		}
	}
	if (!flag)
		cout << "Genre is correct but book is not found-> " << bookName << endl;

}

void Genre::checkAuthor(int id, string genreName, int& authorFlag, int& genreFlag){
	
	for (BookNode* ptr = head; ptr != NULL; ptr = ptr->next) {	
			ptr->a.checkAuthors(id, genreName, ptr->a.getName(), authorFlag, genreFlag);			
	}
}




