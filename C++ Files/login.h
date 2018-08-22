#ifndef LOGIN_H
#define LOGIN_H

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
#include "login.h"
#include "user.h"
#include "mw.h"
#include "hash.h"


class loginWindow : public QWidget {
	Q_OBJECT

public:
	
	loginWindow(MyDataStore* ptr);
	~loginWindow();

private slots:

	void loginUser();	
	void newUser();
	void quitUser();

private:
	
	mainWindow* MW;
	MyDataStore* store;

	QLabel *Name;
	QLabel *Pass;

	QLineEdit *U;
	QLineEdit *P;

	QPushButton *lgn;
	QPushButton *newu;
	QPushButton *quit;


	QVBoxLayout *overall;
	QHBoxLayout *buttons;

	QHBoxLayout *uLayout;
	QHBoxLayout *pLayout;

};

#endif