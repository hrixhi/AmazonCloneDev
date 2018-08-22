#include "book.h"
#include "util.h"

Book::Book(const std::string category, const std::string name,
 double price, int qty, std::string aName, std::string ISBN) :
 Product(category, name, price, qty)
{
 	aName_ = aName;
 	ISBN_ = ISBN;
}


Book::~Book() {

}

std::set<std::string> Book::keywords() const {

	std::set<std::string> tempSet;
	std::set<std::string> finalSet;
	std::set<std::string>::iterator it;

	tempSet = parseStringToWords(name_);

	for(it=tempSet.begin(); it!=tempSet.end(); ++it) {
		finalSet.insert(*it);
	}
	tempSet.clear();

	tempSet = parseStringToWords(aName_);

	for(it=tempSet.begin(); it!=tempSet.end(); ++it) {
		finalSet.insert(*it);
	}
	tempSet.clear();

	finalSet.insert("book");
	finalSet.insert(ISBN_);

	return finalSet;
}

bool Book::isMatch(std::vector<std::string>& searchTerms) const {
	bool isMatch_ = false;
	std::set<std::string> set = Book::keywords();
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

std::string Book::displayString() const {

	std::stringstream ss2, ss3;
	//ss1>>name_;
	ss2<<price_;
	ss3<<qty_;
	//string name = ss1.str();
	std::string price = ss2.str();
	std::string qty = ss3.str();

	return (name_ + "\nAuthor: " + aName_ + " ISBN: " + ISBN_ 
	+ "\n" + price + " " + qty + " left.");
}

void Book::dump(std::ostream& os) const {
	os<<category_<<std::endl;
	os<<name_<<std::endl;
	os<<price_<<std::endl;
	os<<qty_<<std::endl;
	os<<ISBN_<<std::endl;
	os<<aName_<<std::endl;
}

std::string Book::getISBN() {
	return ISBN_;
}

std::string Book::getAuthName(){
	return aName_;
}