// Workshop 5 - Functions and Error Handling
// 2020/02 - Cornel
// 2021/01/19 - Chris
// 2021/02/12 - Cornel

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Collection.h"
#include "Collection.h"
#include "Book.h"
#include "Book.h"
#include "Movie.h"
#include "Movie.h"
#include "SpellChecker.h"
#include "SpellChecker.h"

using namespace sdds;

enum AppErrors
{
	CannotOpenFile = 1, // An input file cannot be opened
	BadArgumentCount = 2, // The application didn't receive anough parameters
};

// The observer function for adding books to the collection:
//   should be called every time a new book is added to the collection
void bookAddedObserver(const Collection<Book>& theCollection,
	const Book& theBook)
{
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

// The observer function for adding movies to the collection:
//   should be called every time a new movie is added to the collection
void movieAddedObserver(const Collection<Movie>& theCollection,
	const Movie& theMovie)
{
	std::cout << "Movie \"" << theMovie.title()
		<< "\" added to collection \"" << theCollection.name()
		<< "\" (" << theCollection.size() << " items).\n";
}

// ws books.txt movies.txt file_missing.txt file_words.txt
int main(int argc, char** argv)
{
	std::cout << "Command Line:\n";
	std::cout << "--------------------------\n";
	for (int i = 0; i < argc; i++)
		std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
	std::cout << "--------------------------\n\n";

	// get the books
	sdds::Collection<sdds::Book> library("Bestsellers");
	if (argc == 5) {
		std::ifstream file(argv[1]);
		if (!file) exit(AppErrors::CannotOpenFile);
		std::string book;
		size_t index = 0;
		do {
			std::getline(file, book);
			if (book[0] != '#') {
				library += Book(book);
				index++;
			}
		} while (file && index < 4);

		library.setObserver(bookAddedObserver);

		do {
			std::getline(file, book);
			if (book[0] != '#') {
				library += Book(book);
				index++;
			}
		} while (file && index < 7);
		file.close();
	}
	else
	{
		std::cerr << "ERROR: Incorrect number of arguments.\n";
		exit(AppErrors::BadArgumentCount);
	}

	double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;

	auto price_adj = [=](Book& bk) {
		if (bk.country() == "US") {
			bk.price() = bk.price() * usdToCadRate;
		}
		else if (bk.country() == "UK" && bk.year() >= 1990 && bk.year() <= 1999) {
			bk.price() = bk.price() * gbpToCadRate;
		}
	};


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	for (size_t i = 0; i < library.size(); i++) {
		price_adj(library[i]);
	}


	std::cout << "-----------------------------------------\n";
	std::cout << "The library content (updated prices)\n";
	std::cout << "-----------------------------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n\n";

	Collection<Movie> theCollection("Action Movies");

	// Process the file
	Movie movies[5];
	if (argc > 2) {
		std::ifstream file(argv[2]);
		if (!file) exit(AppErrors::CannotOpenFile);
		std::string temp;
		size_t index = 0;
		do {
			std::getline(file, temp);
			if (temp[0] != '#') {
				movies[index] = Movie(temp);
				index++;
			}
		} while (file && index < 5);
		file.close();
	}

	std::cout << "-----------------------------------------\n";
	std::cout << "Testing addition and callback function\n";
	std::cout << "-----------------------------------------\n";
	if (argc > 2) {
		((theCollection += movies[0]) += movies[1]) += movies[2];
		theCollection += movies[1];
		theCollection.setObserver(movieAddedObserver);
		theCollection += movies[3];
		theCollection += movies[3];
		theCollection += movies[4];
	}
	else {
		std::cout << "** No movies in the Collection\n";
	}
	std::cout << "-----------------------------------------\n\n";
	
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing exceptions and operator[]\n";
	std::cout << "-----------------------------------------\n";

	try {
		for (auto i = 0u; i < 10; ++i)
			std::cout << theCollection[i];
	}
	catch (const std::out_of_range& out) {
		std::cout << "** EXCEPTION: " << out.what() << std::endl;

	}
		
	std::cout << "-----------------------------------------\n\n";


	std::cout << "-----------------------------------------\n";
	std::cout << "Testing the functor\n";
	std::cout << "-----------------------------------------\n";
	for (auto i = 3; i < argc; ++i)
	{
		try {
			SpellChecker sp(argv[i]);
			for (auto j = 0u; j < library.size(); ++j)
				library[j].fixSpelling(sp);
			sp.showStatistics(std::cout);

			for (auto j = 0u; j < theCollection.size(); ++j)
				theCollection[j].fixSpelling(sp);
			sp.showStatistics(std::cout);
		}
		catch (const char* exception) {
			std::cout << "** EXCEPTION: " << exception << std::endl;
		}
			
	}
	if (argc < 3) {
		std::cout << "** Spellchecker is empty\n";
		std::cout << "-----------------------------------------\n";
	}
	std::cout << "\n";

	std::cout << "=========================================\n";
	std::cout << "Wrapping up this workshop\n";
	std::cout << "--------------- Movies ------------------\n";
	std::cout << theCollection;
	std::cout << "--------------- Books -------------------\n";
	std::cout << library;
	std::cout << "-----------------------------------------\n";
	std::cout << "Testing operator[] (the other overload)\n";
	std::cout << "-----------------------------------------\n";
	const Movie* aMovie = theCollection["Terminator 2"];
	if (aMovie == nullptr)
		std::cout << "** Movie Terminator 2 not in collection.\n";
	aMovie = theCollection["Dark Phoenix"];
	if (aMovie != nullptr)
		std::cout << "In this collection:\n" << *aMovie;
	std::cout << "-----------------------------------------\n\n";

	return 0;
}
