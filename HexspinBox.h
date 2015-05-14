#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>
class QRegExpValidator;

class HexspinBox : public QSpinBox
{
	Q_OBJECT

public:
	HexspinBox(QWidget *parent=0);
	~HexspinBox();

protected:
	QValidator::State validate(QString &text,int &pos)const;
	int valueFromText(const QString &text)const;
	QString textFromValue(int value)const;

private:
	QRegExpValidator *validator;
};

#endif // HEXSPINBOX_H
