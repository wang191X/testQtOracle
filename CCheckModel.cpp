#include "CCheckModel.h"

CCheckModel::CCheckModel(QObject *parent)
: QSqlTableModel(parent)
{

}

CCheckModel::~CCheckModel()
{

}

Qt::ItemFlags CCheckModel::flags(const QModelIndex& index) const
{
	Qt::ItemFlags flags=QSqlTableModel::flags(index);

	if(index.column()==0)
		flags|=Qt::ItemIsUserCheckable;
	else
		flags|=Qt::ItemIsEditable;

	return flags;
}

QVariant CCheckModel::data(const QModelIndex& index,int role) const
{
	QVariant value=QSqlTableModel::data(index,role);

	if(role==Qt::CheckStateRole&&index.column()==0)
		return(QSqlTableModel::data(index).toInt()!=0)?Qt::Checked:Qt::Unchecked;
	else
		return value;
}
