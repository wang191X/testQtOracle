#pragma once
#include <vector>

class CDeletePLTask
{
public:
	CDeletePLTask(void);
	~CDeletePLTask(void);

	void updateRules(int ruleId,int cmdType);
	void sendCMD(std::vector<int>& plidVec);
};
