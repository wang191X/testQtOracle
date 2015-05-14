#include "DeleteXaclTask.h"

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

#include "DeletePLTask.h"

CDeleteXaclTask::CDeleteXaclTask(void)
{
}

CDeleteXaclTask::~CDeleteXaclTask(void)
{
}

void CDeleteXaclTask::sendCMD(int groupId)
{
	QSqlTableModel model;
	QString filter1;
	SXACL* psxacl;
	char* pSendBuff;
	int len,len1;
	int ruleCount;

	model.setTable("xaclrules");
	filter1 = QString("groupid=%1").arg(groupId);
	model.setFilter(filter1);
	model.select();

	ruleCount=model.rowCount();

	if (ruleCount==0)
	{
		//QMessageBox::information(this, tr("information"), G2U(""));
		return;
	}

	psxacl=new SXACL[ruleCount];
	std::vector<int> plidVec;

	for (int i=0;i<model.rowCount();++i)
	{
		QSqlRecord record=model.record(i);
		psxacl[i].cmdType=XACL_DELETE;             
		psxacl[i].id=record.value("id").toInt();
		psxacl[i].PLId=record.value("plid").toInt();
		plidVec.push_back(psxacl[i].PLId);
	}

	CDeletePLTask deletePLTask;
	deletePLTask.sendCMD(plidVec);
    
	len1=sizeof(SXACL);
	len=ruleCount*len1;
	pSendBuff=new char[len];

	for (int i=0;i!=ruleCount;++i)
	{
		memcpy_s(pSendBuff+len1*i, len, (char*)&(psxacl[i]), len1 );
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
		memcpy_s(&psxacl[i],len1,pRecvBuff+len1*i,len1);
		updateRules(psxacl[i].id,psxacl[i].cmdType);
	}

    plidVec.clear();
	delete [] psxacl;
	delete [] pRecvBuff;
	delete [] pSendBuff;
}

void CDeleteXaclTask::updateRules(int ruleId,int cmdType)
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
