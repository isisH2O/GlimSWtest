
// GLIMProjDlg.h: 헤더 파일
//

#pragma once


// CGLIMProjDlg 대화 상자
class CGLIMProjDlg : public CDialogEx
{
	// 생성입니다.
public:
	CGLIMProjDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMPROJ_DIALOG };
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
	int m_edit_line_width;
	int m_edit_radius;
	void drawCircle(int x, int y, int nRadius, int nGray, int mode);
	bool isinCircle(int i, int j, int nCenterX, int nCenterY, int nRadius, int mode);
	void UpdateDisplay();
	void drawInit();
	void drawBigCircle();
	void ThreadWorker();

private:
	CImage m_image;
	int nWidth;
	int nHeight;
	CPoint cpoint[3];
	int pointnum;
	unsigned char* fm;
	bool bInit;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonRandom();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
