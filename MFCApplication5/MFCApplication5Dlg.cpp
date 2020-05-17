
// MFCApplication5Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication5.h"
#include "MFCApplication5Dlg.h"
#include "afxdialogex.h"
#include "Dhspn.h"
#include "FileRW.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication5Dlg 对话框



CMFCApplication5Dlg::CMFCApplication5Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION5_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication5Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication5Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK2, &CMFCApplication5Dlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication5Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCApplication5Dlg 消息处理程序

BOOL CMFCApplication5Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication5Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication5Dlg::OnPaint()
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
HCURSOR CMFCApplication5Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication5Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	CString	strMsg;
	int iRet = dhSendPluDefault();
	switch (iRet)
	{
	case 0:
		strMsg = "操作成功"; break;
	case -1:
		strMsg = "dhip.ini为空或者设置错误"; break;
	case -2:
		strMsg = "dhpluversion.int为空或设置错误"; break;
	case -3:
		strMsg = "dhplupathname.ini为空或设置错误"; break;
	case -4:
		strMsg = "dhplupathname.ini中读取的Plu路径不对,所指向的Plu文件不存在"; break;
	case -5:
		strMsg = "Plu文本为空或者设置错误(如:Plu版本与Plu文本内容不一致等)"; break;
	case -6:
		strMsg = "通信中存在异常,具体信息如下："; strMsg += "\r\n"; break;
	}

	if (iRet == -6)
	{
		CStringArray	m_saReturn;
		RoyaReadFile("Return.txt", m_saReturn);
		for (int i = 0; i < m_saReturn.GetSize(); i++)
		{
			CString strT = m_saReturn[i];
			if (strT == "")continue;
			strT.TrimLeft();
			strT.TrimRight();
			int iF1 = strT.Find('\t');
			if (iF1 == -1)continue;
			strMsg += "\r\n";
			strMsg += strT.Left(iF1);
			strMsg += '\t';
			CString strValue = strT.Right(strT.GetLength() - iF1);
			int iV = atoi(strValue);
			switch (iV)
			{
			case 0:
			{strMsg += "下载成功"; break; }
			case -1:
			{strMsg += "连接失败"; break; }
			case -2:
			{strMsg += "发送后,未收到返回信息"; break; }
			case -3:
			{strMsg += "读缓冲区失败"; break; }
			case -4:
			{strMsg += "ip地址转换失败"; break; }
			case -10:
			{strMsg += "发送后未收到正确返回信息(0d,0a,03结束标志)"; break; }
			default:
			{strMsg += "..."; break; }
			}
		}
	}
	MessageBox(strMsg);
	GetDlgItem(IDOK)->EnableWindow(true);
	
}


void CMFCApplication5Dlg::OnBnClickedOk2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDOK2)->EnableWindow(FALSE);
	CString	strMsg;
	int iRet = dhRcvRdDefault();
	switch (iRet)
	{
	case 0:
		strMsg = "操作成功"; break;
	case -1:
		strMsg = "dhip.ini为空或者设置错误"; break;
	case -2:
		strMsg = "dhpluversion.int为空或设置错误"; break;
	case -3:
		strMsg = "dhplupathname.ini为空或设置错误"; break;
	case -4:
		strMsg = "dhplupathname.ini中读取的Plu路径不对,所指向的Plu文件不存在"; break;
	case -5:
		strMsg = "Plu文本为空或者设置错误(如:Plu版本与Plu文本内容不一致等)"; break;
	case -6:
		strMsg = "通信中存在异常,具体信息如下："; strMsg += "\r\n"; break;
	}

	if (iRet == -6)
	{
		CStringArray	m_saReturn;
		RoyaReadFile("Return.txt", m_saReturn);
		for (int i = 0; i < m_saReturn.GetSize(); i++)
		{
			CString strT = m_saReturn[i];
			if (strT == "")continue;
			strT.TrimLeft();
			strT.TrimRight();
			int iF1 = strT.Find('\t');
			if (iF1 == -1)continue;
			strMsg += "\r\n";
			strMsg += strT.Left(iF1);
			strMsg += '\t';
			CString strValue = strT.Right(strT.GetLength() - iF1);
			int iV = atoi(strValue);
			switch (iV)
			{
			case 0:
			{strMsg += "下载成功"; break; }
			case -1:
			{strMsg += "连接失败"; break; }
			case -2:
			{strMsg += "发送后,未收到返回信息"; break; }
			case -3:
			{strMsg += "读缓冲区失败"; break; }
			case -4:
			{strMsg += "ip地址转换失败"; break; }
			case -10:
			{strMsg += "发送后未收到正确返回信息(0d,0a,03结束标志)"; break; }
			default:
			{strMsg += "..."; break; }
			}
		}
	}
	MessageBox(strMsg);
	GetDlgItem(IDOK2)->EnableWindow(true);

}


void CMFCApplication5Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

