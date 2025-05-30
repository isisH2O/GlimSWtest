
// GLIMProjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GLIMProj.h"
#include "GLIMProjDlg.h"
#include "afxdialogex.h"

// 헤더 파일 설정
#include <thread>
#include <chrono>
#include <random>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 고정상수 정의
#define POINT_NUM		3
#define RANDOM_MAX_NUM	10

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


// CGLIMProjDlg 대화 상자
CGLIMProjDlg::CGLIMProjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMPROJ_DIALOG, pParent)
	, m_edit_line_width(5)
	, m_edit_radius(10)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGLIMProjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LINE_WIDTH, m_edit_line_width);
	DDV_MinMaxInt(pDX, m_edit_line_width, 1, 10);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_edit_radius);
}

BEGIN_MESSAGE_MAP(CGLIMProjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_INIT, &CGLIMProjDlg::OnBnClickedButtonInit)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_RANDOM, &CGLIMProjDlg::OnBnClickedButtonRandom)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CGLIMProjDlg 메시지 처리기

BOOL CGLIMProjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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
	pointnum = 0; // 세 점을 찍는지 확인
	for (int i = 0; i < POINT_NUM; i++)
		cpoint[i] = CPoint(0, 0); // 세 점에 대한 포인트 변수 초기화
	bInit = false; // 이미지 출력을 위한 CImage 생성 확인용

	SetTimer(0, 100, NULL); // 100ms 타이머 설정

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGLIMProjDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGLIMProjDlg::OnPaint()
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
HCURSOR CGLIMProjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 원을 그리는 함수
// mode = 0 : nGray로 채워진 원
// mode = 1 : nGray로 라인 두께로 그려진 원
void CGLIMProjDlg::drawCircle(int x, int y, int nRadius, int nGray, int mode)
{
	int nCenterX = x + nRadius;
	int nCenterY = y + nRadius;
	int nPitch = m_image.GetPitch();

	for (int j = y; j < y + nRadius * 2; j++) {
		for (int i = x; i < x + nRadius * 2; i++) {
			if (isinCircle(i, j, nCenterX, nCenterY, nRadius, mode))
				if ((i >= 0 && i < nWidth) && (j >= 0 && j < nHeight))
					fm[j * nPitch + i] = nGray;
		}
	}
}

// 원을 그리기 위해 반지름 내의 좌표인지를 확인하는 함수
// mode = 0 : 채워진 원
// mode = 1 : 지정된 라인 두께(m_edit_line_width)로 그려진 원
bool CGLIMProjDlg::isinCircle(int i, int j, int nCenterX, int nCenterY, int nRadius, int mode)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (mode == 0) {
		if (dDist < nRadius * nRadius)
			bRet = true;
	}
	else {
		if (dDist < (nRadius * nRadius) && dDist >(nRadius - m_edit_line_width) * (nRadius - m_edit_line_width))
			bRet = true;
	}

	return bRet;
}

// 세 점을 잇는 큰 원을 그리는 함수
void CGLIMProjDlg::drawBigCircle()
{
	CPoint center;
	double radius;

	double d = cpoint[0].x * (cpoint[1].y - cpoint[2].y) - cpoint[0].y * (cpoint[1].x - cpoint[2].x)
		+ cpoint[1].x * cpoint[2].y - cpoint[2].x * cpoint[1].y;

	if (fabs(d) >= 1e-10) { // 세 점이 일직선이 아닌 경우
		double A1 = cpoint[1].x - cpoint[0].x;
		double B1 = cpoint[1].y - cpoint[0].y;
		double C1 = (A1 * (cpoint[0].x + cpoint[1].x) + B1 * (cpoint[0].y + cpoint[1].y)) / 2.0;

		double A2 = cpoint[2].x - cpoint[0].x;
		double B2 = cpoint[2].y - cpoint[0].y;
		double C2 = (A2 * (cpoint[0].x + cpoint[2].x) + B2 * (cpoint[0].y + cpoint[2].y)) / 2.0;

		double D = A1 * B2 - A2 * B1;

		if (fabs(D) >= 1e-10) {  // 세 점이 일직선이 아닌 경우
			// 원의 중심
			center.x = (C1 * B2 - C2 * B1) / D;
			center.y = (A1 * C2 - A2 * C1) / D;

			// 반지름 계산
			radius = sqrt(pow(center.x - cpoint[0].x, 2) + pow(center.y - cpoint[0].y, 2));

			drawCircle(center.x - radius - m_edit_line_width / 2, center.y - radius - m_edit_line_width / 2, (int)radius, 255, 1);
		}
	}
}

// 세 점을 찍는 함수 : 3점을 초과하면 "초기화" 버튼을 누르기 전까지 점이 안찍힘.
void CGLIMProjDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (bInit) {
		UpdateData(TRUE);

		int imgX = point.x - m_edit_radius; // 원의 반지름을 고려하여 현재 포인트에서 
		int imgY = point.y - m_edit_radius; // 반지름을 뺀 위치에 원을 그림

		if (pointnum < POINT_NUM) {
			if (imgX >= 0 && imgX < nWidth && imgY >= 0 && imgY < nHeight) {
				drawCircle(imgX, imgY, m_edit_radius, 255, 0);
			}

			cpoint[pointnum].x = point.x;
			cpoint[pointnum].y = point.y;

			if (++pointnum == POINT_NUM) {
				drawBigCircle();
			}

			UpdateDisplay();
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

// 화면 재 표시
void CGLIMProjDlg::UpdateDisplay()
{
	CClientDC dc(this);
	m_image.Draw(dc, 0, 0);
}

// m_image 버퍼 및 칼라테이블 초기화(?)
void CGLIMProjDlg::drawInit()
{
	m_image.Destroy();
	m_image.Create(nWidth, nHeight, 8);

	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++)
		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

	m_image.SetColorTable(0, 256, rgb);
}

// 세 점을 다시 찍을 수 있도록 화면과 변수 초기화
void CGLIMProjDlg::OnBnClickedButtonInit()
{
	if (bInit) {
		pointnum = 0;
		drawInit();
		UpdateDisplay();
	}
}

// 왼쪽 마우스 클릭하면서 마우스 커서를 움직이는 상태 확인
// 이미 찍힌 세 점의 위치 중에서 하나를 확인하여 확장 또는 재 생성
void CGLIMProjDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON) {
		if (pointnum == 3) {
			int sel = 99; // 이미 찍은 3점 중에 한 점을 클릭하는지 확인
			for (int i = 0; i < POINT_NUM; i++) {
				if (cpoint[i].x > (point.x - m_edit_radius) && cpoint[i].x < (point.x + m_edit_radius)) {
					if (cpoint[i].y > (point.y - m_edit_radius) && cpoint[i].y < (point.y + m_edit_radius)) {
						sel = i;
						cpoint[i].x = point.x;
						cpoint[i].y = point.y;
						break;
					}
				}
			}

			if (sel != 99) {
				drawInit();

				for (int i = 0; i < POINT_NUM; i++)
					drawCircle(cpoint[i].x - m_edit_radius, cpoint[i].y - m_edit_radius, m_edit_radius, 255, 0);
				drawBigCircle();

				UpdateDisplay();
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CGLIMProjDlg::ThreadWorker()
{
	const std::chrono::milliseconds interval(500); // 0.5초 간격 설정

	// 랜덤 설정
	// x 범위 : m_edit_radius ~ (nWidth - m_edit_radius)
	// y 범위 : m_edit_radius ~ (nHeight - m_edit_radius)
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> randX(m_edit_radius, nWidth - m_edit_radius);
	std::uniform_int_distribution<> randY(m_edit_radius, nHeight - m_edit_radius);

	for (int i = 0; i < RANDOM_MAX_NUM; i++) {
		drawInit(); // 화면 초기화

		for (int j = 0; j < POINT_NUM; j++) {
			int x = randX(gen);
			int y = randY(gen);

			cpoint[j].x = x;
			cpoint[j].y = y;

			drawCircle(cpoint[j].x - m_edit_radius, cpoint[j].y - m_edit_radius, m_edit_radius, 255, 0);
		}

		drawBigCircle();
		UpdateDisplay();

		std::this_thread::sleep_for(interval); // 0.5초 기다림
	}
}

void CGLIMProjDlg::OnBnClickedButtonRandom()
{
	if (bInit) {
		std::thread worker(&CGLIMProjDlg::ThreadWorker, this); // 스래드 설정

		worker.detach(); // 백그라운드 실행
	}
}

// 타이머에 의해 이미지를 출력하는 화면 생성
void CGLIMProjDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0) {
		CRect rect;
		CClientDC dc(this);

		GetClientRect(&rect);

		nWidth = rect.Width();
		nHeight = rect.Height() - 80;

		m_image.Create(nWidth, nHeight, 8);

		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_image.SetColorTable(0, 256, rgb);

		m_image.Draw(dc, 0, 0);

		fm = (unsigned char*)m_image.GetBits();

		bInit = true; // 이미지 생성 확인 

		KillTimer(0);
	}

	CDialogEx::OnTimer(nIDEvent);
}
