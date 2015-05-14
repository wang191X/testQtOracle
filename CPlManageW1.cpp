#include "CPlManageW1.h"
#include "cnewpldlg1.h"
#include "GloabeParams.h"
#include "CTitleDlg1.h"


CPlManageW1::CPlManageW1(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	connect(pbAdd, SIGNAL(clicked()),this, SLOT(addPL()));
	connect(pbDelete, SIGNAL(clicked()),this, SLOT(deletePL()));
	connect(pbQuery, SIGNAL(clicked()),this, SLOT(queryPL()));

	model=new QSqlTableModel(this);
	model->setTable("plrules");
	QString filter1 = QString("id>=%1 and id<=%2").arg(plbid).arg(pleid);
	model->setFilter(filter1);
	model->select();
	tvPL->setModel(model);
}

CPlManageW1::~CPlManageW1()
{

}

void CPlManageW1::addPL()
{
	QWidget*  newPLWt=new CNewPLDlg1();
	CTitleDlg1 newPLDlg(0,newPLWt);
	//newACLDlg.setFixedSize(newACLDlg.width(),newACLDlg.height());
	QObject::connect(newPLWt,SIGNAL(okMsg()),&newPLDlg,SLOT(accept()));
	int ret=newPLDlg.exec();

	/*CNewPLDlg1 newPlDlg;

	if (newPlDlg.exec()) 
	{
	}*/
}

void CPlManageW1::deletePL()
{
	QModelIndex index= tvPL->currentIndex();
	model->removeRow(index.row());
	model->submitAll();
}

void CPlManageW1::queryPL()
{
	model->select();
}