#include "mydatastore.h"
#include "util.h"
#include "msort.h"
#include <cmath>

struct ProductRecommendationSorter {
    bool operator()(std::pair<std::string, double> p1, std::pair<std::string, double> p2) {
        if(p1.second != p2.second)
        {
           return (p1.second > p2.second);
        }
        else
        {
           return (p1.first < p2.first);
        }
    }
};

void MyDataStore::addProduct(Product* p) {

	pVec.push_back(p);
	std::set<std::string> tempSet = p->keywords(); 
	std::set<std::string>::iterator it;

	for(it = tempSet.begin(); it != tempSet.end(); ++it) {
		if(keyMap.find(*it) == keyMap.end()) {
			//keyMap.insert(make_pair((*it), p));
			(keyMap[*it]).insert(p);
		}
		else {
			(keyMap.find(*it))->second.insert(p);
		}
	}

	
}

void MyDataStore::URPMap() {


	User* tempUser;
	Product* tempProduct;
	std::set<Product*> tempSetProduct;


	for(unsigned int j = 0; j<uVec.size(); j++) {

		basicSimTemp[uVec[j]] = tempSetProduct;

	}



	for(unsigned int i = 0; i<rVec.size(); i++) {

		for(unsigned int j = 0; j<uVec.size(); j++) {
			
			if(uVec[j]->getName() == rVec[i]->username) {
				tempUser = uVec[j];
				break;
			}
			
		}

		for(unsigned int j = 0; j<pVec.size(); j++) {
			
			if(pVec[j]->getName() == rVec[i]->prodName) {
				tempProduct = pVec[j];
				break;
			}
			
		}


		basicSimTemp[tempUser].insert(tempProduct);

	}

	

}


void MyDataStore::calculateBS() {


	for(unsigned int i = 0; i<uVec.size(); i++) {
		for(unsigned int j = 0; j<uVec.size(); j++) {

			if(i == j) {
				continue;
			}

			std::map<User*, double> mapinmap;

			mapinmap[uVec[j]] = 1;

			std::set<Product*> A = basicSimTemp[uVec[i]];
			std::set<Product*> B = basicSimTemp[uVec[j]];

			std::set<Product*> AIB = setIntersection(A, B);


			std::set<Product*>::iterator it;

			std::vector<int> forAverage;

			if(AIB.begin() == AIB.end()) {
				prMap[uVec[i]] = mapinmap;
			}

			for(it = AIB.begin(); it!= AIB.end(); ++it) {


				int a = 0, b = 0;

				for(unsigned int k = 0; k<rVec.size(); k++) {

					if(rVec[k]->username == uVec[i]->getName() && rVec[k]->prodName == (*it)->getName()) {
						a = rVec[k]->rating;
					}

					if(rVec[k]->username == uVec[j]->getName() && rVec[k]->prodName == (*it)->getName()) {
						b = rVec[k]->rating;
					}

					int x = (abs(a - b))/4; forAverage.push_back(x);

				}  
			}

			double sim = 0;
			for(unsigned int q = 0; q<forAverage.size(); q++) {
				sim += forAverage[q];
			}

			sim = sim/forAverage.size();

			mapinmap[uVec[j]] = sim;
			prMap[uVec[i]] = mapinmap;

		}
	}


}

std::vector<std::pair<std::string, double> > MyDataStore::makeSuggestion(std::string currentUser) {


   User* user;
   std::set<User*>::iterator it;
   //bool found = false;
      
   // for(it = user_set.begin(); it != user_set.end(); ++it)
   // {     
   //    if((*it)->getName() == currentUser)
   //    {
   //       user = *it;
   //       //found = true;
   //       break;
   //    }       
   // }

   for(unsigned int i = 0; i < uVec.size(); i++) {

   		if(currentUser == uVec[i]->getName()) {
   			user = uVec[i];
   			break;
   		}

   }


   //std::cout<<user->getName()<<std::endl;
   std::vector<Product* > tem;

   std::map<User*, std::vector<Product*> > user_product_map;

   user_product_map[user] = tem;


   for(unsigned int i = 0; i<rVec.size(); i++) {

   		if(rVec[i]->username == user->getName()) {

   			Product* qqq;

   			for(unsigned int j = 0; j<pVec.size(); j++) {
   				if(pVec[j]->getName() == rVec[i]->prodName) {
   					qqq = pVec[j];
   					break;
   				}
   			}

   			user_product_map[user].push_back(qqq);
   		}

   }
   
   std::set<Product*>::iterator set_it1;
   std::set<Product*>::iterator set_it2;
   
   //std::set<Product*> products = user_product_map[user];
  
   std::vector<std::pair<Product*, double> > user_map;
   std::vector<std::pair<Product*, double> > user_map1;
   std::vector<std::pair<Product*, double> >::iterator iit;


   for(unsigned i = 0; i<pVec.size(); i++) {

   		// if(user_product_map[user].find(pVec[i]) == user_product_map[user].end()) {
   		// 	user_map.push_back(std::make_pair(pVec[i], 0));
   		// }
   		bool t = false;

   		for(unsigned int j = 0; j<user_product_map[user].size(); j++) {
   			if(user_product_map[user][j] == pVec[i]) {
   				t = true;
   			}
   		}

   		if(!t) {
   			user_map.push_back(std::make_pair(pVec[i], 0));
   		}

   }
   
   for(unsigned int i=0;i<user_map.size(); i++)
   {
      std::string product = (user_map[i].first)->getName();
     

      std::set<Review*> reviews; 

      for(unsigned int i = 0; i<rVec.size(); i++) {

      	if(rVec[i]->prodName == product) {
      		reviews.insert(rVec[i]);
      	}

      }

      //= review_map[product];
      std::set<Review*>::iterator review_it;


      double R = 0;
      double W = 0;


      for(review_it=reviews.begin();review_it!=reviews.end();++review_it)
      {
         std::string user_name = (*review_it)->username;
         double r = (double)((*review_it)->rating);

         User* tempuser;
         for(unsigned int i = 0; i<uVec.size(); i++) {
         	if(uVec[i]->getName() == (*review_it)->username) {
         		tempuser = uVec[i];
         		break;
         	}
         }

         double s = heapValues[tempuser];
         R += ((1-s)*r);
         W += (1-s);
      }
      
      double rating_of_P;
      if(W == 0)
      {
         rating_of_P = 0;
      }
      else
      {
         rating_of_P = R/W;
      }
      
      user_map1.push_back(std::make_pair(user_map[i].first, rating_of_P));

       
   }


   	std::vector<std::pair<std::string, double> > temp;


   	for(iit  = user_map1.begin(); iit!= user_map1.end() ; ++iit) {
   		temp.push_back(std::make_pair(iit->first->getName(), iit->second));

   	}

ProductRecommendationSorter p;
mergeSort(temp,p);
   
   return temp;


}

void MyDataStore::refine(User* uPtr) {

	Heap<std::string> PQ;

	heapValues.clear();

	std::map<User*, double> tempSetx = prMap[uPtr]; 

	std::map<User*, double>::iterator it;

	PQ.push(0, uPtr->getName());
	heapValues.insert(std::make_pair(uPtr, 0))	;

	for(it = tempSetx.begin(); it != tempSetx.end(); ++it) {
		PQ.push(it->second, it->first->getName());
		heapValues[it->first] = it->second;
	}

	while(!PQ.empty()) {

		//std::string v = PQ.top();
		User* v;

		for(unsigned int i = 0; i<uVec.size(); i++) {
			if(PQ.top() == uVec[i]->getName()) {
				v = uVec[i];
				break;
			}
		}


		PQ.pop();
		std::map<User*, double> temp = prMap[v];	

		std::map<User*, double>::iterator itx;

		for(itx = tempSetx.begin(); itx!= tempSetx.end(); ++itx)
		{
			User* u = itx->first;
			double w = itx->second;
			if(tempSetx[u] + w < tempSetx[u])
			{
				PQ.decreaseKey(tempSetx[v] + w, u->getName());
				tempSetx[u]=tempSetx[v] + w;
				heapValues[it->first] = it->second;
			}

		}

	}



}


MyDataStore::MyDataStore() {//: currUser(NULL), temp(false) {
	currUser = NULL;
	temp = false;
}

MyDataStore::~MyDataStore() {
	for(unsigned int i = 0; i<uVec.size(); i++) {
		delete uVec[i];
	}

	for(unsigned int i = 0; i<pVec.size(); i++) {
		delete pVec[i];
	}

	for(unsigned int i = 0; i<rVec.size(); i++) {
		delete rVec[i];
	}
}

void MyDataStore::addUser(User* u) {
	uVec.push_back(u);
	std::vector<Product*> temp;

	uMap.insert(make_pair(u->getName(), temp));
}


void MyDataStore::addPtoU(std::string U, Product* P) {
	
	if(uMap.find(U) == uMap.end()) {
		//std::cout<<"Invalid Username"<<std::endl;
		return;
	}

	uMap[U].push_back(P);
}



//0 is AND
//1 is OR

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, 
	int type) {

	std::set<std::set<Product*> > keySet;	//set of set of products
	std::set<Product*> newset;				//set of products

	std::set<std::set<Product*> >::iterator it;	//iterator for keySet
	std::set<Product*>::iterator itx; //iterator for newset

	std::vector<Product*> toReturn;

	for(unsigned int i = 0; i<terms.size(); i++) {
		if(keyMap.find(terms[i])!=keyMap.end()) {
			keySet.insert(keyMap.find(terms[i])->second);
		}
	}

	if (keySet.size() == 0) return toReturn;

	if(type == 0) {

		// if(keySet.size() != terms.size() ) {
		// 	return toReturn;
		// }
		
			it = keySet.begin();
			newset = *it;
			//newset = *(keySet.begin());
			//newset = (keySet.begin());
		for(it=keySet.begin(); it!=keySet.end(); ++it) {
			std::set<Product*> temp = *it;
			newset = setIntersection<Product*>(newset, temp);
		}
	}
	else if(type == 1) {



		it = keySet.begin();
			newset = *it;
		for(it=keySet.begin(); it!=keySet.end(); ++it) {
			std::set<Product*> temp = *it;
			newset = setUnion<Product*> (newset, temp);
		}
	}

	for(itx = newset.begin(); itx!=newset.end(); ++itx) {
			toReturn.push_back(*itx);
	}

	return toReturn;
}

void MyDataStore::dump(std::ostream& ofile) {
	ofile<<"<products>"<<std::endl;
	for(unsigned int i =0; i<pVec.size(); i++) {
		pVec[i]->dump(ofile);
	}
	ofile<<"</products>"<<std::endl;

	ofile<<"<users>"<<std::endl;
	for(unsigned int i =0; i<uVec.size(); i++) {
		uVec[i]->dump(ofile);
	}
	ofile<<"</users>"<<std::endl;

	ofile<<"<reviews>"<<std::endl;
	for(unsigned int i =0; i<rVec.size(); i++) {
		ofile<<rVec[i]->prodName<<std::endl;
		ofile<<rVec[i]->rating<<" ";
		ofile<<rVec[i]->username<<" ";
		ofile<<rVec[i]->date<<" ";
		ofile<<rVec[i]->reviewText<<std::endl;

	}
	ofile<<"</reviews>"<<std::endl;
}

//This is for HW5 - Review

void MyDataStore::addReview(Review* r) {

	rVec.push_back(r); //Dump storage
	
	unsigned int i;

	for(i = 0; i<pVec.size(); i++) {
		if(pVec[i]->getName() == r->prodName) {
			break;
		}
	}

	if(rMap.find(pVec[i]) == rMap.end()) {
		std::vector<Review*> temp;
		rMap[pVec[i]] = temp;
		rMap[pVec[i]].push_back(r);
	}
	else {
		rMap[pVec[i]].push_back(r);
	}

}

