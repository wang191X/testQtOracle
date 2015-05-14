#include "NewTask2.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>
#include <QtSql/QSqlTableModel>
#include <QString>
#include <QMessageBox>
#include "DataStruct.h"
#include "SocketClient1.h"
#include <QDateTime>
#include <QSqlError>
#include "GloabeParams.h"
#include "SocketClientSyn.h"
#include <vector>

CNewTask2::CNewTask2(void)
{
	connect(pbStart, SIGNAL(clicked()),this, SLOT(start()));
	
	sbXACLGroupid->setMaximum(xaclegid);
	sbXACLGroupid->setMinimum(xaclbgid);
}

CNewTask2::~CNewTask2(void)
{
}

void CNewTask2::start()
{
	newACLTask();
	newXaclTask();
	int aclGroup=sbACLGroupid->value();
	int xaclGroup=sbXACLGroupid->value();
	newTaskRecord1(aclGroup,xaclGroup);
}

void CNewTask2::newXaclTask()
{
	int groupid=sbXACLGroupid->value();

	QSqlTableModel model;
	model.setTable("xaclrules");
	QString filter1 = QString("groupid=%1").arg(groupid);
	model.setFilter(filter1);
	model.select();

	//QString tmp;
	//tmp.setNum(model.rowCount());
	//QMessageBox::information(this, tr("information"), tmp);
	int ruleCount=model.rowCount();

	if (ruleCount==0)
	{
		QMessageBox::information(this, tr("information"), G2U("所选规则组内规则数为0"));
		return;
	}

	SXACL* psxacl=new SXACL[ruleCount];
	
	//SocketClient1 sockClient;
	std::vector<int> plidVec;

	for (int i=0;i<model.rowCount();++i)
	{
		QSqlRecord record=model.record(i);

		psxacl[i].cmdType=XACL_ADD;             
		psxacl[i].id=record.value("id").toInt();
		
	}

	int plCount=plidVec.size();
	SPL* pspl=new SPL[plCount];

	for(int i=0;i!=plCount;++i)
	{
		model.setTable("plrules");
		QString filter1 = QString("id=%1").arg(plidVec[i]);
		model.setFilter(filter1);
		model.select();
		QSqlRecord record=model.record(0);
		pspl[i].cmdType=PL_ADD;             
		

		for (int k=0;k!=64;++k)
		{
			pspl[i].keyValue[k]=0;
			pspl[i].keyMask[k]=0;
		}

		//for (int k=2,j=pspl[i].offset;k<=tmp1.length();k=k+3,++j)
		//{
		//	QString str=tmp1.mid(k,2);
		//	bool ok;
		//	int hex = str.toInt(&ok, 16);
		//	pspl[i].keyValue[j]=(unsigned char)hex;

		//	str=tmp2.mid(k,2);
		//	hex = str.toInt(&ok, 16);
		//	pspl[i].keyMask[j]=(unsigned char)hex;
		//}
	}

	int len1=sizeof(SPL);
	int len=plCount*len1;
	char* pSendBuff=new char[len];

	for (int i=0;i!=plCount;++i)
	{
		memcpy_s(pSendBuff+len1*i, len, (char*)&(pspl[i]), len1 );
	}

	boost::asio::io_service ios;
	CSocketClientSyn socketClientSyn(ios); 
	socketClientSyn.startConnection();
	socketClientSyn.sendData(pSendBuff,len);

	char* pRecvBuff=new char[len];
	socketClientSyn.recvData(pRecvBuff,len);
	socketClientSyn.closeConnection();

	for (int i=0;i!=plCount;++i)
	{
		memcpy_s(&pspl[i],len1,pRecvBuff+len1*i,len1);
		updatePLRules(pspl[i].id,pspl[i].cmdType);
	}

	delete [] pspl;
	plidVec.clear();

	len1=sizeof(SXACL);
	len=ruleCount*len1;
	pSendBuff=new char[len];

	for (int i=0;i!=ruleCount;++i)
	{
		memcpy_s(pSendBuff+len1*i, len, (char*)&(psxacl[i]), len1 );
	}

	socketClientSyn.startConnection();
    socketClientSyn.sendData(pSendBuff,len);

	pRecvBuff=new char[len];
	socketClientSyn.recvData(pRecvBuff,len);
	socketClientSyn.closeConnection();

	for (int i=0;i!=ruleCount;++i)
	{
		memcpy_s(&psxacl[i],len1,pRecvBuff+len1*i,len1);
		updateXACLRules(psxacl[i].id,psxacl[i].cmdType);
	}

	delete [] pRecvBuff;
	delete [] pSendBuff;
	delete [] psxacl;

	//newXACLTaskRecord(groupid);

	QMessageBox::information(this, tr("information"), G2U("下发完成"));

	emit okMsg();
}

void CNewTask2::newTaskRecord1(int aclGroup,int xaclGroup)
{
	//增加和修改数据库任务记录
	QSqlQuery query;
	query.prepare("insert into taskinfo("
		"ID,"
		"BEGINTIME,"
		"STATUS,"
		"USERID,"
		"ACLGROUP,"
		"XACLGROUP"
		")"
		"values("
		":ID,"
		":BEGINTIME,"
		":STATUS,"
		":USERID,"
		":ACLGROUP,"
		":XACLGROUP"
		")");

	QDateTime now = QDateTime::currentDateTime();
	qint64 ms=now.toMSecsSinceEpoch(); 

	query.bindValue(":ID",ms);
	query.bindValue(":BEGINTIME",now);
	query.bindValue(":STATUS",0);
	query.bindValue(":USERID",g_clientId);
	query.bindValue(":ACLGROUP",aclGroup);
	query.bindValue(":XACLGROUP",xaclGroup);            

	bool ret=query.exec();

	if (ret)
	{
		//QMessageBox::information(this, tr("information"), G2U("创建成功"));
	} 
	else
	{
		QString error=query.lastError().text();
		QMessageBox::information(this, tr("information"), error);
	}

	query.clear();
}

void CNewTask2::newTaskRecord(int groupId)
{
	//增加和修改数据库任务记录
	QSqlQuery query;
	query.prepare("insert into taskinfo("
		"ID,"
		"BEGINTIME,"
		"STATUS,"
		"USERID,"
		"GROUPID,"
		"tasktype"
		")"
		"values("
		":ID,"
		":BEGINTIME,"
		":STATUS,"
		":USERID,"
		":GROUPID,"
		":tasktype"
		")");

	QDateTime now = QDateTime::currentDateTime();
	qint64 ms=now.toMSecsSinceEpoch(); 

	query.bindValue(":ID",ms);
	query.bindValue(":BEGINTIME",now);
	query.bindValue(":STATUS",0);
	query.bindValue(":USERID",g_clientId);
	query.bindValue(":GROUPID",groupId);
	query.bindValue(":tasktype",2);            //1表示acl任务，2表示xacl任务

	bool ret=query.exec();

	if (ret)
	{
		//QMessageBox::information(this, tr("information"), G2U("创建成功"));
	} 
	else
	{
		QString error=query.lastError().text();
		QMessageBox::information(this, tr("information"), error);
	}

	query.clear();
}

void CNewTask2::updateXACLRules(int ruleId,int cmdType)
{
	QSqlTableModel model;
	model.setTable("xaclrules");
	QString filter1=QString("id=%1").arg(ruleId);
	model.setFilter(filter1);
	model.select();

	if (model.rowCount()==1)
	{
		QSqlRecord record=model.record(0);
		record.setValue("cmdtype",cmdType);
		model.setRecord(0,record);
	}

	model.submitAll();
	//QString error=model.lastError().text();
	//QMessageBox::information(this, tr("information"), error);

}

void CNewTask2::updatePLRules(int ruleId,int cmdType)
{
	QSqlTableModel model;
	model.setTable("plrules");
	QString filter1=QString("id=%1").arg(ruleId);
	model.setFilter(filter1);
	model.select();

	if (model.rowCount()==1)
	{
		QSqlRecord record=model.record(0);
		record.setValue("cmdtype",cmdType);
		model.setRecord(0,record);
	}

	model.submitAll();
	//QString error=model.lastError().text();
	//QMessageBox::information(this, tr("information"), error);

}
