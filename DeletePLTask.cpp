#include "DeletePLTask.h"

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

CDeletePLTask::CDeletePLTask(void)
{
}

CDeletePLTask::~CDeletePLTask(void)
{
}

void CDeletePLTask::updateRules(int ruleId,int cmdType)
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

void CDeletePLTask::sendCMD(std::vector<int>& plidVec)
{
	QSqlTableModel model;
	QString filter1;
	SPL* pspl;
	
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
		updateRules(pspl[i].id,pspl[i].cmdType);
	}

	delete [] pspl;
	delete [] pRecvBuff;
	delete [] pSendBuff;
}
