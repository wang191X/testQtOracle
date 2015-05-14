#include "CUsrDlg1.h"
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include "DataStruct.h"
#include "GloabeParams.h"

CUsrDlg1::CUsrDlg1(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	connect(pbOk, SIGNAL(clicked()), this, SLOT(onOk()));
	connect(pbCancel, SIGNAL(clicked()), this, SLOT(onCancel()));

	/*sbaegid->setMaximum(aclegid);
	sbabgid->setMinimum(aclbgid);
	sbxegid->setMaximum(xaclegid);
	sbxbgid->setMinimum(xaclbgid);
	sbpeid->setMaximum(pleid);
	sbpbid->setMinimum(plbid);*/
}

CUsrDlg1::~CUsrDlg1()
{

}

void CUsrDlg1::onOk()
{
	int id=sbId->value();
	QString privilege=cbPrivilege->currentText ();
	QString depart=cbDepart->currentText ();
	QString user=leUsr->text();
	QString passwd=lePasswd->text();
	/*int abgid= sbabgid->value();
	int aegid=sbaegid->value();
	int xbgid=sbxbgid->value();
	int xegid=sbxegid->value();
	int pbid=sbpbid->value();
	int peid=sbpeid->value();*/

	QSqlQuery query;
	query.prepare("insert into userinfo(id,privilege,depart,name,passwd,aclbgid,aclegid,xaclbgid,xaclegid,plbid,pleid,usrgid)"
		"values(:id,:privilege,:depart,:name,:passwd,:aclbgid,:aclegid,:xaclbgid,:xaclegid,:plbid,:pleid,:usrgid)");
	query.bindValue(":id",id);
	query.bindValue(":privilege",privilege);
	query.bindValue(":depart",depart);
	query.bindValue(":name",user);
	query.bindValue(":passwd",passwd);
	/*query.bindValue(":aclbgid",abgid);
	query.bindValue(":aclegid",aegid);
	query.bindValue(":xaclbgid",xbgid);
	query.bindValue(":xaclegid",xegid);
	query.bindValue(":plbid",pbid);
	query.bindValue(":pleid",peid);*/
	query.bindValue(":usrgid",g_clientId);
	bool ret=query.exec();

	if (ret)
	{
		QMessageBox::information(this, tr("information"), G2U("创建成功"));
	} 
	else
	{
		QMessageBox::information(this, tr("information"), G2U("创建失败"));
	}

	query.clear();
	emit okMsg();
}

void CUsrDlg1::onCancel()
{
	emit cancelMsg();
}
