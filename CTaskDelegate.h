#ifndef CTASKDELEGATE_H
#define CTASKDELEGATE_H

#include <QItemDelegate>

class CTaskDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	CTaskDelegate(int column,QObject *parent=0);
	~CTaskDelegate();

	void paint(QPainter* painter,const QStyleOptionViewItem& option,
		const QModelIndex& index) const;
private:
	int column;
	
};

#endif // CTASKDELEGATE_H
