#ifndef CTASKMANAGE1_H
#define CTASKMANAGE1_H

#include <QDialog>
#include "ui_TaskManage.h"
#include <QtSql/QSqlTableModel>

class CTaskManage1 : public QDialog,public Ui::TaskManageW
{
	Q_OBJECT

public:
	CTaskManage1(QWidget *parent=0);
	~CTaskManage1();

private:
	QSqlTableModel* model;
	
	private slots:
		void addTask();
		void addXaclTask();
		void deleteTask();
		void queryTask();
};

#endif // CTASKMANAGE1_H
