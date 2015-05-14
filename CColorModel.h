#ifndef CCOLORMODEL_H
#define CCOLORMODEL_H

#include <QSqlTableModel>
#include <QSet>


class CColorModel : public QSqlTableModel
{
	Q_OBJECT

public:
	CColorModel(QObject *parent);
	~CColorModel();

		QSet<int> rowSet;
		QSet<int>yellowSet;
		QSet<int>graySet;
		QSet<int>greenSet;
	
private:
	QVariant data(const QModelIndex& index,int role=Qt::DisplayRole) const;

};

#endif // CCOLORMODEL_H
