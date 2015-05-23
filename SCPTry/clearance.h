#ifndef CLEARANCE_H
#define CLEARANCE_H

#include <QWidget>
#include <Qlist>
#include "stdafx.h"
#include "ui_clearance.h"
#include "lineprinter.h"
#include "USBInterface.h"
#include "ClearanceFile.h"
#include "LocalTime.h"
#include "machtotalsdlg.h"
#include "manualnoteentrydlg.h"
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

class clearance : public QWidget
{
	Q_OBJECT

public:
	clearance(QWidget *parent = 0);
	~clearance();
	void			CheckDirectory(wchar_t*);
	void			GetFilePath();
	void			GetMachineNo();
	void			displayMachineNo();
	void			writeClearanceData();
	BOOL			checkForNotes();
	//Local Time values
	LocalTime time;
	//Printer functions
	void			PrintHeader();
	void			PrintMachine();
	void			PrintFooter();
	void AddToList();
	void ClearList();
	void DisplayGrandTotal();
	void EndOfListReached();
	void GetNextUncountedMachine();
	bool nativeEvent(const QByteArray&, void*, long*);
	//Printer variables
	LinePrinter CPrinter;
	int				seqNo;
	BOOL			printerAvail;

	// File input/output variables
	ClearanceFile	outputFile;
	CStdioFile		outFile;
	CStdioFile		importedMachNo;
	int getNoMachines();
	wchar_t			filePath[250];
	wchar_t			fileName[250];
	wchar_t			date[MAX_LINE_LENGTH];
	wchar_t			buffer[25];
	QStringList		machineList;
	QStringList		amountList;
	double			grandTotal;
	int				count;
	int				*machineNo = NULL;
	int				*totalCounts = NULL;
	int				currentMachineNo;
	int				currentTotalCount;
	int				MAX_NO_MACHINES;
	int				requested_Machine;
	int				countMem;
	int				currentPieces[5];
	bool			clearanceStatus;
	bool			endOfList;
	HWND			hWnd;
	bool nativeEvent(MSG *msg, long *result);
	void			ClearCount();
	CString			s_uncountedMachines;
	bool			checkForMachines();

	QStringListModel *machModel;
	QStringListModel *amountModel;
protected:

	int				m_curNationCode;
	char			m_cyName[CURRENCYNAME_LENGTH];
	double			m_cyValue[MAX_CURRENCYVALUE_NO];
	int				m_cyPiece[MAX_CURRENCYVALUE_NO];

	UINT			m_cyComboCode[MAX_CURRENCYCOMBO_NO];
	int				m_cyComboNumber;
private:
	Ui::clearance ui;
	private slots:
	void	OnBnClickedSaveClearanceBtn();
	void	OnBnClickedStartClearanceBtn();
	void	OnBnClickedGoToMachineBtn();
	void	OnBnClickedNextmachineBtn();
	void	OnBnClickedManualNote();
	void	OnBnClickedClear();
};

#endif // CLEARANCE_H
