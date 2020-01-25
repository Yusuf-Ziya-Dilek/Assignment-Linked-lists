#ifndef __GENRE_H 
#define __GENRE_H 

#include <string> 
using namespace std;
#include "Book.h"

class Genre {
public:
	Genre(const string gname = "");
	~Genre();
	Genre(const Genre& genreToCopy);
	void operator=(const Genre& right);
	string getGenreName() const;
	void setGenreName(const string gName);
	void displayAllBooks();
	void addBook(string bookName);
	void removeBook(string bookName);
	void addAuthor(string bookName, int authorID, string authorName);
	void removeAuthor(string bookName, int authorID);
	void checkAuthor(int id, string genreName, int& authorFlag, int& genreFlag);

	

private:

	struct BookNode {
		Book a;
		BookNode* next;
	};

	BookNode* head;

	string genreName;
};
#endif
