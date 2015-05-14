#include "CInputInfoDlg.h"

CInputInfoDlg::CInputInfoDlg(QWidget *parent)
	: QWidget(parent)
{
	setupUi(this);
	connect(pbOK, SIGNAL(clicked()),this, SLOT(onOk()));
	connect(pbCancel, SIGNAL(clicked()),this, SLOT(onCancel()));
}

CInputInfoDlg::~CInputInfoDlg()
{

}

void CInputInfoDlg::onOk()
{
    emit okMsg();
}

void CInputInfoDlg::onCancel()
{
	emit onCancel();
}
