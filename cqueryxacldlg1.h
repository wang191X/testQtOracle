#ifndef CQUERYXACLDLG1_H
#define CQUERYXACLDLG1_H

#include <QDialog>
#include "ui_QueryXaclDlg.h"

class CQueryXaclDlg1 : public QDialog,public Ui::QueryXaclDlg
{
	Q_OBJECT

public:
	CQueryXaclDlg1(QWidget *parent=0);
	~CQueryXaclDlg1();

private:
	
};

#endif // CQUERYXACLDLG1_H
