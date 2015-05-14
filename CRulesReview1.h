#ifndef CRULESREVIEW1_H
#define CRULESREVIEW1_H

//#include <QDialog>
#include "ui_RulesReview.h"
#include <QtSql/QSqlTableModel>

class CRulesReview1 : public QWidget,public Ui::RulesReviewW
{
	Q_OBJECT

public:
	CRulesReview1(QWidget *parent=0);
	~CRulesReview1();

private:
	QSqlTableModel* model;

	private slots:
		void query();
		void agree();
		void reject();

		void queryXacl();
		void agreeXacl();
		void rejectXacl();

		void queryPL();
		void agreePL();
		void rejectPL();
};

#endif // CRULESREVIEW1_H
