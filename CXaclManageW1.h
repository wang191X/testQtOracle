#ifndef CXACLMANAGEW1_H
#define CXACLMANAGEW1_H

#include <QDialog>
#include "ui_XaclManageW.h"
#include <QtSql/QSqlTableModel>

class CXaclManageW1 : public QDialog,public Ui::XaclManageW
{
	Q_OBJECT

public:
	CXaclManageW1(QWidget *parent=0);
	~CXaclManageW1();

private:
	QSqlTableModel* model;

	private slots:
		void addAcl();
		void deleteAcl();
		void queryAcl();
	
};

#endif // CXACLMANAGEW1_H
