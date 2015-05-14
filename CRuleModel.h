#ifndef CRULEMODEL_H
#define CRULEMODEL_H

#include <QSqlTableModel>

class CRuleModel : public QSqlTableModel
{
	Q_OBJECT

public:
	CRuleModel(QObject *parent);
	~CRuleModel();

private:
	mutable int column1;
	mutable int column2;

private:
	void initData();
	QVariant headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
	QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const;
	
};

#endif // CRULEMODEL_H
