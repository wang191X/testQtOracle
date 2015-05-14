#pragma once
#include <QString>

class IDResource
{
public:
	IDResource(void);
	~IDResource(void);
	
public:
	static int getIdRes(); 
	static int getGroupIdRes(QString& groupDesc);
	static int getMultiIdRes(QString& idType);
	static int getSingleIdRes(QString& idType);
	static int getUsrId(QString& usrName);
	static int getUsrGId(QString& usrName);
	static int existUsrId(QString& usrName);
	static int calcUsrId();
	static int existUsrGId(QString& usrName);
	static int calcUsrGId();
};
