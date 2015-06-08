
// LSBhideDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "MyBMP.h"
#include "LbsHide.hpp"

// CLSBhideDlg �Ի���
class CLSBhideDlg : public CDialogEx
{
// ����
public:
	CLSBhideDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LSBHIDE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	CStatic m_Pic_Original; //ԭͼ�ؼ�
	CStatic m_Pic_Embed; //Ƕ��ͼ�ؼ�
	CString m_szBmpFileName;
	CImage m_Image_Original;
	MyBMP *m_pMyBmp = NULL;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnDestroy();
};
