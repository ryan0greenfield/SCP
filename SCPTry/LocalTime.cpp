#include "stdafx.h"
#include "LocalTime.h"


LocalTime::LocalTime()
{
}


LocalTime::~LocalTime()
{
}

void LocalTime::GetLocalTime()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	l_day = ltm->tm_mday;
	l_month = 1 + ltm->tm_mon;
	l_year = 1900 + ltm->tm_year;
	l_hour = ltm->tm_hour;
	l_minute = ltm->tm_min;
}