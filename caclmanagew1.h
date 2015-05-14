#ifndef CACLMANAGEW1_H
#define CACLMANAGEW1_H

#include <QDialog>
#include "ui_AclManageW.h"
#include <QtSql/QSqlTableModel>

class CAclManageW1 :public QDialog,public Ui::AclManageW
{
	Q_OBJECT

public:
	CAclManageW1(QWidget *parent=0);
	~CAclManageW1();

private:
	QSqlTableModel* model;
	QSqlTableModel* modeltmp;

	private slots:
		void addAcl();
		void deleteAcl();
		void queryAcl();
		void setGroupId();
		void moveRules();
		void copyRules();
		void setGroupTmp();
		void queryAclTmp();
		
};

#endif // CACLMANAGEW1_H
