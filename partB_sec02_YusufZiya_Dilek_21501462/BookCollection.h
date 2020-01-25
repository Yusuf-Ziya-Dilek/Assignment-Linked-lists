#ifndef __BOOKCOLLECTION_H
#define __BOOKCOLLECTION_H 

#include <string> 
using namespace std;
#include "Genre.h" 

class BookCollection {
public:
	BookCollection();
	~BookCollection();
	BookCollection(const BookCollection& bcToCopy);
	void operator=(const BookCollection& right);	
	bool addGenre(const string genreName);
	bool removeGenre(const string genreName);
	void displayAllGenres() const;
	string getName() const;
	void setName(const string bcName);

	//new methods for part B//
	void addBook(string genreName, string bookName);   
	void removeBook(string genreName, string  bookName);   
	void addAuthor(string genreName, string bookName, int authorID, string authorName);   
	void removeAuthor(string genreName, string bookName, int authorID);    
	void displayGenre(string genreName);     
	void displayAuthor(int authorID);

private:
	struct GenreNode {
		Genre g;
		GenreNode* next;
	};

	string name;
	int genreCount;

	GenreNode* head;
	GenreNode* findGenre(string genreName);

};
#endif
