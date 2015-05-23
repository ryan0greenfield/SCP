#pragma once
#include "stdafx.h"
#include "LocalTime.h"
#include <qfile>
class ClearanceFile
{
public:
	ClearanceFile();
	~ClearanceFile();
	void CheckDirectory(wchar_t* filePath);
	void GetFilePath();
	bool is_file_exist();
	wchar_t			filePath[250];
	wchar_t			fileName[250];
	wchar_t			date[42];
	wchar_t			buffer[250];
private:
	LocalTime		time;
};

