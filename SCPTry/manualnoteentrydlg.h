#ifndef MANUALNOTEENTRYDLG_H
#define MANUALNOTEENTRYDLG_H
#define MAX_TYPE_NOTES 5
#include <QDialog>
#include "ui_manualnoteentrydlg.h"

class ManualNoteEntryDlg : public QDialog
{
	Q_OBJECT

public:
	ManualNoteEntryDlg(QWidget *parent = 0);
	~ManualNoteEntryDlg();
	int manualValues[MAX_TYPE_NOTES];
private:
	Ui::ManualNoteEntryDlg ui;
	void setManualValues();
	
private slots:
	void onAccept();

};

#endif // MANUALNOTEENTRYDLG_H
