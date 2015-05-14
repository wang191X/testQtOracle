#ifndef CCHECKMODEL_H
#define CCHECKMODEL_H

#include <QSqlTableModel>

class CCheckModel : public QSqlTableModel
{
	Q_OBJECT

public:
	CCheckModel(QObject *parent);
	~CCheckModel();

	Qt::ItemFlags flags(const QModelIndex& index) const;
	QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const;

private:
	
};

#endif // CCHECKMODEL_H
