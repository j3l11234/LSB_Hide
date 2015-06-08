
// LSBhideDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LSBhide.h"
#include "LSBhideDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CLSBhideDlg �Ի���



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
	DDX_Control(pDX, IDC_EDIT_LOG, m_Edit_LOG);
	DDX_Control(pDX, IDC_EDIT_DATA, m_Edit_Data);
}

BEGIN_MESSAGE_MAP(CLSBhideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CLSBhideDlg::OnBnClickedBtnOpen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_READ, &CLSBhideDlg::OnBnClickedBtnRead)
	ON_BN_CLICKED(IDC_BTN_EMBED, &CLSBhideDlg::OnBnClickedBtnEmbed)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CLSBhideDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CLSBhideDlg ��Ϣ�������

BOOL CLSBhideDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_Pic_Original.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	m_Pic_Embed.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
	//m_Edit_Data.ModifyStyle(0,  WS_VSCROLL | WS_HSCROLL);
	//m_Edit_LOG.ModifyStyle(0,  WS_VSCROLL | WS_HSCROLL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLSBhideDlg::OnPaint()
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
HCURSOR CLSBhideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���
	return;
	//CDialogEx::OnOK();
}


void CLSBhideDlg::OnBnClickedBtnOpen()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
			MessageBox(_T("���ļ�ʧ��"), _T("����"));
			delete m_pMyBmp;
			m_pMyBmp = NULL;
			return;
		}

		m_Image_Original.Destroy();
		// ���ⲿͼ���ļ�װ�ص�CImage������ 
		HRESULT hResult = m_Image_Original.Load(m_szBmpFileName);
		if (FAILED(hResult)) {
			MessageBox(_T("���ļ�ʧ��"), _T("����"));
			delete m_pMyBmp;
			m_pMyBmp = NULL;
			return;
		}
		m_Pic_Original.SetBitmap(HBITMAP(m_Image_Original));
		unsigned int maxLbsLength = m_pMyBmp->getMaxLbsLength() - 8;
		CString text;
		if (maxLbsLength <= 0) {
			text.Format(_T("�ļ�����ɣ��޷�д��\r\n"));
		}
		else {
			text.Format(_T("�ļ�����ɣ���д��%d�ֽ�\r\n"), maxLbsLength);
		}
		
		addToLog(text,true);
		
	}
}


void CLSBhideDlg::OnDestroy()
{

	CDialogEx::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
	if (m_pMyBmp != NULL) {
		delete m_pMyBmp;
		m_pMyBmp = NULL;
	}
}

void CLSBhideDlg::addToLog(CString text, bool append) {
	CString logText;
	m_Edit_LOG.GetWindowText(logText);
	if (append) {
		logText.Append(text);
	} else {
		logText = text;
	}
	m_Edit_LOG.SetWindowText(logText);
}

void CLSBhideDlg::OnBnClickedBtnRead()
{
	if (m_pMyBmp == NULL) {
		MessageBox(_T("�ļ�δ��"), _T("����"));
		return;
	}
	LbsData *lbsdata = lbsHide.getLbsHideData(m_pMyBmp);
	if (lbsdata == NULL) {
		MessageBox(_T("LBS��ȡ����"), _T("����"));
		return;
	}

	CString text;
	CString data(lbsdata->data);
	text.Format(_T("��ȡ��ɣ�length=%d, crc32=%8x \r\n====data=====\r\n%s\r\n====data=====\r\n"), lbsdata->length, lbsdata->crc32, data);
	addToLog(text,true);
	delete lbsdata;
}


void CLSBhideDlg::OnBnClickedBtnEmbed()
{
	if (m_pMyBmp == NULL) {
		MessageBox(_T("�ļ�δ��"), _T("����"));
		return;
	}

	CString data;
	m_Edit_Data.GetWindowText(data);

	int len = WideCharToMultiByte(CP_ACP, 0, data, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, data, -1, ptxtTemp, len, NULL, NULL);

	LbsData lbsData;
	lbsData.data = (BYTE*)ptxtTemp;
	lbsData.length = len;
	
	int result = lbsHide.setLbsHideData(m_pMyBmp, &lbsData);
	if (result == -1) {
		MessageBox(_T("Ƕ�����"), _T("����"));
		return;
	}

	CString text;
	text.Format(_T("Ƕ����ɣ�length=%d, crc32=%8x \r\n"), lbsData.length, lbsData.crc32);
	addToLog(text, true);

	CString temp = m_szBmpFileName + _T("$$$");
	len = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
	ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, temp, -1, ptxtTemp, len, NULL, NULL);
	m_pMyBmp->saveToFile(ptxtTemp);

	m_Image_Embed.Destroy();
	// ���ⲿͼ���ļ�װ�ص�CImage������ 
	HRESULT hResult = m_Image_Embed.Load(temp);
	if (FAILED(hResult)) {
		MessageBox(_T("���ļ�ʧ��"), _T("����"));
		return;
	}
	m_Pic_Embed.SetBitmap(HBITMAP(m_Image_Embed));


	delete[] ptxtTemp;
}


void CLSBhideDlg::OnBnClickedBtnSave()
{
	if (m_pMyBmp == NULL) {
		MessageBox(_T("�ļ�δ��"), _T("����"));
		return;
	}
	CFileDialog dlgFileOpen(FALSE, _T(".bmp"), m_szBmpFileName);

	if (dlgFileOpen.DoModal() != IDOK) {
		return;
	}
		

	CString m_szFileName = dlgFileOpen.GetPathName();


	int len = WideCharToMultiByte(CP_ACP, 0, m_szFileName, -1, NULL, 0, NULL, NULL);
	char *ptxtTemp = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, m_szFileName, -1, ptxtTemp, len, NULL, NULL);
	m_pMyBmp->saveToFile(ptxtTemp);
	MessageBox(_T("�����ļ��ɹ�"), _T("�ɹ�"));
	delete[] ptxtTemp;
}
