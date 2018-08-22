#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include <map>
#include <set>
#include "review.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include "heap.h"
#include <QMessageBox>

class MyDataStore : public DataStore {

public:
	/**
     * Adds a product to the data store
     */
	void addProduct(Product* p);

    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    //void viewCart(std::string name);

    void addPtoU(std::string U, Product* P);

    //void buyCart(std::string user);

    void addReview(Review* r);

    //void getProductAvg();

    MyDataStore();

    ~MyDataStore();

    std::vector<User*> getUsersVector() {
        return uVec;
    }

    std::map <Product*, std::vector<Review*> > rMap;
    std::map<std::string, std::vector<Product*> > uMap;
    std::vector<User*> uVec;
    bool temp;



    std::map<User*, std::map<User*, double> > prMap;

    std::map<User*, double> heapValues;

    std::vector<std::pair<std::string, double> > makeSuggestion(std::string currentUser);

    //relates user to the products he reviews
    std::map<User*, std::set<Product*> > basicSimTemp; 


    void URPMap();
    void calculateBS();
    void refine(User* u);
    std::vector<Review*> rVec;
    std::vector<Product*> pVec;

private:

	std::map<std::string, std::set<Product*> > keyMap;

	 
	//std::map<std::string, std::vector<Product*> > uMap; //This is the cart

    //Review Storage
  
    //td::map <Product*, std::vector<Review*> > rMap;

    User* currUser;

    //new window for viewcart
   


};

#endif