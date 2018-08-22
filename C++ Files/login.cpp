#include "login.h"
#include <cstdlib>
#include "mydatastore.h"
#include "mw.h"
#include <cmath>

loginWindow::loginWindow(MyDataStore* ptr) {

	MW = new mainWindow(ptr);
	store = ptr;
	setWindowTitle("Login");
	
	overall = new QVBoxLayout;

	Name = new QLabel("Username");
	Pass = new QLabel("Password");

	U = new QLineEdit;
	P = new QLineEdit;

	uLayout = new QHBoxLayout;
	pLayout = new QHBoxLayout;
	buttons = new QHBoxLayout;

	overall->addLayout(uLayout);
	overall->addLayout(pLayout);
	overall->addLayout(buttons);

	uLayout->addWidget(Name);
	uLayout->addWidget(U);

	pLayout->addWidget(Pass);
	pLayout->addWidget(P);

	lgn = new QPushButton("Login");
	newu = new QPushButton("New User");
	quit = new QPushButton("Quit");

	buttons->addWidget(lgn);
	buttons->addWidget(newu);
	buttons->addWidget(quit);

	connect(lgn, SIGNAL(clicked()), this, SLOT(loginUser()));
	connect(newu, SIGNAL(clicked()), this, SLOT(newUser()));
	connect(quit, SIGNAL(clicked()), this, SLOT(quitUser()));

	this->setLayout(overall);

}
	
loginWindow::~loginWindow(){

}

void loginWindow::loginUser() {
	
	if(U->text().isEmpty() || P->text().isEmpty()) {
		return;
	}

	bool foundU = false, foundP = false; int x;

	std::string username = U->text().toStdString();
	std::string password = P->text().toStdString();

	for(unsigned int i = 0; i<(store->getUsersVector()).size(); i++) {
		if(username == (store->getUsersVector())[i]->getName()) {
			foundU = true;
			if((store->getUsersVector())[i]->getHashedPass() == hash_str(password.c_str())) {
				foundP = true; x = (int) i;

			}
		}
	}

	if(foundU == false) {
		QMessageBox mymsg(this);  // this is the pointer to the current widget
      	mymsg.setText("Incorrect Username");
      	mymsg.exec();
      	return;
	}

	if(foundP == false) {
		QMessageBox mymsg(this);  // this is the pointer to the current widget
      	mymsg.setText("Incorrect Password");
      	mymsg.exec();
      	return;
	}

	//this->close();
	U->setText("");
	P->setText("");
	MW->setU((store->getUsersVector())[x]);
	MW->show();
}
	
void loginWindow::newUser() {
	
	if(U->text().isEmpty() || P->text().isEmpty()) {
		return;
	}

	std::string username = U->text().toStdString();
	std::string password = P->text().toStdString();

	for(unsigned int i = 0; i<(store->getUsersVector()).size(); i++) {
		if(username == (store->getUsersVector())[i]->getName()) {
			
			QMessageBox mymsg(this);  // this is the pointer to the current widget
      		mymsg.setText("Username used");
      		mymsg.exec();
      		return;

		}
	}

	User* tempUser = new User(username, 100.0, 1, hash_str(password.c_str()));
	store->addUser(tempUser);

	U->setText("");
	P->setText("");

	//this->close();
	MW->setU(tempUser);
	MW->show();

}

void loginWindow::quitUser() {
	this->close();
}