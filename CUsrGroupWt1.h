#ifndef CUSRGROUPWT1_H
#define CUSRGROUPWT1_H

#include <QWidget>
#include "ui_CUsrGroupWt.h"
#include <QtSql/QSqlTableModel>

class CUsrGroupWt1 : public QWidget,public Ui::CUsrGroupWt
{
	Q_OBJECT

public:
	CUsrGroupWt1(QWidget *parent=0);
	~CUsrGroupWt1();

private:
	QSqlTableModel* model;
	
private slots:

void addUsrGroup();
void deleteUsrGroup();
void queryUsrGroup();
	
};

#endif // CUSRGROUPWT1_H
