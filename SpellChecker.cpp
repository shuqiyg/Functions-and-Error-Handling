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
#include <fstream>
#include <iomanip>
#include <string>
#include "SpellChecker.h"

namespace sdds {
	SpellChecker::SpellChecker(const char* filename) {
		std::ifstream file(filename);
		if (!file) throw "Bad file name!";
		std::string input;
		size_t index = 0;
		do {
			std::getline(file, input);
			int first_space = input.find_first_of(' ');
			m_badWords[index] = input.substr(0, first_space);
			m_goodWords[index] = input.substr(input.find_last_of(' ') + 1);
			index++;
		} while (file && index < 6);
		file.close();
	}
	void SpellChecker::operator()(std::string& text) {
		for (unsigned i = 0; i < 6; i++) {
			size_t bword_pos{};
			while(bword_pos != std::string::npos)
			{
				bword_pos = text.find(m_badWords[i]);
				if (bword_pos != std::string::npos) {
					text.replace(bword_pos, m_badWords[i].length(), m_goodWords[i]);
					badWords_count[i]++;
					bword_pos = text.find(m_goodWords[i]) + m_goodWords[i].length();
				};		
			}
		}
	}
	void SpellChecker::showStatistics(std::ostream& os) const {
		os << "Spellchecker Statistics" << std::endl;
		for (size_t i = 0; i < 6; i++) {
			os << std::setw(15) << std::right << m_badWords[i] << ": " << badWords_count[i] << " replacements" << std::endl;
		}
	}
}