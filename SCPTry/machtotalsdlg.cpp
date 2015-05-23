#include "stdafx.h"
#include "machtotalsdlg.h"

MachTotalsDlg::MachTotalsDlg(QWidget *parent)
	: QDialog(parent)
{

	ui.setupUi(this);
	QString qs;
	int grandTotal = 0;
	clearance *w = qobject_cast<clearance*>(this->parent());
	int *totals = w->totalCounts;
	int *machine = w->machineNo;

	for (int i = 0; i<w->MAX_NO_MACHINES; i++)
	{
		if (totals[i] != NULL)
		{
			qs += "Machine: " + QString::number(machine[i]) + "\t\tTotal count: $" + QString::number(totals[i]) + "\r\n\r\n";
			grandTotal += totals[i];
		}
		else
			qs += "Machine: " + QString::number(machine[i]) + "\t\tTotal count: N/A\r\n\r\n";
	}
	qs += "\t\t\tGrand Total: $" + QString::number(grandTotal);
	ui.l_summary->setText(qs);
}

MachTotalsDlg::~MachTotalsDlg()
{

}

void MachTotalsDlg::onBnClickedSave()
{
	setResult(TRUE);
	close();
}
void MachTotalsDlg::onBnClickedCancel()
{
	setResult(FALSE);
	close();
}
void MachTotalsDlg::setResult(bool result)
{
	dlgResult = result;
}
bool MachTotalsDlg::getResult()
{
	return dlgResult;
}