
#pragma once

#include <atlbase.h>
#include <atlimage.h>


// CGlimDlg 대화 상자
class CGlimDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	int m_nNum;
	int m_nNum2;

	CImage m_Image;

	afx_msg void OnBnClickedButton1();
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	
	afx_msg void OnBnClickedButton2();
};
