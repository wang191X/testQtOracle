#include "caclmanagew1.h"
#include "cnewacldlg1.h"
#include "GloabeParams.h"
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QMessageBox>
#include "CTitleDlg1.h"
#include "CCheckModel.h"
#include "CCheckDelegate.h"
#include "CInputInfoDlg.h"

CAclManageW1::CAclManageW1(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	connect(pbAdd, SIGNAL(clicked()),this, SLOT(addAcl()));
	connect(pbDelete, SIGNAL(clicked()),this, SLOT(deleteAcl()));
	connect(pbQuery, SIGNAL(clicked()),this, SLOT(queryAcl()));
	connect(pbSetGroup, SIGNAL(clicked()),this, SLOT(setGroupId()));
	connect(pbSetGroupTmp, SIGNAL(clicked()),this, SLOT(setGroupTmp()));
	connect(tbCopy, SIGNAL(clicked()),this, SLOT(copyRules()));
	connect(tbMove, SIGNAL(clicked()),this, SLOT(moveRules()));
	connect(pbQueryTmp, SIGNAL(clicked()),this, SLOT(queryAclTmp()));
	
	//model=new QSqlTableModel(this);
	model=new CCheckModel(this);
	model->setTable("aclrules");
	QString filter1 = QString("groupid>=%1 and groupid<=%2").arg(aclbgid).arg(aclegid);
	model->setFilter(filter1);
	model->select();
	tvAcl->setModel(model);
	tvAcl->setItemDelegate(new CCheckDelegate(0));

	tvAcl->horizontalHeader()->setMovable(true);
	
	modeltmp=new QSqlTableModel(this);
	modeltmp->setTable("acltmp");
	modeltmp->select();
	tvAclTmp->setModel(modeltmp);
}

CAclManageW1::~CAclManageW1()
{

}

void CAclManageW1::copyRules()
{
	for(int i=0,j=0;i<model->rowCount();++i)
	{
		QSqlRecord record=model->record(i);
		if(2==record.value("isSelected").toInt())
		{
			modeltmp->insertRecord(j,record);
			++j;
		}
	}

	int afd=modeltmp->rowCount();
	
	modeltmp->submitAll();
}

void CAclManageW1::moveRules()
{
	QSqlQuery query;
	bool ret=query.exec("insert into aclrules select * from acltmp");

	if (!ret)
	{
		QString error=query.lastError().text();
		QMessageBox::information(this, tr("information"), error);
		return;
	}    

	query.exec("delete from acltmp");
	
	modeltmp->select();
	model->select();
}

void CAclManageW1::setGroupTmp()
{
	QWidget*  inputWt=new CInputInfoDlg();
	CTitleDlg1 inputDlg(0,inputWt);
	QObject::connect(inputWt,SIGNAL(okMsg()),&inputDlg,SLOT(accept()));
	int ret=inputDlg.exec();
	int groupId=0;

	if(ret)
		groupId=((CInputInfoDlg*)inputWt)->sbGroupId->value();
		
	delete inputWt;
		
	for(int i=0;i<modeltmp->rowCount();++i)
	{
		QSqlRecord record=modeltmp->record(i);
		record.setValue("groupid",groupId);
		modeltmp->setRecord(i,record);
	}
	
	modeltmp->submitAll();
}

void CAclManageW1::setGroupId()
{
	QWidget*  inputWt=new CInputInfoDlg();
	CTitleDlg1 inputDlg(0,inputWt);
	QObject::connect(inputWt,SIGNAL(okMsg()),&inputDlg,SLOT(accept()));
	int ret=inputDlg.exec();
	int groupId=0;

	if(ret)
		groupId=((CInputInfoDlg*)inputWt)->sbGroupId->value();

	for(int i=0;i<model->rowCount();++i)
	{
		QSqlRecord record=model->record(i);
		if(2==record.value("isSelected").toInt())
		{

			record.setValue("groupid",groupId);
			model->setRecord(i,record);
		}
	}

	model->submitAll();

	delete inputWt;
}

void CAclManageW1::addAcl()
{
	QWidget*  newACLWt=new CNewAclDlg1();
	CTitleDlg1 newACLDlg(0,newACLWt);
	//newACLDlg.setFixedSize(newACLDlg.width(),newACLDlg.height());
	QObject::connect(newACLWt,SIGNAL(okMsg()),&newACLDlg,SLOT(accept()));
	int ret=newACLDlg.exec();

	delete newACLWt;

	//CNewAclDlg1 newAclDlg1;

	//if (newAclDlg1.exec()) 
	//{
	//}
}

void CAclManageW1::deleteAcl()
{
	QModelIndex index= tvAcl->currentIndex();
	QSqlRecord record= model->record(index.row());
	int cmdtype=record.value("cmdtype").toInt();

	if (cmdtype==ACL_ADD_SUCCESS)
	{
		QMessageBox::information(this, tr("information"), G2U("该规则已下发，不能删除"));
		return;
	}
	model->removeRow(index.row());
	model->submitAll();
}

void CAclManageW1::queryAclTmp()
{
	modeltmp->select();
}

void CAclManageW1::queryAcl()
{
	model->select();
}
