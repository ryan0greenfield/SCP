#pragma once
class LocalTime
{
public:
	LocalTime();
	~LocalTime();
	UINT			l_minute;
	UINT			l_hour;
	UINT			l_day;
	UINT			l_month;
	UINT			l_year;

	void			GetLocalTime();
};

