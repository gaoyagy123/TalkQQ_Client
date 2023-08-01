// GameApp.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "GameApp.h"
#include "afxdialogex.h"


// GameApp 对话框

IMPLEMENT_DYNAMIC(GameApp, CDialogEx)

GameApp::GameApp(CWnd* pParent /*=NULL*/)
	: CDialogEx(GameApp::IDD, pParent)
{

}

GameApp::~GameApp()
{
}

void GameApp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON3, G_Button3);
	DDX_Control(pDX, IDC_BUTTON4, G_Button4);
	DDX_Control(pDX, IDC_BUTTON1, M_Button1);
	DDX_Control(pDX, IDC_TREE1, tlist1);
	DDX_Control(pDX, IDC_BUTTON6, TButton1);
	DDX_Control(pDX, IDC_BUTTON7, TButton2);
	DDX_Control(pDX, IDC_BUTTON5, TButton3);
	DDX_Control(pDX, IDC_HEADBITMAP, headicon);
	DDX_Control(pDX, IDC_STATICNICK, NickName);
	DDX_Control(pDX, IDC_STATIC1, Gold);
	DDX_Control(pDX, IDC_TREE3, headlist);
	DDX_Control(pDX, IDC_EDIT1, findedit);
	DDX_Control(pDX, IDC_STATIC6, numid);
	DDX_Control(pDX, IDC_TREE2, flist);
}


BEGIN_MESSAGE_MAP(GameApp, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &GameApp::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON3, &GameApp::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &GameApp::OnBnClickedButton4)
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_MESSAGE(UM_SOCK, OnSock)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON6, &GameApp::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &GameApp::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON5, &GameApp::OnBnClickedButton5)
	ON_STN_CLICKED(IDC_HEADBITMAP, &GameApp::OnStnClickedHeadbitmap)
	ON_NOTIFY(NM_KILLFOCUS, IDC_TREE3, &GameApp::OnKillfocusTree3)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE3, &GameApp::OnSelchangedTree3)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &GameApp::OnSelchangedTree1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, &GameApp::OnDblclkTree1)
	ON_WM_TIMER()
	ON_WM_NCHITTEST()
	ON_WM_MOVING()
	ON_NOTIFY(TVN_SELCHANGING, IDC_TREE2, &GameApp::OnTvnSelchangingTree2)
	ON_EN_SETFOCUS(IDC_EDIT1, &GameApp::OnSetfocusEdit1)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE2, &GameApp::OnNMDblclkTree2)
	ON_NOTIFY(NM_RCLICK, IDC_TREE1, &GameApp::OnRclickTree1)
	ON_COMMAND(ID_1, &GameApp::On1)
	ON_BN_CLICKED(IDC_BUTTON2, &GameApp::OnBnClickedButton2)
END_MESSAGE_MAP()


// GameApp 消息处理程序


void GameApp::OnBnClickedButton1()
{
	if (!flist.IsWindowVisible())
	{
		CString str;
		findedit.GetWindowTextA(str);
		if (str == "") return;
		CFont font;
		font.m_hObject = GetStockObject(DEFAULT_GUI_FONT);
		flist.SetFont(&font);
		font.DeleteObject();
		flist.DeleteAllItems();
		flist.InsertItem("查找到的好友", -99, -99, TVI_ROOT);
		SearchmyFriend(str);

		SendMsg("Fid", App->MyName, str);

		CRect rc, ac;
		tlist1.GetClientRect(&ac);
		tlist1.MapWindowPoints(this, &rc);
		rc.right = ac.right;
		rc.bottom = ac.bottom;
		GetClientRect(&ac);
		rc.top -= 37;
		rc.bottom = ac.bottom;
		flist.MoveWindow(&rc);
		ShowHideFind(true);
	}
	else
	{
		ShowHideFind(false);
	}
	// TODO:  在此添加控件通知处理程序代码
}


void GameApp::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
//	SetFocus();
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));

	CDialogEx::OnLButtonDown(nFlags, point);
}


void GameApp::OnBnClickedButton3()
{
	this->DestroyWindow();
	// TODO:  在此添加控件通知处理程序代码
}


void GameApp::OnBnClickedButton4()
{
	WINDOWPLACEMENT lwndpl;
	WINDOWPLACEMENT * lpwndpl;
	lpwndpl = &lwndpl;
	GetWindowPlacement(lpwndpl);
	lpwndpl->showCmd = SW_SHOWMINIMIZED;
	SetWindowPlacement(lpwndpl);
}


BOOL GameApp::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	::ShellExecuteA(NULL, "open", "regsvr32.exe", "ImageOle.DLL /s", 0, 0);
	ModifyStyleEx(0, WS_EX_COMPOSITED, 0);

	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_ICON1));
	char *A = (char *)AfxGetAppName();

	strcpy_s(m_nid.szTip, A);
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
	// TODO:  在此添加额外的初始化

	HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP2));
	SetBackgroundImage(hBitmap);

	SetFontSize(IDC_EDIT1, 21);
	SetFontSize(IDC_BUTTON3, 18);
	SetFontSize(IDC_BUTTON4, 18);
	SetFontSize(IDC_STATICNICK, 90);
	SetFontSize(IDC_STATIC1, 20);
	SetFontSize(IDC_BUTTON5, 18);
	SetFontSize(IDC_BUTTON6, 18);
	SetFontSize(IDC_BUTTON7, 18);
	G_Button3.SetTextColor(RGB(220, 220, 220));
	G_Button4.SetTextColor(RGB(220, 220, 220));
	TButton1.SetTextColor(RGB(220, 220, 220));
	TButton2.SetTextColor(RGB(220, 220, 220));
	TButton3.SetTextColor(RGB(220, 220, 220));
	TButton1.SetmStye(1);
	TButton2.SetmStye(1);
	TButton3.SetmStye(1);
	G_Button3.Settm(0);
	G_Button4.Settm(0);

	M_Button1.SetmStye(IDB_BITMAP3);
	M_Button1.Settm(50);
	

	CreateImageList();
	CreateImageHead();

	App->S = Connect(this->m_hWnd);
	myFont.CreatePointFont(200, "MS Shell Dlg");
	GetUserInfo();
	tlist1.SetFocus();
	//unsigned int nDummy;
	//m_hThread = (HANDLE)_beginthreadex(NULL, 0, _ThreadAnimation, this,
	//	CREATE_SUSPENDED, &nDummy);

	return TRUE;  
}


void GameApp::GetUserInfo()
{
	SendMsg("Lgi", App->MyName, App->MyPd);
}
void GameApp::CreateImageList()
{
	App->imagelist1.Create(32,32, ILC_COLOR32, 2, 2);
	for (int i = 211; i <= 278; i++)
	{
		App->imagelist1.Add(AfxGetApp()->LoadIconA(i));
	}
	tlist1.SetImageList(&App->imagelist1, LVSIL_NORMAL);
	flist.SetImageList(&App->imagelist1, LVSIL_NORMAL);
	App->facelist1.Create(64, 64, ILC_COLOR32 | ILC_MASK, 2, 2);
	for (int i = 282; i <= 369; i++)
	{
		App->facelist1.Add(AfxGetApp()->LoadIconA(i));
	}
}
void GameApp::CreateImageHead()
{
	RECT rc;
	headicon.GetClientRect(&rc);
	App->imagelisthead.Create(rc.right - rc.left, rc.bottom - rc.top, ILC_COLOR32 | ILC_MASK, 2, 2);
	for (int i = 211; i <= 278; i++)
	{
		App->imagelisthead.Add(AfxGetApp()->LoadIconA(i));
	}

}

HTREEITEM GameApp::AddItem(HTREEITEM hRoot, CString TXT, UINT ImageList, int No)
{

	TV_INSERTSTRUCT TCItem;
	TCItem.hParent = hRoot;//增加根项
	TCItem.hInsertAfter = TVI_LAST;//在最后项之后
	TCItem.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;//设屏蔽
	TCItem.item.pszText = (LPSTR)(LPCSTR)TXT;
	TCItem.item.lParam = No;//序号 
	TCItem.item.iImage = ImageList;//正常图标
	TCItem.item.iSelectedImage = ImageList;//选中时图标
	return tlist1.InsertItem(&TCItem);
}
HTREEITEM GameApp::AddItemSearch(HTREEITEM hRoot, CString TXT, UINT ImageList, int No)
{

	TV_INSERTSTRUCT TCItem;
	TCItem.hParent = hRoot;//增加根项
	TCItem.hInsertAfter = TVI_LAST;//在最后项之后
	TCItem.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;//设屏蔽
	TCItem.item.pszText = (LPSTR)(LPCSTR)TXT;
	TCItem.item.lParam = No;//序号 
	TCItem.item.iImage = ImageList;//正常图标
	TCItem.item.iSelectedImage = ImageList;//选中时图标
	return flist.InsertItem(&TCItem);
}
void GameApp::SetFontSize(UINT IDC, int Size)
{
	CFont * f;
	f = new CFont;
	f->CreateFont(Size,            // nHeight 
		Size,           // nWidth 
		0,           // nEscapement 
		0,           // nOrientation 
		FW_BOLD,     // nWeight 
		TRUE,        // bItalic 
		FALSE,       // bUnderline 
		0,           // cStrikeOut 
		ANSI_CHARSET,              // nCharSet 
		OUT_DEFAULT_PRECIS,        // nOutPrecision 
		CLIP_DEFAULT_PRECIS,       // nClipPrecision 
		DEFAULT_QUALITY,           // nQuality 
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily 
		_T("新宋体"));              // lpszFac

	GetDlgItem(IDC)->SetFont(f);
	delete[] f;
}


LRESULT GameApp::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
		case WM_RBUTTONUP:                                        // 右键起来时弹出菜单
			{

				LPPOINT lpoint = new tagPOINT;
				::GetCursorPos(lpoint);                    // 得到鼠标位置
				CMenu menu;
				menu.CreatePopupMenu();                    // 声明一个弹出式菜单
				menu.AppendMenu(MF_STRING, WM_DESTROY, (LPCTSTR)(CString)"关闭");
				menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
				HMENU hmenu = menu.Detach();
				menu.DestroyMenu();
				delete lpoint;
			}
			break;

		case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
			{
				int shinrkid = GetShinkId();
				if (shinrkid >= 0)
				{
					talktotalk *dlg = new talktotalk;
					dlg->Create(IDD_TALKTOTALK, this);
					dlg->ShowWindow(SW_SHOW);
					dlg->TalkId = shinrkid;
					dlg->MyNick = MyNick;
					dlg->InitUser();
					break;
				}
				if (ShowMsg()) break;
				this->ShowWindow(SW_RESTORE||5);         // 显示主窗口
				this->SetForegroundWindow();
			}
			break;
		case WM_LBUTTONUP:                          // 双击左键的处理
			{						   
				this->ShowWindow(5);         // 显示主窗口
			}
			break;
	}
	return 0;
}

bool GameApp::ShowMsg()
{
	if (System.num > 0)
	{
		MsgDiaglog *dlg = new MsgDiaglog;
		dlg->Create(IDD_MSG, this);
		dlg->ShowWindow(SW_SHOW);
		int i = System.num - 1;
		dlg->TalkId = atoi(System.obj[i][2]);
		if (System.obj[i][4] == "1")
		{

			dlg->MyNick.Format("%s(%.8d)向您发出好友邀请，是否接受请求？",
				System.obj[i][1], dlg->TalkId);
			dlg->msg.SetWindowTextA(System.obj[i][5]);
		}
		else if (System.obj[i][4] == "2")
		{
			if (System.obj[i][5] == "1")
				dlg->MyNick.Format("%s(%.8d)已经成功加为你的好友了！",
				System.obj[i][1], dlg->TalkId);
			else
				dlg->MyNick.Format("%s(%.8d)拒绝了你的好友邀请！",
				System.obj[i][1], dlg->TalkId);
			dlg->msg.SetReadOnly(true);
		}
		else if (System.obj[i][4] == "3")
		{
			dlg->MyNick = "您好！服务器向您发布了一则系统公告！！";
			dlg->msg.ReplaceSel(System.obj[i][5]);
			//dlg->msg.SetReadOnly(true);
		}
		dlg->IconId = atoi(System.obj[i][3]);
		dlg->Type = atoi(System.obj[i][4]);

		dlg->InitUser();
		System.num -= 1;
		return true;
	}
	return false;
}

BOOL GameApp::DestroyWindow()
{
	    Shell_NotifyIcon(NIM_DELETE, &m_nid);
		myFont.DeleteObject();
		WCleanup(App->S);
		ExitProcess(0);
		return CDialogEx::DestroyWindow();
}


void GameApp::OnSize(UINT nType, int cx, int cy)
{
	
	CDialogEx::OnSize(nType, cx, cy);
	CRgn m_rgn;
	CRect rc;
	GetWindowRect(&rc); //获得窗口矩形
	rc -= rc.TopLeft();
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 8, 8); //根据窗口矩形创建一个圆角矩形
	SetWindowRgn(m_rgn, TRUE);
	DeleteObject(m_rgn);


}


HBRUSH GameApp::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
		if (nCtlColor == CTLCOLOR_STATIC)
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(RGB(0xE0, 0xE0, 0xE0));
			return (HBRUSH)::GetStockObject(NULL_BRUSH);
		}
		
		
		return hbr;	// TODO:  在此更改 DC 的任何特性

		// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	}



void GameApp::OnBnClickedButton6()
{
	tlist1.ShowWindow(0);
	tlist1.DeleteAllItems();
	tlist1.ShowWindow(5);
	TButton2.SetDown(false);
	
	TButton3.SetDown(false);
	TButton2.InvalidateRect(NULL);
	TButton3.InvalidateRect(NULL);
	AddFriend();

	// TODO:  在此添加控件通知处理程序代码
}


void GameApp::OnBnClickedButton7()
{
	tlist1.DeleteAllItems();
	TButton1.SetDown(false);
	TButton3.SetDown(false);
	TButton1.InvalidateRect(NULL);
	TButton3.InvalidateRect(NULL);
	// TODO:  在此添加控件通知处理程序代码
}


void GameApp::OnBnClickedButton5()
{
	tlist1.DeleteAllItems();
	TButton1.SetDown(false);
	TButton2.SetDown(false);
	TButton1.InvalidateRect(NULL);
	TButton2.InvalidateRect(NULL);
	// TODO:  在此添加控件通知处理程序代码
}

void GameApp::Wstartup()
{
	WSADATA Data;

	WSAStartup(0x202, &Data);

}
void GameApp::WCleanup(LONG S)
{
	closesocket(S);
	WSACleanup(); //关闭 Winsock
}
int GameApp::Connect(HWND Hw)
{
	SOCKET S;
	S = socket(AF_INET, 1, 0); //创建套接字，s 是socket功能返回的文件描述符
	if (S < 1)
	{
		WCleanup(S);
		return 0;
	}
	CMFCApplication2Dlg Dlg;
	Sock.sin_family = AF_INET; //socket类型
	CString IP = Dlg.GetIni("URL", "IP", "");
	if (IP.IsEmpty()) IP = "192.168.1.188";

	Sock.sin_addr.S_un.S_addr = inet_addr(IP); //所用的IP地119.75.217.56

	Sock.sin_port = htons(5556);
	int Res = connect(S, (struct sockaddr*)&Sock, sizeof(Sock)); //绑定端口
	if (Res != 0) {
		WCleanup(S);
		return 0;
	}
	Res = WSAAsyncSelect(S, Hw, UM_SOCK, 1 | FD_CLOSE);
	return S;
}

int GameApp::SendMsg(CString head, CString User, CString Info)
{
	msgHead MSG;
	strcpy_s(MSG.head, (LPSTR)(LPCTSTR)head);
	strcpy_s(MSG.UserMsg, User.GetBuffer(0));
	MSG.UserLen = User.GetLength();
	MSG.MaxLenth = Info.GetLength();
	int hlen = sizeof(msgHead);
	int len = hlen + Info.GetLength();
	byte *FF = new byte[len];
	CopyMemory(FF, &MSG, hlen);
	CopyMemory(FF + hlen, Info.GetBuffer(0), Info.GetLength());
	int Res = send(App->S, (char*)FF, len, NULL);
	delete[] FF;
	return Res;
}
LRESULT GameApp::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch (WSAGETSELECTEVENT(lParam))
	{
		case FD_READ:
		{
			//unsigned int nDummy;

			//m_hThread = (HANDLE)_beginthreadex(NULL, 0, ServerThread, this, 0, &nDummy);
			GetMessageSock();
			break;
		}
		case FD_CLOSE:
		{
			AfxMessageBox("服务器断开连接！\n");
			this->DestroyWindow();
			break;
		}
	}
	return 1;
}
unsigned int __stdcall GameApp::ServerThread(void* pvParam) {
	GameApp* app = (GameApp*)pvParam;
	app->GetMessageSock();
	_endthreadex(0);
	CloseHandle(app->m_hThread);
	return 1;
}
void GameApp::GetMessageSock()
{
	long Rec;
	int ReMsg;
	CString Msg;

	byte* buff = Recibir(App->S, &Rec);
	byte *buf = buff;
	long bufRec = Rec;
	do
	{
		if (Rec < sizeof(msgHead))
			ReMsg = -1;
		else
			ReMsg = GetMsgHead(buff);

		switch (ReMsg)
		{
			case -1:
			{
					   Rec = RevPic(buff, Rec);
					   break;
			}
			case 3:
			{
					  RevPic(buff, Rec);
					  break;
			}
			case 0:
			{
					  Msg = GetMsg(buff, Rec);
					  InitUser(Msg);
					  break;
			}
			case 1:
			{
					  Msg = GetMsg(buff, Rec);
					  SendMsg("Rek", App->MyName, "");
					  break;
			}
			case 2:
			{
					  SendHead head;
					  CopyMemory(&head, buff, sizeof(head));
					  CString ComeUser = head.UserMsg;
					  ComeUser = ComeUser.Left(head.UserLen);
					  int msgid = SearchFriend(ComeUser);
					  if (msgid == -1) return;
					  Msg = GetMsg(buff, Rec);
					  int i = App->msg[msgid].num;
					  App->msg[msgid].obj[i].msg = Msg;
					  App->msg[msgid].obj[i].objnum = 0;
					  App->msg[msgid].num++;
					  SetTimer(1, 500, NULL);
					  break;
			}
			case 4:
			{
					  Msg = GetMsg(buff, Rec);
					  if (Msg != "Faild")
						  ShowSearchUser(Msg);
					  else
						  findedit.SetWindowTextA("没有找到匹配的好友");
					  break;
			}
			case 5:
			{
					  Msg = GetMsg(buff, Rec);
					  GetAdFriend(Msg);
					  break;
			}
			case 6:
			{
					  Msg = GetMsg(buff, Rec);
					  ReciveFriend(Msg);
					  break;
			}
			case 7:
			{
					  Msg = GetMsg(buff, Rec);
					  SysSpeaker(Msg);
					  break;
			}
			case 8:
			{
					  AfxMessageBox("账号重复登录！\n");
					  this->DestroyWindow();
					  break;
			}
		}
		if (ReMsg >= 0)
		{
			msgHead pHead;
			memcpy(&pHead, buff, sizeof(msgHead));
			int hLen = sizeof(msgHead);
			int mLen = pHead.MaxLenth;
			Rec = Rec - mLen - hLen;
			buff = buff + mLen + hLen;
		}
		else
		{
			if (Rec > 0)
			{
				buff += bufRec - Rec;
				bufRec = Rec;
			}
		}
	} while (Rec > 0);
	delete[] buf;
}
void GameApp::SysSpeaker(CString Msg)
{
	System.obj[System.num][0] = "系统公告";
	System.obj[System.num][1] = "系统公告";
	System.obj[System.num][2] = "0";
	System.obj[System.num][3] = "SyS";
	System.obj[System.num][4] = "3";
	System.obj[System.num][5] = Msg;
	System.num += 1;
	SetTimer(2, 500, NULL);
}

void GameApp::ReciveFriend(CString Msg)
{
	CMFCApplication2Dlg dlg;
	std::vector<CString> Fr = dlg.Split(Msg, "|");
	std::vector<CString> sr = dlg.Split(Fr[0], ",");
	System.obj[System.num][0] = sr[0];
	System.obj[System.num][1] = sr[1];
	System.obj[System.num][2] = sr[2];
	System.obj[System.num][3] = sr[3];
	System.obj[System.num][4] = "2";
	System.obj[System.num][5] = Fr[1];
	System.num += 1;
	SetTimer(2, 500, NULL);
	if (Fr[1]=="1") GetUserInfo();
}
void GameApp::ShowSearchUser(CString Msg)
{
	UINT i;
	CMFCApplication2Dlg dlg;
	flist.InsertItem("其他非好友联系人", -2, -2, TVI_ROOT);
	if (Msg.Find("|") > 0)
	{
		std::vector<CString> Fr = dlg.Split(Msg, "|");
		for (i = 0; i < Fr.size(); i++)
		{
			ShowFindUser(Fr[i]);
		}
	}
	else
	{
		ShowFindUser(Msg);
	}

}
void GameApp::SearchmyFriend(CString Msg)
{
	int i, k;
	CString str;
	for (i = 0; i <= 99; i++)
	{
		if (App->Friend[i][2] == "") continue;
		str.Format("%.8d", atoi(App->Friend[i][2]));
		if (App->Friend[i][1].Find(Msg) >= 0 || str.Find(Msg) >= 0)
		{
			str.Format("%s(%.8d)", App->Friend[i][1], atoi(App->Friend[i][2]));
			k = atoi(App->Friend[i][3]);
			AddItemSearch(TVI_ROOT, str, k, i);
		}
	}
}
void GameApp::ShowHideFind(bool s)
{
	int a, b;
	if (s)
	{
		a = 0;
		b = 5;
		M_Button1.SetmStye(IDB_BITMAP7);
		M_Button1.Settm(100);
		findedit.SetR(false);
		M_Button1.SetR(false);
	}
	else
	{
		a = 5;
		b = 0;
		M_Button1.SetmStye(IDB_BITMAP3);
		M_Button1.Settm(50);
		findedit.SetR(true);
		M_Button1.SetR(true);
	}
	findedit.Invalidate();
	M_Button1.Invalidate();
	tlist1.ShowWindow(a);
	TButton1.ShowWindow(a);
	TButton2.ShowWindow(a);
	TButton3.ShowWindow(a);
	flist.ShowWindow(b);
}
void GameApp::ShowFindUser(CString str)
{
	std::vector<CString> k;
	CMFCApplication2Dlg dlg;
	int i, n;
	k = dlg.Split(str, ",");
	n = atoi(k[2]);
	str.Format("%s(%.8d)", k[1], n);
	i = atoi(k[3]);
	AddItemSearch(TVI_ROOT, str, i, -n-1);
}
CString GameApp::GetMsg(byte *buff, int Rec)
{
	msgHead head;
	memcpy(&head, buff, sizeof(msgHead));
	int hLen = sizeof(msgHead);
	int mLen = head.MaxLenth;
	char tmp[MAX_SENDMSG_LENGTH];
	memcpy(tmp, buff + hLen, mLen);
	tmp[mLen] = 0;
	return (CString)(LPCSTR)tmp;
}
int GameApp::GetMsgHead(byte *buff)
{
	msgHead head;
	memcpy(&head, buff, sizeof(msgHead));
	return CheckHead(head);
}
int GameApp::CheckHead(msgHead Head)
{
	Head.head[3] = 0;
	CString str = (CString)(LPCSTR)Head.head;
	if (str == "Int") return 0;
	if (str == "Chk") return 1;
	if (str == "Tak") return 2;
	if (str == "Pic") return 3;
	if (str == "Fid") return 4;
	if (str == "AdF") return 5;
	if (str == "AdR") return 6;
	if (str == "SyS") return 7;
	if (str == "LoF") return 8;
	return -1;
}
long GameApp::RevPic(byte *buff, long Rec)
{
	int ReRev = 0;
	if (!App->RecPic[RevPicId].Start)
	{
		SendHead head;
		CopyMemory(&head, buff, sizeof(head));
		CString ComeUser = head.UserMsg;
		
		ComeUser = ComeUser.Left(head.UserLen);
		RevPicId = SearchFriend(ComeUser);
		if (RevPicId == -1) return 0;
			;

		App->RecPic[RevPicId].MaxLen = head.MaxLenth;
		App->RecPic[RevPicId].RevLen = 0;
		App->RecPic[RevPicId].Start = true;

		CopyMemory(App->RecPic[RevPicId].Pic, head.Pic, sizeof(PicInfo)* head.ObjNum);
		CheckNewFolder(".Cache");
		App->RecPic[RevPicId].ObjNum = head.ObjNum;
		App->RecPic[RevPicId].RevNum = 0;
		App->RecPic[RevPicId].Talk = "";
		buff = buff + sizeof(SendHead);
		Rec = Rec - sizeof(SendHead);
		ReRev = NewRevFile(buff);
	}
	int re = 0;
	int Max = App->RecPic[RevPicId].MaxLen;
	
    do
	{ 
		int i = App->RecPic[RevPicId].RevNum - 1;
		int max = App->RecPic[RevPicId].Pic[i].MaxLen;
		int remain = max - App->RecPic[RevPicId].obj[i].RevLen;
		re = Rec - remain;
		HANDLE hFile = CreateFile(App->RecPic[RevPicId].obj[i].strpath,
			GENERIC_WRITE, FILE_SHARE_WRITE, 0, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			App->RecPic[RevPicId].Start = false;
			if (re < 0)
				Rec = 0;
			else
			{
				buff = buff + remain;
				Rec = re;
			}
			return Rec;
		}
		SetFilePointer(hFile, 0, NULL, FILE_END);

		if (remain < Rec) Rec = remain;
		DWORD Send;
		WriteFile(hFile, buff, Rec, &Send, NULL);
		CloseHandle(hFile);
		App->RecPic[RevPicId].RevLen = App->RecPic[RevPicId].RevLen + Rec;
		App->RecPic[RevPicId].obj[i].RevLen = App->RecPic[RevPicId].obj[i].RevLen + Rec;
		ReRev = 0;
		buff = buff + remain;
		if (App->RecPic[RevPicId].obj[i].RevLen >= max)
		{
			ReRev = NewRevFile(buff);
		}
		Rec = re < 0 ? 0: re;
	} while (ReRev == 1);
	if (App->RecPic[RevPicId].RevLen < Max && ReRev == 2)
	{
		int len = Max - App->RecPic[RevPicId].RevLen;
		char tmp[MAX_SENDMSG_LENGTH];
		CopyMemory(tmp, buff, len);
		tmp[len] = 0;
		App->RecPic[RevPicId].Talk = (CString)(LPCSTR)tmp;
		App->RecPic[RevPicId].RevLen = App->RecPic[RevPicId].RevLen + len;
		Rec = Rec - len;
	}
	if (App->RecPic[RevPicId].RevLen >= Max)
	{
		App->RecPic[RevPicId].Start = false;
		int objID = App->msg[RevPicId].num;

		App->msg[RevPicId].obj[objID].msg = App->RecPic[RevPicId].Talk + "/Pic";

		App->msg[RevPicId].obj[objID].objnum = App->RecPic[RevPicId].ObjNum;

		for (int k = 0; k <= App->RecPic[RevPicId].ObjNum - 1; k++)
		{
			App->msg[RevPicId].obj[objID].obj[k].Sel = App->RecPic[RevPicId].Pic[k].Sel;
			App->msg[RevPicId].obj[objID].obj[k].strpath = App->RecPic[RevPicId].obj[k].strpath;
			App->msg[RevPicId].obj[objID].obj[k].Type = App->RecPic[RevPicId].obj[k].Type;
		}
		App->msg[RevPicId].num++;
		SetTimer(1, 500, NULL);
	}
	return Rec;
}
int GameApp::GetShinkId()
{
	for (int i = 0; i <= 99; i++)
	{
		if (App->msg[i].num > 0) return i;
	}
	return -1;
}
int GameApp::NewRevFile(byte* buff)
{
	if (App->RecPic[RevPicId].RevNum >= App->RecPic[RevPicId].ObjNum) return 2;
	CString lpszFilePah;
	int SJS;
	ULONG RND;
	SJS = rand() % 10000;
	RND = GetTickCount();
	lpszFilePah.Format(".Cache\\%d&%d%d.", RND, SJS, App->RecPic[RevPicId].RevNum);
	CString T = GetType(buff);
	lpszFilePah = lpszFilePah + T;
	App->RecPic[RevPicId].obj[App->RecPic[RevPicId].RevNum].strpath = lpszFilePah;
	App->RecPic[RevPicId].obj[App->RecPic[RevPicId].RevNum].Type = T;
	App->RecPic[RevPicId].obj[App->RecPic[RevPicId].RevNum].RevLen = 0;
	App->RecPic[RevPicId].RevNum++;
	return 1;
}

int GameApp::SearchFriend(CString ComeUser)
{
	int i;
	for (i = 0; i <= 99; i++)
	{
		if (App->Friend[i][0] == ComeUser) break;
	}
	if (i == 100) return -1;
	return i;
}
CString GameApp::GetType(byte *buff)
{
	byte buf1, buf2;
	CString tmp = "000000";
	char *head = (LPSTR)(LPCTSTR)tmp;
	CopyMemory(&buf1, buff, 1);
	CopyMemory(&buf2, buff + 1, 1);
	if (buf1 == 0xFF && buf2 == 0xD8) return "jpg";
	if (buf1 == 0x42 && buf2 == 0x4D) return "bmp";
	CopyMemory(head, buff, 6);
	if (strcmp(head, "GIF89a") >= 0 || strcmp(head, "GIF87a") >= 0) return "gif";
	return "bmp";
}
void GameApp::CheckNewFolder(CString strpath)
{
	if (!CreateDirectory(strpath, NULL))
	{
		DWORD dwError = GetLastError();
		if (ERROR_PATH_NOT_FOUND == dwError)
		{
			AfxMessageBox(_T("目录创建不成功！"));
			return;
		}
	}
}


void GameApp::InitUser(CString Msg)
{
	CMFCApplication2Dlg dlg;
	unsigned int i = 0;
	std::vector<CString> k;
	std::vector<CString> lines = dlg.Split(Msg, "-");
	CFont font;
	font.m_hObject = GetStockObject(DEFAULT_GUI_FONT);
	tlist1.SetFont(&font);
	font.DeleteObject();
	tlist1.DeleteAllItems();
	ClearFriend();
	if (!lines[0].IsEmpty() && lines[0] != "0")
	{
		if (lines[0].Find("|") > 0)
		{
			std::vector<CString> Fr = dlg.Split(lines[0], "|");
			for (i = 0; i < Fr.size(); i++)
			{
				k = dlg.Split(Fr[i], ",");
				App->Friend[i][0] = k[0];
				App->Friend[i][1] = k[1];
				App->Friend[i][2] = k[2];
				App->Friend[i][3] = k[3];
			}
		}
		else
		{
			k = dlg.Split(lines[0], ",");
			App->Friend[0][0] = k[0];
			App->Friend[0][1] = k[1];
			App->Friend[0][2] = k[2];
			App->Friend[0][3] = k[3];
		}
		AddFriend();
	}

	i = atoi(lines[4]);
	headicon.ModifyStyle(0xF, SS_ICON |SS_CENTERIMAGE);
	headicon.SetIcon(App->imagelisthead.ExtractIconA(i));
	myheadid = i;
	SetDlgItemTextA(NickName.GetDlgCtrlID(), lines[1]);
	MyNick = lines[1];
	CString Desc = "金币：" + lines[3];
	Gold.SetWindowTextA(Desc);

	i = atoi(lines[2]);
	Desc.Format("ID:%.8d", i);
	numid.SetWindowTextA(Desc);

	font.m_hObject = GetStockObject(DEFAULT_GUI_FONT);
	Gold.SetFont(&font);
	font.DeleteObject();

	NickName.SetFont(&myFont);
	
}
void GameApp::ClearFriend()
{
	for (int i = 0; i <= 99; i++)
	{
		for (int j = 0; j <= 3; j++)
			App->Friend[i][j] = "";
	}
}
void GameApp::AddFriend()
{
	int i, k;
	CString str;
	tlist1.SetItemHeight(38);
	for (i = 0; i <= 99; i++)
	{
		if (App->Friend[i][0].IsEmpty() || App->Friend[i][0]=="0") return;
		k = atoi(App->Friend[i][2]);
		str.Format("%s(%.8d)", App->Friend[i][1], k);
		k = atoi(App->Friend[i][3]);
		AddItem(TVI_ROOT, str, k, i);
	}

}

byte* GameApp::Recibir(LONG S, long *Rev)
{
	byte buff[MAX_MSG_LENGTH];
	long Res = recv(S, (char*)buff, MAX_MSG_LENGTH, NULL); //接收信息
	if (Res == -1) {
		WCleanup(S);
		return 0;
	}
	byte *buf = new byte[Res];
	CopyMemory(buf, buff, Res);
	*Rev = Res;
	return buf;
}

void GameApp::OnStnClickedHeadbitmap()
{
	if (!headlist.IsWindowVisible())
	{
		SetHeadList();
		RECT ac;
		CRect rc;
		headicon.GetClientRect(&ac);
		CPoint pt(0, 0);
		headicon.MapWindowPoints(this, &pt, 1);
		headlist.GetWindowRect(&rc);
		headlist.MoveWindow(pt.x, pt.y + ac.bottom, rc.Width(), rc.Height());
		headlist.SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		HTREEITEM hItem = headlist.GetRootItem();
		for (int i = 1; i <= myheadid; i++)
		{
			hItem = headlist.GetNextSiblingItem(hItem);
		}
		headlist.SelectItem(hItem);
		headlist.SetFocus();
		SetControlEnabled(FALSE);
	}
	else
	{
		SetControlEnabled(true);
	}
	
}
void GameApp::SetControlEnabled(BOOL A)
{

	TButton1.EnableWindow(A);
	TButton2.EnableWindow(A);
	TButton3.EnableWindow(A);
	int B;
	if (A)
		B = 5;
	else
		B = 0;
	findedit.EnableWindow(A);
	findedit.ShowWindow(B);
	tlist1.ShowWindow(B);
	if (A)
	{
		CString str;
		str.Format(_T("%d"), myheadid);
		SendMsg("Ico", App->MyName, str);
		headlist.ShowWindow(0);
		ModifyStyleEx(0, WS_EX_COMPOSITED, 0);
	}
	else
	{
		ModifyStyleEx(WS_EX_COMPOSITED, 0, 0);
		headlist.ShowWindow(5);
	}
		
}

void GameApp::SetHeadList()
{
	headlist.SetImageList(&App->imagelisthead, LVSIL_NORMAL);
	for (int i = 0; i <= 67; i++)
	{
		TV_INSERTSTRUCT TCItem;
		TCItem.hParent = TVI_ROOT;//增加根项
		TCItem.hInsertAfter = TVI_LAST;//在最后项之后
		TCItem.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE;//设屏蔽
		TCItem.item.lParam = 0;//序号 
		TCItem.item.iImage = i;//正常图标
		TCItem.item.iSelectedImage = i;//选中时图标
		headlist.InsertItem(&TCItem);
	}
}

void GameApp::OnKillfocusTree3(NMHDR *pNMHDR, LRESULT *pResult)
{
	//SetControlEnabled(true);
	*pResult = 0;
}

void GameApp::OnSelchangedTree3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hItem;
	hItem = headlist.GetSelectedItem();
	if (hItem == NULL) return;
	int count, f;
	headlist.GetItemImage(hItem, count, f);
	headicon.SetIcon(App->imagelisthead.ExtractIconA(count));
	myheadid = count;
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
}


BOOL GameApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void GameApp::OnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	*pResult = 0;
}


void GameApp::OnDblclkTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	HTREEITEM hItem = tlist1.GetSelectedItem();
	if (hItem == NULL) return;
	TVITEMA A;
	A.hItem = hItem;
	A.mask = TVIF_PARAM;
	tlist1.GetItem(&A);

	CWnd *hw = FindControlWnd(this, App->Friend[A.lParam][1], A.lParam);
	if (hw != NULL)
	{
		hw->SetForegroundWindow();
		return;
	}
	talktotalk *dlg = new talktotalk;
	dlg->Create(IDD_TALKTOTALK, this);
	dlg->ShowWindow(SW_SHOW);
	dlg->TalkId = A.lParam;
	dlg->MyNick = MyNick;
	dlg->InitUser();
	*pResult = 0;
}


void GameApp::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnTimer(nIDEvent);
	if (nIDEvent == 1)
	{
		int icon;
		int shinrkid = GetShinkId();
		if (shinrkid >= 0)
		{
			icon = atoi(App->Friend[shinrkid][3]);
			CWnd *Hw = FindControlWnd(this, App->Friend[shinrkid][1], shinrkid);
			if (Hw != NULL)
			{
				talktotalk* TalkApp = (talktotalk *)Hw;
				for (int k = App->msg[shinrkid].num - 1; k >= 0; k--)
				{
					CString str = TalkApp->SetStr(App->Friend[shinrkid][1],
						App->msg[shinrkid].obj[k].msg);
					//text1.InserPic(shinrkid);
					TalkApp->SetTalkFormat(str);
				}
				App->msg[shinrkid].num = 0;
				return;
			}
			Shinrk(icon);
		}
		else
		{
			KillTimer(1);
			m_nid.hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
			int m = Shell_NotifyIcon(NIM_MODIFY, &m_nid);
		}
	}

	if (nIDEvent == 2)
	{
		if (System.num > 0)
		{
			Shinrk(375);
		}
		else
		{
			KillTimer(2);
			m_nid.hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
			int m = Shell_NotifyIcon(NIM_MODIFY, &m_nid);
		}
	}
}
void GameApp::Shinrk(int shinrkIcon)
{
	if (m_bIsIcon)
	{
		if (shinrkIcon == 375)
			m_nid.hIcon = AfxGetApp()->LoadIcon(shinrkIcon);
		else
			m_nid.hIcon = App->imagelisthead.ExtractIconA(shinrkIcon);
		int m = Shell_NotifyIcon(NIM_MODIFY, &m_nid);
		m_bIsIcon = false;
	}
	else
	{
		m_nid.hIcon = AfxGetApp()->LoadIcon(1);
		int m = Shell_NotifyIcon(NIM_MODIFY, &m_nid);
		m_bIsIcon = true;
	}
}

void GameApp::SendPic(CString Header, ObjSend obj, CString Info)
{
	SendHead Head;
	int i, ret, talklen;
	TRANSMIT_FILE_BUFFERS transFileBuf = { 0 };
	HANDLE hFile;

	strcpy_s(Head.head, "Pic");
	strcpy_s(Head.UserMsg, (LPSTR)(LPCTSTR)Header);
	Head.UserLen = Header.GetLength();
	Head.ObjNum = obj.num;
	Head.MaxLenth = 0;
	for (i = 0; i <= obj.num - 1; i++)
	{
		hFile = CreateFile(obj.obj[i].strpath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		Head.Pic[i].MaxLen = GetFileSize(hFile, NULL);
		CloseHandle(hFile);
		Head.MaxLenth = Head.MaxLenth + Head.Pic[i].MaxLen;
		Head.Pic[i].Sel = obj.obj[i].Sel;
	}
	transFileBuf.Head = &Head;
	transFileBuf.HeadLength = sizeof(Head);
	talklen = Info.GetLength();
	if (talklen > 0)
	{
		Head.MaxLenth = Head.MaxLenth + talklen;
		if (obj.num == 1)
		{
			transFileBuf.Tail = (LPSTR)(LPCTSTR)Info;
			transFileBuf.TailLength = talklen;
		}
	}
	hFile = CreateFile(obj.obj[0].strpath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ret = TransmitFile(App->S, hFile, 0, 0, NULL, &transFileBuf, TF_USE_DEFAULT_WORKER);
	CloseHandle(hFile);
	if (obj.num == 1) return;
	for (i = 1; i <= obj.num - 2; i++)
	{
		hFile = CreateFile(obj.obj[i].strpath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		ret = TransmitFile(App->S, hFile, 0, 0, NULL, NULL, TF_USE_KERNEL_APC | TF_WRITE_BEHIND);
		CloseHandle(hFile);
	}
	transFileBuf.Head = NULL;
	transFileBuf.HeadLength = 0;
	if (talklen > 0)
	{
		transFileBuf.Tail = (LPSTR)(LPCTSTR)Info;
		transFileBuf.TailLength = talklen;
	}
	i = obj.num - 1;
	hFile = CreateFile(obj.obj[i].strpath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ret = TransmitFile(App->S, hFile, 0, 0, NULL, &transFileBuf, TF_USE_KERNEL_APC | TF_WRITE_BEHIND);
	CloseHandle(hFile);

}

void GameApp::myTransmitFile(SOCKET hSocket, HANDLE hFile, LPTRANSMIT_FILE_BUFFERS lpTransmitBuffers)
{
	int Res = 5000;
	int first = Res;
	int filestart = 0;
	DWORD read;
	byte *buff = new byte[Res];
	if (lpTransmitBuffers != NULL)
	{
		filestart = lpTransmitBuffers->HeadLength;
		CopyMemory(buff, lpTransmitBuffers, filestart);
		first = Res - filestart;
	}
	ReadFile(hFile, buff + filestart, first, &read, NULL);
	send(hSocket, (char*)buff, Res, NULL);
	delete[] buff;
}



LRESULT GameApp::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	return CDialogEx::OnNcHitTest(point);
}


void GameApp::OnMoving(UINT fwSide, LPRECT pRect)
{
	CDialogEx::OnMoving(fwSide, pRect);
	int   cx = GetSystemMetrics(SM_CXSCREEN);
	CRect rc;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &rc, 0);
	int cy = rc.Height();
	int w = pRect->right - pRect->left;

	if (pRect->top <= 0) //在上边有效距离内，自动靠拢。  
	{
		pRect->bottom -= pRect->top;
		pRect->top = 0;
	}
	else if (pRect->left <= 0) //在左边有效距离内  
	{
		pRect->right = w;
		pRect->left = 0;
		pRect->bottom = cy;
		pRect->top = 0;
	}
	else if (pRect->right >= cx) //在右边有效距离内，ScreenX为屏幕宽度，可由GetSystemMetrics(SM_CYSCREEN)得到。  
	{
		pRect->left = cx - w;
		pRect->right = cx;
		pRect->bottom = cy;
		pRect->top = 0;
	}

	CRect t1;
	tlist1.GetWindowRect(&t1);
	ScreenToClient(&t1);
	tlist1.MoveWindow(t1.left, t1.top, t1.Width(), pRect->bottom-pRect->top - t1.top);
	CString a;
	ClientToScreen(&t1);
	a.Format("%d\n", t1.left);
	TRACE(a);
}

void GameApp::OnTvnSelchangingTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	TCHAR szBuf[1024];
	TVITEM lvi = pNMTreeView->itemNew;
	lvi.mask = LVIF_TEXT;
	lvi.pszText = szBuf;
	lvi.cchTextMax = 1024;
	flist.GetItem(&lvi);
	CString str = lvi.pszText;
	if (str == "其他非好友联系人" || str == "查找到的好友")
		*pResult = 1;
	else
		*pResult = 0;
}


void GameApp::GetAdFriend(CString Msg)
{
	int i = Msg.Find("|");
	CString info = Msg.Left(i);
	CString InfoEx = Msg.Mid(i + 1);
	CMFCApplication2Dlg Dlg;
	std::vector<CString> Fr = Dlg.Split(info, ",");
	System.obj[System.num][0] = Fr[0];
	System.obj[System.num][1] = Fr[1];
	System.obj[System.num][2] = Fr[2];
	System.obj[System.num][3] = Fr[3];
	System.obj[System.num][4] = "1";
	System.obj[System.num][5] = InfoEx;
	System.num += 1;
	SetTimer(2, 500, NULL);
}


void GameApp::OnSetfocusEdit1()
{
	findedit.SetWindowTextA("");
	// TODO:  在此添加控件通知处理程序代码
}


void GameApp::OnNMDblclkTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hItem = flist.GetSelectedItem();
	if (hItem == NULL) return;
	TVITEMA A;
	A.hItem = hItem;
	A.mask = TVIF_PARAM | TVIF_IMAGE;
	flist.GetItem(&A);
	if (A.lParam >= 0)
	{
		talktotalk *dlg = new talktotalk;
		dlg->Create(IDD_TALKTOTALK, this);
		dlg->ShowWindow(SW_SHOW);
		dlg->TalkId = A.lParam;
		dlg->MyNick = MyNick;
		dlg->InitUser();
	}
	else
	{
		MsgDiaglog *dlg = new MsgDiaglog;
		CString str = flist.GetItemText(hItem);

		dlg->Create(IDD_MSG, this);
		dlg->ShowWindow(SW_SHOW);
		dlg->TalkId = abs(A.lParam + 1);
		dlg->MyNick = "是否向" + str + "发出好友邀请？";
		dlg->IconId = A.iImage;
		dlg->Type = 0;
		dlg->InitUser();
	}
	*pResult = 0;
}

void GameApp::OnRclickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint point;

	GetCursorPos(&point);

	CPoint pointInTree = point;

	tlist1.ScreenToClient(&pointInTree);

	HTREEITEM item;

	UINT flag = TVHT_ONITEM;

	item = tlist1.HitTest(pointInTree, &flag);

	if (item != NULL)

	{

		tlist1.SelectItem(item);

		CMenu menu;

		menu.LoadMenu(IDR_MENU2);

		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this, NULL);

	}
}


void GameApp::On1()
{
	HTREEITEM hItem = tlist1.GetSelectedItem();
	if (hItem == NULL) return;
	TVITEMA A;
	A.hItem = hItem;
	A.mask = TVIF_PARAM;
	tlist1.GetItem(&A);
	int i = A.lParam;
	SendMsg("DeF", App->MyName, App->Friend[i][0]);
}

CWnd* GameApp::FindControlWnd(CWnd* ParentWnd, CString Title, int id)
{
	CWnd *hChild = ParentWnd->GetWindow(GW_ENABLEDPOPUP);
	CString str;
	for (; hChild != NULL; hChild = hChild->GetWindow(GW_HWNDNEXT))
	{
		hChild->GetWindowTextA(str);
		if (str == Title)
		{
			talktotalk* App = (talktotalk *)hChild;
			if (App->TalkId == id) return hChild;
		}
	}
	return NULL;
}

void GameApp::OnBnClickedButton2()
{   
	DWORD pid;
	GetWindowThreadProcessId(m_hWnd, &pid);
	HANDLE Pro = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
}
