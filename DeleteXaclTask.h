#pragma once
#include "deletetask.h"

class CDeleteXaclTask :
	public CDeleteTask
{
public:
	CDeleteXaclTask(void);
	~CDeleteXaclTask(void);

public:
	void updateRules(int ruleId,int cmdType);
	void sendCMD(int groupId);
};
