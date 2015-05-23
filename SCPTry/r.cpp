#include "stdafx.h"
#include "r.h"
#include <qdebug.h>
#include <setupapi.h>
#include <dbt.h>
//#pragma comment (lib, "USBInterface")
#define WM_MYMSG	(WM_USER+1000)
r::r(QWidget *parent)
	: QWidget(parent, Qt::Window)
{
	// This works
	ui.setupUi(this);
	hWnd = (HWND)this->winId();
	BN_Initialize(hWnd, WM_MYMSG);
}

r::~r()
{

}
bool r::nativeEvent(const QByteArray& eventType, void* message, long* result)
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
					ui.label->setText("Connected with the Banknote Device...");
					BN_SetControlMode(BN_ONLINE_MODE);
					//BN_SetCommunicationMode(BN_DETECTION_MODE);
					//BN_SetCommunicationMode(BN_BNSERIAL_MODE);

				}
				else if (lParam == USB_NOTOPENED)
				{
					ui.label->setText("Could not connect!");
				}

			}
			break;

			case DEVICEREMOVE_MSG:
			{

				ui.label->setText("Connected with the Banknote Device...");
				if (lParam == USB_UNPLUG)
				{

					ui.label->setText("Banknote Device has just been removed...");
					CWaitCursor wait;
					Sleep(200);

					//	GetDlgItem(IDC_START_CLEARANCE)->EnableWindow(FALSE);

				}
				else if (lParam == USB_NULL)
				{
					ui.label->setText("Cannot find any Banknote Device....");
	//				CWaitCursor wait;
//					Sleep(200);
					//	GetDlgItem(IDC_START_CLEARANCE)->EnableWindow(FALSE);
				}
			}
			break;

			case ERRORMSG_MSG:
			{
				QString tmp;
				wchar_t msg[255];
				//	BN_GetNextErrMessage(msg, 255);
				ui.label->setText(tmp.fromWCharArray(msg));
			}
			break;
			default:

				ui.label->setText("Connected with the Banknote Device...");
				break;
			}
		}
		
	}
	return QWidget::nativeEvent(eventType, message, result);
}