#pragma once
#include "deletetask.h"

class CDeleteAclTask :
	public CDeleteTask
{
public:
	CDeleteAclTask(void);
	~CDeleteAclTask(void);

public:
	void updateRules(int ruleId,int cmdType);
	void sendCMD(int groupId);
};
