#ifndef CUSRDLG1_H
#define CUSRDLG1_H

#include <QDialog>
//#include "ui_UsrDlg.h"
#include "ui_CUsrWt.h"

class CUsrDlg1 : public QWidget,public Ui::CNewUsrWt
{
	Q_OBJECT

public:
	CUsrDlg1(QWidget *parent=0);
	~CUsrDlg1();

signals:
	void okMsg();
	void cancelMsg();

private:
	
	private slots:
		void onOk();
		void onCancel();
};

#endif // CUSRDLG1_H
