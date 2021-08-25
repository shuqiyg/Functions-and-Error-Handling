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

#ifndef SPELLCHECKER_H_
#define SPELLCHECKER_H_

constexpr unsigned M_WORDS{ 6 };
namespace sdds {
	/*class BadWords_Count {
		unsigned count{};
	public:
		BadWords_Count& operator++(int);
		unsigned re_count() const;
	};*/
	class SpellChecker {
		std::string m_badWords[M_WORDS]{};
		std::string m_goodWords[M_WORDS]{};
		unsigned badWords_count[M_WORDS]{};
	public:
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;
	};	
}

#endif // !SPELLCHECKER_H_

