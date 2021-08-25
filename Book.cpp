/* Workshop 5 - Functions and Error Handling
   Name: Shuqi Yang
   Std ID: 132162207
   Email: syang136@myseneca.ca
   Date: 06-28-2021
   -------------------------------------------------------
   I have done all the coding by myself and only copied the
   code that my professor provided to complete my workshops
   and assignments.
 */
#include <iostream>
#include <string>
#include <iomanip>
#include "Book.h"

namespace sdds {
	Book::Book() {}
	Book::Book(const std::string& strBook) {
		//author
		unsigned first_comma = strBook.find(",");
		author = strBook.substr(0, first_comma);
		unsigned start = author.find_first_not_of(' ');
		unsigned end = author.find_last_not_of(' ');
		author = author.substr(start, end - start + 1);
		//title
		unsigned title_pos = first_comma + 1;
		unsigned scd_comma = strBook.find(',', title_pos);
		bk_title = strBook.substr(title_pos, scd_comma - title_pos);
		start = bk_title.find_first_not_of(' ');
		end = bk_title.find_last_not_of(' ');
		bk_title = bk_title.substr(start, end - start + 1);
		//country
		unsigned country_pos = scd_comma + 1;
		unsigned third_comma = strBook.find(',', country_pos);
		bk_country = strBook.substr(country_pos, third_comma - country_pos);
		start = bk_country.find_first_not_of(' ');
		end = bk_country.find_last_not_of(' ');
		bk_country = bk_country.substr(start, end - start + 1);
		//price
		unsigned price_pos = third_comma + 1;
		unsigned fourth_comma = strBook.find(',', price_pos);
		std::string price_str = strBook.substr(price_pos, fourth_comma - price_pos + 1);
		bk_price = stod(price_str);
		//year
		unsigned year_pos = fourth_comma + 1;
		unsigned fifth_comma = strBook.find(',', year_pos);
		std::string year_str = strBook.substr(year_pos, fifth_comma - year_pos + 1);
		bk_year = stoi(year_str);
		//description
		unsigned desc_pos = fifth_comma + 1;
		desc = strBook.substr(desc_pos);
		start = desc.find_first_not_of(' ');
		end = desc.find_last_not_of(' ');
		desc = desc.substr(start, end - start + 1);
	}
	const std::string& Book::title() const {
		return bk_title;
	}
	const std::string& Book::country() const {
		return bk_country;
	}
	const size_t& Book::year() const {
		return bk_year;
	}
	double& Book::price() {
		return bk_price;
	}

	std::ostream& operator << (std::ostream& os, const Book& book){
		os << std::setw(20) << book.author << " | " << std::setw(22) << book.bk_title << " | " << std::setw(5) << book.bk_country << " | " << std::setw(4) << book.bk_year << " | " << std::setw(6) << std::fixed << std::setprecision(2) << book.bk_price << " | " << book.desc << std::endl;
		return os;
	}
}