// RichEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "RichEdit.h"
#include "talktotalk.h"

// CRichEdit

IMPLEMENT_DYNAMIC(CRichEdit, CRichEditCtrl)

CRichEdit::CRichEdit()
{

}

CRichEdit::~CRichEdit()
{
}


BEGIN_MESSAGE_MAP(CRichEdit, CRichEditCtrl)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

CString CRichEdit::WcharLeft(CString str, int left)
{
	WCHAR C[UNICODE_STRING_MAX_CHARS] = { 0 };
	int A = sizeof(C);
	MultiByteToWideChar(CP_ACP, 0, str, -1, C, sizeof(C));
	C[left] = 0;
	CString ret;
	char* pszMultiByte;
	int iSize = WideCharToMultiByte(CP_ACP, 0, C, -1, NULL, 0, NULL, NULL);
	pszMultiByte = (char*)malloc((iSize + 1));
	WideCharToMultiByte(CP_ACP, 0, C, -1, pszMultiByte, iSize, NULL, NULL);
	ret = (CString)(LPCSTR)pszMultiByte;
	free(pszMultiByte);
	pszMultiByte = NULL;
	return ret;
}
int CRichEdit::GetWcharLen(CString Str)
{
	WCHAR C[UNICODE_STRING_MAX_CHARS] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, Str, -1, C, sizeof(C));
	int ret = lstrlenW(C);
	return ret;
}
int CRichEdit::FindWcharL(CString Str, CString find, int Start)
{
	WCHAR C[UNICODE_STRING_MAX_CHARS] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, Str, -1, C, sizeof(C));
	WCHAR F[UNICODE_STRING_MAX_CHARS] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, find, -1, F, sizeof(F));
	WCHAR T[UNICODE_STRING_MAX_CHARS] = { 0 };
	int i, L, FL;
	L = lstrlenW(F);
	FL = lstrlenW(C);
	for (i = Start; i <= FL - L; i++)
	{
		StrCpyNW(T, C + i, L + 1);
		if (StrCmpCW(T, F) == 0) return i;
	}
	return -1;
}
CString CRichEdit::WcharMid(CString str, int mid)
{
	WCHAR C[UNICODE_STRING_MAX_CHARS] = { 0 };
	MultiByteToWideChar(CP_ACP, 0, str, -1, C, sizeof(C));
	wchar_t *e = C + mid;
	CString ret;
	char* pszMultiByte;
	int iSize = WideCharToMultiByte(CP_ACP, 0, e, -1, NULL, 0, NULL, NULL);
	pszMultiByte = (char*)malloc((iSize + 1));
	WideCharToMultiByte(CP_ACP, 0, e, -1, pszMultiByte, iSize, NULL, NULL);
	ret = (CString)(LPCSTR)pszMultiByte;
	free(pszMultiByte);
	pszMultiByte = NULL;
	return ret;
}


CString CRichEdit::RecoverObj(CString Src)
{
	int i, j = 0 , k = 0;
	CString A, B, C;
	for (i = 0; i <= 999; i++)
	{
		if (obj[i][0] != 0)
		{
			obj[i][1] = obj[i][1] - k + j * 3;
			A = WcharLeft(Src, obj[i][1]);
			B = WcharMid(Src, obj[i][1] + 1);
			if ((obj[i][0] < 999))
			{
				C.Format("%d", obj[i][0] - 1);
				if (C.GetLength() < 2)
					C = "/i0" + C;
				else
					C = "/i" + C;
				j++;
			}
			else
			{
				C = "";
				k++;
			}
			Src = A + C + B;
			obj[i][0] = 0;
			obj[i][1] = 0;
		}
	}
	return Src;
}
BOOL CRichEdit::GetPic(REOBJECT FAR* pObject)
{
	CRichEditCtrl* pTextIn1 = this;
	IRichEditOle* pITextIn1 = pTextIn1->GetIRichEditOle();
	LONG lCount = pITextIn1->GetObjectCount();

	LRESULT lRet;
	for (int i = 0; i<lCount; i++)
	{
		lRet = pITextIn1->GetObject(0, pObject, REO_GETOBJ_POLEOBJ);
		if (lRet == S_OK)
		{
			pObject->poleobj->Release();
			if (pObject->poleobj == m_pPicObj)
			{
				return TRUE;
			}
		}

	}
	return FALSE;
}

void CRichEdit::SetEndSel(bool set)
{
	endsel = set;
}
BOOL CRichEdit::InserPic(CString Str, int headlen)
{
	LONG i = 0, k, j = 0, h, Max = Str.GetLength() - 8;
	BOOL A = FALSE;
	int iStart = 0, num;
	CString Bq;
	do
	{
		i = MyFind(Str, i, &iStart);
		if (i >= 0)
		{
			k = GetStrNum(Str, "\r\n", iStart);
			h = i - k - j * 3;
			SetSel(h, h + 4);
			Bq = Str.Mid(iStart, 4);
			num = GetPicNum(Bq);
			if (num >= 1000 && iStart == Max)
			{
				switch (num)
				{
				case DIYFACE:
					InserDiyFace(headlen, k);
				case SELFFACE:
					SelfDiyFace(headlen, k);
				}
			}
			else if (num < 1000)
			{
				InserGif(num);
				j++;
			}
			i = iStart + 1;
			A = TRUE;
		}
	} while (i >= 0 && i <= Max);
	if (endsel || A)
	{
		h = Str.GetLength();
		SetSel(h, h);
	}
	return A;
}
void CRichEdit::InserDiyFace(int headlen, int k)
{
	talktotalk *p = (talktotalk *)GetParent();
	int index = p->TalkId;
	int b = App->msg[index].num - 1;
	if (App->msg[index].obj[b].objnum == 0) return;
	ReplaceSel("");
	headlen = headlen - k;
	for (int k = 0; k <= App->msg[index].obj[b].objnum - 1; k++)
		InserObjbyString(App->msg[index].obj[b].obj[k].strpath,
		App->msg[index].obj[b].obj[k].Type, 
		App->msg[index].obj[b].obj[k].Sel + headlen);

	App->msg[index].obj[b].objnum = 0;
	App->msg[index].num--;
}
void CRichEdit::SelfDiyFace(int headlen, int k)
{
	if (objectSend.num == 0) return;
	ReplaceSel("");
	headlen = headlen - k;
	for (int b = 0; b <= objectSend.num - 1; b++)
		InserObjbyString(objectSend.obj[b].strpath,
		objectSend.obj[b].Type, objectSend.obj[b].Sel + headlen);

}
bool CRichEdit::CheckPic(CString str)
{
	int a=atoi(str);
	if (a < 88 && a >= 0) return true;
	return false;
}
int CRichEdit::GetPicNum(CString str)
{
	if (str == "/Pic") return DIYFACE;
	if (str == "/Slf") return SELFFACE;
	int len = str.GetLength();
	CString Num = str.Right(len - 2);
	return atoi(Num);
}
int CRichEdit::GetStrNum(CString Str, CString iStr, LONG Over)
{
	int i = 0, j = -1;
	do
	{
		j = Str.Find(iStr, j + 1);
		if (j >= 0 && j < Over) i++;
	} while (j >= 0 && j < Over);
	return i;
}
int CRichEdit::MyFind(CString Str,  int iStart, int *outindex)
{
	int i;
	int k = Str.GetLength() - 4;
	for (i = iStart; i <= k; i++)
	{
		if (Str.Mid(i, 2) == "/i")
		{
			if (CheckPic(Str.Mid(i + 2, 2))) break;
		//	i = i + 4;
		}
		if (Str.Mid(i, 4) == "/Pic") break;
		if (Str.Mid(i, 4) == "/Slf") break;
	}
	if (i <= k)
	{
		*outindex = i;
		int j = HasChineseChar(Str.Left(i));
		return i - j;
	}
	return -1;
}

int CRichEdit::HasChineseChar(CString Cstr)
{
	int nLen = Cstr.GetLength();
	int k = 0;
	unsigned char ch1;
	for (int i = 0; i != nLen; ++i)
	{
		ch1 = Cstr[i];
		if (ch1 >= 0xA0)
		{
			k++;
		}
		else continue;
	}
	return k / 2;
}


int CRichEdit::GetPicInfo()
{
	BOOL bSavePicSuccess = FALSE;
	IRichEditOle* pRichOle = this->GetIRichEditOle() ;
	int nCount = pRichOle->GetObjectCount(); // 当前m_ChatEdit中所有的object对象
	int objnum = 0;
	for (int i = 0; i<nCount; i++)
	{
		REOBJECT reobject;
		memset(&reobject, 0, sizeof(REOBJECT));
		reobject.cbStruct = sizeof(REOBJECT);

		SCODE sc = pRichOle->GetObject(i, &reobject, REO_GETOBJ_ALL_INTERFACES); // 获取到reobject对象
		if (sc != S_OK)
		{
			continue;
		}
		obj[i][0] = reobject.dwUser + 1;
		obj[i][1] = reobject.cp;
		if (reobject.dwUser >= 999) objnum++;
		/*
		if ((reobject.dwFlags & REO_SELECTED) != REO_SELECTED) // 检验当前reobject是否处于选中状态
		{
			continue; // 不是当前选中的对象，继续查找
		}

		IDataObject* pDataObject = NULL;
		sc = reobject.poleobj->QueryInterface(IID_IDataObject, (void**)&pDataObject); // 获取IDataObject信息
		if (sc != S_OK)
		{
			break; // 已经找到选中的图片对象，获取信息失败，直接退出
		}

		// 要对fm参数进行设置，指明要从IStorage中获取什么样的信息，否则GetData接口会获取stg信息失败
		STGMEDIUM stg;
		FORMATETC fm;
		fm.cfFormat = CF_BITMAP;        // Clipboard format = CF_BITMAP
		fm.ptd = NULL;                  // Target Device = Screen
		fm.dwAspect = DVASPECT_CONTENT; // Level of detail = Full content
		fm.lindex = -1;                 // Index = Not applicaple
		fm.tymed = TYMED_GDI;           // 对应CF_BITMAP

		HRESULT hr = pDataObject->GetData(&fm, &stg);
		if (hr != S_OK || stg.hBitmap == NULL)
		{
			break; // 已经找到选中的图片对象，获取信息失败，直接退出
		}
		*/
	}
	if (pRichOle)
	{
		pRichOle->Release();
		pRichOle = NULL;;
	}
	return objnum;
}

void CRichEdit::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类

	// 下面这个可选，去掉RichEdit的双字体设置
	// 因为说实话，我不知道怎么分别设置中英文字体，如果哪位同学知道请告诉
	// 我一下
//	DWORD fontStyle = SendMessage(EM_GETLANGOPTIONS);
//	fontStyle &= ~IMF_DUALFONT;
//	SendMessage(EM_SETLANGOPTIONS, 0, fontStyle);

	// 修改为背景透明，刷避免闪烁，我们自己绘制白色背景
	ModifyStyleEx(0,  WS_EX_COMPOSITED);

	// 这个接口指针使用非常频繁，存下来提高效率
	// 启动定时器，用于更新动画
	m_pRichEditOle = GetIRichEditOle();
	SetTimer(FRM_TIMER_ID, MIN_FRM_DELAY, NULL);
	SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	CRichEditCtrl::PreSubclassWindow();
}

void CRichEdit::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == FRM_TIMER_ID) {
		int nObjectCount = m_pRichEditOle->GetObjectCount();
		if (nObjectCount > 0) {
			CRect rc;
			GetRect(rc); // 得到可输入的矩形区域
			// 分别使用左上角和右下角的点得到最小和最大字符索引
			// 即可见区域的最小和最大字符索引
			int cpMin = CharFromPos(rc.TopLeft());
			int cpMax = CharFromPos(rc.BottomRight());

			// 使用二分查找算法找到第一个字符索引大于或等于cpMin的对象索引
			int iFirst = FindFirstObject(cpMin, nObjectCount);
			REOBJECT reo = { 0 };
			reo.cbStruct = sizeof(REOBJECT);

			// 从第一个索引开始遍历对象更换帧
			for (int i = iFirst; i < nObjectCount; i++)
			{
				if (m_pRichEditOle->GetObject(i, &reo, REO_GETOBJ_POLEOBJ) == S_OK)
				{
					reo.poleobj->Release();
					// 当前对象的字符索引大于最大字符索引，说明对象不在可见区域，停止遍历
					if (reo.cp > cpMax) {
						break;
					}
					if (reo.dwUser < 999)
					{
						CPoint A;
						A = PosFromChar(reo.cp);
						RECT B;
						B.left = A.x;
						B.top = A.y;
						B.right = A.x + 70;
						B.bottom = A.y + 64;
						InvalidateRect(&B);
					}
				}
			}
		}
		else {
			CRichEditCtrl::OnTimer(nIDEvent);
		}
	}
}

int CRichEdit::FindFirstObject(int cpMin, int nObjectCount)
{
	// 标准的二分查找算法，不用解释了
	int low = 0;
	int high = nObjectCount - 1;
	REOBJECT reoMid = { 0 };
	reoMid.cbStruct = sizeof(REOBJECT);
	while (low <= high) {
		int mid = (low + high) >> 1;

		 if (m_pRichEditOle->GetObject(mid, &reoMid, REO_GETOBJ_POLEOBJ) != S_OK) {
			return -1;
		}
		reoMid.poleobj->Release();
		if (reoMid.cp == cpMin) {
			return mid;
		}
		else if (reoMid.cp < cpMin) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}

	// 只不过最后没找到时不是返回-1，而是返回low，此时low必然大于或等于high
	// 刚好满足条件
	return low;
}

void CRichEdit::OnDestroy()
{
	// 停止定时器，这是必要的
	KillTimer(FRM_TIMER_ID);
	// 清空内容，目的是删除所有插入的COleImage对象
	SetWindowText(_T(""));
	// 但是别忘了，RichEdit支持多级撤消，对象虽然删除了，但是撤消缓存
	// 中还保留有对象的引用，清空撤消缓存才能真正的释放这些对象
	EmptyUndoBuffer();

	// 上面的工作必须在父类OnDestroy前调用，否则窗口已经销毁，清理没用
	CRichEditCtrl::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

void CRichEdit::InserGif(int index)  //strFilePath   gif文件路径
{
	LPLOCKBYTES  lpLockBytes = NULL;
	SCODE  sc;
	HRESULT  hr;;
	//print  to  RichEdit'  s  IClientSite 
	LPOLECLIENTSITE  m_lpClientSite;
	//A  smart  point  to  IAnimator 
	ImageOleLib::IGifAnimatorPtr  m_lpAnimator;
	//ptr  2  storage                 ;    
	LPSTORAGE  m_lpStorage;
	//the  object  2  b  insert  2 
	LPOLEOBJECT m_lpObject;
	//Create  lockbytes 

	sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
		AfxThrowOleException(sc);
	ASSERT(lpLockBytes != NULL);
	//use  lockbytes  to  create  storage 
	sc = ::StgCreateDocfileOnILockBytes(lpLockBytes,
		STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &m_lpStorage);
	if (sc != S_OK)
	{
		VERIFY(lpLockBytes->Release() == 0);
		lpLockBytes = NULL;
		AfxThrowOleException(sc);
	}
	ASSERT(m_lpStorage != NULL);
	//get  the  ClientSite  of  the  very  RichEditCtrl 
	GetIRichEditOle()->GetClientSite(&m_lpClientSite);
	ASSERT(m_lpClientSite != NULL);
	try
	{
		//Initlize  COM  interface 

		hr = ::CoInitialize(NULL);//(  NULL,  COINIT_APARTMENTTHREADED  ); 
		if (FAILED(hr))
			_com_issue_error(hr);

		//Get  GifAnimator  object 
		//here,  I  used  a  smart  point,  so  I  do ; not  need  to  free  it 
		hr = m_lpAnimator.CreateInstance(ImageOleLib::CLSID_GifAnimator);;
		if (FAILED(hr)) _com_issue_error(hr);
		//COM  operation  need  BSTR,  so  get  a  BSTR 
		CString strpath;
		strpath.Format("%d", index + 1);
		if (strpath.GetLength() < 2)
			strpath = "face\\00" + strpath + ".gif";
		else
			strpath = "face\\0" + strpath + ".gif";
		BSTR  path = strpath.AllocSysString();
		//Load  the  gif 
		hr = m_lpAnimator->LoadFromFile(path);
		if (FAILED(hr))
			_com_issue_error(hr);

		TRACE0(m_lpAnimator->GetFilePath());

		//get  the  IOleObject 
		hr = m_lpAnimator.QueryInterface(IID_IOleObject, (void**)&m_lpObject);
		if (FAILED(hr))
			_com_issue_error(hr);

		//Set  it  2  b  inserted 
		OleSetContainedObject(m_lpObject, TRUE);

		//2  insert  in  2  richedit,  you  need  a  struct  of  REOBJECT 
		REOBJECT  reobject;
		ZeroMemory(&reobject, sizeof(REOBJECT));
		reobject.cbStruct = sizeof(REOBJECT);;
		CLSID  clsid;
		sc = m_lpObject->GetUserClassID(&clsid);
		if (sc != S_OK)
			AfxThrowOleException(sc);
		//set  clsid 
		reobject.clsid = clsid;
		//can  be  selected 
		reobject.cp = REO_CP_SELECTION;
		//content,  but  not  static 
		reobject.dvaspect = DVASPECT_CONTENT;
		//goes  in  the  same  line  of  text  line 
		reobject.dwFlags = REO_BELOWBASELINE;  //REO_RESIZABLE    | 
		reobject.dwUser = index;
		//the  very  object 
		reobject.poleobj = m_lpObject;
		//client  site  contain  the  object 
		reobject.polesite = m_lpClientSite;
		//the  storage   
		reobject.pstg = m_lpStorage;

		SIZEL  sizel;
		sizel.cx = sizel.cy = 0;
		reobject.sizel = sizel;
		HWND  hWndRT = this->m_hWnd;

		GetIRichEditOle()->InsertObject(&reobject);
		::SendMessage(hWndRT, EM_SCROLLCARET, (WPARAM)0, (LPARAM)0);
		VARIANT_BOOL  ret;
		//do  frame  changing 
		ret = m_lpAnimator->TriggerFrameChange();
		//show  it 
		m_lpObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, m_lpClientSite, 0, m_hWnd, NULL);
		m_lpObject->DoVerb(OLEIVERB_SHOW, NULL, m_lpClientSite, 0, m_hWnd, NULL);

		//redraw  the  window  to  show  animation 
		RedrawWindow();
		if (m_lpClientSite)
		{
			m_lpClientSite->Release();
			m_lpClientSite = NULL;;
		}
		if (m_lpObject)
		{
			m_lpObject->Release();
			m_lpObject = NULL;;
		}
		if (m_lpStorage)
		{
			m_lpStorage->Release();
			m_lpStorage = NULL;;
		}
		SysFreeString(path);
	}
	catch (_com_error  e)
	{
		AfxMessageBox(e.ErrorMessage());
		::CoUninitialize();;
	}
}
void CRichEdit::InserObjbyString(CString strpath, CString Type, int Sel)  //strFilePath   gif文件路径
{ 
	LPLOCKBYTES  lpLockBytes = NULL;
	SCODE  sc;
	HRESULT  hr;;
	//print  to  RichEdit'  s  IClientSite 
	LPOLECLIENTSITE  m_lpClientSite;
	//A  smart  point  to  IAnimator 
	ImageOleLib::IGifAnimatorPtr  m_lpAnimator;
	//ptr  2  storage                 ;    
	LPSTORAGE  m_lpStorage;
	//the  object  2  b  insert  2 
	LPOLEOBJECT            m_lpObject;
	//Create  lockbytes 

	sc = ::CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
		AfxThrowOleException(sc);
	ASSERT(lpLockBytes != NULL);
	//use  lockbytes  to  create  storage 
	sc = ::StgCreateDocfileOnILockBytes(lpLockBytes,
		STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &m_lpStorage);
	if (sc != S_OK)
	{
		VERIFY(lpLockBytes->Release() == 0);
		lpLockBytes = NULL;
		AfxThrowOleException(sc);
	}
	ASSERT(m_lpStorage != NULL);
	//get  the  ClientSite  of  the  very  RichEditCtrl 
	GetIRichEditOle()->GetClientSite(&m_lpClientSite);
	ASSERT(m_lpClientSite != NULL);
	try
	{
		//Initlize  COM  interface 

		hr = ::CoInitialize(NULL);//(  NULL,  COINIT_APARTMENTTHREADED  ); 
		if (FAILED(hr))
			_com_issue_error(hr);

		//Get  GifAnimator  object 
		//here,  I  used  a  smart  point,  so  I  do ; not  need  to  free  it 
		hr = m_lpAnimator.CreateInstance(ImageOleLib::CLSID_GifAnimator);;
		if (FAILED(hr)) _com_issue_error(hr);
		//COM  operation  need  BSTR,  so  get  a  BSTR 
		BSTR  path = strpath.AllocSysString();
		//Load  the  gif 
		hr = m_lpAnimator->LoadFromFile(path);
		if (FAILED(hr))
			_com_issue_error(hr);

		TRACE0(m_lpAnimator->GetFilePath());

		//get  the  IOleObject 
		hr = m_lpAnimator.QueryInterface(IID_IOleObject, (void**)&m_lpObject);
		if (FAILED(hr))
			_com_issue_error(hr);

		//Set  it  2  b  inserted 
		OleSetContainedObject(m_lpObject, TRUE);

		//2  insert  in  2  richedit,  you  need  a  struct  of  REOBJECT 
		REOBJECT  reobject;
		ZeroMemory(&reobject, sizeof(REOBJECT));
		reobject.cbStruct = sizeof(REOBJECT);;
		CLSID  clsid;
		sc = m_lpObject->GetUserClassID(&clsid);
		if (sc != S_OK)
			AfxThrowOleException(sc);
		//set  clsid 
		reobject.clsid = clsid;
		//can  be  selected 

		reobject.cp = Sel >= 0?Sel: REO_CP_SELECTION;
		//content,  but  not  static 
		reobject.dvaspect = DVASPECT_CONTENT;
		//goes  in  the  same  line  of  text  line 
		reobject.dwFlags = REO_BELOWBASELINE;
		int TYPE;
		if (Type == "gif")
			TYPE = 999;
		else
			TYPE = 1000;
		reobject.dwUser = TYPE;
		//the  very  object 
		reobject.poleobj = m_lpObject;
		//client  site  contain  the  object 
		reobject.polesite = m_lpClientSite;
		//the  storage   
		reobject.pstg = m_lpStorage;

		SIZEL  sizel;
		sizel.cx = sizel.cy = 0;
		reobject.sizel = sizel;
		HWND  hWndRT = this->m_hWnd;

		GetIRichEditOle()->InsertObject(&reobject);
		::SendMessage(hWndRT, EM_SCROLLCARET, (WPARAM)0, (LPARAM)0);
		VARIANT_BOOL  ret;
		//do  frame  changing 
		ret = m_lpAnimator->TriggerFrameChange();
		//show  it 
		m_lpObject->DoVerb(OLEIVERB_UIACTIVATE, NULL, m_lpClientSite, 0, m_hWnd, NULL);
		m_lpObject->DoVerb(OLEIVERB_SHOW, NULL, m_lpClientSite, 0, m_hWnd, NULL);

		//redraw  the  window  to  show  animation 
		RedrawWindow();
		if (m_lpClientSite)
		{
			m_lpClientSite->Release();
			m_lpClientSite = NULL;;
		}
		if (m_lpObject)
		{
			m_lpObject->Release();
			m_lpObject = NULL;;
		}
		if (m_lpStorage)
		{
			m_lpStorage->Release();
			m_lpStorage = NULL;;
		}
		SysFreeString(path);
	}
	catch (_com_error  e)
	{
		AfxMessageBox(e.ErrorMessage());
		::CoUninitialize();;
	}
}

void CRichEdit::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nSBCode == SB_THUMBTRACK)
	{
		InvalidateRect(NULL);
	}
	CRichEditCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL CRichEdit::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	WPARAM A;
	if (zDelta > 0)
		A = SB_LINEUP;
	else
		A = SB_LINEDOWN;
	SendMessage(WM_VSCROLL, A, 0);
	return CRichEditCtrl::OnMouseWheel(nFlags, zDelta, pt);
}
