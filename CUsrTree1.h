#ifndef CUSRTREE1_H
#define CUSRTREE1_H

#include <QWidget>
#include <ui_CUsrTree.h>

class CUsrTree1 : public QWidget,public Ui::CUsrTree
{
	Q_OBJECT

public:
	CUsrTree1(QWidget *parent=0);
	~CUsrTree1();
protected:
     void contextMenuEvent(QContextMenuEvent *event);
	 
private:
	QAction* refreshAct;
	QAction* deleteAct;
	
	void queryUsrs(QHash<QString, int>& hash);
	void queryUsrRuleGroup();
	void loadUsrTree();
	void initUsrGroup();
	void initGeneralUsr();
	void initData();
	void loadGroupInfo(int usrId,QTreeWidgetItem* parentItem);
	
	void deleteRuleGroup(int gId);
	void deleteRules(int gId);

private slots: 
	void queryUsrRules(QTreeWidgetItem *, int);
	void refreshList();
	void deleteNode();

};

#endif // CUSRTREE1_H
