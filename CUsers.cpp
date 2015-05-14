#include "CUsers.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include "CUsrDlg1.h"
#include "DataStruct.h"
#include <QModelIndex>
#include <QMessageBox>
#include <QSqlError>
#include <QString>
#include "CTitleDlg1.h"
#include "GloabeParams.h"
#include "CAddUsrGroup1.h"

CUsers::CUsers(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	connect(pbAdd, SIGNAL(clicked()),this, SLOT(addUsers()));
	connect(pbDelete, SIGNAL(clicked()),this, SLOT(deleteUser()));
	connect(pbQuery, SIGNAL(clicked()),this, SLOT(queryUser()));
	model=new QSqlTableModel(this);
	model->setTable("ksuser");
	QString filter=QString("usergroupid=%1").arg(g_clientId);
	model->setFilter(filter);
	model->select();

	tvUsers->setModel(model);
}

CUsers::~CUsers()
{

}

void CUsers::addUsers()
{
	QWidget*  newUsrGroupWt=new CAddUsrGroup1();
	((CAddUsrGroup1*)newUsrGroupWt)->cbPrivilege->addItem(tr(""));
	CTitleDlg1 newUsrGroupDlg(0,newUsrGroupWt);
	QObject::connect(newUsrGroupWt,SIGNAL(okMsg()),&newUsrGroupDlg,SLOT(accept()));
	int ret=newUsrGroupDlg.exec();

	// QWidget* newUsrWt=new CUsrDlg1();
	// CTitleDlg1 newUsrDlg(0,newUsrWt);
	// QObject::connect(newUsrWt,SIGNAL(okMsg()),&newUsrDlg,SLOT(accept()));
	// int ret=newUsrDlg.exec();
	model->select();

	/*CUsrDlg1 usrDlg;
	usrDlg.exec();*/
}

void CUsers::deleteUser()
{
	QModelIndex index= tvUsers->currentIndex();
	model->removeRow(index.row());
	model->submitAll();
	/*QString error=model->lastError().text();
	QMessageBox::information(this, tr("information"), error);*/
}

void CUsers::queryUser()
{
	model->select();
}
