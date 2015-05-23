#ifndef MACHTOTALSDLG_H
#define MACHTOTALSDLG_H

#include <QDialog>
#include "ui_machtotalsdlg.h"
#include "clearance.h"
class MachTotalsDlg : public QDialog
{
	Q_OBJECT 

public:
	MachTotalsDlg(QWidget *parent);
	~MachTotalsDlg();
	int machine[100];
	int totals[100];
	bool getResult();

private:
	Ui::MachTotalsDlg ui;
	void setResult(bool);
	bool dlgResult;
	private slots:
	void onBnClickedSave();
	void onBnClickedCancel();
};

#endif // MACHTOTALSDLG_H
