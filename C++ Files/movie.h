#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

#include "product.h"
#include "util.h"

class Movie : public Product {
	public:
		Movie(const std::string category, const std::string name, 
		double price, int qty, std::string genre, std::string rate);
		~Movie();
		std::set<std::string> keywords() const;
		bool isMatch(std::vector<std::string>& searchTerms) const;
		std::string displayString() const;
		void dump(std::ostream& os) const;
		std::string getGenre();
		std::string getRating();
	private:
		std::string genre_;
		std::string rating_;
};

#endif