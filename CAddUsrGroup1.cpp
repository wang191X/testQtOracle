#include "CAddUsrGroup1.h"
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include "GloabeParams.h"
#include <QQueue>
#include <QSqlRecord>
#include <QDateTime>

CAddUsrGroup1::CAddUsrGroup1(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	this->setFixedSize(this->width(),this->height());

	connect(pbOk, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(pbCancel, SIGNAL(clicked()), this, SLOT(onCancel()));
	
	initUIData();
}

CAddUsrGroup1::~CAddUsrGroup1()
{

}

void CAddUsrGroup1::initUIData()
{
	isUsr=TRUE;
	//cbPrivilege->addItem(tr("超级管理员"));
	//cbPrivilege->addItem(tr("用户组管理员"));
}

int CAddUsrGroup1::assignUsrId()
{
	QSqlTableModel model;
	model.setTable("ksuser");
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
	
	int beginNum=1;
	int endNum=0;
	const int maxIdRes=10;
	QQueue<int>queueId;

	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		endNum=record.value("userid").toInt();
		
		for (int i=beginNum;i!=endNum;++i)
		{
			//qDebug() << i; // output all names
			queueId.enqueue(i);
		}

		beginNum=endNum+1;
	}

	while(queueId.count()<maxIdRes)
	{
		++endNum;
		queueId.enqueue(endNum);
	}

	int resId=queueId.dequeue();
	return resId;
}


int CAddUsrGroup1::assignUsrGroupId()
{

	QSqlTableModel model;
	model.setTable("ksusergroup");
	model.setSort( 0, Qt::AscendingOrder);
	model.select();

	int beginNum=1;
	int endNum=0;
	const int maxIdRes=10;
	QQueue<int>queueId;

	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		endNum=record.value("usergroupid").toInt();

		for (int i=beginNum;i!=endNum;++i)
		{
			//qDebug() << i; // output all names
			queueId.enqueue(i);
		}

		beginNum=endNum+1;
	}

	while(queueId.count()<maxIdRes)
	{
		++endNum;
		queueId.enqueue(endNum);
	}

	int resId=queueId.dequeue();
	return resId;
}

void CAddUsrGroup1::insertUsrRecord()
{
	int id=assignUsrId();
	QString privilege=cbPrivilege->currentText();
	QString userGroup=leUsrGroup->text();
	QString passwd=lePasswd->text();
	QString depart=cbDepart->currentText();

	QSqlQuery query;
	
	query.prepare("insert into ksuser("
					"USERID,"
					"USERNAME,"
					"PASSWORD,"
					"PRIVILEGE,"
					"DEPART,"
					"USERGROUPID,"
					"TIME"
				   ") values("
				    ":USERID,"
					":USERNAME,"
					":PASSWORD,"
					":PRIVILEGE,"
					":DEPART,"
					":USERGROUPID,"
					":TIME"
				   ")");
	query.bindValue(":USERID",id);
	query.bindValue(":USERNAME",userGroup);
	query.bindValue(":PASSWORD",passwd);
	query.bindValue(":PRIVILEGE",privilege);
	query.bindValue(":DEPART",depart);
	query.bindValue(":USERGROUPID",g_clientId);
	QDateTime now = QDateTime::currentDateTime();
	query.bindValue(":TIME",now);
	bool ret=query.exec();

	if (!ret)
	{
		QString str=query.lastError().text();
		QMessageBox::information(this, tr("information"), str);
	}

	query.clear();
}

void CAddUsrGroup1::insertUsrGRecord()
{
	int id=assignUsrGroupId();
	QString privilege=cbPrivilege->currentText();
	QString userGroup=leUsrGroup->text();
	QString passwd=lePasswd->text();
	QString depart=cbDepart->currentText();
	/*int abgid= sbabgid->value();
	int aegid=sbaegid->value();
	int xbgid=sbxbgid->value();
	int xegid=sbxegid->value();
	int pbid=sbpbid->value();
	int peid=sbpeid->value();*/

	QSqlQuery query;
	
	query.prepare("insert into ksusergroup("
					"USERGROUPID,"
					"USERGROUP,"
					"PASSWORD,"
					"PRIVILEGE,"
					"DEPART,"
					"TIME"
				   ") values("
				   ":USERGROUPID,"
				   ":USERGROUP,"
				   ":PASSWORD,"
				   ":PRIVILEGE,"
				   ":DEPART,"
				   ":TIME"
				   ")");
	query.bindValue(":USERGROUPID",id);
	query.bindValue(":USERGROUP",userGroup);
	query.bindValue(":PASSWORD",passwd);
	query.bindValue(":PRIVILEGE",privilege);
	query.bindValue(":DEPART",depart);
	QDateTime now = QDateTime::currentDateTime();
	query.bindValue(":TIME",now);
	bool ret=query.exec();

	if (!ret)
	{
		QString str=query.lastError().text();
		QMessageBox::information(this, tr("information"), str);
	}

	query.clear();
}

void CAddUsrGroup1::onOk()
{
	if(isUsr)
	{
		insertUsrRecord();
	}
	else
	{
		insertUsrGRecord();
	}

	emit okMsg();

}

void CAddUsrGroup1::onCancel()
{
	emit cancelMsg();
}