#include "CCheckDelegate.h"
#include <QCheckBox>


CCheckDelegate::CCheckDelegate(int column,QObject *parent)
: QItemDelegate(parent)
{
	this->column=column;
}

CCheckDelegate::~CCheckDelegate()
{

}

bool CCheckDelegate::editorEvent( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index )
{
	if (index.column()==column)
	{
		if(event->type()==QEvent::MouseButtonPress)
		{
			QVariant value = index.data(Qt::CheckStateRole);
			Qt::CheckState state = (static_cast<Qt::CheckState>(value.toInt()) == Qt::Checked
				? Qt::Unchecked : Qt::Checked);
			bool flag=model->setData(index,state);//,Qt::EditRole);
			model->submit();
			// bool flag=model->setData(index, state, Qt::CheckStateRole);
			return flag;
			//bool isSelected=var.toBool();
			//return model->setData(index,!isSelected,Qt::CheckStateRole);
		}
		
		return true;
	}
	else
	{
		return QItemDelegate::editorEvent(event, model, option, index );
	}
}

//void CCheckDelegate::paint(QPainter* painter,const QStyleOptionViewItem& option,
//						   const QModelIndex& index) const
//{
//	if(index.column()==column)
//	{
//		QStyleOptionViewItem myOption=option;
//		myOption.displayAlignment=Qt::AlignRight|Qt::AlignVCenter;
//		//QString text=index.model()->data(index,Qt::DisplayRole).toString();
//
//		//drawDisplay(painter,myOption,myOption.rect,text);
//		//drawFocus(painter,myOption,myOption.rect);
//	}
//	else
//	{
//		QItemDelegate::paint(painter,option,index);
//	}
//}
//void CCheckDelegate::updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const
//{
//if(index.column()==column)
//	{
//		editor->setGeometry(option.rect);
//	}
//	else
//		QItemDelegate::updateEditorGeometry(editor,option,index);
//}
//
//QWidget * CCheckDelegate::createEditor ( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex & index) const 
//{
//	if(index.column()==column)
//	{
//		QCheckBox* checkBox=new QCheckBox(parent);
//		checkBox->setCheckState(Qt::Unchecked);
//		return checkBox;
//	}
//	else
//		return QItemDelegate::createEditor(parent,option,index);
//}
//
//
//void CCheckDelegate::setEditorData ( QWidget *editor, const QModelIndex & index) const
//{
//if(index.column()==column)
//	{
//		int isSelected=index.model()->data(index,Qt::DisplayRole).toInt();
//		QCheckBox* checkBox=qobject_cast<QCheckBox*>(editor);
//		//checkBox->setCheckState(Qt::Checked);
//	}
//	else
//		QItemDelegate::setEditorData(editor,index);
//}
//
//void CCheckDelegate::setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex & index) const
//{
//}