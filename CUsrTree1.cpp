#include "CUsrTree1.h"
#include <QtSql/QSqlError>
#include "GloabeParams.h"
#include <QTreeWidgetItem>
#include <QSqlQuery>
#include <QList>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>

CUsrTree1::CUsrTree1(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	
	//connect(usrTreeWt, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(queryUsrRules(QTreeWidgetItem*,int)));
	refreshAct = new QAction(tr("刷新"), this);
	deleteAct = new QAction(tr("删除"), this);
    connect(refreshAct, SIGNAL(triggered()), this, SLOT(refreshList()));
	connect(deleteAct, SIGNAL(triggered()), this, SLOT(deleteNode()));
	
	initData();
}

CUsrTree1::~CUsrTree1()
{

}

void CUsrTree1::queryUsrs(QHash<QString, int>& hash)
{
	QSqlQuery q;
	QString querySql=QString("select userid,username from ksuser where usergroupid=%1").arg(g_clientId);
	q.exec(querySql);
		
	while (q.next())
	{
		hash.insert(q.value(1).toString(), q.value(0).toInt());
	}
	
	return;
}

void CUsrTree1::queryUsrRuleGroup()
{
}

void CUsrTree1::loadUsrTree()
{
}

void CUsrTree1::initUsrGroup()
{
	QHash<QString, int> hash;
	queryUsrs(hash);
	QHashIterator<QString, int> i(hash);
	QTreeWidgetItem *rootItem = new QTreeWidgetItem((QTreeWidget*)0);
	QString strId;
    strId.setNum(g_clientId);
	rootItem->setText(0, strId);
	rootItem->setText(1, g_clientUsr);
	
	while (i.hasNext()) {
		i.next();
		QTreeWidgetItem *parentItem = new QTreeWidgetItem(rootItem);
		strId.setNum(i.value());
		parentItem->setText(0, strId);
		parentItem->setText(1, i.key());
		loadGroupInfo(i.value(),parentItem);
		//cout << i.key() << ": " << i.value() << endl;
	}
	usrTreeWt->addTopLevelItem(rootItem);
	//queryGeneralUsr(hash);
	//queryUsrRuleGroup();
	//loadUsrTree();
}

void CUsrTree1::loadGroupInfo(int usrId,QTreeWidgetItem* parentItem)
{
	QSqlQuery q;
	QString querySql=QString("select distinct rulesid,rulesname from rules where userid=%1").arg(usrId);
	q.exec(querySql);
	
	while (q.next())
	{
		QString groupId=q.value(0).toString();
		QString groupDesc=q.value(1).toString();
		QTreeWidgetItem *childItem = new QTreeWidgetItem(parentItem);
		childItem->setText(0, groupId);
		childItem->setText(1, groupDesc);
		//items.append(childItem);
	}
}

// void CUsrTree1::queryGeneralUsr(QHash<QString, int>* hash)
// {
	// QTreeWidgetItem *parentItem = new QTreeWidgetItem((QTreeWidget*)0);
	// parentItem->setText(0, g_clientUsr);
	// //QList<QTreeWidgetItem *> items;
	// loadGroupInfo(g_clientId,parentItem);
	// usrTreeWt->addTopLevelItem(parentItem);
// }

void CUsrTree1::contextMenuEvent(QContextMenuEvent *event)
{
	QMenu menu(this);
	menu.setStyleSheet(
		"QMenu {"
		"background-color: rgb(205, 230, 255); "
		"border: 1px solid black;"
		"margin: 2px;"
		"}"
	);

    menu.addAction(refreshAct);
	menu.addAction(deleteAct);
    menu.exec(event->globalPos());
}

void CUsrTree1::refreshList()
{
	initData();
}

void CUsrTree1::deleteNode()
{
	 QMessageBox msgBox;
	 msgBox.setInformativeText(tr("确定删除吗？"));
     msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
     msgBox.setDefaultButton(QMessageBox::Cancel);
     int ret = msgBox.exec();
	 
	 if(ret)
	 {
		 QTreeWidgetItem* item = usrTreeWt->currentItem();
		 int gId=item->text(0).toInt();
		 deleteRuleGroup(gId);
		 deleteRules(gId);
		 initData();
	 }
}

void CUsrTree1::deleteRuleGroup(int gId)
{
	QSqlQuery q;
	QString querySql=QString("delete from rules where rulesid=%2").arg(gId);
	q.exec(querySql);
}

void CUsrTree1::deleteRules(int gId)
{
	QSqlQuery q;
	QString querySql=QString("delete from rule where rulesid=%2").arg(gId);
	q.exec(querySql);
}

void CUsrTree1::initGeneralUsr()
{
	QTreeWidgetItem *parentItem = new QTreeWidgetItem((QTreeWidget*)0);
	QString strId;
	strId.setNum(g_clientId);
	parentItem->setText(0, strId);
	parentItem->setText(1, g_clientUsr);
	//QList<QTreeWidgetItem *> items;
	loadGroupInfo(g_clientId,parentItem);
	usrTreeWt->addTopLevelItem(parentItem);
	//QHash<QString, int> hash;
	//hash.insert(g_clientUsr, g_clientId);
	//queryGeneralUsr(hash);

	//queryUsrRuleGroup();
	//loadUsrTree();
}

void CUsrTree1::initData()
{
	usrTreeWt->clear();

	if(g_privilege==3)
	{
		//若为普通用户
		initGeneralUsr();
	}
	else if(g_privilege==2)
	{
		//若为用户组管理员
		initUsrGroup();
	}
}

void CUsrTree1::queryUsrRules(QTreeWidgetItem * item, int column)
{
	QTreeWidgetItem *pp=item->parent();
	QString str=pp->text(0);
}