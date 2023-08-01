
// MFCApplication2Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CMFCApplication2Dlg �Ի���



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


// CMFCApplication2Dlg ��Ϣ�������

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	HBITMAP hBitmap = ::LoadBitmap(AfxGetApp()->m_hInstance,
		MAKEINTRESOURCE(IDB_BITMAP1));
	//���þ�̬�ؼ�����ʽ��ʹ�����ʹ��λͼ������λ����ʾʹ����
	m_ctrlPicture.ModifyStyle(0xF, SS_BITMAP);// | SS_CENTERIMAGE);
	m_ctrlPicture.SetBitmap(hBitmap);
	m_Button2.SetBkColor(RGB(0xD0, 0xD0, 0xD0));
	m_Button1.SetBkColor(RGB(0xD0, 0xD0, 0xD0));
	m_Button3.SetBkColor(RGB(0x80, 0x80, 0x80));
	m_Button3.SetTextColor(RGB(0xC0, 0xC0, 0xC0));
	m_Button4.SetBkColor(RGB(0x80, 0x80, 0x80));
	m_Button4.SetTextColor(RGB(0xC0, 0xC0, 0xC0));
	
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	ReadIni();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	WSACleanup(); //�ر� Winsock
	

}
int CMFCApplication2Dlg::SendLogin(CString MSG,HWND Hw)
{
	

	 S = socket(AF_INET, 1, 0); //�����׽��֣�s ��socket���ܷ��ص��ļ�������


	if (S < 1)
	{
		WCleanup(S);
		return 0;
	}

  //	memset((char*)&Sock, sizeof(Sock), NULL);
	Sock.sin_family = AF_INET; //socket����
	CString IP = GetIni((CString)"URL", (CString)"IP", (CString)"");
	if (IP.IsEmpty()) IP = "192.168.1.188";
		 
	Sock.sin_addr.S_un.S_addr = inet_addr(CStringToChar(IP)); //���õ�IP��119.75.217.56
	Sock.sin_port = htons(5555);
	int Res = connect(S, (struct sockaddr*)&Sock, sizeof(Sock)); //�󶨶˿�
	if (Res != 0) {
		WCleanup(S);
		return 0;
	}
	char *FF = CStringToChar(MSG);
	
	int Ret = send(S, FF, strlen(FF), NULL);
	Res = WSAAsyncSelect(S, Hw, UM_SOCK, 1); //�����׽��ִ���������ʽ���߷�������ʽ,��Ϣ���͵Ĵ����� pic���� Form1.Picture1
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
			ReMsg = "��½�ɹ�";
		}
		else if (Msg == "LoginFaild-2")
		{
			ReMsg = "�û������������";
		}
		else if (Msg == "LoginFaild-1")
		{
			ReMsg = "�û�������";
		}
		else if (Msg == "RegFaild")
		{
			ReMsg = "ע��ʧ��";
		}
		else if (Msg == "RegSucess")
		{
			ReMsg = "ע��ɹ�";
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


	 S = socket(AF_INET, 1, 0); //�����׽��֣�s ��socket���ܷ��ص��ļ�������


	if (S < 1)
	{
		WCleanup(S);
		return 0;
	}
	// memset((char*)&Sock, sizeof(Sock), NULL);
	Sock.sin_family = AF_INET; //socket����
	Sock.sin_addr.S_un.S_addr = inet_addr("112.127.115.32"); //���õ�IP��119.75.217.56

	Sock.sin_port = htons(80);
	int Res = connect(S, (struct sockaddr*)&Sock, sizeof(Sock)); //�󶨶˿�
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
	CHAR FF[4000]; //�ض��建������СΪ 2000
	int Res = recv(S, FF, sizeof(FF), NULL); //������Ϣ
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
	CHAR FF[4000]; //�ض��建������СΪ 2000
	int Res = recv(S, FF, sizeof(FF), NULL); //������Ϣ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}


int CMFCApplication2Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//ReadIni();
	Wstartup();
	return 0;
}
void CMFCApplication2Dlg::SetiniSet(CString Name, CString Value)
{
	SetIni(Value, Name, (CString)"����", NULL);
}
CString CMFCApplication2Dlg::ReadIniSet(CString Name)
{
	return GetIni(Name, (CString)"����", (CString)"");
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

		// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	CalcCountVs((CString)"����", (CString)".\\set.ini");
}
int CMFCApplication2Dlg::CalcCount(CString strPathName)
{
	TCHAR chSectionNames[2048] = { 0 };      //���н�����ɵ��ַ�����
	char * pSectionName; //�����ҵ���ĳ�������ַ������׵�ַ
	int i;      //iָ������chSectionNames��ĳ��λ�ã���0��ʼ��˳�����
	int j = 0;     //j����������һ�������ַ������׵�ַ����ڵ�ǰi��λ��ƫ����
	int count = 0;     //ͳ�ƽڵĸ���

	//CString name;
	//char id[20];
	::GetPrivateProfileSectionNames(chSectionNames, 2048, strPathName);
	
	for (i = 0; i<2048; i++, j++)
	{
		if (chSectionNames[0] == '\0')
			break;      //�����һ���ַ�����0����˵��ini��һ����Ҳû��
		if (chSectionNames[i] == '\0')
		{
			pSectionName = (char*)&chSectionNames[i - j]; //�ҵ�һ��0����˵��������ַ���ǰ������j��ƫ������
			//����һ���������׵�ַ
			j = -1;        //�ҵ�һ��������j��ֵҪ��ԭ����ͳ����һ��������ַ��ƫ����
			//����-1����Ϊ�����ַ��������һ���ַ�0����ֹ����������Ϊ����
			//��һ����

			//�ڻ�ȡ������ʱ����Ի�ȡ�ý��м���ֵ��ǰ��������֪���ý�������Щ����
			AfxMessageBox((CString)(LPCWSTR)pSectionName);     //���ҵ�����ʾ����
			CalcCountVs((CString)(LPCWSTR)pSectionName, strPathName);
			if (chSectionNames[i + 1] == 0)
			{
				break;     //���������ڵ��ַ�����0ʱ�������еĽ��������ҵ���ѭ����ֹ
			}
		}

	}
	return count;
}
int CMFCApplication2Dlg::CalcCountVs(CString Tname, CString strPathName)
{
	TCHAR chValueNames[2048] = { 0 };      //���н�����ɵ��ַ�����
	char * pName; //�����ҵ���ĳ�������ַ������׵�ַ
	int a, b = 0;
	int count = 0;     //ͳ�ƽڵĸ���

	//CString name;
	//char id[20];
	GetPrivateProfileSection(Tname, chValueNames, 2048, strPathName);
	for (a = 0; a<2048; a++, b++)
	{
		if (chValueNames[0] == '\0')
			break;      //�����һ���ַ�����0����˵��ini��һ����Ҳû��
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
				break;     //���������ڵ��ַ�����0ʱ�������еĽ��������ҵ���ѭ����ֹ
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	
    CString str;
	CWnd *pWnd = GetFocus(); //��ǰ���
	 //��ȡ�ؼ�ID
	if (pWnd == NULL) return;
	if (pWnd->GetParent() != this) return;
	int c = pWnd->GetDlgCtrlID();
	char B[5];
	_itoa_s(c, B, sizeof(B),10);
	pWnd->GetWindowText(str);
	SetiniSet((CString)(LPCSTR)B,str);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication2Dlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString str;
	CWnd *pWnd = GetFocus(); //��ǰ���
	//��ȡ�ؼ�ID
	if (pWnd == NULL) return;
	if (pWnd->GetParent() != this) return;
	int c = pWnd->GetDlgCtrlID();
	char B[5];
	_itoa_s(c, B, sizeof(B), 10);
	pWnd->GetWindowText(str);
	SetiniSet((CString)(LPCSTR)B, str);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	
	return hbr;	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
}


void CMFCApplication2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SetFocus();
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication2Dlg::OnStnClickedStatic1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication2Dlg::OnBnClickedButton3()
{
	CMFCApplication2Dlg::OnCancel();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication2Dlg::OnBnClickedButton4()
{
	WINDOWPLACEMENT lwndpl;
	WINDOWPLACEMENT * lpwndpl;
	lpwndpl = &lwndpl;
	GetWindowPlacement(lpwndpl);
	lpwndpl->showCmd = SW_SHOWMINIMIZED;
	SetWindowPlacement(lpwndpl);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	CRgn m_rgn;
	CRect rc;
	GetWindowRect(&rc); //��ô��ھ���
	rc -= rc.TopLeft();
	m_rgn.CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 10, 10); //���ݴ��ھ��δ���һ��Բ�Ǿ���
	SetWindowRgn(m_rgn, TRUE);
	DeleteObject(m_rgn);
}


void CMFCApplication2Dlg::OnSetfocusEdit1()
{
	m_pic.Stop();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CMFCApplication2Dlg::OnSetfocusButton2()
{
	m_pic.Stop();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


BOOL CMFCApplication2Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
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
