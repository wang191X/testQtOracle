#ifndef CPLMANAGEW1_H
#define CPLMANAGEW1_H

#include <QDialog>
#include "ui_PlManageW.h"
#include <QtSql/QSqlTableModel>

class CPlManageW1 : public QDialog,public Ui::PlManageW
{
	Q_OBJECT

public:
	CPlManageW1(QWidget *parent=0);
	~CPlManageW1();

private:
	QSqlTableModel* model;
	
	private slots:
		void addPL();
		void deletePL();
		void queryPL();
};

#endif // CPLMANAGEW1_H
