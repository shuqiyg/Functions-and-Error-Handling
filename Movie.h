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

#ifndef MOVIE_H_
#define MOVIE_H_

namespace sdds {
	class Movie {
		std::string m_title {};
		size_t release_year {};
		std::string m_desc{};
	public:
		Movie();
		const std::string& title() const;
		Movie(const std::string& strMovie);
		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(this->m_title);
			spellChecker(this->m_desc);
		};
		friend std::ostream& operator << (std::ostream&, const Movie&);
	};
}

#endif // !MOVIE_H_

