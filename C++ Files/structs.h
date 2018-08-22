#include "mw.h"

struct AlphaStrComp {
    bool operator()(Product* lhs, Product* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs->getName() < rhs->getName(); 
    }
  };

 struct RatingComp {
    bool operator()(Product* lhs, Product* rhs) 
    { 
    	int avg1 = 0, avg2 = 0;

    	if(dbPtr->rMap.find(lhs) != dbPtr->rMap.end()) {
    		for(unsigned int i = 0; i < rMap[lhs].size(); i++) {
    			avg1 += rMap[lhs][i]->rating;
    		}
    		avg1 = avg1/rMap[lhs].size();
    	}

    	if(dbPtr->rMap.find(rhs) != dbPtr->rMap.end()) {
    		for(unsigned int i = 0; i < rMap[rhs].size(); i++) {
    			avg2 += rMap[rhs][i]->rating;
    		}
    		avg2 = avg2/rMap[rhs].size();
    	}

      return avg1 < avg2; 
    }
  };

  struct OldFirst {
    bool operator()(Review* lhs, Review* rhs) 
    { 
    	int date1 = lhs->date;
    	int date2 = rhs->date;

    	bool v;

    	for(int i =0; i<10; i++) {
    		
    		if(i == 4 || i == 7) {
    			continue;
    		}

    		if(date1[i] != date2[i]) {
    			return date1[i] < date2[i];
    		}
    	}

      return true;
    }
  };


  struct newFirst {
    bool operator()(Review* lhs, Review* rhs) 
    { 
    	int date1 = lhs->date;
    	int date2 = rhs->date;

    	bool v;

    	for(int i =0; i<10; i++) {
    		
    		if(i == 4 || i == 7) {
    			continue;
    		}

    		if(date1[i] != date2[i]) {
    			return date1[i] > date2[i];
    		}
    	}

      return true;
    }
  };