
// MFCApplication2Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMFCApplication2Dlg 对话框



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication2Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);

}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_pic);
	DDX_Control(pDX, IDC_STATIC2, m_ctrlPicture);
	DDX_Control(pDX, IDC_BUTTON1, m_Button1);
	DDX_Control(pDX, IDC_BUTTON2, m_Button2);
	DDX_Control(pDX, IDC_BUTTON3, m_Button3);
	DDX_Control(pDX, IDC_BUTTON4, m_Button4);
	DDX_Control(pDX, IDC_EDIT1, useredit);
	DDX_Control(pDX, IDC_EDIT2, pswdedit);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_MESSAGE(UM_SOCK, OnSock)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication2Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication2Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	ON_WM_DRAWITEM()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_STN_CLICKED(IDC_STATIC1, &CMFCApplication2Dlg::OnStnClickedStatic1)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
	ON_WM_SIZE()
	ON_EN_SETFOCUS(IDC_EDIT1, &CMFCApplication2Dlg::OnSetfocusEdit1)
	ON_BN_SETFOCUS(IDC_BUTTON2, &CMFCApplication2Dlg::OnSetfocusButton2)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	//设置静态控件的样式，使其可以使用位图，并试位标显示使居中
	m_ctrlPicture.ModifyStyle(0xF, SS_BITMAP);// | SS_CENTERIMAGE);
	m_ctrlPicture.SetBitmap(hBitmap);
	m_Button2.SetBkColor(RGB(0xD0, 0xD0, 0xD0));
	m_Button1.SetBkColor(RGB(0xD0, 0xD0, 0xD0));
	m_Button3.SetBkColor(RGB(0x80, 0x80, 0x80));
	m_Button3.SetTextColor(RGB(0xC0, 0xC0, 0xC0));
	m_Button4.SetBkColor(RGB(0x80, 0x80, 0x80));
	m_Button4.SetTextColor(RGB(0xC0, 0xC0, 0xC0));
	
	// TODO:  在此添加额外的初始化代码
	ReadIni();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication2Dlg::Wstartup()
{
	WSADATA Data;

	WSAStartup(0x202, &Data);

}
void CMFCApplication2Dlg::WCleanup(LONG S)
{
	closesocket(S);
	WSACleanup(); //关闭 Winsock
	

}
int CMFCApplication2Dlg::SendLogin(CString MSG,HWND Hw)
{
	

	 S = socket(AF_INET, 1, 0); //创建套接字，s 是socket功能返回的文件描述符


	if (S < 1)
	{
		WCleanup(S);
		return 0;
	}

  //	memset((char*)&Sock, sizeof(Sock), NULL);
	Sock.sin_family = AF_INET; //socket类型
	CString IP = GetIni((CString)"URL", (CString)"IP", (CString)"");
	if (IP.IsEmpty()) IP = "192.168.1.188";
		 
	Sock.sin_addr.S_un.S_addr = inet_addr(CStringToChar(IP)); //所用的IP地119.75.217.56
	Sock.sin_port = htons(5555);
	int Res = connect(S, (struct sockaddr*)&Sock, sizeof(Sock)); //绑定端口
	if (Res != 0) {
		WCleanup(S);
		return 0;
	}
	char *FF = CStringToChar(MSG);
	
	int Ret = send(S, FF, strlen(FF), NULL);
	Res = WSAAsyncSelect(S, Hw, UM_SOCK, 1); //设置套接字处于阻塞方式或者非阻塞方式,消息发送的窗口是 pic，即 Form1.Picture1
	return S;
}
LRESULT CMFCApplication2Dlg::OnSock(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
	case FD_READ:
	//	::AfxMessageBox(Recibirs(S));
		CString Msg = Recibir(S);
		CString ReMsg;
		if (Msg == "LoginSucess")
		{
			ReMsg = "登陆成功";
		}
		else if (Msg == "LoginFaild-2")
		{
			ReMsg = "用户名或密码错误";
		}
		else if (Msg == "LoginFaild-1")
		{
			ReMsg = "用户名错误";
		}
		else if (Msg == "RegFaild")
		{
			ReMsg = "注册失败";
		}
		else if (Msg == "RegSucess")
		{
			ReMsg = "注册成功";
		}
		//
		if (Msg == "LoginSucess")
		{
			GameApp Dlg;
			CMFCApplication2App* App = (CMFCApplication2App *)AfxGetApp();
			GetDlgItem(IDC_EDIT1)->GetWindowText(App->MyName);
			GetDlgItem(IDC_EDIT2)->GetWindowText(App->MyPd);
		
			this->ShowWindow(0);
			Dlg.DoModal();
			//this->DestroyWindow();
		}
		else
		{
			

			m_pic.Stop();
			AfxMessageBox(ReMsg); 
			GetDlgItem(IDC_BUTTON1)->ShowWindow(5);
			GetDlgItem(IDC_BUTTON2)->ShowWindow(5);
			m_Button1.Settm(100);
			m_Button2.Settm(100);
			m_Button3.Settm(100);
			m_Button4.Settm(100);
			m_Button1.InvalidateRect(NULL, FALSE);
			m_Button2.InvalidateRect(NULL, FALSE);
			m_Button3.InvalidateRect(NULL, FALSE);
			m_Button4.InvalidateRect(NULL, FALSE);
			GetDlgItem(IDC_EDIT1)->ShowWindow(5);
			GetDlgItem(IDC_EDIT2)->ShowWindow(5);

			GetDlgItem(IDC_STATIC)->ShowWindow(5);
			GetDlgItem(IDC_STATIC5)->ShowWindow(5);
		}
		
	}
	
	return 1;
}

CString CMFCApplication2Dlg::GetTime()
{
	sockaddr_in Sock;
	LONG Buf = 1;


	 S = socket(AF_INET, 1, 0); //创建套接字，s 是socket功能返回的文件描述符


	if (S < 1)
	{
		WCleanup(S);
		return 0;
	}
	// memset((char*)&Sock, sizeof(Sock), NULL);
	Sock.sin_family = AF_INET; //socket类型
	Sock.sin_addr.S_un.S_addr = inet_addr("112.127.115.32"); //所用的IP地119.75.217.56

	Sock.sin_port = htons(80);
	int Res = connect(S, (struct sockaddr*)&Sock, sizeof(Sock)); //绑定端口
	if (Res != 0) {
		WCleanup(S);
		return 0;
	}
	char FF[] = "GET / HTTP/1.1\r\n"
	"Accept: text/html, application/xhtml+xml, */*\r\n"
	"Accept-Language: zh-CN\r\n"
	"Referer: http://www.icetime.com.cn/\r\n"
	"User-Agent: Mozilla/5.0 (compatible; MSIE 10.0; Windows NT 6.2; WOW64; Trident/6.0)\r\n"
	"Host: www.icetime.com.cn\r\n"
	"Cache-Control: no-cache\r\n\r\n";

	int Ret = send(S, FF, sizeof(FF), NULL);
	closesocket(S);
	return Recibirs(S);
}
CString CMFCApplication2Dlg::Recibirs(LONG S)
{
	CHAR FF[4000]; //重定义缓冲区大小为 2000
	int Res = recv(S, FF, sizeof(FF), NULL); //接收信息
	if (Res == -1) {
		WCleanup(S);
		return 0;
	}
	std::vector<CString> lines = Split((CString)FF, (CString)"\r\n");
	for (unsigned int i = 0; i<lines.size(); i++) {
		//		AfxMessageBox(lines[i]);
		if (Instr(lines[i], (CString)"Date") >= 0) {
			CString Tmp = lines[i].Mid(6, lines[i].GetLength() - 6);
			//	AfxMessageBox(Tmp);

			int nYear, nMonth, nDate, nHour, nMin, nSec;
			//CHAR A[10];
			CHAR C[4], sMonth[4];
			sscanf_s(CStringToChar(Tmp), "%3s,%2d %3s %4d %2d:%2d:%2d GMT", C, 4, &nDate, sMonth, 4, &nYear, &nHour, &nMin, &nSec);
			nMonth = CMon((CString)sMonth);
			CTime T(nYear, nMonth, nDate, nHour, nMin, nSec);
			CTimeSpan TT(0, 8, 0, 0);
			T = T + TT;
			CString Ret = T.Format("%Y-%m-%d %H:%M:%S");
			return Ret;

			//	

			//	CTime t(nYear, nMonth, nDate, nHour, nMin, nSec);
		}
	}
	//   
	return 0;
}
CString CMFCApplication2Dlg::Recibir(LONG S)
{
	CHAR FF[4000]; //重定义缓冲区大小为 2000
	int Res = recv(S, FF, sizeof(FF), NULL); //接收信息
	if (Res == -1) {
		WCleanup(S);
		return 0;
	}
	CString Tmp = (CString)(LPCSTR)FF;
	Tmp = Tmp.Left(Res);
	closesocket(S);
		return Tmp;

}
int CMFCApplication2Dlg::CMon(CString A)
{
	if (A == "Jan")
		return 1;
	else if (A == "Feb")
		return 2;
	else if (A == "Mar")
		return 3;
	else if (A == "Apr")
		return 4;
	else if (A == "May")
		return 5;
	else if (A == "Jun")
		return 6;
	else if (A == "Jul")
		return 7;
	else if (A == "Aug")
		return 8;
	else if (A == "Sep")
		return 9;
	else if (A == "Oct")
		return 10;
	else if (A == "Nov")
		return 11;
	else if (A == "Dec")
		return 12;
	return 0;
}

std::vector<CString> CMFCApplication2Dlg::Split(CString oriStr, CString Plit)
{
	std::vector<CString> ret;
	int begin = 0;
	for (int i = 0; i <= oriStr.GetLength() - Plit.GetLength(); i++) {
		if (oriStr.Mid(i, Plit.GetLength()) == Plit) {
			CString ok = oriStr.Mid(begin, i - begin);
			ret.push_back(ok);
			begin = i + Plit.GetLength();
			i = begin - 1;
		}
	}
	if (begin < oriStr.GetLength()) {
		CString ok = oriStr.Mid(begin, oriStr.GetLength() - begin);
		ret.push_back(ok);
	}

	return ret;
}

int CMFCApplication2Dlg::Instr(CString str1, CString str2)
{
	for (int i = 0; i <= str1.GetLength() - str2.GetLength(); i++) {
		if (str1.Mid(i, str2.GetLength()) == str2) {
			return i;
		}
	}

	return -1;
}


void CMFCApplication2Dlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


int CMFCApplication2Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	//ReadIni();
	Wstartup();
	return 0;
}
void CMFCApplication2Dlg::SetiniSet(CString Name, CString Value)
{
	SetIni(Value, Name, (CString)"设置", NULL);
}
CString CMFCApplication2Dlg::ReadIniSet(CString Name)
{
	return GetIni(Name, (CString)"设置", (CString)"");
}
void CMFCApplication2Dlg::OnBnClickedButton1()
{
	CString Uname, Passwd,MSG;
	GetDlgItem(IDC_EDIT1)->GetWindowText(Uname);
	
	GetDlgItem(IDC_EDIT2)->GetWindowText(Passwd);
	MSG = Uname + "&" + Passwd;
	SendLogin(MSG,this->m_hWnd);
	if (m_pic.Load(MAKEINTRESOURCE(IDR_GIF1), _T("gif"))) m_pic.Draw();
	m_Button1.Settm(0);
	m_Button2.Settm(0);
	m_Button3.Settm(0);
	m_Button4.Settm(0);
	GetDlgItem(IDC_EDIT1)->ShowWindow(0);
	GetDlgItem(IDC_EDIT2)->ShowWindow(0);
	GetDlgItem(IDC_STATIC)->ShowWindow(0);
	GetDlgItem(IDC_STATIC5)->ShowWindow(0);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(0);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(0);

		// TODO:  在此添加控件通知处理程序代码
}


int CMFCApplication2Dlg::SetIni(CString KeyValue, CString KeyName, CString  KeyGroup, CString PathName)
{
	CString strKeyGroup, strPathName;
	strKeyGroup = (KeyGroup == "" ? (CString)"Setup" : KeyGroup);
	if (PathName = "") {
		char Path[1024] = { 0 };
		GetCurrentDirectory(sizeof(Path), (LPSTR)Path);
		strPathName = (CString)(LPCTSTR)Path;
		CString Tmp = (strPathName.Right(1) == "\\" ? (CString)"" : (CString)"\\");
		strPathName = strPathName + Tmp + (CString)"Set.ini";
	}
	else {
		strPathName = PathName;
	}
	return WritePrivateProfileString(strKeyGroup, KeyName, KeyValue, strPathName);
}

CString CMFCApplication2Dlg::GetIni(CString KeyName, CString KeyGroup, CString PathName)
{
		CString strKeyGroup, strPathName;
		char strRtn[255];
		strKeyGroup = (KeyGroup == "" ? (CString)"Setup" : KeyGroup);
		if (PathName = "")
		{
			char Path[1024] = { 0 };
			GetCurrentDirectory(sizeof(Path), (LPSTR)Path);
			strPathName = (CString)(LPCTSTR)Path;
			CString Tmp = (strPathName.Right(1) == "\\" ? (CString)"" : (CString)"\\");
			strPathName = strPathName + Tmp + (CString)"Set.ini";
		}
		else
		{
			strPathName = PathName;
		}
		int nSize = GetPrivateProfileString(strKeyGroup, KeyName, NULL,(LPSTR)strRtn, sizeof(strRtn), strPathName);
		if (nSize > 0)
		{
			CString Ret = (CString)(LPCTSTR)strRtn;
			return Ret.Left(nSize); 
		}
		return 0;
}

void CMFCApplication2Dlg::ReadIni()
{
	CalcCountVs((CString)"设置", (CString)".\\set.ini");
}
int CMFCApplication2Dlg::CalcCount(CString strPathName)
{
	TCHAR chSectionNames[2048] = { 0 };      //所有节名组成的字符数组
	char * pSectionName; //保存找到的某个节名字符串的首地址
	int i;      //i指向数组chSectionNames的某个位置，从0开始，顺序后移
	int j = 0;     //j用来保存下一个节名字符串的首地址相对于当前i的位置偏移量
	int count = 0;     //统计节的个数

	//CString name;
	//char id[20];
	::GetPrivateProfileSectionNames(chSectionNames, 2048, strPathName);
	
	for (i = 0; i<2048; i++, j++)
	{
		if (chSectionNames[0] == '\0')
			break;      //如果第一个字符就是0，则说明ini中一个节也没有
		if (chSectionNames[i] == '\0')
		{
			pSectionName = (char*)&chSectionNames[i - j]; //找到一个0，则说明从这个字符往前，减掉j个偏移量，
			//就是一个节名的首地址
			j = -1;        //找到一个节名后，j的值要还原，以统计下一个节名地址的偏移量
			//赋成-1是因为节名字符串的最后一个字符0是终止符，不能作为节名
			//的一部分

			//在获取节名的时候可以获取该节中键的值，前提是我们知道该节中有哪些键。
			AfxMessageBox((CString)(LPCWSTR)pSectionName);     //把找到的显示出来
			CalcCountVs((CString)(LPCWSTR)pSectionName, strPathName);
			if (chSectionNames[i + 1] == 0)
			{
				break;     //当两个相邻的字符都是0时，则所有的节名都已找到，循环终止
			}
		}

	}
	return count;
}
int CMFCApplication2Dlg::CalcCountVs(CString Tname, CString strPathName)
{
	TCHAR chValueNames[2048] = { 0 };      //所有节名组成的字符数组
	char * pName; //保存找到的某个节名字符串的首地址
	int a, b = 0;
	int count = 0;     //统计节的个数

	//CString name;
	//char id[20];
	GetPrivateProfileSection(Tname, chValueNames, 2048, strPathName);
	for (a = 0; a<2048; a++, b++)
	{
		if (chValueNames[0] == '\0')
			break;      //如果第一个字符就是0，则说明ini中一个节也没有
		if (chValueNames[a] == '\0')
		{
			pName = (char*)&chValueNames[a - b];
			b = -1;
			CString T = (CString)(LPCSTR)pName;
			int i = Instr(T, (CString) "=");
			CString ID, VA;
			ID = T.Left(i);
			VA = T.Mid(i+1);
			int IDC;
			IDC = atoi(CStringToChar(ID));
			GetDlgItem(IDC)->SetWindowText(VA);
			if (chValueNames[a + 1] == 0)
			{
				break;     //当两个相邻的字符都是0时，则所有的节名都已找到，循环终止
			}
		}

	}
	return count;
}

char* CMFCApplication2Dlg::CStringToChar(CString Tmp)
{
	return (LPSTR)(LPCTSTR)Tmp;
}


void CMFCApplication2Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	
    CString str;
	CWnd *pWnd = GetFocus(); //当前句柄
	 //获取控件ID
	if (pWnd == NULL) return;
	if (pWnd->GetParent() != this) return;
	int c = pWnd->GetDlgCtrlID();
	char B[5];
	_itoa_s(c, B, sizeof(B),10);
	pWnd->GetWindowText(str);
	SetiniSet((CString)(LPCSTR)B,str);
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	CString str;
	CWnd *pWnd = GetFocus(); //当前句柄
	//获取控件ID
	if (pWnd == NULL) return;
	if (pWnd->GetParent() != this) return;
	int c = pWnd->GetDlgCtrlID();
	char B[5];
	_itoa_s(c, B, sizeof(B), 10);
	pWnd->GetWindowText(str);
	SetiniSet((CString)(LPCSTR)B, str);
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnBnClickedButton2()
{
	RegWnd Dlg;
	//	this->ShowWindow(SW_HIDE);
	Dlg.DoModal();
}


HBRUSH CMFCApplication2Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0xC0, 0xC0, 0xC0));
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	
	return hbr;	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
}


void CMFCApplication2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SetFocus();
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication2Dlg::OnStnClickedStatic1()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnBnClickedButton3()
{
	CMFCApplication2Dlg::OnCancel();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnBnClickedButton4()
{
	WINDOWPLACEMENT lwndpl;
	WINDOWPLACEMENT * lpwndpl;
	lpwndpl = &lwndpl;
	GetWindowPlacement(lpwndpl);
	lpwndpl->showCmd = SW_SHOWMINIMIZED;
	SetWindowPlacement(lpwndpl);
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn m_rgn;
	CRect rc;
	GetWindowRect(&rc); //获得窗口矩形
	rc -= rc.TopLeft();
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 10, 10); //根据窗口矩形创建一个圆角矩形
	SetWindowRgn(m_rgn, TRUE);
	DeleteObject(m_rgn);
}


void CMFCApplication2Dlg::OnSetfocusEdit1()
{
	m_pic.Stop();
	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication2Dlg::OnSetfocusButton2()
{
	m_pic.Stop();
	// TODO:  在此添加控件通知处理程序代码
}


BOOL CMFCApplication2Dlg::PreTranslateMessage(MSG* pMsg)
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
