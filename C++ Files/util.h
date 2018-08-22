#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates  )
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T> tempSet;
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator test;

	for(it = s1.begin(); it!= s1.end(); ++it) {
		test = s2.find(*it);
		if(test!=s2.end()) {
			tempSet.insert(*it);
		}
	}

	return tempSet;

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
	typename std::set<T> tempSet;
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator test;

	for(it = s1.begin(); it!= s1.end(); ++it) {
		tempSet.insert(*it);
	}

	for(it = s2.begin(); it!= s2.end(); ++it) {
		test = s1.find(*it);
		if(test==s1.end()) {
			tempSet.insert(*it);
		}
	}

	return tempSet;
}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/
//whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) ;

// trim from end
std::string &rtrim(std::string &s) ;

// trim from both ends
std::string &trim(std::string &s) ;
#endif
