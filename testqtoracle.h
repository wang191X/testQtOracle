#ifndef TESTQTORACLE_H
#define TESTQTORACLE_H

#include <QtGui/QMainWindow>
#include "ui_testqtoracle.h"
#include <QStackedWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QBitmap>
#include <QPainter>
#include "CRulesReview1.h"
#include "CUsers.h"
 #include "CRuleManage1.h"
#include "CUsrTree1.h"
#include <QSplitter>
 #include "CUsrGroupWt1.h"

class testQtOracle : public QMainWindow,public Ui::testQtOracleClass
{
	Q_OBJECT

public:
	testQtOracle(QWidget *parent = 0, Qt::WFlags flags = 0);
	~testQtOracle();

private:
	QStackedWidget* stackedWidget;
	void loadFunction(int privilege);
	void contDB();
	void setwinsLayout();

	CUsers* usersDlg;
	CRulesReview1* rulesReview;
	CUsrGroupWt1* usrGroup;
	QSplitter* mainSplitter;
	CRuleManage1* ruleManage;
	CUsrTree1* usrTree;

	private slots:
		/*void queryAcl();
		void queryXacl();
		void queryPL();
		void newAcl();
		void newXacl();
		void newPL();*/
		void users();
		void aclManage();
		void ruleManageFun();
		void ruleReview();
		void xaclManage();
		void plManage();
		void usrGroupFun();
		

public slots:
void onMaxWindow();

protected:
	//void paintEvent(QPaintEvent * event)
	//{
	//	//生成一张位图
	//	QBitmap objBitmap(size()); 
	//	//QPainter用于在位图上绘画
	//	QPainter painter(&objBitmap); 
	//	//填充位图矩形框(用白色填充)
	//	painter.fillRect(rect(),Qt::white);
	//	painter.setBrush(QColor(0,0,0)); 
	//	//在位图上画圆角矩形(用黑色填充)
	//	painter.drawRoundedRect(this->rect(),10,10);
	//	//使用setmask过滤即可
	//	setMask(objBitmap);
	//}

	//void mousePressEvent(QMouseEvent *event)
	//{ 
	//	if(event->button() == Qt::LeftButton)  
	//	{  
	//		dragPosition = event->globalPos() - frameGeometry().topLeft();  

	//		//QRect rect = ui.titleFrame->frameRect();  
	//		QRect rect = horizontalLayout->contentsRect(); 
	//		if(rect.contains(event->pos()))  
	//		{  
	//			m_bMoveable = true;  
	//		}  
	//		event->accept();  
	//	}  
	//}  

	//void mouseMoveEvent(QMouseEvent *event)   
	//{        
	//	if(event->buttons() & Qt::LeftButton && !isMaximized () && m_bMoveable)  
	//	{  
	//		move(event->globalPos() - dragPosition);  
	//		event->accept();  
	//	}  

	//}  

	//void mouseReleaseEvent(QMouseEvent *event)   
	//{   
	//	if(m_bMoveable)  
	//	{  
	//		m_bMoveable = false;  
	//	}  
	//}

private:    

	QPoint dragPosition;
	bool m_bMoveable;
};


#endif // TESTQTORACLE_H
