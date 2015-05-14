#ifndef CNEWPLDLG1_H
#define CNEWPLDLG1_H

#include <QDialog>
//#include "ui_NewPLDlg.h"
#include "ui_CNewPLWt.h"
#include "DataStruct.h"

class CNewPLDlg1 :  public QWidget,public Ui::CNewPLWt
{
	Q_OBJECT

public:
	CNewPLDlg1(QWidget *parent=0);
	~CNewPLDlg1();

public:
	SPL spl;
signals:
	void okMsg();
	void cancelMsg();

private:

	private slots:
		void onOk();
		void onCancel();
};

#endif // CNEWPLDLG1_H
