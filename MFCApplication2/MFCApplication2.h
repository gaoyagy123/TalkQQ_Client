
// MFCApplication2.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once
#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif
#include "resource.h"		// ������
#include "MyTreeCtrl.h"
#define MAX_MSG_LENGTH				5000
#define MAX_SENDMSG_LENGTH              3000
typedef struct ObjRevInfo {
	CString strpath;
	LONG RevLen;
	CString Type;
} ObjRevInfo;
typedef struct PicInfo {
	long MaxLen;
	int Sel;
} PicInfo;
typedef struct RecvPic {
	bool Start;
	LONG MaxLen;
	LONG RevLen;
	int ObjNum;
	int RevNum;
	PicInfo Pic[100];
	ObjRevInfo obj[100];
	CString Talk;
} RecvPic;
typedef struct SendHead {
	char head[4];
	char UserMsg[20];
	int UserLen;
	long MaxLenth;
	int ObjNum;
	PicInfo Pic[100];
} SendHead;
typedef struct ObjInfo {
	CString strpath;
	CString Type;
	int Sel;
} ObjInfo;

typedef struct ObjSend {
	int num;
	ObjInfo obj[100];
} ObjSend;

typedef struct msgHead{
	char head[4];
	char UserMsg[20];
	int UserLen;
	long MaxLenth;
} msgHead;


typedef struct ObjRev {
	CString msg;
	int objnum;
	ObjInfo obj[100];
} ObjRev;
typedef struct objRecive {
	int num;
	ObjRev obj[100];
} objRecive;

class CMFCApplication2App : public CWinApp
{
public:
	CMFCApplication2App();
	CString MyName, MyPd;
	CImageList imagelisthead;
	CImageList imagelist1;
	CImageList facelist1;
	CString Friend[100][4];
	objRecive msg[100];
	SOCKET S;
	RecvPic RecPic[100];

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};

extern CMFCApplication2App theApp;