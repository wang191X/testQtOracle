#ifndef CUSERS_H
#define CUSERS_H

//#include <QDialog>
//#include "ui_CAddUsers.h"
#include "ui_CUsrWidget.h"
#include <QtSql/QSqlTableModel>

class CUsers : public QWidget,public Ui::CUsrWt
{
	Q_OBJECT

public:
	CUsers(QWidget *parent=0);
	~CUsers();

private:
	QSqlTableModel* model;

	private slots:
		void addUsers();
		void deleteUser();
		void queryUser();
		//void users();
};

#endif // CUSERS_H
