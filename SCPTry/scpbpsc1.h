#ifndef SCPBPSC1_H
#define SCPBPSC1_H
#include "stdafx.h"
#include <QtWidgets/QMainWindow>
#include "ui_scpbpsc1.h"
#include "clearance.h"
class SCPBPSC1 : public QMainWindow
{
	Q_OBJECT

public:
	SCPBPSC1(QWidget *parent = 0);
	~SCPBPSC1();
	
private:
	Ui::SCPBPSC1Class ui;
	
private slots:
	void sOpenClearance();
};

#endif // SCPBPSC1_H
