#include "util.h"
#include "clothing.h"
#include <sstream>


Clothing::Clothing(const std::string category, const std::string name, 
	double price, int qty, std::string size, std::string brand) :
	Product(category, name, price, qty), size_(size), brand_(brand) {

		size_ = size;
		brand_ = brand;

}
		
Clothing::~Clothing() {

}
		
std::set<std::string> Clothing::keywords() const {
	std::set<std::string> tempSet;
	std::set<std::string> finalSet;
	std::set<std::string>::iterator it;

	tempSet = parseStringToWords(name_);

	for(it=tempSet.begin(); it!=tempSet.end(); ++it) {
		finalSet.insert(*it);
	}
	tempSet.clear();

	tempSet = parseStringToWords(brand_);

	for(it=tempSet.begin(); it!=tempSet.end(); ++it) {
		finalSet.insert(*it);
	}
	tempSet.clear();
	finalSet.insert("clothing");

	return finalSet;

}
		
bool Clothing::isMatch(std::vector<std::string>& searchTerms) const {

	bool isMatch_ = false;
	std::set<std::string> set = Clothing::keywords();
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

std::string Clothing::displayString() const {

	std::stringstream ss2, ss3;
	//ss1>>name_;
	ss2<<price_;
	ss3<<qty_;
	//string name = ss1.str();
	std::string price = ss2.str();
	std::string qty = ss3.str();

	return (name_ + "\nBrand: " + brand_ + " Size: " + size_ 
		+ "\n" + price + " " + qty + " left.");
}

void Clothing::dump(std::ostream& os) const {
	os<<category_<<std::endl;
	os<<name_<<std::endl;
	os<<price_<<std::endl;
	os<<qty_<<std::endl;
	os<<size_<<std::endl;
	os<<brand_<<std::endl;
}

std::string Clothing::getSize() {
	return size_;
}

std::string Clothing::getBrand() {
	return brand_;
}