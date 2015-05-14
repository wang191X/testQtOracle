#pragma once

class CDeleteTask
{
public:
	CDeleteTask(void);
	virtual ~CDeleteTask(void);

public:
	virtual void updateRules(int ruleId,int cmdType)=0;
	virtual void sendCMD(int groupId)=0;
};
