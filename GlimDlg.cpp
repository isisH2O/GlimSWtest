#include "pch.h"
#include <iostream>

#include <atlimage.h>

#include "framework.h"
#include "Glim.h"
#include "GlimDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#pragma comment(linker, "/entry:mainCRTStartup /subsystem:console")
#endif

using namespace std;

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	
	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	//AfxMessageBox(_T("hello windows"));
	
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGlimDlg 대화 상자
CGlimDlg::CGlimDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIM_DIALOG, pParent), m_nNum(0), m_nNum2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimDlg::OnBnClickedButton1()
{
	//AfxMessageBox(_T("hello windows"));
	//int nTest = 85;
	//m_nNum = nTest;
	UpdateData(true);

	/* int nSum = 0;
		for (int i = 0;i < m_nNum; i++) {
		cout << i << endl;
			nSum += i;
		}
		m_nNum = nSum;*/

	int nSum = m_nNum + m_nNum2;
	cout << m_nNum << " + " << m_nNum2 << " = " << nSum << endl;

	CString strResult;
	strResult.Format(_T("%d"), nSum);
	SetDlgItemText(IDC_STATIC_RESULT, strResult);

	UpdateData(false);
}

void CGlimDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  기존 컨트롤 객체 바인딩 제거 DDX_Control(pDX, IDC_EDIT1, m_nNum);
	DDX_Text(pDX, IDC_EDIT1, m_nNum);
	DDX_Text(pDX, IDC_EDIT2, m_nNum2);
}

BEGIN_MESSAGE_MAP(CGlimDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGlimDlg::OnBnClickedButton1) 
	ON_EN_CHANGE(IDC_EDIT1, &CGlimDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGlimDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CGlimDlg 메시지 처리기

BOOL CGlimDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_nNum = 100; 
	m_nNum2 = 0;
	UpdateData(FALSE); 
	
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	SetDlgItemText(IDC_STATIC_RESULT, _T("0"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CAboutDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	AfxMessageBox(_T("About button clicked"));
	UpdateData(false);
}


void CGlimDlg::OnEnChangeEdit1()
{
	
}


void CGlimDlg::OnBnClickedButton2()
{
	int nWidth = 500;
	int nHeight = 320;
	int nBpp = 8;

	m_Image.Create(nWidth, nHeight, 8);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++) {
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		}
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = abs(m_Image.GetPitch());
	if (nPitch < nWidth) {
		AfxMessageBox(_T("Pitch 값이 너무 작습니다."));
		return;
	}

	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	if (fm == nullptr) {
		AfxMessageBox(_T("비트 포인터 가져오기 실패"));
		return;
	}

	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			fm[j * nPitch + i] = j % 256;
		}
	}

	CClientDC dc(this);
	m_Image.Draw(dc, 15, 60);
}
