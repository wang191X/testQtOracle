#include "CXaclManageW1.h"
#include "cnewxacldlg1.h"
#include "GloabeParams.h"
#include <QSqlRecord>
#include <QMessageBox>
#include "CTitleDlg1.h"

CXaclManageW1::CXaclManageW1(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	connect(pbAdd, SIGNAL(clicked()),this, SLOT(addAcl()));
	connect(pbDelete, SIGNAL(clicked()),this, SLOT(deleteAcl()));
	connect(pbQuery, SIGNAL(clicked()),this, SLOT(queryAcl()));

	model=new QSqlTableModel(this);
	model->setTable("xaclrules");
	QString filter1 = QString("groupid>=%1 and groupid<=%2").arg(xaclbgid).arg(xaclegid);
	model->setFilter(filter1);
	model->select();
	tvXacl->setModel(model);
}

CXaclManageW1::~CXaclManageW1()
{

}

void CXaclManageW1::addAcl()
{
	QWidget*  newXACLWt=new CNewXaclDlg1();
	CTitleDlg1 newXACLDlg(0,newXACLWt);
	//newACLDlg.setFixedSize(newACLDlg.width(),newACLDlg.height());
	QObject::connect(newXACLWt,SIGNAL(okMsg()),&newXACLDlg,SLOT(accept()));
	int ret=newXACLDlg.exec();

	/*CNewXaclDlg1 newXaclDlg;

	if (newXaclDlg.exec()) 
	{
	}*/
}

void CXaclManageW1::deleteAcl()
{
	QModelIndex index= tvXacl->currentIndex();
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

void CXaclManageW1::queryAcl()
{
	model->select();
}
