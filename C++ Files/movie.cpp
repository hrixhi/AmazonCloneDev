#include "util.h"
#include "movie.h"
#include <sstream>

Movie::Movie(const std::string category, const std::string name, double price,
 int qty, std::string genre, std::string rate) : 
Product(category, name, price, qty) //genre_(genre), rating_(rate) {
	{
		genre_ = genre;
		rating_ = rate;
	}

Movie::~Movie() {

}

std::set<std::string> Movie::keywords() const {
	std::set<std::string> tempSet;
	std::set<std::string> finalSet;
	std::set<std::string>::iterator it;

	tempSet = parseStringToWords(name_);

	for(it=tempSet.begin(); it!=tempSet.end(); ++it) {
		finalSet.insert(*it);
	}
	tempSet.clear();

	tempSet = parseStringToWords(genre_);

	for(it=tempSet.begin(); it!=tempSet.end(); ++it) {
		finalSet.insert(*it);
	}
	tempSet.clear();
	finalSet.insert("movie");

	return finalSet;
}

bool Movie::isMatch(std::vector<std::string>& searchTerms) const {
	bool isMatch_ = false;
	std::set<std::string> set = Movie::keywords();
	std::set<std::string>::iterator it;

	for(unsigned int i = 0; i<searchTerms.size(); i++) {
		it = set.find(searchTerms[i]);
		if(it != set.end()) {
			isMatch_ = true;
			break;
		}
	}

	return isMatch_;
}

std::string Movie::displayString() const {
	std::stringstream ss2, ss3;
	//ss1>>name_;
	ss2<<price_;
	ss3<<qty_;
	//string name = ss1.str();
	std::string price = ss2.str();
	std::string qty = ss3.str();

	return (name_ + "\nGenre: " + genre_ + " Rating: " + rating_ 
		+ "\n" + price + " " + qty + " left.");
}

void Movie::dump(std::ostream& os) const {
	os<<category_<<std::endl;
	os<<name_<<std::endl;
	os<<price_<<std::endl;
	os<<qty_<<std::endl;
	os<<genre_<<std::endl;
	os<<rating_<<std::endl;
}

std::string Movie::getGenre() {
	return genre_;
}

std::string Movie::getRating() {
	return rating_;
}