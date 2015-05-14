#ifndef CINPUTINFODLG_H
#define CINPUTINFODLG_H

#include <QWidget>
#include "ui_CInputInfoWt.h"

class CInputInfoDlg : public QWidget,public Ui::CInputInfoWt
{
	Q_OBJECT

public:
	CInputInfoDlg(QWidget *parent=0);
	~CInputInfoDlg();

private:

signals:
	void okMsg();
	void cancelMsg();

private slots:
		void onOk();
		void onCancel();
	
};

#endif // CINPUTINFODLG_H
