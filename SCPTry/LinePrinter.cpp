#include "stdafx.h"
#include "LinePrinter.h"


LinePrinter::LinePrinter()
{
}


LinePrinter::~LinePrinter()
{
}
void LinePrinter::SetPrinterName(LPWSTR printerName)
{
	printerType = printerName;
}
bool LinePrinter::InitPrinter()
{
	DocInfo.pDatatype = _T("RAW"); // datatype is Null (it can be EMF also)
	DocInfo.pDocName = _T("c60_print.prn"); // Name of the Document 
	DocInfo.pOutputFile = NULL; // Output is to the printer
	if (!OpenPrinter(printerType, &hPrinter, NULL))  //you should change name of printer
		return FALSE;
	if (!StartDocPrinter(hPrinter, 1, (LPBYTE)&DocInfo))
		return FALSE;
	if (!StartPagePrinter(hPrinter))
		return FALSE;
	return TRUE;
}

void LinePrinter::PrintDivider()
{

	char divider[MAX_LINE_LENGTH];
	memset(divider, '-', MAX_LINE_LENGTH);
	WritePrinter(hPrinter, divider, MAX_LINE_LENGTH, &written);
}

void LinePrinter::WriteLine(char* line1)
{
	DWORD written;
	WritePrinter(hPrinter, line1, strlen(line1), &written);
}

void LinePrinter::PrintLine()
{
	EndPagePrinter(hPrinter);
	EndDocPrinter(hPrinter);
	ClosePrinter(hPrinter);
}
void LinePrinter::CutPaper()
{
	WritePrinter(hPrinter, CUT_PAPER_CODE, strlen(CUT_PAPER_CODE), &written);
	
}
