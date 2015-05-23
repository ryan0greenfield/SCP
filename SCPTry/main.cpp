#pragma once
#include "stdafx.h"
#include "scpbpsc1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SCPBPSC1 w;
	w.show();
	return a.exec();
}
