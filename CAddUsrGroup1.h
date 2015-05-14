#ifndef CADDUSRGROUP1_H
#define CADDUSRGROUP1_H

#include <QWidget>
#include "Ui_CAddUsrGroup.h"

class CAddUsrGroup1 : public QWidget,public Ui::CAddUsrGroup
{
	Q_OBJECT

public:
	CAddUsrGroup1(QWidget *parent=0);
	~CAddUsrGroup1();

public:
	bool isUsr;

private:
	void initUIData();
	int assignUsrId();
	int assignUsrGroupId();
	void insertUsrRecord();
	void insertUsrGRecord();

signals:
	void okMsg();
	void cancelMsg();

	private slots:
		void onOk();
		void onCancel();
	
};

#endif // CADDUSRGROUP1_H
