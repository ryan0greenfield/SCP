#pragma once
#include "stdafx.h"
#include "clearance.h"
#define WM_MYMSG	(WM_USER+1000)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <setupapi.h>
#include <dbt.h>
clearance::clearance(QWidget *parent)
	: QWidget(parent, Qt::Window)
{
	// This works
	ui.setupUi(this);
	hWnd = (HWND)this->winId();
	BN_Initialize(hWnd, WM_MYMSG);
	GetMachineNo();
	// Initialise count array
	for (int i = 0; i <= MAX_NO_MACHINES; i++)
		totalCounts[i] = 0;
	//initialize pieces array
	for (int i = 0; i <= MAX_TYPE_NOTES; i++)
	{
		currentPieces[i]=0;
		m_cyPiece[i]=0;
	}
	time.GetLocalTime();
	CPrinter.SetPrinterName(_T("Custom Q3"));
	count = 0;
}


clearance::~clearance()
{
	BN_Destroy();
}

bool clearance::nativeEvent(const QByteArray& eventType, void* message, long* result)
{

	MSG *msg = static_cast<MSG *>(message);
	QString msgName;
	//CString ww((LPCTSTR)msg->wParam);
	//CString ss((LPCTSTR)msg->lParam);
	//WPARAM wParam;
	LPARAM lParam = msg->lParam;
	int msgType = msg->message;
	switch (msgType)
	{
	case WM_MYMSG:
	{
		switch (msg->wParam)
		{
		case DEVICEARRIVAL_MSG:
		{
			if (lParam == USB_CONNECTED)
			{
				
				ui.l_machine_status->setText("Connected with the Banknote Device...");
				ui.btn_Begin_Clearance->setEnabled(TRUE);
				BN_SetControlMode(BN_ONLINE_MODE);
				//BN_SetCommunicationMode(BN_DETECTION_MODE);
				//BN_SetCommunicationMode(BN_BNSERIAL_MODE);

			}
			else if (lParam == USB_NOTOPENED)
			{
				ui.l_machine_status->setText("Could not connect!");
			}

		}
		break;

		case DEVICEREMOVE_MSG:
		{
			if (lParam == USB_UNPLUG)
			{

				ui.l_machine_status->setText("Banknote Device has just been removed...");
				
				ui.btn_Begin_Clearance->setEnabled(FALSE);

			}
			else if (lParam == USB_NULL)
			{
				ui.l_machine_status->setText("Cannot find any Banknote Device....");
				
				ui.btn_Begin_Clearance->setEnabled(TRUE);
			}
		}
		break;

		case ERRORMSG_MSG:
		{
			QString tmp;
			wchar_t msg[255];
			BN_GetNextErrMessage(msg, 255);
			//ui.l_machine_status->setText(tmp.fromWCharArray(msg));
		}
		break;

		case SCANRAWIMG_MSG:
		{
		}
		break;

		case TITODATA_MSG:
		{

		}
		break;

		case BNSERIAL_MSG:
		{
		}
		break;

		case NATIONSET_MSG:
		{

		}
		break;


		case DEVICE_ERROR_MSG:
		{
			_ERR_STATUS err;
			if (BN_GetDeviceError(err) == BN_SUCCESS)
			{
				switch (err)
				{
				case BN_BILLPATH_ERR:
					ui.l_machine_status->setText("bill path error");
					break;
				case BN_PAPERJAM_ERR:
					ui.l_machine_status->setText("paper jam");
					break;
				case BN_RS_FULL_ERR:
					ui.l_machine_status->setText("reject stacker full");
					break;
				case BN_CS_FULL_ERR:
					ui.l_machine_status->setText("counted stacker full");
					break;
				case BN_REMOVE_CS_ERR:
					ui.l_machine_status->setText("please remove banknotes from counted stacker");
					break;
				case BN_REMOVE_RS_ERR:
					ui.l_machine_status->setText("please remove banknotes from reject stacker");
					break;
				case BN_UPATH_OPEN_ERR:
					ui.l_machine_status->setText("upper bill path is opened");
					break;
				case BN_LPATH_OPEN_ERR:
					ui.l_machine_status->setText("lower bill path is opened");
					break;
				case BN_UP_ABNORMAL_ERR:
					ui.l_machine_status->setText("upper bill path error");
					break;
				case BN_LP_ABNORMAL_ERR:
					ui.l_machine_status->setText("lower bill path error");
					break;
				case BN_REMOVE_HP_ERR:
					ui.l_machine_status->setText("please remove banknotes from hopper");
					break;
				case BN_SOLENOID_ERR:
					ui.l_machine_status->setText("solenoid error");
					break;
				case BN_OVER_BUFFER_ERR:
					ui.l_machine_status->setText("buffer overflow");
					break;
				case BN_BATCH_FAIL_ERR:
					ui.l_machine_status->setText("current batch is not reached");
					break;
				case BN_MOTOR_ERR:
					ui.l_machine_status->setText("motor overflow");
					break;
				}
			}
		}
		break;


		case PAPERDECT_MSG:
		{

			double amount = 0;
			m_curNationCode = (int)lParam;
			BN_GetDetectionResult((BYTE)lParam, m_cyValue, m_cyPiece, amount);
			QString tmpString;
			currentTotalCount = amount;
			ui.l_total_amount->setText(tmpString.number(amount));
			int tp = 0;
			//Grand total count display
			for (int i = 0; i < MAX_CURRENCYVALUE_NO; i++)
			{
				currentPieces[i] = m_cyPiece[i];
				tp += m_cyPiece[i];
			}
			ui.l_grand_total->setText(tmpString.number(tp));
			// Make this into seperate function?

			//Five Dollar Count display
			ui.l_5count->setText(tmpString.number(currentPieces[0]));
			//Ten Dollar Count display
			ui.l_10count->setText(tmpString.number(currentPieces[1]));
			//Twenty Dollar Count display
			ui.l_20count->setText(tmpString.number(currentPieces[2]));
			//Fifty Dollar Count display
			ui.l_50count->setText(tmpString.number(currentPieces[3]));
			//Hundred Dollar Count display
			ui.l_100count->setText(tmpString.number(currentPieces[4]));
		}
		break;
		}
	}
	break;
	default:
		break;
	}
	return QWidget::nativeEvent(eventType, message, result);
}
int clearance::getNoMachines()
{
	importedMachNo.Open(_T("C:\\test\\MN.txt"), CFile::modeRead);
	int i = 0;
	while (importedMachNo.ReadString(buffer, 10) != NULL)
		i++;
	importedMachNo.Close();
	return i;
}

void clearance::GetMachineNo()
{
	MAX_NO_MACHINES = getNoMachines();
	int i = 0;
	totalCounts = new int[MAX_NO_MACHINES];
	machineNo = new int[MAX_NO_MACHINES];
	importedMachNo.Open(_T("C:\\test\\MN.txt"), CFile::modeRead);
	while (importedMachNo.ReadString(buffer, 10) != NULL)
	{
		machineNo[i] = _wtoi(buffer);
		i++;
	}
	importedMachNo.Close();
}

void clearance::displayMachineNo()
{
	ui.l_current_machine_no->setText(QString::number(currentMachineNo));
}

// Write clearance data to text file, current path c:\test\clearance data
//Move this to clearance file class
void clearance::writeClearanceData()
{

	outputFile.GetFilePath();

	//add check for if file open
	outFile.Open(outputFile.fileName, CFile::modeCreate | CFile::modeWrite);

	//Write beginning part of BASIC format

	// Write Clearance date
	outFile.WriteString(_T("Clearance Date,"));
	_tcscpy(date, _T(""));
	_itow(time.l_day - 1, buffer, 10);
	_tcscat(date, buffer);
	_tcscat(date, _T("/"));
	_itow(time.l_month, buffer, 10);
	_tcscat(date, buffer);
	_tcscat(date, _T("/"));
	_itow(time.l_year, buffer, 10);
	_tcscat(date, buffer);
	outFile.WriteString(date);
	outFile.WriteString(_T(","));
	_itow(time.l_hour, buffer, 10);
	outFile.WriteString(buffer);
	outFile.WriteString(_T(":"));
	_itow(time.l_minute, buffer, 10);
	if (time.l_minute < 10)
		outFile.WriteString(_T("0"));
	outFile.WriteString(buffer);
	outFile.WriteString(_T("\n"));

	//Write Created date
	outFile.WriteString(_T("Created Date,"));
	_tcscpy(date, _T(""));
	_itow(time.l_day, buffer, 10);
	_tcscat(date, buffer);
	_tcscat(date, _T("/"));
	_itow(time.l_month, buffer, 10);
	_tcscat(date, buffer);
	_tcscat(date, _T("/"));
	_itow(time.l_year, buffer, 10);
	_tcscat(date, buffer);
	outFile.WriteString(date);
	outFile.WriteString(_T(","));
	_itow(time.l_hour, buffer, 10);
	outFile.WriteString(buffer);
	outFile.WriteString(_T(":"));
	_itow(time.l_minute, buffer, 10);
	if (time.l_minute < 10)
		outFile.WriteString(_T("0"));
	outFile.WriteString(buffer);
	outFile.WriteString(_T("\n"));


	//Write MACHINE NUMBER and total count
	for (int i = 0; i < MAX_NO_MACHINES; i++) // MAX MAHINE NO
	{
		if (totalCounts[i] != NULL)
		{
			_itow(machineNo[i], buffer, 10);
			outFile.WriteString(buffer);
			outFile.WriteString(_T(","));
			_itow(totalCounts[i], buffer, 10);
			outFile.WriteString(buffer);
			outFile.WriteString(_T("\n"));
		}
	}

	outFile.WriteString(_T("END"));
	outFile.Flush();
	outFile.Close();
}

// Checks if notes have been left in machine when moving from machine
BOOL clearance::checkForNotes()
{
	int sensorStatus;
	BN_GetSensorStatus(sensorStatus);
	switch (sensorStatus)
	{
	case 2:
		return TRUE;
		break;
	case 4:

		return TRUE;
		break;
	case 6:
		return TRUE;
		break;
	}
	return FALSE;
}

// Prepare for printing, to be called before any print command
void clearance::PrintHeader()
{

	if (CPrinter.InitPrinter())
	{

		char cBuffer[MAX_LINE_LENGTH] = ""; //use char solely for printing
		char tmp[MAX_LINE_LENGTH] = "";
		CPrinter.WriteLine("\t\tSCP Clearance\n");
		CPrinter.PrintDivider();
		CPrinter.WriteLine("\nClearance Date: ");

		_itoa(time.l_day - 1, cBuffer, 10);
		strcat(tmp, cBuffer);
		strcat(tmp, "/");
		_itoa(time.l_month, cBuffer, 10);
		strcat(tmp, cBuffer);
		strcat(tmp, "/");
		_itoa(time.l_year, cBuffer, 10);
		strcat(tmp, cBuffer);
		strcat(tmp, "\n");
		CPrinter.WriteLine(tmp);
		memset(tmp, NULL, MAX_LINE_LENGTH);

		//Current Date
		CPrinter.WriteLine("Current Date: ");
		_itoa(time.l_day, cBuffer, 10);
		strcat(tmp, cBuffer);
		strcat(tmp, "/");
		_itoa(time.l_month, cBuffer, 10);
		strcat(tmp, cBuffer);
		strcat(tmp, "/");
		_itoa(time.l_year, cBuffer, 10);
		strcat(tmp, cBuffer);
		strcat(tmp, "\n");
		CPrinter.WriteLine(tmp);
		memset(tmp, NULL, MAX_LINE_LENGTH);
		CPrinter.PrintDivider();
		CPrinter.WriteLine("Seq.\tMachine\t\tCount\tACCM\n");
		CPrinter.PrintLine();
		seqNo = 1;
	}
}

// Prints the current machine number and count
void clearance::PrintMachine()
{
	//add check for if added in middle of clearance
	if (CPrinter.InitPrinter())
	{
		char cBuffer[MAX_LINE_LENGTH] = "";
		char tempCh[MAX_LINE_LENGTH];
		_itoa(seqNo, tempCh, 10);
		strcat(cBuffer, tempCh);
		strcat(cBuffer, "\t");
		_itoa(currentMachineNo, tempCh, 10);
		strcat(cBuffer, tempCh);
		_itoa(currentTotalCount, tempCh, 10);
		strcat(cBuffer, "\t\t$");
		strcat(cBuffer, tempCh);
		_itoa(grandTotal, tempCh, 10);
		strcat(cBuffer, "\t$");
		strcat(cBuffer, tempCh);
		strcat(cBuffer, "\n");
		CPrinter.WriteLine(cBuffer);
		CPrinter.PrintLine();
		seqNo++;
	}
}

// Prints end of clearance grand total
void clearance::PrintFooter()
{
	if (CPrinter.InitPrinter())
	{

		char cBuffer[MAX_LINE_LENGTH] = "";
		char tempCh[MAX_LINE_LENGTH] = "";
		CPrinter.PrintDivider();
		//WritePrinter(hPrinter, "\x1d211001", 6, &written); // Double text size
		CPrinter.WriteLine("\nGrand Total : $");
		//WritePrinter(hPrinter, "\x1d210000", 6, &written); //reset size
		_itoa(grandTotal, tempCh, 10);
		strcat(cBuffer, tempCh);
		strcat(cBuffer, "\n");
		CPrinter.WriteLine(cBuffer);
		memset(cBuffer, NULL, MAX_LINE_LENGTH);
		CPrinter.PrintDivider();
		CPrinter.WriteLine("\nTotal Machines Counted: ");
		int noMach = 0;
		for (int i = 0; i < sizeof(totalCounts) / sizeof(totalCounts[0]); i++)
		{
			if (totalCounts[i] != NULL && totalCounts[i] != 0)
				noMach++;
		}
		_itoa(noMach, tempCh, 10);
		strcat(cBuffer, tempCh);
		strcat(cBuffer, "\n");
		CPrinter.WriteLine(cBuffer);
		memset(cBuffer, NULL, MAX_LINE_LENGTH);
		CPrinter.PrintDivider();
		CPrinter.WriteLine("\n\n");
		CPrinter.WriteLine("Clearance completed by: __________________");
		CPrinter.CutPaper();
		CPrinter.PrintLine();
	}
}
 //Adds machine and count to list
 //Need to account for if machine has already been counted
void clearance::AddToList()
{
	amountModel = new QStringListModel(this);
	machModel = new QStringListModel(this);
	amountList << QString::number(currentTotalCount);
	machineList << QString::number(currentMachineNo);
	amountModel->setStringList(amountList);
	ui.lv_recentlyCounted->setModel(amountModel);
	machModel->setStringList(machineList);
	ui.lv_recentlyMachine->setModel(machModel);
}
// Clears list at end of count
void clearance::ClearList()
{
	ui.lv_recentlyCounted->reset();
	ui.lv_recentlyMachine->reset();
}

void clearance::DisplayGrandTotal()
{
	grandTotal = 0;
	for (int i = 0; i < sizeof(totalCounts) / sizeof(totalCounts[0]); i++)
		grandTotal += totalCounts[i];
	ui.l_grand_total->setText(QString::number(grandTotal));
}

void clearance::EndOfListReached()
{

	AfxMessageBox(_T("Machine listing finished"), MB_OK | MB_ICONERROR);
	ui.l_current_machine_no->setText("END OF MACHINE LIST");
	endOfList = TRUE;
	ui.btn_Next_Machine->setEnabled(FALSE);
}

void clearance::GetNextUncountedMachine()
{
	for (int i = count; i <= MAX_NO_MACHINES; i++)
	{

		if (totalCounts[count] != NULL)
		{
			count = i;
		}
		else
			break;
	}
}
// Make into arrow button VVV
void clearance::ClearCount()
{
	currentTotalCount = 0;
	for (int i = 0; i <= MAX_TYPE_NOTES; i++)
	{
		currentPieces[i] = 0;
	}
	//Five Dollar Count display
	ui.l_5count->setText(QString::number(currentTotalCount));
	//Ten Dollar Count display
	ui.l_10count->setText(QString::number(currentTotalCount));
	//Twenty Dollar Count display
	ui.l_20count->setText(QString::number(currentTotalCount));
	//Fifty Dollar Count display
	ui.l_50count->setText(QString::number(currentTotalCount));
	//Hundred Dollar Count display
	ui.l_100count->setText(QString::number(currentTotalCount));
	ui.l_total_amount->setText(QString::number(currentTotalCount));
	ui.l_total_pieces->setText(QString::number(currentTotalCount));

}

bool clearance::checkForMachines()
{
	int uncountedIndex = 0;
	CString tmp = _T("");
	s_uncountedMachines.Empty();
	s_uncountedMachines = _T("The following machines are uncounted:\n");
	bool uncounted = FALSE;
	int uncountedMachines[100];
	for (int t = 0; t < MAX_NO_MACHINES; t++)
	{
		if (totalCounts[t] == 0 || totalCounts[t] == NULL)
		{
			uncountedMachines[uncountedIndex] = machineNo[t];
			tmp.Format(_T("%d"), machineNo[t]);
			s_uncountedMachines += tmp + _T("\n");
			uncountedIndex++;
			uncounted = TRUE;
		}
	}
	s_uncountedMachines += _T("Continue anyway?");
	if (uncounted)
		return TRUE;
	else
		return FALSE;
}

void clearance::OnBnClickedNextmachineBtn()
{

	if (endOfList == TRUE)
		return;
	// Check sensor status and disallow continue if notes still in machine THIS NEEDS TO BE TESTED
	if (checkForNotes() == TRUE)
		AfxMessageBox(_T("Money left in machine, clear before continuing."));
	else
	{
		//Enable for test without machine
		//currentTotalCount = 1;
		// Save current machine count
		//Check for 0 count

		if (currentTotalCount == 0)
			if (AfxMessageBox(_T("Machine has not been counted.\nAre you sure you want to continue?"), MB_YESNO | MB_ICONSTOP) == IDYES)
				totalCounts[count] = NULL;
			else
				return;
		else
		{
			totalCounts[count] = currentTotalCount;
			DisplayGrandTotal();

			AddToList();
			if (printerAvail)
				PrintMachine();
		}
		BN_ActClearButton();
		ClearCount();
		count++;
		GetNextUncountedMachine();
		// Check for if at end of list
		if (count == MAX_NO_MACHINES)
		{
			EndOfListReached();
			return;
		}
		currentMachineNo = machineNo[count];
		displayMachineNo();
		// Add condition for count_mem if != NULL then continue like normal SEPERATE FUNCTION?
	}
}

void clearance::OnBnClickedStartClearanceBtn()
{
	//BN_SetPureCounterMode(TRUE);
	BN_SetCumulativeMode(TRUE);
	BN_ActClearButton();
	BN_ActStartButton();
	currentMachineNo = machineNo[count];
	endOfList = FALSE;
	ui.btn_Begin_Clearance->setEnabled(FALSE);
	ui.btn_Next_Machine->setEnabled(TRUE);
	ui.btn_End_Clearance->setEnabled(TRUE);
	ui.btn_Go_To->setEnabled(TRUE);
	ui.btn_Manual->setEnabled(TRUE);
	displayMachineNo();
	currentMachineNo = machineNo[count];
	currentTotalCount = 0;

	if (ui.chk_Printer->isChecked())
	{
		printerAvail = TRUE;
		PrintHeader();
	}

	clearanceStatus = TRUE;
}
//add check for if machine has already been counted
void clearance::OnBnClickedGoToMachineBtn()
{
	if (checkForNotes() == TRUE)
		return;
	QString tmp = ui.edit_Machine->text();
	requested_Machine = tmp.toInt();
	countMem = count;
	for (int i = 0; i <= MAX_NO_MACHINES; i++)
		if (requested_Machine == machineNo[i])
		{
			count = i;
			currentMachineNo = machineNo[i];
			displayMachineNo();
			endOfList = FALSE;
			QString tmpString;
			return;
		}
		else if (i == MAX_NO_MACHINES)
		{
			AfxMessageBox(_T("Machine not found"), MB_OK | MB_ICONERROR);
			return;
		}
	// Add check for if notes still in machine, message box to please remove notes
}

void clearance::OnBnClickedSaveClearanceBtn()
{
	if (checkForNotes() == TRUE)
		return;
	if (checkForMachines() == TRUE)
		if (AfxMessageBox(s_uncountedMachines, MB_YESNO | MB_ICONSTOP) == IDNO)
			return;
	MachTotalsDlg *dlg = new MachTotalsDlg(this);
	dlg->setParent(this);
	dlg->exec();
	if (dlg->result() == TRUE)
	{
		if (printerAvail)
		{
			PrintFooter();
		}
		writeClearanceData();
		AfxMessageBox(_T("Clearance saved successfully!"), MB_ICONINFORMATION | MB_OK);
		// Reset totals for new clearance
		count = 0;
		for (int t = 0; t < sizeof(totalCounts) / sizeof(totalCounts[0]); t++)
			totalCounts[t] = 0;
		//ClearList();
		//GetDlgItem(IDC_START_CLEARANCE)->EnableWindow(TRUE);
		ui.btn_Clear->setEnabled(FALSE);
		ui.btn_End_Clearance->setEnabled(FALSE);
		ui.btn_Go_To->setEnabled(FALSE);
		ui.btn_Manual->setEnabled(FALSE);
		ui.btn_Next_Machine->setEnabled(FALSE);
		ui.l_machine_status->setText("");
		clearanceStatus = FALSE;
	}
}

void clearance::OnBnClickedManualNote()
{
	ManualNoteEntryDlg *dlg = new ManualNoteEntryDlg(this);
	dlg->setParent(this);
	dlg->exec();
	if (dlg->result()==TRUE)
	{
		int manualNotes[5];
		for (int i=0; i < MAX_TYPE_NOTES; i++)
		{
			manualNotes[i] = dlg->manualValues[i];
		}
		int j[5] = { 5, 10, 20, 50, 100 };
		int tp = 0;
		for (int i = 0; i < 5; i++)
		{
			currentPieces[i] += manualNotes[i];
			currentTotalCount += manualNotes[i]*j[i];
			tp += manualNotes[i];
		}

		QString tmpString;
		//Five Dollar Count display
		ui.l_5count->setText(tmpString.number(currentPieces[0]));
		//Ten Dollar Count display
		ui.l_10count->setText(tmpString.number(currentPieces[1]));
		//Twenty Dollar Count display
		ui.l_20count->setText(tmpString.number(currentPieces[2]));
		//Fifty Dollar Count display
		ui.l_50count->setText(tmpString.number(currentPieces[3]));
		//Hundred Dollar Count display
		ui.l_100count->setText(tmpString.number(currentPieces[4]));
		//total
		ui.l_total_pieces->setText(tmpString.number(tp));
		ui.l_total_amount->setText("$"+tmpString.number(currentTotalCount));
		//ui.l_total_pieces->setText(tmpString.number(currentPieces));

	}

}


void clearance::OnBnClickedClear()
{
	ClearCount();
}
