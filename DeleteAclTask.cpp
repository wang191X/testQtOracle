#include "DeleteAclTask.h"

#include <QtSql/QSqlTableModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QString>
#include <QMessageBox>
#include <QDateTime>
#include <QSqlError>
#include <QObject>

#include "DataStruct.h"
#include "SocketClient1.h"
#include "GloabeParams.h"
#include "SocketClientSyn.h"

CDeleteAclTask::CDeleteAclTask(void)
{
}

CDeleteAclTask::~CDeleteAclTask(void)
{
}

void CDeleteAclTask::sendCMD(int groupId)
{
	QSqlTableModel model;
	QString filter1;
	SACL* psacl;
	char* pSendBuff;
	int len,len1;
	int ruleCount;

	model.setTable("aclrules");
	filter1 = QString("groupid=%1").arg(groupId);
	model.setFilter(filter1);
	model.select();

	ruleCount=model.rowCount();

	if (ruleCount==0)
	{
		//QMessageBox::information(this,"information", G2U(""));
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

	boost::asio::io_service ios;
	CSocketClientSyn socketClientSyn(ios); 
	socketClientSyn.startConnection();
	socketClientSyn.sendData(pSendBuff,len);

	char* pRecvBuff=new char[len];
	socketClientSyn.recvData(pRecvBuff,len);
	socketClientSyn.closeConnection();

	for (int i=0;i!=ruleCount;++i)
	{
		memcpy_s(&psacl[i],len1,pRecvBuff+len1*i,len1);
		updateRules(psacl[i].id,psacl[i].cmdType);
	}
	delete [] psacl;
	delete [] pRecvBuff;
	delete [] pSendBuff;
}

void CDeleteAclTask::updateRules(int ruleId,int cmdType)
{
	QSqlTableModel model;
	model.setTable("aclrules");
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
