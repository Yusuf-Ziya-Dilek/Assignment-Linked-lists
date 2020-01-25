#include "Book.h"
#include <iostream>

Book::Book(): name(""), head(NULL){
}

Book::Book(const string name){
	this->name = name;
	head = NULL;
}

Book::~Book(){
	if (head != NULL) {
		AuthorNode* ptr = head;
		while (ptr != NULL) {
			AuthorNode* toBeDeleted = ptr;

			ptr = ptr->next;

			toBeDeleted->next = NULL;
			delete toBeDeleted;
			toBeDeleted = NULL;
		}
	}	
}

Book::Book(const Book& bookToCopy){
	if (bookToCopy.head == NULL) {
		head = NULL;
	}
	else {
		head = new AuthorNode;
		head->a = bookToCopy.head->a;

		AuthorNode* newPtr = head;

		for (AuthorNode* origPtr = bookToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new AuthorNode;
			newPtr = newPtr->next;
			newPtr->a = origPtr->a;
		}
		newPtr->next = NULL;
	}
}

void Book::operator=(const Book& right){
	if (right.head == NULL) {
		head = NULL;
	}
	else {
		head = new AuthorNode;
		head->a = right.head->a;

		AuthorNode* newPtr = head;

		for (AuthorNode* origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new AuthorNode;
			newPtr = newPtr->next;
			newPtr->a = origPtr->a;
		}
		newPtr->next = NULL;
	}
}

string Book::getName() const{
	return name;
}

void Book::setName(const string bookName){
	name = bookName;
}

bool Book::addAuthor(const int id, const string name){
	//check id
	for (AuthorNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		if (id == ptr->a.getID())
			return false;
	}

	if(head == NULL) {
		head = new AuthorNode;
		head->a.setID(id);
		head->a.setName(name);
		head->next = NULL;

		return true;
	}
	else {
		AuthorNode* newPtr;
		for (newPtr = head; newPtr->next != NULL; newPtr = newPtr->next);

		newPtr->next = new AuthorNode;
		newPtr = newPtr->next;
		newPtr->a.setID(id);
		newPtr->a.setName(name);
		newPtr->next = NULL;
		return true;
	
	}	

}

bool Book::removeAuthor(const int id){	
	AuthorNode* prev = NULL;
	for (AuthorNode* cur = head; cur != NULL; cur = cur->next) {
		if (cur->a.getID() == id) {
			if (prev == NULL) {
				head = head->next;

				cur->next = NULL;
				delete cur;
				cur = NULL;

				return true;
			}
			else {
				prev->next = cur->next;
				
				cur->next = NULL;
				delete cur;
				cur = NULL;

				return true;
			}
		}
		prev = cur;
	}
	cout << "Error while removing : Wrong ID" << endl;
	return false;
}

void Book::displayAuthors() const{
	if (head == NULL)
		cout << "	No Authors exist" << endl;
	else {
		AuthorNode* newPtr;
		for (newPtr = head; newPtr != NULL; newPtr = newPtr->next) {			
			cout << "	Author " << newPtr->a.getID() << ", " << "Author " << newPtr->a.getName() << endl;
		}				
	}	
}

void Book::checkAuthors(int id, string genreName, string bookName, int& authorFlagInt, int& genreFlagInt){
	
	for (AuthorNode* cur = head; cur != NULL; cur = cur->next) {
		if (id == cur->a.getID()) {
			if (authorFlagInt == 0) {
				cout << "Author " << id << " Author " << cur->a.getName() << "\n" << "Genre " << genreName << endl;
				cout << "	Book " << bookName << endl;				
				authorFlagInt = 1;
				genreFlagInt = 1;
			}
			else {
				if (genreFlagInt == 0) {
					cout << "Genre " << genreName << endl;
					cout << "	Book " << bookName << endl;
					genreFlagInt = 1;
				}
				else {
					cout << "	Book " << bookName << endl;
				}
			}
		}
	}

}

Book::AuthorNode* Book::findAuthor(int id){
	for (AuthorNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		if (id == ptr->a.getID())
			return ptr;
	}
	return NULL;
}
