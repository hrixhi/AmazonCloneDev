#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
	
	string preTest, postTest = "";
	int lastPunc = -1;
	bool temp = true;
	set<string> tempSet;

	istringstream ss;
	ss.str(rawWords);

	while(ss>>preTest) {
		
		//ss>>preTest;		DOES IT TO BOTH!!!???
		temp = true;
		lastPunc = -1;
		postTest = "";

		for(unsigned int i = 0; i<preTest.length(); i++) {
			if(ispunct(preTest[i])) {
				temp = false;
				break;
			}
		}

		if(temp == true && preTest.length()>=2) {
			tempSet.insert(convToLower(preTest));
		}
		else {
			for(unsigned int i = 0; i<preTest.length(); i++) {

				if(ispunct(preTest[i])) {
					if(i-lastPunc>=3) {
						for(unsigned int j = lastPunc+1; j<i; j++) {
							postTest = postTest + preTest[j];
						}
						tempSet.insert(convToLower(postTest));
						postTest = "";
						lastPunc = i;
					}
					else {
						lastPunc = i;
					}
				}

			}

			if(preTest.length() - lastPunc >=3) {
				for(unsigned int j = lastPunc+1; j<preTest.length(); j++) {
					postTest = postTest + preTest[j];
				}
				tempSet.insert(convToLower(postTest));
				postTest = "";
			}
		}

	}
	return tempSet;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823
 ///whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
