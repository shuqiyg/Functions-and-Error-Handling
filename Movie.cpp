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

#include <ostream>
#include <iomanip>
#include <string>
#include "Movie.h"

namespace sdds {
	Movie::Movie() {};
	const std::string& Movie::title() const {
		return this->m_title;
	}
	Movie::Movie(const std::string& strMovie) {
		//title
		unsigned first_comma = strMovie.find(",");
		m_title = strMovie.substr(0, first_comma);
		unsigned start = m_title.find_first_not_of(' ');
		unsigned end = m_title.find_last_not_of(' ');
		m_title = m_title.substr(start, end - start + 1);
		//year
		unsigned year_pos = first_comma + 1;
		unsigned second_comma = strMovie.find(',', year_pos);
		std::string year_str = strMovie.substr(year_pos, second_comma - year_pos + 1);
		release_year = stoi(year_str);
		//description
		unsigned desc_pos = second_comma + 1;
		m_desc = strMovie.substr(desc_pos);
		start = m_desc.find_first_not_of(' ');
		end = m_desc.find_last_not_of(' ');
		m_desc = m_desc.substr(start, end - start + 1);
	}
	std::ostream& operator << (std::ostream& os, const Movie& movie) {
		os << std::setw(40) << movie.m_title << " | " << std::setw(4) << movie.release_year << " | " << movie.m_desc << std::endl;
		return os;
	}
}