
// LSBhideDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyBMP.h"
#include "LbsHide.hpp"

// CLSBhideDlg 对话框
class CLSBhideDlg : public CDialogEx
{
// 构造
public:
	CLSBhideDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_LSBHIDE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CStatic m_Pic_Original; //原图控件
	CStatic m_Pic_Embed; //嵌入图控件
	CString m_szBmpFileName;
	CImage m_Image_Original;
	CImage m_Image_Embed;
	CEdit m_Edit_LOG;
	MyBMP *m_pMyBmp = NULL;
	LbsHide lbsHide;

	// 生成的消息映射函数
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
	afx_msg void OnBnClickedBtnNoise();
	afx_msg void OnBnClickedBtnStat();
	CEdit m_Edit_Key;
};
