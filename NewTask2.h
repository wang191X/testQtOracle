#pragma once
#include "cnewtask1.h"

class CNewTask2 :
	public CNewTask1
{
public:
	CNewTask2(void);
	virtual ~CNewTask2(void);

public slots:
		void start();
	
private:
	void newXaclTask();
	void newTaskRecord(int groupId);
	void newTaskRecord1(int aclGroup,int xaclGroup);
	void updateXACLRules(int ruleId,int cmdType);
	void updatePLRules(int ruleId,int cmdType);
};
