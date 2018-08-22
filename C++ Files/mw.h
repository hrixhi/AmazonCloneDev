#ifndef MW_H
#define MW_H

#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include "mydatastore.h"
#include "datastore.h"
#include <QComboBox>
#include <QRadioButton>
#include <QFileDialog>
#include <fstream>
#include <string>
#include <vector>
#include "util.h"
#include <sstream>
#include "msort.h"
#include <QMessageBox>
#include "mw.h"
#include <fstream>

struct alphaStrComp {
    bool operator()(Product* lhs, Product* rhs) 
    { // Uses string's built in operator< 
      // to do lexicographic (alphabetical) comparison
      return lhs->getName() < rhs->getName(); 
    }
  };

 extern MyDataStore* dbPtrx;

 struct RatingComp {
    bool operator()(Product* lhs, Product* rhs) 
    { 
    	int avg1 = 0, avg2 = 0;

    	if(dbPtrx->rMap.find(lhs) != dbPtrx->rMap.end()) {
    		for(unsigned int i = 0; i < dbPtrx->rMap[lhs].size(); i++) {
    			avg1 += dbPtrx->rMap[lhs][i]->rating;
    		}
    		avg1 = avg1/dbPtrx->rMap[lhs].size();
    	}

    	if(dbPtrx->rMap.find(rhs) != dbPtrx->rMap.end()) {
    		for(unsigned int i = 0; i < dbPtrx->rMap[rhs].size(); i++) {
    			avg2 += dbPtrx->rMap[rhs][i]->rating;
    		}
    		avg2 = avg2/dbPtrx->rMap[rhs].size();
    	}

      return avg1 < avg2; 
    }
  };

  struct OldFirst {
    bool operator()(Review* lhs, Review* rhs) 
    { 
    	
      return lhs->date < rhs->date;
    }
  };


  struct newFirst {
    bool operator()(Review* lhs, Review* rhs) 
    {
      return lhs->date > rhs->date;
    }
  };


class mainWindow : public QWidget {
	Q_OBJECT
public:
	//mainWindow();
	mainWindow(MyDataStore* ar);
	~mainWindow();

	void setU(User* u);

	void setPtr(MyDataStore* db);
	void viewCartx(std::string name, MyDataStore* ptr);
    void buyCartxxx(std::string user, MyDataStore* ptr);

private slots:
	void changeUser();
	//void changeUser(int x);
	void viewCart();
	void buyCart();
	void saveDB();
	void search();
	void changeToAnd();
	void changeToOr();
	void sortHits(int x);
	void productSelected(QListWidgetItem* itemx);
	void sortChanged(int x);
	void addToCart();
	void revFunc();
	void addReviewFunc();
	void textCheck();

	void LOG();
	void prodRec();

	void buyCartxx();
    void deleteElementCart();


private:
	MyDataStore *dbPtr;
	User* selectedUserPtr;
	Product* selectedProductPtr;

	User* u;

	QPushButton *pR;
	QPushButton *logout;

	//Basic layout
	QHBoxLayout *mainLayout;
	QVBoxLayout *userArea;
	QVBoxLayout *searchArea;
	QVBoxLayout *productArea;

	//userArea
	QLabel *AMAZON;
	QLabel *selectUser;
	QLineEdit *usernameInput;
	QPushButton *usernameInputSearch;
	QHBoxLayout *usernameInputLayout;
	QLabel *Or;
	QLabel* selectedU;
	QComboBox *userList;
	QPushButton *buycart;
	QPushButton *viewcart;
	QHBoxLayout *lastOptions;
	QPushButton *saveDatabase;
	QPushButton *quit;
	QPushButton *rev;

	//searchArea
	QLabel *searchx;
	QLineEdit *productInput;
	QPushButton *productInputSearch;
	QHBoxLayout *productInputLayout;
	QRadioButton *andButton;
	QRadioButton *orButton;
	QComboBox *whichSortList;
	QListWidget *searchResults;
	QHBoxLayout *RBLayout;

	//productArea
	QLabel *productName;
	QLabel *pName;
	QComboBox *sortReviews;
	QListWidget *reviews;
	QPushButton *addCart;

	//new window for viewCart
	QListWidget *cart;
    QWidget *newWindow;
    QVBoxLayout *newWindowLayout;
    QPushButton *deleteItem;
    QPushButton *buyCartx;
    QLabel *viewlabel;

    //new window for review
    QWidget *reviewWindow;
    QComboBox *ratingw;
    QComboBox *yearw;
    QLabel *status;
    QComboBox *monthw;
    QComboBox *dayw;
    QTextEdit *reviewText;
    QPushButton *addRevieww;
    QVBoxLayout *reviewLayout;
    QHBoxLayout *dateLayout;
    QLabel *ratingLabel;
    QLabel *dateLabel;
    QLabel *enterLabel;
    QLabel *userToReview;
    QLabel *productToReview;
  

	int typeOfSearch;// = 0; //0 is and 1 is or
	vector<Product*> hits;

	int typeOfSort;// = 0; //0 is alph 1 is rating based

	alphaStrComp alpha;
	RatingComp rate;
	OldFirst oldx;
	newFirst newx;
	vector<Review*> reviewsToSort;

	int typeOfDateSort;// = 0;
	bool isEmpty;

};

#endif



