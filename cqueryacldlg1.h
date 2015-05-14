#ifndef CQUERYACLDLG1_H
#define CQUERYACLDLG1_H

#include <QDialog>
#include "ui_QueryAclDlg.h"

class CQueryAclDlg1 : public QDialog,public Ui::QueryAclDlg
{
	Q_OBJECT

public:
	CQueryAclDlg1(QWidget *parent=0);
	~CQueryAclDlg1();

private:
	
};

#endif // CQUERYACLDLG1_H
