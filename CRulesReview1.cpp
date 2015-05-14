#include "CRulesReview1.h"
#include <QString>
#include "GloabeParams.h"


CRulesReview1::CRulesReview1(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);

	connect(pbAgree, SIGNAL(clicked()),this, SLOT(agree()));
	connect(pbQuery, SIGNAL(clicked()),this, SLOT(query()));
	connect(pbReject, SIGNAL(clicked()),this, SLOT(reject()));
	/*connect(pbXaclAgree, SIGNAL(clicked()),this, SLOT(agreeAcl()));
	connect(pbXaclQuery, SIGNAL(clicked()),this, SLOT(queryAcl()));
	connect(pbXaclReject, SIGNAL(clicked()),this, SLOT(rejectAcl()));
	connect(pbPLAgree, SIGNAL(clicked()),this, SLOT(agreeAcl()));
	connect(pbPLQuery, SIGNAL(clicked()),this, SLOT(queryAcl()));
	connect(pbPLReject, SIGNAL(clicked()),this, SLOT(rejectAcl()));*/

	model=new QSqlTableModel(this);
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	model->setTable("rule");
	QString filter1 = QString("ispassed=0 and usrgid=%1").arg(g_clientId);
	model->setFilter(filter1);
	model->select();
	tvRule->setModel(model);

	// modelXacl=new QSqlTableModel(this);
	// modelXacl->setEditStrategy(QSqlTableModel::OnManualSubmit);
	// modelXacl->setTable("xaclrules");
	// filter1 = QString("ispassed=0");
	// modelXacl->setFilter(filter1);
	// modelXacl->select();
	// tvXacl->setModel(modelXacl);

	// modelPL=new QSqlTableModel(this);
	// modelPL->setEditStrategy(QSqlTableModel::OnManualSubmit);
	// modelPL->setTable("plrules");
	// filter1 = QString("ispassed=0");
	// modelPL->setFilter(filter1);
	// modelPL->select();
	// tvPL->setModel(modelPL);
}

CRulesReview1::~CRulesReview1()
{

}

void CRulesReview1::query()
{
	model->select();
}


void CRulesReview1::agree()
{
	QModelIndex index= tvRule->currentIndex();
	int column=model->fieldIndex("ispassed");
	model->setData (model->index(index.row(),column),1,Qt::EditRole);
	model->submitAll();
}

void CRulesReview1::reject()
{
	QModelIndex index= tvRule->currentIndex();
	int column=model->fieldIndex("ispassed");
	model->setData (model->index(index.row(),column),2,Qt::EditRole);
	model->submitAll();
}

void CRulesReview1::queryXacl()
{
	//modelXacl->select();
}


void CRulesReview1::agreeXacl()
{
	//modelXacl->submitAll();
}

void CRulesReview1::rejectXacl()
{
	//modelXacl->revertAll();
}

void CRulesReview1::queryPL()
{
	//modelPL->select();
}


void CRulesReview1::agreePL()
{
	//modelPL->submitAll();
}

void CRulesReview1::rejectPL()
{
	//modelPL->revertAll();
}
