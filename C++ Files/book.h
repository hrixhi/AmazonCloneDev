#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>

#include "product.h"
#include "util.h"

class Book : public Product {
	public:
		Book(const std::string category, const std::string name, 
	double price, int qty, std::string aName, std::string ISBN);
		~Book();
		std::set<std::string> keywords() const;
		bool isMatch(std::vector<std::string>& searchTerms) const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
		std::string getISBN();
		std::string getAuthName();
	private:
		std::string ISBN_;
		std::string aName_;
};

#endif