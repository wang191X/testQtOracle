#include "testqtoracle.h"
#include <QtGui/QApplication>

#include <QtSql/QSqlDatabase>

#include <QtGui>
#include "CLoginDlg1.h"
#include <QCleanlooksStyle>
#include <QPlastiqueStyle>
#include <QWindowsXPStyle>
#include "CTitleDlg1.h"
#include "CLoginDlg1.h"
#include <QObject>
#include "GloabeParams.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(new QPlastiqueStyle);
	QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
   
	//QWidget*  loginWt=new CLoginDlg1();
	//CTitleDlg1 loginDlg(0,loginWt);
	//loginDlg.label_2->setText(G2U(""));
	////loginDlg.toolButtonmax->setHidden(true);
	////loginDlg.setFixedSize(loginDlg.width(),loginDlg.height());
	//QObject::connect(loginWt,SIGNAL(okMsg()),&loginDlg,SLOT(accept()));
	//QObject::connect(loginWt,SIGNAL(cancelMsg()),&loginDlg,SLOT(reject()));
	//int ret=loginDlg.exec();

	//if (!ret) 
	//{
	//	return -1;
	//}
	
	testQtOracle w;
	
    w.setWindowFlags(Qt::FramelessWindowHint);
	//w.showMaximized();
	w.onMaxWindow();
	w.show();

	return a.exec();
}
