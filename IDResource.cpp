#include "IDResource.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlError>
#include <QQueue>
#include <QObject>

IDResource::IDResource(void)
{
}

IDResource::~IDResource(void)
{
}

int IDResource::getIdRes()
{
	QSqlQuery q;
	QString querySql=QString("select max(ruleid) from rule");
	q.exec(querySql);
	
	while (q.next())
	{
		return q.value(0).toInt()+1;
	}
	
	return 1;
}

int IDResource::getGroupIdRes(QString& groupDesc)
{
	//若组描述存在，分配同样组id，若组描述不存在，分配新组id
	QSqlQuery q;
	QString querySql=QString("select rulesid from rules where rulesname='%1'").arg(groupDesc);
	q.exec(querySql);
	
	while (q.next())
	{
		return q.value(0).toInt();
	}
	
	querySql=QString("select max(rulesid) from rules");
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

int IDResource::getMultiIdRes(QString& idType)
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

int IDResource::getSingleIdRes(QString& idType)
{
	QSqlTableModel model;
	model.setTable(idType);
	QString filter1="";
	int minNum,maxNum;

	if (idType==tr("ACLID"))
	{
		filter1=QString("ID>=%1 and ID<=%2").arg(g_minACLID).arg(g_maxACLID);
		minNum=g_minACLID;
		maxNum=g_maxACLID;
	}
	else if (idType==tr("XACLID"))
	{
		filter1=QString("ID>=%1 and ID<=%2").arg(g_minXACLID).arg(g_maxXACLID);
		minNum=g_minXACLID;
		maxNum=g_maxXACLID;
	}
	else if (idType==tr("PLID"))
	{
		filter1=QString("ID>=%1 and ID<=%2").arg(g_minPLID).arg(g_maxPLID);
		minNum=g_minPLID;
		maxNum=g_maxPLID;
	}
	
	model.setFilter(filter1);
	model.setSort( 0, Qt::AscendingOrder);
	model.select();
		
	QSet<int>idSet;
	
	for(int j=0;j<model.rowCount();++j)
	{
		QSqlRecord record=model.record(j);
		idSet<<record.value("id").toInt();
	}
	
	QQueue<int>queueId;
	
	for(int j=minNum;j!=maxNum+1;++j)
	{
		if(!idSet.contains(j))
		{
			queueId.enqueue(j);
		}
	}
	
	idSet.clear();
	
	if(queueId.count()<=0)
	{
		QMessageBox::information(this, tr("information"), tr("无可用ID资源"));
	}

	while(true)
	{
		int resId=queueId.dequeue();
	    if(!idConflict(resId,idType))
			return resId;
	}
	
	return 0;
}

int IDResource::getUsrId(QString& usrName)
{
	int id=existUsrId(usrName);
	
	if(id>=0)
	{
		return id;
	}
	
	return calcUsrId();
}

int IDResource::getUsrGId(QString& usrName)
{
	int id=existUsrGId(usrName);
	
	if(id>=0)
	{
		return id;
	}
	
	return calcUsrGId();
}

int IDResource::existUsrId(QString& usrName)
{
	QSqlQuery q;
	QString querySql=QString("select username,userid from ksuser where username='%1'").arg(usrName);
	q.exec(querySql);
	
	while (q.next())
	{
		return q.value(1).toInt();
	}
	
	return -1;
}

int IDResource::calcUsrId()
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

int IDResource::existUsrGId(QString& usrName)
{
	QSqlQuery q;
	QString querySql=QString("select usergroup,usergroupid from ksusergroup where usergroup='%1'").arg(usrName);
	q.exec(querySql);
	
	while (q.next())
	{
		return q.value(1).toInt();
	}
	
	return -1;
}

int IDResource::calcUsrGId()
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
