#include "testqtoracle.h"
#include <QDialog>
#include <QtGui/QPushButton>
#include "GloabeParams.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include "GloabeParams.h"
#include <QtGlobal>
#include <QPixmap>
#include <QDesktopWidget>
#include <QSqlDriver>

 
testQtOracle::testQtOracle(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	setupUi(this);
	//setWindowFlags(Qt::FramelessWindowHint);
	//this->setStyleSheet("border:1px solid #222");       
	QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);        
	toolButtonclose->setIcon(pix); 
	/*pix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);        
	toolButtonmax->setIcon(pix);*/         
	pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);        
	toolButtonmin->setIcon(pix);         

	connect(toolButtonclose, SIGNAL( clicked() ), this, SLOT(close()));        
	connect(toolButtonmin, SIGNAL( clicked() ), this, SLOT(onMaxWindow()));       
	//connect(toolButtonmax, SIGNAL( clicked() ), this, SLOT(onMaxWindow()));
	
	/*pix.load("D:\\80G\\icon\\0.png");
	tbAcl->setIcon(pix.scaled(100,100)); 
	tbXacl->setIcon(pix.scaled(100,100)); 
	tbPL->setIcon(pix.scaled(100,100)); 
	tbTask->setIcon(pix.scaled(100,100)); 
	tbUser->setIcon(pix.scaled(100,100)); 
	tbRuleView->setIcon(pix.scaled(100,100));*/ 


	//connect(tbPL, SIGNAL(clicked()),this, SLOT(plManage()));
	//connect(tbXacl, SIGNAL(clicked()),this, SLOT(xaclManage()));
	connect(tbRuleManage, SIGNAL(clicked()),this, SLOT(ruleManageFun()));
	//connect(tbAcl, SIGNAL(clicked()),this, SLOT(aclManage()));
	connect(tbUser, SIGNAL(clicked()),this, SLOT(users()));
	connect(tbRuleView, SIGNAL(clicked()),this, SLOT(ruleReview()));
	connect(tbUsrGroup, SIGNAL(clicked()),this, SLOT(usrGroupFun()));
	
	contDB();
	setwinsLayout();
	loadFunction(g_privilege);

	ruleManage->socketClientSyn=new CSocketClientSyn(); 
	ruleManage->socketClientSyn->startConnection();
	QString statusMsg1="";

	if (ruleManage->socketClientSyn->connStatus==-1)
	{
		statusMsg1=tr("连接服务端超时");
		QString statusMsg=tr("当前用户：")+g_clientUsr+"**************"+statusMsg1;
		statusBar1->showMessage(statusMsg);//(G2U(statusMsg.toAscii()));
	}
	else
	{
		QString statusMsg=tr("当前用户：")+g_clientUsr;
		statusBar1->showMessage(statusMsg);//(G2U(statusMsg.toAscii()));
	}
	
}

testQtOracle::~testQtOracle()
{
	ruleManage->socketClientSyn->closeConnection();
	delete ruleManage->socketClientSyn;
}

void testQtOracle::setwinsLayout()
{
	stackedWidget=new QStackedWidget;

	usersDlg=new CUsers(this);
	rulesReview=new CRulesReview1(this);
	usrGroup=new CUsrGroupWt1(this);
	mainSplitter=new QSplitter(Qt::Horizontal,0);
	ruleManage=new CRuleManage1();
	usrTree=new CUsrTree1();

	QObject::connect(usrTree->usrTreeWt,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
	ruleManage,SLOT(queryNormalRules(QTreeWidgetItem*,int)));
	mainSplitter->insertWidget(0,usrTree);
	mainSplitter->insertWidget(1,ruleManage);
	stackedWidget->insertWidget (0, mainSplitter);
	stackedWidget->insertWidget (1, rulesReview);
	stackedWidget->insertWidget (2, usersDlg);
	stackedWidget->insertWidget (3, usrGroup);
	
	gridLayout_2->addWidget(stackedWidget);
	//setCentralWidget(stackedWidget);
}

void testQtOracle::contDB()
{
	QSqlDatabase db=QSqlDatabase::addDatabase("QOCI");
	//QSqlDatabase db=QSqlDatabase::addDatabase("QODBC");
	db.setHostName(g_ip);
	db.setDatabaseName(g_dbName);
	db.setUserName(g_usr);
	db.setPassword(g_passwd);

	if (!db.open())
	{
		QString str=db.lastError().text();
		QMessageBox::information(this, tr("information"), G2U(str.toAscii()));
	}
}

void testQtOracle::loadFunction(int privilege1)
{
	if(privilege1==1)
	{
		//tbAcl->setHidden(true);
		//tbXacl->setHidden(true);
		//tbPL->setHidden(true);
		tbRuleManage->setHidden(true);
		tbUser->setHidden(true);
		tbRuleView->setHidden(true);
		
		stackedWidget->setCurrentIndex(3);
	}
	else if (privilege1==2)
	{
		//tbAcl->setHidden(true);
		//tbXacl->setHidden(true);
		//tbPL->setHidden(true);
		//tbRuleManage->setHidden(true);
		tbUsrGroup->setHidden(true);
		
		//menuTask->menuAction()-> setVisible(false);
		//actionAclManage->setVisible(false);
		//actionXaclManage->setVisible(false);
		//actionPlManage->setVisible(false);

		stackedWidget->setCurrentIndex(1);

		ruleManage->pbAdd->setEnabled(false);
		ruleManage->pbApply->setEnabled(false);
		ruleManage->pbDeleteTmp->setEnabled(false);
		ruleManage->pbOK->setEnabled(false);
		ruleManage->pbUnLoad->setEnabled(false);
		ruleManage->pbDelete->setEnabled(false);
		
	}
	else if (privilege1==3)
	{
		tbUser->setHidden(true);
		tbRuleView->setHidden(true);
		tbUsrGroup->setHidden(true);
		//menuUsr->menuAction()-> setVisible(false);
		//actionRulesReview->setVisible(false);

		stackedWidget->setCurrentIndex(0);
	}
}

void testQtOracle::users()
{
	stackedWidget->setCurrentIndex(2);
}

void testQtOracle::aclManage()
{
	stackedWidget->setCurrentIndex(1);
}

void testQtOracle::xaclManage()
{
	stackedWidget->setCurrentIndex(2);
}

void testQtOracle::plManage()
{
	stackedWidget->setCurrentIndex(3);
}

void testQtOracle::ruleManageFun()
{
	stackedWidget->setCurrentIndex(0);
}

void testQtOracle::ruleReview()
{
	stackedWidget->setCurrentIndex(1);
}

void testQtOracle::usrGroupFun()
{
stackedWidget->setCurrentIndex(3);
}

void testQtOracle::onMaxWindow()
{
	QDesktopWidget* tmpWindow=new QDesktopWidget();
	QRect rect=tmpWindow->availableGeometry();

	if (rect==geometry())
	{
		//QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);        
		//toolButtonmin->setIcon(pix);
		showMinimized();
	}
	else
	{
		QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);        
		toolButtonmin->setIcon(pix);  
		setGeometry(rect);
	}
}

