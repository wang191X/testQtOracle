#include "CColorModel.h"
 #include <QColor>

CColorModel::CColorModel(QObject *parent)
	: QSqlTableModel(parent)
{

}

CColorModel::~CColorModel()
{
	rowSet.clear();
	yellowSet.clear();
	graySet.clear();
	greenSet.clear();
}

QVariant CColorModel::data(const QModelIndex& index,int role) const
{
	QVariant value=QSqlTableModel::data(index,role);

	if(role==Qt::BackgroundRole&&rowSet.contains(index.row()))
	{
		return QColor(255, 0, 0, 127);
	}
	else if (role==Qt::BackgroundRole&&yellowSet.contains(index.row()))
	{
		return QColor(255, 255, 0, 127);
	}
	else if (role==Qt::BackgroundRole&&graySet.contains(index.row()))
	{
		return QColor(Qt::gray);
	}
	else if (role==Qt::BackgroundRole&&greenSet.contains(index.row()))
	{
		return QColor(0, 255, 0, 127);
	}
	else
		return value;
}