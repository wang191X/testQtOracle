#include "CIdResource.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QQueue>
#include "GloabeParams.h"
#include <QSet>
#include <QSqlRecord>
#include <QMessageBox>
#include <QDebug>

CIdResource::CIdResource(QObject *parent)
	: QObject(parent)
{
	initUsrIdPool();
	initUsrGIdPool();
	initRuleIdPool();
	initRulesIdPool();
	initACLIdPool();
	initXACLIdPool();
	initPLIdPool();
}

CIdResource::~CIdResource()
{

}

int CIdResource::getIdRes()
{
	// QSqlQuery q;
	// QString querySql=QString("select max(ruleid) from rule");
	// q.exec(querySql);
	
	// while (q.next())
	// {
		// return q.value(0).toInt()+1;
	// }
	
	// return 1;
	
	return queueRuleId.dequeue();
}

//int CIdResource::getGroupIdRes(QString& groupDesc)
int CIdResource::getGroupIdRes()
{
	// //若组描述存在，分配同样组id，若组描述不存在，分配新组id
	// QSqlQuery q;
	// QString querySql=QString("select rulesid from rules where rulesname='%1'").arg(groupDesc);
	// q.exec(querySql);
	
	// while (q.next())
	// {
		// return q.value(0).toInt();
	// }
	
	// querySql=QString("select max(rulesid) from rules");
	// q.exec(querySql);
	// int retId=0;
	
	// while (q.next())
	// {
		// retId=q.value(0).toInt()+1;
	// }
	
	// if(retId==0)
		// retId=1;
	
	// return retId;
	
	return queueRulesId.dequeue();
}

int CIdResource::getMultiIdRes(QString& idType)
{
	QSqlQuery q;
	//QSqlRecord rec;

	if(idType=="acl")
	{
		q.exec("select id from aclid order by id");
		//rec = q.record();
	}
	else if(idType=="xacl")
	{
		q.exec("select id from xaclid order by id");
		//rec = q.record();
	}
	else if(idType=="pl")
	{
		q.exec("select id from plid order by id");
		//rec = q.record();
	}
	
	//qDebug() << "Number of columns: " << rec.count();
	int beginNum=0;
	int endNum=0;
	const int maxIdRes=10000;
	QQueue<int>queueId;

	while (q.next())
	{
		endNum=q.value(0).toInt();
		
		for (int i=beginNum;i!=endNum;++i)
		{
			//qDebug() << i; // output all names
			queueId.enqueue(i);
		}

		beginNum=endNum+1;
	}

	while(queueId.count()<maxIdRes)
	{
		++endNum;
		queueId.enqueue(endNum);
	}
	
	return 0;
}

int CIdResource::getSingleIdRes(QString& idType)
{
	// QSqlTableModel model;
	// model.setTable(idType);
	// QString filter1="";
	// int minNum,maxNum;

	if (idType==tr("ACLID"))
	{
		while(true)
		{
			int resId=queueACLId.dequeue();
			
			if(!idConflict(resId,idType))
				return resId;
		}
		
		//return queueACLId.dequeue();
		// filter1=QString("ID>=%1 and ID<=%2").arg(g_minACLID).arg(g_maxACLID);
		// minNum=g_minACLID;
		// maxNum=g_maxACLID;
	}
	else if (idType==tr("XACLID"))
	{
		while(true)
		{
			int resId=queueXACLId.dequeue();
			
			if(!idConflict(resId,idType))
				return resId;
		}
		//return queueXACLId.dequeue();
		// filter1=QString("ID>=%1 and ID<=%2").arg(g_minXACLID).arg(g_maxXACLID);
		// minNum=g_minXACLID;
		// maxNum=g_maxXACLID;
	}
	else if (idType==tr("PLID"))
	{
		while(true)
		{
			int resId=queuePLId.dequeue();
			
			if(!idConflict(resId,idType))
				return resId;
		}
		//return queuePLId.dequeue();
		// filter1=QString("ID>=%1 and ID<=%2").arg(g_minPLID).arg(g_maxPLID);
		// minNum=g_minPLID;
		// maxNum=g_maxPLID;
	}
	
	// model.setFilter(filter1);
	// model.setSort( 0, Qt::AscendingOrder);
	// model.select();
		
	// QSet<int>idSet;
	
	// for(int j=0;j<model.rowCount();++j)
	// {
		// QSqlRecord record=model.record(j);
		// idSet<<record.value("id").toInt();
	// }
	
	// QQueue<int>queueId;
	
	// for(int j=minNum;j!=maxNum+1;++j)
	// {
		// if(!idSet.contains(j))
		// {
			// queueId.enqueue(j);
		// }
	// }
	
	// idSet.clear();
	
	// if(queueId.count()<=0)
	// {
		// //QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		// QMessageBox msgBox;
		// msgBox.setText(tr("无可用ID资源"));
		// int ret = msgBox.exec();
		// return -1;
	// }

	// while(true)
	// {
		// int resId=queueId.dequeue();
	    // if(!idConflict(resId,idType))
			// return resId;
	// }
	
	// return 0;
}

bool CIdResource::idConflict(int id,QString& idType)
{
	QSqlQuery q;
	QString querySql;
	//QSqlRecord rec;
	querySql=QString("insert into %1(id) values(%2)").arg(idType).arg(id);
	return !q.exec(querySql);
}

//int CIdResource::getUsrId(QString& usrName)
int CIdResource::getUsrId()
{
	// int id=existUsrId(usrName);
	
	// if(id>=0)
	// {
		// return id;
	// }
	
	// return calcUsrId();
	
	return queueUsrId.dequeue();
}

//int CIdResource::getUsrGId(QString& usrName)
int CIdResource::getUsrGId()
{
	// int id=existUsrGId(usrName);
	
	// if(id>=0)
	// {
		// return id;
	// }
	
	//return calcUsrGId();
	return queueUsrGId.dequeue();
}

int CIdResource::existUsrId(std::string& usrName1)
{
	QString usrName(tr(usrName1.c_str()));
	QSqlQuery q;
	QString querySql=QString("select username,userid from ksuser where username='%1'").arg(usrName);
	q.exec(querySql);
	
	while (q.next())
	{
		return q.value(1).toInt();
	}
	
	return -1;
}

int CIdResource::calcUsrId()
{
	QSqlQuery q;
	QString querySql=QString("select max(userid) from ksuser");
	q.exec(querySql);
	int retId=0;
	
	while (q.next())
	{
		retId=q.value(0).toInt()+1;
	}
	
	if(retId==0)
		retId=1;
	
	return retId;
}

int CIdResource::existUsrGId(std::string& usrName1)
{
	QString usrName(tr(usrName1.c_str()));
	QSqlQuery q;
	QString querySql=QString("select usergroup,usergroupid from ksusergroup where usergroup='%1'").arg(usrName);
	q.exec(querySql);
	
	while (q.next())
	{
		return q.value(1).toInt();
	}
	
	return -1;
}

int CIdResource::calcUsrGId()
{
	QSqlQuery q;
	QString querySql=QString("select max(usergroupid) from ksusergroup");
	q.exec(querySql);
	int retId=0;
	
	while (q.next())
	{
		retId=q.value(0).toInt()+1;
	}
	
	if(retId==0)
		retId=1;
	
	return retId;
}

int CIdResource::initUsrIdPool()
{
	QSqlTableModel model;
	model.setTable("ksuser");
	//QString filter1="";
	int minNum=1,maxNum=10000;

	//filter1=QString("ID>=%1 and ID<=%2").arg(g_minACLID).arg(g_maxACLID);
	//minNum=g_minACLID;
	//maxNum=g_maxACLID;
	
	//model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
	
	while(model.canFetchMore())
	{
		model.fetchMore();
	}
	
	QSet<int>idSet;
	
	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("userid").toInt();
	}
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queueUsrId.enqueue(j);
		}
	}
	
	idSet.clear();
	
	if(queueUsrId.count()<=0)
	{
		//QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		QMessageBox msgBox;
		msgBox.setText(tr("无可用ID资源"));
		int ret = msgBox.exec();
		return -1;
	}

	return 0;
}
int CIdResource::initUsrGIdPool()
{
	QSqlTableModel model;
	model.setTable("ksusergroup");
	//QString filter1="";
	int minNum=1,maxNum=10000;

	//filter1=QString("ID>=%1 and ID<=%2").arg(g_minACLID).arg(g_maxACLID);
	//minNum=g_minACLID;
	//maxNum=g_maxACLID;
	
	//model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
	
	while(model.canFetchMore())
	{
		model.fetchMore();
	}
		
	QSet<int>idSet;
	
	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("usergroupid").toInt();
	}
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queueUsrGId.enqueue(j);
		}
	}
	
	idSet.clear();
	
	if(queueUsrGId.count()<=0)
	{
		//QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		QMessageBox msgBox;
		msgBox.setText(tr("无可用ID资源"));
		int ret = msgBox.exec();
		return -1;
	}

	return 0;
}
int CIdResource::initRuleIdPool()
{
	QSqlTableModel model;
	model.setTable("rule");
	//QString filter1="";
	int minNum=1,maxNum=100000;

	//filter1=QString("ID>=%1 and ID<=%2").arg(g_minACLID).arg(g_maxACLID);
	//minNum=g_minACLID;
	//maxNum=g_maxACLID;
	
	//model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
	
	while(model.canFetchMore())
	{
		model.fetchMore();
	}
		
	QSet<int>idSet;
	
	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("ruleid").toInt();
	}
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queueRuleId.enqueue(j);
		}
	}
	
	idSet.clear();
	
	if(queueRuleId.count()<=0)
	{
		//QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		QMessageBox msgBox;
		msgBox.setText(tr("无可用ID资源"));
		int ret = msgBox.exec();
		return -1;
	}

	return 0;
}
int CIdResource::initRulesIdPool()
{
	QSqlTableModel model;
	model.setTable("rules");
	//QString filter1="";
	int minNum=1,maxNum=100000;

	//filter1=QString("ID>=%1 and ID<=%2").arg(g_minACLID).arg(g_maxACLID);
	//minNum=g_minACLID;
	//maxNum=g_maxACLID;
	
	//model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
	
	while(model.canFetchMore())
	{
		model.fetchMore();
	}
		
	QSet<int>idSet;
	
	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("rulesid").toInt();
	}
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queueRulesId.enqueue(j);
		}
	}
	
	idSet.clear();
	
	if(queueRulesId.count()<=0)
	{
		//QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		QMessageBox msgBox;
		msgBox.setText(tr("无可用ID资源"));
		int ret = msgBox.exec();
		return -1;
	}

	return 0;
}
int CIdResource::initACLIdPool(){
	QSqlTableModel model;
	model.setTable("ACLID");
	QString filter1="";
	int minNum,maxNum;

	filter1=QString("ID>=%1 and ID<=%2").arg(g_minACLID).arg(g_maxACLID);
	minNum=g_minACLID;
	maxNum=g_maxACLID;
	
	model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();

	while(model.canFetchMore())
	{
		model.fetchMore();
	}
		
	QSet<int>idSet;
	
	//qDebug()<<model.rowCount();


	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("id").toInt();
	}
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queueACLId.enqueue(j);
		}
	}

	//qDebug()<<idSet.capacity();
	//qDebug()<<idSet.count();
	
	idSet.clear();
	
	if(queueACLId.count()<=0)
	{
		//QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		QMessageBox msgBox;
		msgBox.setText(tr("无可用ID资源"));
		int ret = msgBox.exec();
		return -1;
	}

	return 0;
}
int CIdResource::initXACLIdPool(){
	QSqlTableModel model;
	model.setTable("XACLID");
	QString filter1="";
	int minNum,maxNum;

	filter1=QString("ID>=%1 and ID<=%2").arg(g_minXACLID).arg(g_maxXACLID);
	minNum=g_minXACLID;
	maxNum=g_maxXACLID;
	
	model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
	
	while(model.canFetchMore())
	{
		model.fetchMore();
	}
		
	QSet<int>idSet;
	
	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("id").toInt();
	}
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queueXACLId.enqueue(j);
		}
	}
	
	idSet.clear();
	
	if(queueXACLId.count()<=0)
	{
		//QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		QMessageBox msgBox;
		msgBox.setText(tr("无可用ID资源"));
		int ret = msgBox.exec();
		return -1;
	}

	return 0;
}

int CIdResource::initPLIdPool(){
	QSqlTableModel model;
	model.setTable("PLID");
	QString filter1="";
	int minNum,maxNum;

	filter1=QString("ID>=%1 and ID<=%2").arg(g_minPLID).arg(g_maxPLID);
	minNum=g_minPLID;
	maxNum=g_maxPLID;
	
	model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
	
	while(model.canFetchMore())
	{
		model.fetchMore();
	}
		
	QSet<int>idSet;
	
	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("id").toInt();
	}
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queuePLId.enqueue(j);
		}
	}
	
	idSet.clear();
	
	if(queuePLId.count()<=0)
	{
		//QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
		QMessageBox msgBox;
		msgBox.setText(tr("无可用ID资源"));
		int ret = msgBox.exec();
		return -1;
	}

	return 0;
}
