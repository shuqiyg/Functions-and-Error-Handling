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
#ifndef BOOK_H_
#define BOOK_H_

namespace sdds {
	class Book {
		std::string author{};
		std::string bk_title{};
		std::string bk_country{};
		size_t bk_year{};
		double bk_price{};
		std::string desc{};
	public:
		Book();
		const std::string& title() const;
		const std::string& country() const;
		const size_t& year() const;
		double& price();
		Book(const std::string& strBook);
		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(this->desc);
		}
		friend std::ostream& operator << (std::ostream&, const Book&);
	};
}

#endif
