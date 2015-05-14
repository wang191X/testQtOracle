#ifndef CQUERYPLDLG1_H
#define CQUERYPLDLG1_H

#include <QDialog>
#include "ui_QueryPLDlg.h"

class CQueryPLDlg1 : public QDialog,public Ui::QueryPLDlg
{
	Q_OBJECT

public:
	CQueryPLDlg1(QWidget *parent=0);
	~CQueryPLDlg1();

private:
	
};

#endif // CQUERYPLDLG1_H
