#include "stdafx.h"
#include "ClearanceFile.h"


ClearanceFile::ClearanceFile()
{
	time.GetLocalTime();
}


ClearanceFile::~ClearanceFile()
{
}
// Create directory if it does not exist
void ClearanceFile::CheckDirectory(wchar_t* filePath)
{
	if (!CreateDirectory(filePath, NULL))
	{
		return;
	}
}

void ClearanceFile::GetFilePath()
{
	_tcscpy(filePath, _T("C:\\test\\Clearance Data\\"));
	_itow(time.l_year, buffer, 10);
	_tcscat(filePath, buffer);

	CheckDirectory(filePath);
	// Change month from int to string
	switch (time.l_month)
	{
	default:
		AfxMessageBox(_T("No time data read"), MB_OK | MB_ICONINFORMATION);
		break;
	case 1:
		_tcscat(filePath, _T("\\January"));
		break;
	case 2:
		_tcscat(filePath, _T("\\Febuary"));
		break;
	case 3:
		_tcscat(filePath, _T("\\March"));
		break;
	case 4:
		_tcscat(filePath, _T("\\April"));
		break;
	case 5:
		_tcscat(filePath, _T("\\May"));
		break;
	case 6:
		_tcscat(filePath, _T("\\June"));
		break;
	case 7:
		_tcscat(filePath, _T("\\July"));
		break;
	case 8:
		_tcscat(filePath, _T("\\August"));
		break;
	case 9:
		_tcscat(filePath, _T("\\September"));
		break;
	case 10:
		_tcscat(filePath, _T("\\October"));
		break;
	case 11:
		_tcscat(filePath, _T("\\November"));
		break;
	case 12:
		_tcscat(filePath, _T("\\December"));
		break;

	}
	CheckDirectory(filePath);
	_tcscpy(fileName, filePath);
	_tcscat(fileName, _T("\\"));
	_itow(time.l_day, buffer, 10);
	_tcscat(fileName, buffer);
	_tcscat(fileName, _T("-"));
	_itow(time.l_month, buffer, 10);
	_tcscat(fileName, buffer);
	_tcscat(fileName, _T("-"));
	_itow(time.l_year, buffer, 10);
	_tcscat(fileName, buffer);
	_tcscat(fileName, _T(".txt"));
}

bool ClearanceFile::is_file_exist()
{
	//QFile inputFile(fileName);
	//if (inputFile.open(QIODevice::ReadOnly))
	//{
	return TRUE;
}