
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
	CImage m_Image_Embed;
	CEdit m_Edit_LOG;
	MyBMP *m_pMyBmp = NULL;
	LbsHide lbsHide;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void addToLog(CString text,bool append);
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtnRead();
	afx_msg void OnBnClickedBtnEmbed();
	CEdit m_Edit_Data;
	afx_msg void OnBnClickedBtnSave();
};
