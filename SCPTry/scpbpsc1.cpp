#pragma once
#include "stdafx.h"
#include "scpbpsc1.h"
#include "clearance.h"
SCPBPSC1::SCPBPSC1(QWidget *parent)
	: QMainWindow(parent)
{
	QIcon icon("/SCPBPSC1/Resources/sqlogoppp.ico");
	setWindowIcon(icon);
	ui.setupUi(this);
	
}

SCPBPSC1::~SCPBPSC1()
{

}

void SCPBPSC1::sOpenClearance()
{
	clearance *dlg = new clearance;
	dlg->show();
}
