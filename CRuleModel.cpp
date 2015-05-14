#include "CRuleModel.h"

CRuleModel::CRuleModel(QObject *parent)
	: QSqlTableModel(parent)
{
	initData();
}

CRuleModel::~CRuleModel()
{

}

void CRuleModel::initData()
{
	column1=0;
	column2=0;
}

QVariant CRuleModel::headerData ( int section, Qt::Orientation orientation, int role) const
{
	QVariant value=QSqlTableModel::headerData(section,orientation,role);

	if (value.toString()=="KEYVALUE")
	{
		column1=section;
	}
	else if (value.toString()=="KEYMASK")
	{
		column2=section;
	}

	return value;
}

QVariant CRuleModel::data(const QModelIndex& index,int role) const
{
	QVariant value=QSqlTableModel::data(index,role);

	if(role==Qt::DisplayRole&&(index.column()==column1||index.column()==column2))
	{
		QByteArray ss=value.toByteArray();
		QString str="0x";
		QByteArray s1=ss.toHex();
		char *data = s1.data();
		
		while (*data) {
			str.append(*data);
			//qDebug()<<*data;
			++data;
			str.append(*data);
			//qDebug()<<*data;
			++data;
			str=str.toUpper()+" ";
		}

		return str;
	}
	else
		return value;
}