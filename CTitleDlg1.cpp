#include "CTitleDlg1.h"

CTitleDlg1::CTitleDlg1(QWidget *parent,QWidget *child)
	: QDialog(parent)
{
	setupUi(this);

	connect(toolButtonclose, SIGNAL( clicked() ), this, SLOT(close()));        
	connect(toolButtonmin, SIGNAL( clicked() ), this, SLOT(showMinimized()));       
	connect(toolButtonmax, SIGNAL( clicked() ), this, SLOT(onMaxWindow()));
	toolButtonmax->setHidden(true);

	setWindowFlags(Qt::FramelessWindowHint);
	QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);        
	toolButtonclose->setIcon(pix); 
	pix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);        
	toolButtonmax->setIcon(pix);         

	formLayout->addWidget(child);
}

CTitleDlg1::~CTitleDlg1()
{

}


void CTitleDlg1::onMaxWindow()
{
	if (isMaximized())
	{
		QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);        
		toolButtonmax->setIcon(pix);
		showNormal();
	}
	else
	{
		QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);        
		toolButtonmax->setIcon(pix);   
		showMaximized();
	}
}

