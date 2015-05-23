#include "stdafx.h"
#include "manualnoteentrydlg.h"

ManualNoteEntryDlg::ManualNoteEntryDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

ManualNoteEntryDlg::~ManualNoteEntryDlg()
{

}

void ManualNoteEntryDlg::onAccept()
{
	setManualValues();
	close();
	setResult(TRUE);
	
}
void ManualNoteEntryDlg::setManualValues()
{
	manualValues[0] = ui.in_5->value();
	manualValues[1] = ui.in_10->value();
	manualValues[2] = ui.in_20->value();
	manualValues[3] = ui.in_50->value();
	manualValues[4] = ui.in_100->value();
}