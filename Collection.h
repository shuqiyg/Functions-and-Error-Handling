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
#ifndef COLLECTION_H_
#define COLLECTION_H_
#include <string>

namespace sdds {
	template <typename T>
	class Collection {
		std::string c_name;
		T* collection;
		size_t c_size;
		void (*c_observer)(const Collection<T>& collection, const T& item);
	public:
		Collection(const std::string& name) {
			c_name = name;
			collection = nullptr;
			c_size = 0u;
			c_observer = nullptr;
		};
		Collection(const Collection&) = delete;
		Collection(Collection&&) = delete;
		Collection& operator=(const Collection&) = delete;
		Collection& operator=(Collection&&) = delete;
		~Collection() {
			delete[] collection;
			c_observer = nullptr;
		};
		const std::string& name() const {
			return c_name;
		};
		size_t size() const {
			return c_size;
		};
		void setObserver(void (*observer)(const Collection<T>& collection, const T& item)) {
			c_observer = observer;
		};
		Collection<T>& operator+=(const T& item) {
			bool exist = false;
			for (size_t i = 0; i < c_size && !exist; i++) {
				exist = collection[i].title() == item.title() ? true : false;
			}
			if (!exist) {
				T* temp_collection = new T[++c_size];
				for (size_t i = 0; i < c_size - 1; i++) {
					temp_collection[i] = collection[i];
				}
				temp_collection[c_size - 1] = item;
				delete[] collection;
				collection = std::move(temp_collection);
				if(c_observer != nullptr) c_observer(*this, item);
			}
			return *this;
		};
		T& operator[](size_t idx) const {
			if (idx < 0 || idx > c_size - 1) {
				throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(c_size) + "] items.");
			}
			return collection[idx];
		};
		T* operator[](const std::string& title) const {
			bool exist = false;
			for (size_t i = 0; i < c_size && !exist; i++) {
				exist = collection[i].title() == title ? true : false;
				if (exist) {
					return &collection[i];
				}
			}
			return nullptr;	
		};
	};
	template<typename T>
	std::ostream& operator << (std::ostream& os, const Collection<T>& col) {
		for (size_t i = 0; i < col.size(); i++) {
			os << col[i];
		}
		return os;
	};
}


#endif // !COLLECTION_H_

