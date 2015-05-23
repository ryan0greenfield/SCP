#pragma once
#include "stdafx.h"
#include <winspool.h>
#define MAX_LINE_LENGTH 42
#define CUT_PAPER_CODE "\n\n\n\n\n\n\x1Bi"
class LinePrinter
{
public:
	LinePrinter();
~LinePrinter();
void			SetPrinterName(LPWSTR);
bool			InitPrinter();
void			PrintDivider();
void			WriteLine(char *);
void			PrintLine();
void			CutPaper();
HANDLE			hPrinter;
DOC_INFO_1		DocInfo;
DWORD			written;
private:
LPWSTR			printerType;
};

