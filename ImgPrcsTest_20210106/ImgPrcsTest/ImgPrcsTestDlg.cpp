
// ImgPrcsTestDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "ImgPrcsTest.h"
#include "ImgPrcsTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CImgPrcsTestDlg 대화 상자




CImgPrcsTestDlg::CImgPrcsTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImgPrcsTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMainImgBuf = NULL;
	hueBuf = NULL;
	satBuf = NULL;
	valBuf = NULL;
	isFileOpen = 0;
}

void CImgPrcsTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_MAIN_DISP, m_DispCtrl);
}

BEGIN_MESSAGE_MAP(CImgPrcsTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CImgPrcsTestDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_HUE, &CImgPrcsTestDlg::OnBnClickedButtonHue)
	ON_BN_CLICKED(IDC_BUTTON_SAT, &CImgPrcsTestDlg::OnBnClickedButtonSat)
	ON_BN_CLICKED(IDC_BUTTON_VAL, &CImgPrcsTestDlg::OnBnClickedButtonVal)
	ON_BN_CLICKED(IDC_BUTTON_ORIGIN, &CImgPrcsTestDlg::OnBnClickedButtonOrigin)
	ON_BN_CLICKED(IDC_BUTTON_DETECT_YELLOW, &CImgPrcsTestDlg::OnBnClickedButtonDetectYellowFun)
	ON_BN_CLICKED(IDC_BUTTON_DETECT_YELLOW_PIXEL, &CImgPrcsTestDlg::OnBnClickedButtonDetectYellowPixel)
END_MESSAGE_MAP()


// CImgPrcsTestDlg 메시지 처리기

BOOL CImgPrcsTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.


	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CImgPrcsTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CImgPrcsTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		if(m_pMainImgBuf){
			DisplayImage(m_pMainImgBuf);
		}
		CDialog::OnPaint();
	}

}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CImgPrcsTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CImgPrcsTestDlg::DisplayImage(IplImage* pImage)//, CDC *pDC, CRect& rect)
{
	CDC *pDC = m_DispCtrl.GetDC();
	CRect rect;
	m_DispCtrl.GetClientRect(&rect);

	if (pImage == NULL || pDC == NULL)
		return;



	BITMAPINFO bitmapInfo;
	memset(&bitmapInfo, 0, sizeof(bitmapInfo));
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	
	bitmapInfo.bmiHeader.biWidth = pImage->width;
	bitmapInfo.bmiHeader.biHeight = -pImage->height;

	IplImage *tempImage = NULL;

	if (pImage->nChannels == 1)
	{
		tempImage = cvCreateImage(cvSize(pImage->width, pImage->height), IPL_DEPTH_8U, 3);
		cvCvtColor(pImage, tempImage, CV_GRAY2BGR);
	}
	else if (pImage->nChannels == 3)
	{
		tempImage = cvCloneImage(pImage);
	}

	bitmapInfo.bmiHeader.biBitCount = tempImage->depth * tempImage->nChannels;

	pDC->SetStretchBltMode(COLORONCOLOR);
	::StretchDIBits(pDC->GetSafeHdc(), rect.left, rect.top,
		rect.right, rect.bottom,
		0, 0, tempImage->width, tempImage->height,
		tempImage->imageData, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	
	m_DispCtrl.ReleaseDC(pDC);
	cvReleaseImage(&tempImage);
}

void CImgPrcsTestDlg::OnBnClickedButtonOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	char szFilter[] = "image(*.jpg;*.bmp;*.png)|*.jpg;*.bmp;*.png|";

	CFileDialog dlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(CString)szFilter,NULL);

	if(IDOK != dlg.DoModal()){
		AfxMessageBox(_T("파일을 선택하지 않았습니다."));
		return; 
	}
	
	// 변수 사용하기 전 메모리 할당 해제
	if(m_pMainImgBuf){
		cvReleaseImage(&m_pMainImgBuf);
	}

	m_pMainImgBuf = cvLoadImage((char*)(LPCTSTR)dlg.GetPathName());

	DisplayImage(m_pMainImgBuf);

// Edit by Namjae
	hueBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	satBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	valBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	cvSplit(m_pMainImgBuf, hueBuf, satBuf, valBuf, NULL);
// Edit by Namjae

	isFileOpen = 1;

}
	
	// 얼굴 인식
	//cv::CascadeClassifier face_classifier;
	//face_clasccifier.load("C:\\Users\\us er\\Downloads\\haarcascade_frontalface_default.xml");


void CImgPrcsTestDlg::OnBnClickedButtonOrigin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!isFileOpen){
		AfxMessageBox(_T("선택된 이미지가 없습니다."));
		return;
	}
	DisplayImage(m_pMainImgBuf);
}


void CImgPrcsTestDlg::OnBnClickedButtonHue()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!isFileOpen){
		AfxMessageBox(_T("선택된 이미지가 없습니다."));
		return;
	}
	DisplayImage(hueBuf);
	
}

void CImgPrcsTestDlg::OnBnClickedButtonSat()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!isFileOpen){
		AfxMessageBox(_T("선택된 이미지가 없습니다."));
		return;
	}
	DisplayImage(satBuf);
}

void CImgPrcsTestDlg::OnBnClickedButtonVal()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(!isFileOpen){
		AfxMessageBox(_T("선택된 이미지가 없습니다."));
		return;
	}
	DisplayImage(valBuf);
}

BOOL CImgPrcsTestDlg::DestroyWindow(){
	
	cvReleaseImage( &m_pMainImgBuf );
	cvReleaseImage( &hueBuf );
	cvReleaseImage( &satBuf );
	cvReleaseImage( &valBuf );
	return CDialog::DestroyWindow();
}


// Mat to IplImage*
IplImage* CImgPrcsTestDlg::Mat_toIpl(Mat img){
	IplImage* convertImg;
	convertImg = new IplImage(img);

	return convertImg;
}

// IplImage* to Mat
Mat CImgPrcsTestDlg::Ipl_toMat(IplImage* img){
	Mat convertImg; 
	convertImg = cvarrToMat(img);

	return convertImg;
}

void CImgPrcsTestDlg::OnBnClickedButtonDetectYellowFun()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(!isFileOpen){
		AfxMessageBox(_T("선택된 이미지가 없습니다."));
		return;
	}
	
	//색상 검출
	Mat bgrImg = Ipl_toMat(m_pMainImgBuf);

	Mat hsvImg, yellow_mask, yellowImg;
	IplImage* convertImgBuf;

	cvtColor(bgrImg, hsvImg, COLOR_BGR2HSV);   //hsv변환
	Scalar lower_yellow = Scalar(20, 20, 100);
	Scalar upper_yellow = Scalar(32, 255, 255);

	inRange(hsvImg, lower_yellow, upper_yellow, yellow_mask); //이진화
	bitwise_and(bgrImg, bgrImg, yellowImg, yellow_mask);
	
	convertImgBuf = Mat_toIpl(yellowImg);
	DisplayImage(convertImgBuf);

}

void CImgPrcsTestDlg::OnBnClickedButtonDetectYellowPixel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if(!isFileOpen){
		AfxMessageBox(_T("선택된 이미지가 없습니다."));
		return;
	}

	Mat bgrImg, hsvImg;
	bgrImg = Ipl_toMat(m_pMainImgBuf);
	cvtColor(bgrImg, hsvImg, COLOR_BGR2HSV);
	IplImage* convertImgBuf = Mat_toIpl(hsvImg);
	
	for(int col=0; col<convertImgBuf->widthStep; col+=convertImgBuf->nChannels){
		for (int row=0; row<convertImgBuf->height; row++){
			
			int idx = col + row*convertImgBuf->widthStep;
			char h = convertImgBuf->imageData[idx];
			char s = convertImgBuf->imageData[idx+1];
			char v = convertImgBuf->imageData[idx+2];
			
			//yellow->!(20<=h && h<=32)
			if(!(20<=h && h<=32)){
			convertImgBuf->imageData[idx] = 0;
			convertImgBuf->imageData[idx+1] = 0; 
			convertImgBuf->imageData[idx+2] = 0;
			}
			/*
			else{
			convertImgBuf->imageData[idx] = 254;
			convertImgBuf->imageData[idx+1] = 254; 
			convertImgBuf->imageData[idx+2] = 254;
			}
			*/

		}
	}

	DisplayImage(convertImgBuf);
}
