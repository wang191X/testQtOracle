#ifndef CLOGINDLG1_H
#define CLOGINDLG1_H

//#include <QDialog>
//#include "ui_LoginDlg.h"
#include "ui_CLoginWt.h"

class CLoginDlg1 : public QWidget,public Ui::CLoginWt
{
	Q_OBJECT

public:
	CLoginDlg1(QWidget *parent=0);
	~CLoginDlg1();

private:
bool queryUsrTable();
bool queryUsrGroupTable();

signals:
	void okMsg();
	void cancelMsg();

	private slots:
		void onOk();
		void onCancel();

};

#endif // CLOGINDLG1_H
