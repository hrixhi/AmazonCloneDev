#include "mw.h"

MyDataStore* dbPtrx;



mainWindow::mainWindow(MyDataStore* ar) : dbPtr(ar), selectedUserPtr(ar->uVec[0]), selectedProductPtr(NULL) {

	typeOfSort = 0;
	typeOfSearch = 0;
	typeOfDateSort = 0;
	u = NULL;
	isEmpty = true;

	dbPtrx = ar;
	
	setWindowTitle("Amazon");

	//primary layouts initialization
	mainLayout = new QHBoxLayout;
	userArea = new QVBoxLayout;
	searchArea = new QVBoxLayout;
	productArea = new QVBoxLayout;

	//Adding the three sub layouts to the main layout
	mainLayout->addLayout(userArea);
	mainLayout->addLayout(searchArea);
	mainLayout->addLayout(productArea);

	//==================================================
	//User Area
	//==================================================

	//initializing user layouts and widgets
	AMAZON = new QLabel("WELCOME TO AMAZON!");
	selectUser = new QLabel("Welcome! Explore your options \n around this software and have fun!");
	//usernameInput = new QLineEdit;

	std::ostringstream str1;
	str1 << (selectedUserPtr->getBalance());
	std::string strw = str1.str();

	QString qstr = QString::fromStdString("Current User: " + ar->uVec[0]->getName() + "\nAvailable Balance: " + strw);
	selectedU = new QLabel(qstr);
	// usernameInputSearch = new QPushButton("Select User");
	// usernameInputLayout = new QHBoxLayout;
	// Or = new QLabel("Or");
	// userList = new QComboBox;
	buycart = new QPushButton("Buy Cart");
	viewcart = new QPushButton("View Cart");
	lastOptions = new QHBoxLayout;
	saveDatabase = new QPushButton("Save");
	quit = new QPushButton("Quit");
	rev = new QPushButton("Add Review");



	//initializing the review window
	reviewWindow = new QWidget;
    ratingw = new QComboBox;
    yearw = new QComboBox;
    monthw = new QComboBox;
    dayw = new QComboBox;
    reviewText = new QTextEdit;
    addRevieww = new QPushButton("Add");
    reviewLayout = new QVBoxLayout;
    dateLayout = new QHBoxLayout;
    ratingLabel = new QLabel("Select Rating");
    dateLabel = new QLabel("Select Date");
    enterLabel = new QLabel("Enter Review");
    userToReview = new QLabel;
    productToReview = new QLabel;
    status = new QLabel;

    connect(addRevieww, SIGNAL(clicked()), this, SLOT(addReviewFunc()));

    for(int i = 2017; i<2031; i++){
    	QString u = QString::number(i);
    	  yearw->addItem(u);
    }

    for(int i = 1; i<13; i++) {
    	QString u = QString::number(i);
    	monthw->addItem(u);
    }

    for(int i = 1; i<32; i++) {
    	QString u = QString::number(i);
    	dayw->addItem(u);
    }

    for(int i = 1; i<6; i++) {
    	QString u = QString::number(i);
    	ratingw->addItem(u);
    }

    dateLayout->addWidget(yearw);
    dateLayout->addWidget(monthw);
    dateLayout->addWidget(dayw);

    reviewLayout->addWidget(userToReview);
    reviewLayout->addWidget(productToReview);
    reviewLayout->addWidget(dateLabel);
    reviewLayout->addLayout(dateLayout);
    reviewLayout->addWidget(ratingLabel);
    reviewLayout->addWidget(ratingw);
    reviewLayout->addWidget(enterLabel);
    reviewLayout->addWidget(reviewText);
    reviewLayout->addWidget(status);
    reviewLayout->addWidget(addRevieww);

    reviewWindow->setLayout(reviewLayout);

    connect(addRevieww, SIGNAL(clicked()), this, SLOT(addReviewFunc()));
    connect(reviewText, SIGNAL(textChanged()), this, SLOT(textCheck()));

	// QHBoxLayout *dateLayout;
  	//   QLabel *ratingLabel;
  	//   QLabel *dateLabel;
  	//   QLabel *enterLabel;



	//Adding the sub-sub lyouts to the sub layout userSearch
	// usernameInputLayout->addWidget(usernameInput);
	// usernameInputLayout->addWidget(usernameInputSearch);

	lastOptions->addWidget(saveDatabase);
	lastOptions->addWidget(quit);

	userArea->addWidget(AMAZON);
	userArea->addWidget(selectUser);
	userArea->addWidget(selectedU);
	// userArea->addLayout(usernameInputLayout);
	// userArea->addWidget(Or);
	// userArea->addWidget(userList);
	pR = new QPushButton("Product Recommendations");
	logout = new QPushButton("Logout");
	userArea->addWidget(viewcart);
	userArea->addWidget(buycart);
	userArea->addWidget(rev);
	userArea->addWidget(pR); 
	userArea->addWidget(logout);
	userArea->addLayout(lastOptions);

	connect(pR, SIGNAL(clicked()), this, SLOT(prodRec()));


	// for(unsigned int i = 0; i < (dbPtr->getUsersVector()).size(); i++) {
	// 	QString qstr = QString::fromStdString((dbPtr->getUsersVector())[i]->getName());
	// 	userList->addItem(qstr);
	// }

	//Connections for the userArea
	// connect(usernameInputSearch, SIGNAL(clicked()), this, SLOT(changeUser()));
	// connect(userList, SIGNAL(currentIndexChanged(int)), this, SLOT(changeUser(int)));
	connect(viewcart, SIGNAL(clicked()), this, SLOT(viewCart()));
	connect(buycart, SIGNAL(clicked()), this, SLOT(buyCart()));

	connect(rev, SIGNAL(clicked()), this, SLOT(revFunc()));

	connect(logout, SIGNAL(clicked()), this, SLOT(LOG()));

	connect(saveDatabase, SIGNAL(clicked()), this, SLOT(saveDB()));
	connect(quit, SIGNAL(clicked()), this, SLOT(close()));

	//==================================================
	//Search Area
	//==================================================
	

	searchx = new QLabel("Search for a Product");
	productInput = new QLineEdit;
	productInputSearch = new QPushButton("Search");
	productInputLayout = new QHBoxLayout;
	RBLayout = new QHBoxLayout;
	andButton = new QRadioButton("AND");
	orButton = new QRadioButton("OR");
	whichSortList = new QComboBox;
	searchResults = new QListWidget;

	//setting layout
	productInputLayout->addWidget(productInput);
	productInputLayout->addWidget(productInputSearch);

	RBLayout->addWidget(andButton);
	RBLayout->addWidget(orButton);

	searchArea->addWidget(searchx);	
	searchArea->addLayout(productInputLayout);
	searchArea->addLayout(RBLayout);
	searchArea->addWidget(whichSortList);
	searchArea->addWidget(searchResults);

	andButton->setChecked(true);
	//initializing connections
	connect(productInputSearch, SIGNAL(clicked()), this, SLOT(search()));
	connect(andButton, SIGNAL(clicked()), this, SLOT(changeToAnd()));
	connect(orButton, SIGNAL(clicked()), this, SLOT(changeToOr()));

	whichSortList->addItem("Alphabetically");
	whichSortList->addItem("Average Rating: High - Low");
	whichSortList->setCurrentIndex(whichSortList->findText("Alphabetically"));

	connect(whichSortList, SIGNAL(currentIndexChanged(int)), this, SLOT(sortHits(int)));

	//==================================================
	//Product Area
	//==================================================

	productName = new QLabel("Selected Product Info");
	pName = new QLabel;
	sortReviews = new QComboBox;
	reviews = new QListWidget;
	addCart = new QPushButton("Add to Cart");

	//set Layout

	productArea->addWidget(productName);
	productArea->addWidget(pName);
	productArea->addWidget(sortReviews);
	productArea->addWidget(reviews);
	productArea->addWidget(addCart);

	sortReviews->addItem("New - Old");
	sortReviews->addItem("Old - New");
	//sortReviews->setCurrentIndex(whichSortList->findText("New - Old"));

	connect(searchResults, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(productSelected(QListWidgetItem*)));
	connect(sortReviews, SIGNAL(currentIndexChanged(int)), this, SLOT(sortChanged(int)));
	connect(addCart, SIGNAL(clicked()), this, SLOT(addToCart()));

	//Extra Window initialization

	//newWindow = new QWidget
	cart = new QListWidget;	
	newWindow = new QWidget;
    newWindowLayout = new QVBoxLayout;
    deleteItem = new QPushButton("Delete Selected Item");
    buyCartx = new QPushButton("Buy Cart");
    viewlabel = new QLabel("This is the current cart");

    newWindowLayout->addWidget(viewlabel);
    newWindowLayout->addWidget(cart);
    newWindowLayout->addWidget(deleteItem);
    newWindowLayout->addWidget(buyCartx);

    newWindow->setWindowTitle("Cart");
    reviewWindow->setWindowTitle("New Review");

    newWindow->setLayout(newWindowLayout);

    connect(deleteItem, SIGNAL(clicked()), this, SLOT(deleteElementCart()));
    connect(buyCartx, SIGNAL(clicked()), this, SLOT(buyCart()));

	this->setLayout(mainLayout);

}


void mainWindow::LOG() {
	this->close();
}



void mainWindow::prodRec() {
	
	dbPtr->URPMap();

	//std::cout<<"1"<<endl;
	dbPtr->calculateBS();
	//std::cout<<"2"<<endl;
	dbPtr->refine(selectedUserPtr);
	//std::cout<<"3"<<endl;

	bool tempx = false;

	// for(unsigned int j = 0; dbPtr->getUsersVector().size(); j++) {
	// 	if(  (dbPtr->basicSimTemp)[(dbPtr->getUsersVector())[j]].size() == dbPtr->pVec.size() ) {
	// 		tempx = true;
	// 		break;
	// 	}
	// }

	//std::cout<<"4"<<endl;


	if(tempx) {

		QMessageBox mymsg(this);  // this is the pointer to the current widget
      	mymsg.setText("No recommendations available");
      	mymsg.exec();
      	return;

	}

//std::cout<<"5"<<endl;
	std::ofstream out_file;

	out_file.open("rec.txt");


	std::vector<std::pair<std::string, double> > temp = dbPtr->makeSuggestion(selectedUserPtr->getName());

	out_file<<selectedUserPtr->getName()<<endl;

//std::cout<<"6"<<endhl;

	for(unsigned int i = 0; i<temp.size(); i++) {

		out_file<<temp[i].second<<" "<<temp[i].first<<endl;
	}

	out_file.close();

}



void mainWindow::addReviewFunc() {
	if(isEmpty) {
		QString p = QString::fromStdString("No text inserted, try again!");
		status->setText(p);
		return;
	}

	std::ostringstream str1;
	str1 << (yearw->currentText().toStdString());
	std::string year = str1.str();

	std::ostringstream str2;
	str2 << (monthw->currentText().toStdString());
	std::string month = str2.str();
	if(month.length() == 1) {
		month = "0" + month;
	}

	std::ostringstream str3;
	str3 << (dayw->currentText().toStdString());
	std::string day = str3.str();
	if(day.length() == 1) {
		day = "0" + day;
	}

	std::istringstream ss;
	int x;
	ss.str(ratingw->currentText().toStdString());
	ss>>x;

	std::string date = year + "-" + month + "-" + day;

	Review *newReview = new Review(selectedProductPtr->getName(), x, selectedUserPtr->getName(),
	 date, reviewText->toPlainText().toStdString());

	dbPtr->addReview(newReview);
	isEmpty=true;

	reviewText->clear();
	reviewWindow->close();
	productSelected(searchResults->currentItem());

}

void mainWindow::textCheck() {	
	isEmpty = false;
}

void mainWindow::revFunc() {

	if(selectedUserPtr==NULL || selectedProductPtr == NULL) {
		return;
	}

	QString u = QString::fromStdString("Current User: " + selectedUserPtr->getName());
	QString p = QString::fromStdString("Selected Product: " + selectedProductPtr->getName());

	userToReview->setText(u);
	productToReview->setText(p);

	reviewWindow->show();
}


void mainWindow::setPtr(MyDataStore* db) {
		dbPtr = db;
		dbPtrx = db;
	}

void mainWindow::setU(User* u) {
	
	selectedUserPtr = u;

	std::ostringstream str1;
	str1 << (selectedUserPtr->getBalance());
	std::string strw = str1.str();

	QString qstr = QString::fromStdString("Current User: " + u->getName() + "\nAvailable Balance: " + strw);
	selectedU->setText(qstr);

}

void mainWindow::changeUser() {

	// u = NULL;

	// if(usernameInput->text().isEmpty()) {
	// 	usernameInput->setText("");
	// 	return;
	// }

	// for(unsigned int i = 0; i < (dbPtr->getUsersVector()).size(); i++) {
	// 	if((dbPtr->getUsersVector())[i]->getName() == usernameInput->text().toStdString()) {
	// 		u = (dbPtr->getUsersVector())[i];
	// 	}
	// }

	// if(u == NULL) {
	// 	usernameInput->setText("ERROR! Re-enter");
	// 	return;
	// }


	// selectedUserPtr = u;
	// usernameInput->setText("");

	// std::ostringstream str1;
	// str1 << (selectedUserPtr->getBalance());
	// std::string strw = str1.str();

	// QString qstrx = QString::fromStdString("Current User: " + selectedUserPtr->getName() + "\nAvailable Balance: " + strw);
	// selectedU->setText(qstrx);
	
	// QString qstr = QString::fromStdString(u->getName());
	
	// userList->setCurrentIndex(userList->findText(qstr));

}

// void mainWindow::changeUser() {

// 	//int y = x;
// 	// selectedUserPtr = (dbPtr->getUsersVector())[x];

// 	// //selectedU->setText(selectedUserPtr->getName());

// 	// std::ostringstream str1;
// 	// str1 << (selectedUserPtr->getBalance());
// 	// std::string strw = str1.str();

// 	// QString qstr = QString::fromStdString("Current User: " + selectedUserPtr->getName() + "\nAvailable Balance: " + strw);
// 	// selectedU->setText(qstr);

// }

void mainWindow::viewCart() {
	
	if(selectedUserPtr == NULL) {
		return;
	}

	//dbPtr->viewCart(u->getName());
	viewCartx(selectedUserPtr->getName(), dbPtr);

}

void mainWindow::buyCart() {
	if(selectedUserPtr == NULL) {
		return;
	}

	//dbPtr->buyCart(u->getName());
	buyCartxxx(selectedUserPtr->getName(), dbPtr);
}

void mainWindow::saveDB() {
	std::string filename = QFileDialog::getSaveFileName().toStdString();
	std::ofstream out_file(filename.c_str());
	dbPtr->dump(out_file);
}

void mainWindow::search() {
	
	std::string toSearch = productInput->text().toStdString();
	std::istringstream ss;
	ss.str(toSearch);
	vector<std::string> temp;
	std::string s;
	std::string term;

	while(ss>>s) {
		term = convToLower(s);
		temp.push_back(term);
	}

	hits = dbPtr->search(temp, typeOfSearch); ///unsorted list

	if(typeOfSort == 0) {
		mergeSort(hits, alpha);
	}
	else {
		mergeSort(hits, rate);
	}

	//STILL LEFT
	searchResults->clear();
	for(unsigned int i = 0; i<hits.size(); i++) {
		std::ostringstream strs;
		strs << (hits[i]->getPrice());
		std::string str = strs.str();
		QString qstr = QString::fromStdString(hits[i]->getName() + "\n" + str);
		searchResults->addItem(qstr);
	}
}

void mainWindow::changeToAnd() {
	typeOfSearch = 0;
}	

void mainWindow::changeToOr() {
	typeOfSearch = 1;
}

void mainWindow::sortHits(int x) {

	if(typeOfSort == x) {
		return;
	}


		typeOfSort = x;
		searchResults->clear();

		if(typeOfSort == 0) {
			mergeSort(hits, alpha);
		}
		else {
			mergeSort(hits, rate);
		}

		for(unsigned int i = 0; i<hits.size(); i++) {

			std::ostringstream strs;
		strs << (hits[i]->getPrice());
		std::string str = strs.str();
			QString qstr = QString::fromStdString(hits[i]->getName() + "\n" + str);
			searchResults->addItem(qstr);
		}

	
}

void mainWindow::productSelected(QListWidgetItem* itemx) {
// productName = new QLabel("Selected Product Info");
	// pName = new QLabel;
	// sortReviews = new QComboBox;
	// reviews = new QListWidget;
	// addCart = new QPushButton("Add to Cart");
	bool temp = false;
	int x;

	for(int i = 0; i<searchResults->count(); i++) {
		if(searchResults->item(i) == itemx) {
			x = i;
			temp = true;
		}
	}

	if(!temp) {
		return;
	}

	selectedProductPtr = hits[x];

	std::ostringstream str1;
		str1 << (hits[x]->getQty());
		std::string strw = str1.str();

	QString qstr = QString::fromStdString(selectedProductPtr->getName() + "\n" + "Quantity: " + strw);
	pName->setText(qstr);
	reviews->clear();
	reviewsToSort.clear();

	//std::cout<<"this";
	

	if(dbPtr->rMap.find(hits[x]) == dbPtr->rMap.end()) {
		return;
	}
	else {
		for(unsigned int i = 0; i< dbPtr->rMap[hits[x]].size(); i++) {
			reviewsToSort.push_back(dbPtr->rMap[hits[x]][i]);
		}
	}

	if(typeOfDateSort == 0) {
		mergeSort(reviewsToSort, newx);
	} else {
		mergeSort(reviewsToSort, oldx);
	}

	for(unsigned int i = 0; i< dbPtr->rMap[hits[x]].size(); i++) {

		std::ostringstream strs;
		strs << reviewsToSort[i]->rating;
		std::string str = strs.str();

		QString temp = QString::fromStdString(dbPtr->rMap[hits[x]][i]->prodName
			+ "\n" + str + " " + reviewsToSort[i]->username + " "
			+ reviewsToSort[i]->date + " " + reviewsToSort[i]->reviewText);
			reviews->addItem(temp);
	}
}

void mainWindow::sortChanged(int x) {

	if(selectedProductPtr == NULL) {
		return;
	}

	if(x == typeOfDateSort) {
		return;
	}

	typeOfDateSort = x;
	
	reviews->clear();
	reviewsToSort.clear();

	//std::cout<<"this";

	if(dbPtr->rMap.find(selectedProductPtr) == dbPtr->rMap.end()) {
		return;
	}
	else {
		for(unsigned int i = 0; i< dbPtr->rMap[selectedProductPtr].size(); i++) {
			reviewsToSort.push_back(dbPtr->rMap[selectedProductPtr][i]);
		}
	}

	if(typeOfDateSort == 0) {
		mergeSort(reviewsToSort, newx);
	} else {
		mergeSort(reviewsToSort, oldx);
	}

	for(unsigned int i = 0; i< dbPtr->rMap[selectedProductPtr].size(); i++) {

		std::ostringstream strs;
		strs << reviewsToSort[i]->rating;
		std::string str = strs.str();

		QString temp = QString::fromStdString(dbPtr->rMap[selectedProductPtr][i]->prodName
			+ "\n" + str + " " + reviewsToSort[i]->username + " "
			+ reviewsToSort[i]->date + " " + reviewsToSort[i]->reviewText);
			reviews->addItem(temp);
	}

}

void mainWindow::addToCart() {
	if(selectedProductPtr == NULL || selectedUserPtr == NULL) {
		return;
	}

	dbPtr->addPtoU(selectedUserPtr->getName(), selectedProductPtr);
}

void mainWindow::deleteElementCart() {


	if(dbPtr->uMap[selectedUserPtr->getName()].size() == 0) {
		return;
	}

	int x = cart->currentRow();
	dbPtr->uMap[selectedUserPtr->getName()].erase(dbPtr->uMap[selectedUserPtr->getName()].begin() + x);
	QListWidgetItem* temp = cart->takeItem(x);
	int y = temp->type();
	y += 4;//does nothing
}

void mainWindow::buyCartxx() {
	dbPtr->temp = true;
	//dbPtr->buyCart(selectedUserPtr->getName());
	buyCartxxx(selectedUserPtr->getName(), dbPtr);


}

void mainWindow::buyCartxxx(std::string user, MyDataStore* ptr) {

	if(ptr->uMap.find(user) == ptr->uMap.end()) {
		//std::cout<<"Invalid Username"<<std::endl;
		return;
	}

	if(ptr->uMap[user].size() == 0) {
		//std::cout<<"Cart is empty, nothing to buy."<<std::endl;
		return;
	}

	User* usrptr = NULL;

	for(unsigned int i = 0; i<ptr->uVec.size(); i++) {
		if(ptr->uVec[i]->getName() == user) {
			usrptr = ptr->uVec[i];
			break;
		}
	} 

	for(unsigned int i = 0; i<ptr->uMap[user].size(); i++) {
		//product = uMap[user][i]; Keep in mind
		if((usrptr->getBalance() >= ptr->uMap[user][i]->getPrice()) &&
		 (ptr->uMap[user][i]->getQty() >0 )) {

			usrptr->deductAmount(ptr->uMap[user][i]->getPrice());	//reduce user's total
			ptr->uMap[user][i]->subtractQty(1);						//reduce qty
			ptr->uMap[user].erase(ptr->uMap[user].begin() + i);		//removes from the cart
			if(ptr->temp) { 
				QListWidgetItem *temp = cart->takeItem(i);	
				//QListWidgetItem* temp = cart->takeItem(x);
				int x = temp->type();
				x += 4;//does nothing
			}		//remove from GUI cart

			i--;
		}
	} 

	cart->clear();

	for(unsigned int i = 0; i<ptr->uMap[user].size(); i++) {
		QString qstr = QString::fromStdString(ptr->uMap[user][i]->getName());
		cart->addItem(qstr);
	}

	ptr->temp = false;
	std::ostringstream str1;
		str1 << (selectedProductPtr->getQty());
		std::string strw = str1.str();

	QString qstr = QString::fromStdString(selectedProductPtr->getName() + "\n" + "Quantity: " + strw);
	pName->setText(qstr);


	std::ostringstream str2;
	str2 << (selectedUserPtr->getBalance());
	std::string strw2 = str2.str();

	QString qstrx = QString::fromStdString("Current User: " + selectedUserPtr->getName() + "\nAvailable Balance: " + strw2);
	selectedU->setText(qstrx);
}


void mainWindow::viewCartx(std::string name, MyDataStore* ptr) {
	//std::set<Product*>::iterator it;
	// for(it = uMap[name].begin(); it!= uMap[name].end(); ++it) {
	// 	cout<<(*it)->displayString()<<endl;
	// }

	//newWindow = new QWidget;
   
	cart->clear();

	if(ptr->uMap.find(name) == ptr->uMap.end()) {
		//std::cout<<"Invalid Username"<<std::endl;
		return;
	}

	// if(ptr->uMap[name].size()==0) {
	// 	//std::cout<<"Cart is empty, nothing to show."<<std::endl;
	// 	return;
	// }

	//have to display this as Qstring in the list uMap[name][i]->displayString()
	// for(unsigned int i = 0; i< ptr->uVec.size(); i++) {
	// 	if(ptr->uVec[i]->getName() == name) {
	// 		selectedUserPtr = ptr->uVec[i];
	// 	}
	// }

	for(unsigned int i = 0; i<ptr->uMap[name].size(); i++) {
		QString qstr = QString::fromStdString(ptr->uMap[name][i]->getName());
		cart->addItem(qstr);
	}


	newWindow->show();
}

mainWindow::~mainWindow() {
	//does nothing so far
}
