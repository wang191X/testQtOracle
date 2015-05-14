#include "CTaskManage1.h"
#include "CNewTask1.h"
#include "CNewXaclTask.h"
#include <QSqlRecord>
#include "CTaskDelegate.h"
#include <QSqlError>
#include <QString>
#include <QMessageBox>
#include "DataStruct.h"
#include "SocketClient1.h"
#include <QDateTime>
#include <QSqlError>
#include "GloabeParams.h"
#include "SocketClientSyn.h"
#include "DeleteTask.h"
#include "DeleteAclTask.h"
#include "DeleteXaclTask.h"
#include "CTitleDlg1.h"
#include "NewTask2.h"

CTaskManage1::CTaskManage1(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);
	connect(pbNewTask, SIGNAL(clicked()),this, SLOT(addTask()));
	//connect(pbNewXaclTask,SIGNAL(clicked()),this, SLOT(addXaclTask()));
	connect(pbDeleteTask, SIGNAL(clicked()),this, SLOT(deleteTask()));
	connect(pbQueryTask, SIGNAL(clicked()),this, SLOT(queryTask()));

	model=new QSqlTableModel(this);
	model->setTable("taskinfo");
	model->select();
	tvTask->setItemDelegate(new CTaskDelegate(0));
	tvTask->setModel(model);
	tvTask->setColumnWidth(1,130);
}

CTaskManage1::~CTaskManage1()
{

}

void CTaskManage1::addTask()
{
	//QWidget*  newTaskWt=new CNewTask1();
	QWidget*  newTaskWt=new CNewTask2();
	CTitleDlg1 newTaskDlg(0,newTaskWt);
	newTaskDlg.setFixedSize(newTaskDlg.width(),newTaskDlg.height());
	QObject::connect(newTaskWt,SIGNAL(okMsg()),&newTaskDlg,SLOT(accept()));
	int ret=newTaskDlg.exec();

	/*CNewTask1 newTask;
	newTask.exec();*/
}

void CTaskManage1::addXaclTask()
{
	QWidget*  newXACLTaskWt=new CNewXaclTask();
	CTitleDlg1 newXACLTaskDlg(0,newXACLTaskWt);
	QObject::connect(newXACLTaskWt,SIGNAL(okMsg()),&newXACLTaskDlg,SLOT(accept()));
	int ret=newXACLTaskDlg.exec();

	/*CNewXaclTask newXaclTask;
	newXaclTask.exec();*/
}

void CTaskManage1::deleteTask()
{
	QModelIndex index= tvTask->currentIndex();
	//QString error=model->lastError().text();
	//QMessageBox::information(this, tr("information"), error);
	QSqlRecord record= model->record(index.row());
	int groupId=record.value("groupid").toInt();
	int taskType=record.value("tasktype").toInt();;//是acl还是xacl
	model->removeRow(index.row());
	model->submitAll();

	CDeleteTask* deleteTask;

	if (taskType==1)
	{
		deleteTask=new CDeleteAclTask();
		deleteTask->sendCMD(groupId);
	}
	else if(taskType==2)
	{
		deleteTask=new CDeleteXaclTask();
		deleteTask->sendCMD(groupId);
	}

	/*QSqlTableModel model;
	QString filter1;
	SXACL* psxacl;
	SACL* psacl;
	SPL* pspl;
	char* pSendBuff;
	int len,len1;
	int ruleCount;
	
	if(taskType==1)
	{
		model.setTable("aclrules");
		filter1 = QString("groupid=%1").arg(groupId);
		model.setFilter(filter1);
		model.select();

		ruleCount=model.rowCount();

		if (ruleCount==0)
		{
			QMessageBox::information(this, tr("information"), G2U("所选规则组内规则数为0"));
			return;
		}

		psacl=new SACL[ruleCount];

		for (int i=0;i<model.rowCount();++i)
		{
			QSqlRecord record=model.record(i);
			psacl[i].cmdType=ACL_DELETE;             
			psacl[i].id=record.value("id").toInt();
		}

		len1=sizeof(SACL);
		len=ruleCount*len1;
		pSendBuff=new char[len];

		for (int i=0;i!=ruleCount;++i)
		{
			memcpy_s(pSendBuff+len1*i, len, (char*)&(psacl[i]), len1 );
		}
	}
	else if (taskType==2)
	{
		model.setTable("xaclrules");
		filter1 = QString("groupid=%1").arg(groupId);
		model.setFilter(filter1);
		model.select();

		ruleCount=model.rowCount();

		if (ruleCount==0)
		{
			QMessageBox::information(this, tr("information"), G2U("所选规则组内规则数为0"));
			return;
		}

		psxacl=new SXACL[ruleCount];
		std::vector<int> plidVec;

		for (int i=0;i<model.rowCount();++i)
		{
			QSqlRecord record=model.record(i);
			psxacl[i].cmdType=XACL_DELETE;             
			psxacl[i].id=record.value("id").toInt();
			plidVec.push_back(psxacl[i].PLId);
		}

		int plCount=plidVec.size();
		pspl=new SPL[plCount];

		for(int i=0;i!=plCount;++i)
		{
			model.setTable("plrules");
			QString filter1 = QString("id=%1").arg(plidVec[i]);
			model.setFilter(filter1);
			model.select();
			QSqlRecord record=model.record(0);
			pspl[i].cmdType=PL_DELETE;             
			pspl[i].id=record.value("id").toInt();
		}


		len1=sizeof(SXACL);
		len=ruleCount*len1;
		pSendBuff=new char[len];

		for (int i=0;i!=ruleCount;++i)
		{
			memcpy_s(pSendBuff+len1*i, len, (char*)&(psxacl[i]), len1 );
		}
	}

	boost::asio::io_service ios;
	CSocketClientSyn socketClientSyn(ios); 
	socketClientSyn.startConnection();
	socketClientSyn.sendData(pSendBuff,len);

	char* pRecvBuff=new char[len];
	socketClientSyn.recvData(pRecvBuff,len);
	socketClientSyn.closeConnection();
	CDeleteTask* deleteTask;

	if(taskType==1)
	{
		for (int i=0;i!=ruleCount;++i)
		{
			memcpy_s(&psacl[i],len1,pRecvBuff+len1*i,len1);
			deleteTask=new CDeleteAclTask();
			deleteTask->updateRules(psacl[i].id,psacl[i].cmdType);
		}
		delete [] psacl;
	}
	else if (taskType==2)
	{
		for (int i=0;i!=ruleCount;++i)
		{
			memcpy_s(&psxacl[i],len1,pRecvBuff+len1*i,len1);
			deleteTask=new CDeleteXaclTask();
			deleteTask->updateRules(psxacl[i].id,psxacl[i].cmdType);
		}
		delete [] psxacl;
	}

	delete [] pRecvBuff;
	delete [] pSendBuff;*/
	
}

void CTaskManage1::queryTask()
{
	model->select();
}