#ifndef CNEWTASK1_H
#define CNEWTASK1_H

#include <QDialog>
//#include "ui_AddTask.h"
#include "ui_CTaskWt.h"


class CNewTask1 : public QWidget,public Ui::CTaskWt
{
	Q_OBJECT

public:
	CNewTask1(QWidget *parent=0);
	~CNewTask1();

signals:
	void okMsg();
	void cancelMsg();

protected:
	void newACLTask();
	virtual void newTaskRecord(int groupId);
	int mapRuleGroup(int groupId);
	void updateRules(int ruleId,int cmdType);

	public slots:
		virtual void start();
};

#endif // CNEWTASK1_H
