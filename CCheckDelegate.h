#ifndef CTASKDELEGATE_H
#define CTASKDELEGATE_H

#include <QItemDelegate>
#include <QEvent>
#include <QSqlRelationalDelegate>

class CCheckDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	CCheckDelegate(int column,QObject *parent=0);
	~CCheckDelegate();

	bool editorEvent( QEvent * event, QAbstractItemModel * model, const QStyleOptionViewItem & option, const QModelIndex & index );
	/*void paint(QPainter* painter,const QStyleOptionViewItem& option,
		const QModelIndex& index) const;*/
	/*void updateEditorGeometry ( QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	QWidget *createEditor ( QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex & index) const;
	void setEditorData ( QWidget *editor, const QModelIndex & index) const;
	void setModelData ( QWidget *editor, QAbstractItemModel *model, const QModelIndex & index) const;*/
		
private:
	int column;

	
};

#endif // CTASKDELEGATE_H
