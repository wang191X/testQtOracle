#include "CTaskDelegate.h"

CTaskDelegate::CTaskDelegate(int column,QObject *parent)
	: QItemDelegate(parent)
{
	this->column=column;
}

CTaskDelegate::~CTaskDelegate()
{

}

void CTaskDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,
						  const QModelIndex& index) const
{
	if(index.column()==column)
	{
		QStyleOptionViewItem myOption=option;
		myOption.displayAlignment=Qt::AlignRight|Qt::AlignVCenter;
		QString text=index.model()->data(index,Qt::DisplayRole).toString();

		drawDisplay(painter,myOption,myOption.rect,text);
		drawFocus(painter,myOption,myOption.rect);
	}
	else
	{
		QItemDelegate::paint(painter,option,index);
	}
}