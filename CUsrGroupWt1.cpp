#include "CUsrGroupWt1.h"
#include "CAddUsrGroup1.h"
#include "CTitleDlg1.h"

CUsrGroupWt1::CUsrGroupWt1(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

    connect(pbAdd, SIGNAL(clicked()),this, SLOT(addUsrGroup()));
	connect(pbDelete, SIGNAL(clicked()),this, SLOT(deleteUsrGroup()));
	connect(pbQuery, SIGNAL(clicked()),this, SLOT(queryUsrGroup()));
	model=new QSqlTableModel(this);
	model->setTable("ksusergroup");
	model->select();

	tvUsrGroup->setModel(model);
}

CUsrGroupWt1::~CUsrGroupWt1()
{

}

void CUsrGroupWt1::addUsrGroup()
{
	QWidget* newUsrGroupWt=new CAddUsrGroup1();
	((CAddUsrGroup1*)newUsrGroupWt)->isUsr=FALSE;
	((CAddUsrGroup1*)newUsrGroupWt)->cbPrivilege->addItem(tr("超级管理员"));
	((CAddUsrGroup1*)newUsrGroupWt)->cbPrivilege->addItem(tr("用户组管理员"));
	CTitleDlg1 newUsrGroupDlg(0,newUsrGroupWt);
	QObject::connect(newUsrGroupWt,SIGNAL(okMsg()),&newUsrGroupDlg,SLOT(accept()));
	int ret=newUsrGroupDlg.exec();
}

void CUsrGroupWt1::deleteUsrGroup()
{
QModelIndex index= tvUsrGroup->currentIndex();
	model->removeRow(index.row());
	model->submitAll();
}

void CUsrGroupWt1::queryUsrGroup()
{
	model->select();
}