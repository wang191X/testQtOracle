#ifndef CIDRESOURCE_H
#define CIDRESOURCE_H

#include <QObject>
#include <QQueue>

class CIdResource : public QObject
{
	Q_OBJECT

public:
	CIdResource(QObject *parent=0);
	~CIdResource();

public:
	QQueue<int>queueACLId;
	QQueue<int>queueXACLId;
	QQueue<int>queuePLId;
	QQueue<int>queueUsrId;
	QQueue<int>queueUsrGId;
	QQueue<int>queueRuleId;
	QQueue<int>queueRulesId;

	int getIdRes(); 
	//int getGroupIdRes(QString& groupDesc);
	int getGroupIdRes();
	int getMultiIdRes(QString& idType);
	int getSingleIdRes(QString& idType);
	//int getUsrId(QString& usrName);
	int getUsrId();
	//int getUsrGId(QString& usrName);
	int getUsrGId();
	int existUsrId(std::string& usrName1);
	int calcUsrId();
	int existUsrGId(std::string& usrName1);
	int calcUsrGId();
	bool idConflict(int id,QString& idType);
	
	int initUsrIdPool();
	int initUsrGIdPool();
	int initRuleIdPool();
	int initRulesIdPool();
	int initACLIdPool();
	int initXACLIdPool();
	int initPLIdPool();
};

#endif // CIDRESOURCE_H
