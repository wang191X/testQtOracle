#ifndef CNEWACLDLG1_H
#define CNEWACLDLG1_H

#include <QDialog>
//#include "ui_NewAclDlg.h"
#include "ui_CNewACLWt.h"
#include "DataStruct.h"

class CNewAclDlg1 : public QWidget,public Ui::CNewACLWt
{
	Q_OBJECT

public:
	CNewAclDlg1(QWidget *parent=0);
	~CNewAclDlg1();

public:
	SACL sacl;

signals:
	void okMsg();
	void cancelMsg();

private:
	void initData();

	private slots:
		void onOk();
		void onCancel();
};

#endif // CNEWACLDLG1_H
