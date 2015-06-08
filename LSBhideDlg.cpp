
// LSBhideDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LSBhide.h"
#include "LSBhideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLSBhideDlg 对话框



CLSBhideDlg::CLSBhideDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLSBhideDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLSBhideDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_ORIGINAL, m_Pic_Original);
	DDX_Control(pDX, IDC_PIC_EMBED, m_Pic_Embed);
}

BEGIN_MESSAGE_MAP(CLSBhideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CLSBhideDlg::OnBnClickedBtnOpen)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLSBhideDlg 消息处理程序

BOOL CLSBhideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	m_Pic_Original.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	m_Pic_Embed.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLSBhideDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CLSBhideDlg::OnPaint()
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
HCURSOR CLSBhideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnOK()
{
	// TODO:  在此添加专用代码和/或调用基类
	return;
	//CDialogEx::OnOK();
}


void CLSBhideDlg::OnBnClickedBtnOpen()
{
	// TODO:  在此添加控件通知处理程序代码
	CFileDialog dlgFileOpen(TRUE, _T(".bmp"), _T(""));
	
	if (dlgFileOpen.DoModal() == IDOK)
	{
		m_szBmpFileName = dlgFileOpen.GetPathName();
		if (m_pMyBmp != NULL) {
			delete m_pMyBmp;
			m_pMyBmp = NULL;
		}

		int len = WideCharToMultiByte(CP_ACP, 0, m_szBmpFileName, -1, NULL, 0, NULL, NULL);
		char *ptxtTemp = new char[len + 1];
		WideCharToMultiByte(CP_ACP, 0, m_szBmpFileName, -1, ptxtTemp, len, NULL, NULL);
		m_pMyBmp = new MyBMP(ptxtTemp);
		delete[] ptxtTemp;

		if (!m_pMyBmp->OK) {
			MessageBox(_T("打开文件失败"), _T("错误"));
			delete m_pMyBmp;
			m_pMyBmp = NULL;
		} else {
			m_Image_Original.Destroy();
			// 将外部图像文件装载到CImage对象中 
			HRESULT hResult = m_Image_Original.Load(m_szBmpFileName);
			if (FAILED(hResult)) {
				MessageBox(_T("打开文件失败"), _T("错误"));
				delete m_pMyBmp;
				m_pMyBmp = NULL;
				return;
			}
			m_Pic_Original.SetBitmap(HBITMAP(m_Image_Original));
		}
	}
}


void CLSBhideDlg::OnDestroy()
{

	CDialogEx::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
	if (m_pMyBmp != NULL) {
		delete m_pMyBmp;
		m_pMyBmp = NULL;
	}
}
