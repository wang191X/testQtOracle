#include "CLoginDlg1.h"
#include "GloabeParams.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QString>


CLoginDlg1::CLoginDlg1(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	this->setFixedSize(this->width(),this->height());

	connect(okButton, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(onCancel()));
	
	QSqlDatabase db=QSqlDatabase::addDatabase("QOCI");
	//QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
	db.setHostName(g_ip);
	//QString dsn="Driver={microsoft odbc for oracle};server=rulesdb;uid=ruleadmin,pwd=123456";
	db.setDatabaseName(g_dbName);
	db.setUserName(g_usr);
	db.setPassword(g_passwd);

	if (!db.open())
	{
		QString str=db.lastError().text();
		QMessageBox::information(this, tr("information"), G2U(str.toAscii()));
	}
}

CLoginDlg1::~CLoginDlg1()
{

}

bool CLoginDlg1::queryUsrTable()
{
	QString sql = QString("select "
					"USERID,"
                   "USERNAME,"
                   "PASSWORD,"
                   "PRIVILEGE,"
                   "DEPART,"
                   "USERGROUPID"
				   " from ksuser where USERNAME='%1' and PASSWORD='%2'").arg(g_clientUsr).arg(g_clientPasswd);
	QSqlQuery query(sql);

	if(query.next())
	{
		g_clientId=query.value(0).toInt();
		g_ParentId=query.value(5).toInt();
		QString tmp=query.value(3).toString();
		
		g_privilege=3;

		return true;
	}
	else
	{
		return false;
	}
}

bool CLoginDlg1::queryUsrGroupTable()
{
	QString sql = QString("select "
					"USERGROUPID,"
                   "USERGROUP,"
                   "PASSWORD,"
                   "PRIVILEGE,"
                   "DEPART"
				   " from ksusergroup where USERGROUP='%1' and PASSWORD='%2'").arg(g_clientUsr).arg(g_clientPasswd);
	QSqlQuery query(sql);

	if(query.next())
	{
		g_clientId=query.value(0).toInt();
		//g_ParentId=query.value(5).toInt();
		g_ParentId=0;
		QString tmp=query.value(3).toString();
		
		if (tmp==tr("超级管理员"))
		{
			g_privilege=1;
		}
		else if (tmp==tr("用户组管理员"))
		{
			g_privilege=2;
		}

		query.clear();
		return true;
	}
	else
	{
		return false;
	}
}

void CLoginDlg1::onOk()
{
	g_clientUsr =leUsr->text();
	g_clientPasswd=lePasswd->text();
	
	if(queryUsrTable()||queryUsrGroupTable())
	{
		emit okMsg();
	}
	else
	{
		QMessageBox::information(this, tr("information"), tr("用户名或密码错误"));
	}
	
}

void CLoginDlg1::onCancel()
{
	emit cancelMsg();
}