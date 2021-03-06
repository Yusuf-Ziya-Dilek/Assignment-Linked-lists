#include "BookCollection.h"
#include <iostream>
#include <algorithm>


BookCollection::BookCollection() : name(""), genreCount(0), head(NULL) {

}

BookCollection::~BookCollection() {
	if (genreCount != 0) {
		GenreNode* ptr = head;
		while (ptr != NULL) {
			GenreNode* toBeDeleted = ptr;

			ptr = ptr->next;

			toBeDeleted->next = NULL;
			delete toBeDeleted;
			toBeDeleted = NULL;
		}
	}
}

BookCollection::BookCollection(const BookCollection& bcToCopy) :genreCount(bcToCopy.genreCount) {
	if (bcToCopy.head == NULL) {
		head = NULL;
	}
	else {
		head = new GenreNode;
		head->g = bcToCopy.head->g;

		GenreNode* newPtr = head;

		for (GenreNode* origPtr = bcToCopy.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new GenreNode;
			newPtr = newPtr->next;
			newPtr->g = origPtr->g;
		}
		newPtr->next = NULL;
	}



}

void BookCollection::operator=(const BookCollection& right) {

	if (right.head == NULL) {
		head = NULL;
		genreCount = 0;
	}
	else {
		genreCount = right.genreCount;

		head = new GenreNode;
		head->g = right.head->g;

		GenreNode* newPtr = head;

		for (GenreNode* origPtr = right.head->next; origPtr != NULL; origPtr = origPtr->next) {
			newPtr->next = new GenreNode;
			newPtr = newPtr->next;
			newPtr->g = origPtr->g;
		}
		newPtr->next = NULL;
	}
}

void BookCollection::displayAllGenres() const {
	if (head == NULL)
		cout << "--Empty--";
	else {
		GenreNode* newPtr;
		for (newPtr = head; newPtr != NULL; newPtr = newPtr->next) {
			cout << "Genre " << newPtr->g.getGenreName() << endl;
			newPtr->g.displayAllBooks();
		}
	}
}

bool BookCollection::addGenre(const string genreName) {

	// Control case insensitive 
	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->g.getGenreName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2)
			return false;
	}

	if (head == NULL) {
		head = new GenreNode;
		head->g.setGenreName(genreName);
		head->next = NULL;

		genreCount++;
		return true;
	}
	else {
		GenreNode* newPtr = head;
		for (int i = 1; i < genreCount; i++) {
			newPtr = newPtr->next;
		}

		newPtr->next = new GenreNode;
		newPtr = newPtr->next;
		newPtr->g.setGenreName(genreName);
		newPtr->next = NULL;

		genreCount++;
		return true;
	}
}

bool BookCollection::removeGenre(const string genreName) {
	if (head == NULL) {
		cout << "Could not remove";
		return false;
	}
	else {
		GenreNode* prev = NULL;
		for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
			string s1 = ptr->g.getGenreName();
			string s2 = genreName;
			transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
			transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

			if (s1 == s2) {
				if (prev == NULL) {// first index
					GenreNode* toBeDeleted = head;
					head = head->next;

					toBeDeleted->next = NULL;
					delete toBeDeleted;
					toBeDeleted = NULL;
					genreCount--;
					return true;
				}
				else {
					prev->next = ptr->next;

					ptr->next = NULL;
					delete ptr;
					ptr = NULL;

					genreCount--;
					return true;
				}
			}
			prev = ptr;
		}
		cout << "Could not remove" << endl;
		return false;
	}
}

string BookCollection::getName() const {
	return name;
}

void BookCollection::setName(const string bcName) {
	name = bcName;
}

void BookCollection::addBook(string genreName, string bookName){
	bool flag = false;
	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->g.getGenreName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2) {// genre is found
			ptr->g.addBook(bookName);
			flag = true;
		}
	}
	if(!flag)
		cout << "Could not find the specified Genre ->"<< genreName  << endl;
}

void BookCollection::removeBook(string genreName, string bookName){
	bool flag = false;
	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->g.getGenreName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2) {// genre is found
			ptr->g.removeBook(bookName);
			flag = true;
		}
	}
	if (!flag)
		cout << "Could not find the specified Genre ->" << genreName << endl;

}

void BookCollection::addAuthor(string genreName, string bookName, int authorID, string authorName){
	bool flag = false;
	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->g.getGenreName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2) {// genre is found
			ptr->g.addAuthor(bookName, authorID, authorName);
			flag = true;
		}
	}
	if (!flag)
		cout << "Could not find the specified Genre ->" << genreName << endl;

}

void BookCollection::removeAuthor(string genreName, string bookName, int authorID){
	bool flag = false;
	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->g.getGenreName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2) {// genre is found
			ptr->g.removeAuthor(bookName, authorID);
			flag = true;
		}
	}
	if (!flag)
		cout << "Could not find the specified Genre ->" << genreName << endl;

}

void BookCollection::displayGenre(string genreName){	
	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->g.getGenreName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2) {
			cout << "Genre " << ptr->g.getGenreName() << endl;
			ptr->g.displayAllBooks();
		}
	}	
}

void BookCollection::displayAuthor(int authorID){
	int authorFlag = 0;
	int genreFlag = 0;
	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		ptr->g.checkAuthor(authorID, ptr->g.getGenreName(), authorFlag, genreFlag);
		genreFlag = 0;
	}
	if (authorFlag == 0)
		cout << "--Empty--" << endl;
}

BookCollection::GenreNode* BookCollection::findGenre(string genreName) {

	for (GenreNode* ptr = head; ptr != NULL; ptr = ptr->next) {
		string s1 = ptr->g.getGenreName();
		string s2 = genreName;
		transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
		transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

		if (s1 == s2)
			return ptr;
	}

	return NULL;
}
