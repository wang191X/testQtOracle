#include "cminbutton.h"
#include <QPixmap>
 #include <QStyle>

CMinButton::CMinButton(QWidget *parent)
	: QToolButton(parent)
{
	QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);        
	setIcon(pix);
}

CMinButton::~CMinButton()
{

}
