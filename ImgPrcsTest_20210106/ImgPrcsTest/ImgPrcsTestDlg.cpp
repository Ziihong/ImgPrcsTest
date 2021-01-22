
// ImgPrcsTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ImgPrcsTest.h"
#include "ImgPrcsTestDlg.h"




// QR test
#include "zxing/LuminanceSource.h"

using namespace zxing;

#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/common/HybridBinarizer.h>
using namespace qrcode;






#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CImgPrcsTestDlg ��ȭ ����




CImgPrcsTestDlg::CImgPrcsTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImgPrcsTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pMainImgBuf = NULL;     // Load Image
	m_hueImgBuf = NULL;
	m_satImgBuf = NULL;
	m_valImgBuf = NULL;
	m_hsvImgBuf = NULL;		 // bgr -> hsv Image	
	m_blobImgBuf = NULL;	 // blob Image
	m_adapThrImgBuf = NULL;  // adaptive threshold Image
	isFileOpen = 0;
	checkBlob = NULL; 
	center_x = 0; center_y = 0;
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
	ON_BN_CLICKED(IDC_BUTTON_DETECT, &CImgPrcsTestDlg::OnBnClickedButtonDetect)
	ON_BN_CLICKED(IDC_BUTTON_BLOB_LABELING, &CImgPrcsTestDlg::OnBnClickedButtonBlobLabeling)
	ON_BN_CLICKED(IDC_BUTTON_ADAPTIVE_THRESHOLD, &CImgPrcsTestDlg::OnBnClickedButtonAdaptiveThreshold)
	ON_BN_CLICKED(IDC_BUTTON_QR_CODE, &CImgPrcsTestDlg::OnBnClickedButtonQrCode)
END_MESSAGE_MAP()


// CImgPrcsTestDlg �޽��� ó����

BOOL CImgPrcsTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.


	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CImgPrcsTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
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

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	char szFilter[] = "image(*.jpg;*.bmp;*.png)|*.jpg;*.bmp;*.png|";

	CFileDialog dlg(TRUE, NULL,NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,(CString)szFilter,NULL);

	if(IDOK != dlg.DoModal()){
		AfxMessageBox(_T("������ �������� �ʾҽ��ϴ�."));
		return; 
	}
	
	// ���� ����ϱ� �� �޸� �Ҵ� ����
	if(m_pMainImgBuf)	cvReleaseImage(&m_pMainImgBuf);
	if(m_hueImgBuf)		cvReleaseImage(&m_hueImgBuf);
	if(m_satImgBuf)		cvReleaseImage(&m_satImgBuf);
	if(m_valImgBuf)		cvReleaseImage(&m_valImgBuf);
	if(m_hsvImgBuf)		cvReleaseImage(&m_hsvImgBuf);
	if(m_blobImgBuf)	cvReleaseImage(&m_blobImgBuf);
	if(m_adapThrImgBuf) cvReleaseImage(&m_adapThrImgBuf);

	m_pMainImgBuf = cvLoadImage((char*)(LPCTSTR)dlg.GetPathName());

	DisplayImage(m_pMainImgBuf);
	
	// h, s, v�� ����
	m_hueImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	m_satImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	m_valImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	cvSplit(m_pMainImgBuf, m_hueImgBuf, m_satImgBuf, m_valImgBuf, NULL);

	isFileOpen = 1;

	m_hsvImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 3);
	cvCvtColor(m_pMainImgBuf, m_hsvImgBuf, CV_BGR2HSV);

	SetDlgItemInt(IDC_EDIT_HUE_LOWER, 0);
	SetDlgItemInt(IDC_EDIT_HUE_UPPER, 180);
	SetDlgItemInt(IDC_EDIT_SAT_LOWER, 0);
	SetDlgItemInt(IDC_EDIT_SAT_UPPER, 255);
	SetDlgItemInt(IDC_EDIT_VAL_LOWER, 0);
	SetDlgItemInt(IDC_EDIT_VAL_UPPER, 255);
}


void CImgPrcsTestDlg::OnBnClickedButtonOrigin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	DisplayImage(m_pMainImgBuf);
}


void CImgPrcsTestDlg::OnBnClickedButtonHue()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	DisplayImage(m_hueImgBuf);
	
}

void CImgPrcsTestDlg::OnBnClickedButtonSat()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	DisplayImage(m_satImgBuf);
}

void CImgPrcsTestDlg::OnBnClickedButtonVal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	DisplayImage(m_valImgBuf);
}

BOOL CImgPrcsTestDlg::DestroyWindow(){
	
	cvReleaseImage( &m_pMainImgBuf );
	cvReleaseImage( &m_hueImgBuf );
	cvReleaseImage( &m_satImgBuf );
	cvReleaseImage( &m_valImgBuf );
	cvReleaseImage( &m_hsvImgBuf );
	cvReleaseImage( &m_blobImgBuf );
	cvReleaseImage( &m_adapThrImgBuf );

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


void CImgPrcsTestDlg::OnBnClickedButtonDetect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	
	if(m_hsvImgBuf) cvReleaseImage(&m_hsvImgBuf);
	m_hsvImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 3);
	cvCvtColor(m_pMainImgBuf, m_hsvImgBuf, CV_BGR2HSV);

	
	int hue_rangeLower = GetDlgItemInt(IDC_EDIT_HUE_LOWER);
	int hue_rangeUpper = GetDlgItemInt(IDC_EDIT_HUE_UPPER);
	int sat_rangeLower = GetDlgItemInt(IDC_EDIT_SAT_LOWER);
	int sat_rangeUpper = GetDlgItemInt(IDC_EDIT_SAT_UPPER);
	int val_rangeLower = GetDlgItemInt(IDC_EDIT_VAL_LOWER);
	int val_rangeUpper = GetDlgItemInt(IDC_EDIT_VAL_UPPER);
	 

	// user input nothing || out of range
	if(hue_rangeLower <= 0)							{ hue_rangeLower = 0;		SetDlgItemInt(IDC_EDIT_HUE_LOWER, 0); }
	if(sat_rangeLower <= 0)							{ sat_rangeLower = 0;		SetDlgItemInt(IDC_EDIT_SAT_LOWER, 0); }
	if(val_rangeLower == 0)							{ val_rangeLower = 0;		SetDlgItemInt(IDC_EDIT_VAL_LOWER, 0); }
	if(hue_rangeUpper == 0 || hue_rangeUpper > 180) { hue_rangeUpper = 180;		SetDlgItemInt(IDC_EDIT_HUE_UPPER, 180); }
	if(sat_rangeUpper == 0 || sat_rangeUpper > 255) { sat_rangeUpper = 255;		SetDlgItemInt(IDC_EDIT_SAT_UPPER, 255); }
	if(val_rangeUpper == 0 || val_rangeUpper > 255) { val_rangeUpper = 255;		SetDlgItemInt(IDC_EDIT_VAL_UPPER, 255); }


	// detect Image
	if(hue_rangeLower > hue_rangeUpper){
		int temp = hue_rangeUpper;
		hue_rangeUpper = hue_rangeLower;
		hue_rangeLower = temp;
	}

	if(sat_rangeLower > sat_rangeUpper){
		int temp = sat_rangeUpper;
		sat_rangeUpper = sat_rangeLower;
		sat_rangeLower = temp;
	}

	if(val_rangeLower > val_rangeUpper){
		int temp = val_rangeUpper;
		val_rangeUpper = val_rangeLower;
		val_rangeLower = temp;
	}

	for(int col=0; col<m_hsvImgBuf->widthStep; col+=m_hsvImgBuf->nChannels){
		for (int row=0; row<m_hsvImgBuf->height; row++){
			
			int idx = col + row*m_hsvImgBuf->widthStep;
			unsigned char h = m_hsvImgBuf->imageData[idx];
			unsigned char s = m_hsvImgBuf->imageData[idx+1];
			unsigned char v = m_hsvImgBuf->imageData[idx+2];
			
			//yellow->!(20<=h && h<=32)
			//blue->!(90<h && h<120)
			//green->!(30<h && h<80)
			if(!(hue_rangeLower<=h && h<=hue_rangeUpper && sat_rangeLower<=s && s<=sat_rangeUpper && val_rangeLower<=v && v<=val_rangeUpper)){
				m_hsvImgBuf->imageData[idx] = 0;
				m_hsvImgBuf->imageData[idx+1] = 0; 
				m_hsvImgBuf->imageData[idx+2] = 0;
			}
		}
	}

	cvCvtColor(m_hsvImgBuf, m_hsvImgBuf, CV_HSV2BGR);  // m_hsvImgBuf -> bgr Image

	DisplayImage(m_hsvImgBuf);
}


void CImgPrcsTestDlg::OnBnClickedButtonBlobLabeling()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}

	// clone detect Image
	if(m_blobImgBuf) cvReleaseImage(&m_blobImgBuf);
	m_blobImgBuf = cvCloneImage(m_hsvImgBuf);

	int countRow = m_blobImgBuf->height;
	int countCol = m_blobImgBuf->widthStep;
	
	checkBlob = new int[countCol + countRow*countCol];


	// checkBlob initialize
	for(int col=0; col<countCol; col++){
		for (int row=0; row<countRow; row++){
			int idx = col + row*countCol;
			checkBlob[idx] = 0;
		}
	}

	int val_rangeBlob = GetDlgItemInt(IDC_EDIT_BLOB_VAL);
	if(val_rangeBlob <= 0)	val_rangeBlob = 0;
	else if(val_rangeBlob > 255) val_rangeBlob = 255;
	

	int label_h = 10;
	for(int col=0; col<countCol; col+=m_blobImgBuf->nChannels){
		for (int row=0; row<countRow; row++){
			
			int idx = col + row*countCol;
			unsigned char h = m_blobImgBuf->imageData[idx];
			unsigned char s = m_blobImgBuf->imageData[idx+1];
			unsigned char v = m_blobImgBuf->imageData[idx+2];
			
			if(!(val_rangeBlob < v)){
				m_blobImgBuf->imageData[idx] = 0;
				m_blobImgBuf->imageData[idx+1] = 0; 
				m_blobImgBuf->imageData[idx+2] = 0;
			}
			else{
				m_blobImgBuf->imageData[idx] = 255;
				m_blobImgBuf->imageData[idx+1] = 255;
				m_blobImgBuf->imageData[idx+2] = 255;
				
				checkBlob[idx] = 1;
			} 
		}
	}
	

	// blob labeling
	for(int col=0; col<countCol; col+=m_blobImgBuf->nChannels){
		for(int row=0; row<countRow; row++){
			int blobPixel;	// blob size
			int idx = col + row*countCol;

			if(checkBlob[idx] == 1){
				center_x = 0; center_y = 0;

				blobPixel = blobSize(m_blobImgBuf, label_h, row, col);
				center_x /= blobPixel;
				center_y /= blobPixel;
			
				cvCircle(m_blobImgBuf, cvPoint(center_y, center_x), 1, cvScalar((label_h+90), 255, 255));

				label_h += 10;			
			}
		}	
	}
	
	cvCvtColor(m_blobImgBuf, m_blobImgBuf, CV_HSV2BGR);

	DisplayImage(m_blobImgBuf);

	delete[] checkBlob;

}

int CImgPrcsTestDlg::blobSize(IplImage* image, int label_h, int row, int col){
	int countRow = image->height;
	int countCol = image->widthStep;
	int idx = col + row*countCol;

	if(col<0 || row<0 || col>countCol-1 || row>countRow-1){
		return 0;
	}
	
	if(checkBlob[idx] != 1 || checkBlob[idx] == 0) return 0;
	

	// 2�̻����� labeling
	checkBlob[idx] = label_h/10+1;

	// labeling ������ �߽� ��ǥ
	center_x += row;
	center_y += col/3;

	m_blobImgBuf->imageData[idx] = label_h;
	m_blobImgBuf->imageData[idx+1] = 255;
	m_blobImgBuf->imageData[idx+2] = 255;

	
	return 1+blobSize(image, label_h, row, col-3)
		+blobSize(image, label_h, row+1, col-3)
		+blobSize(image, label_h, row+1, col)
		+blobSize(image, label_h, row+1, col+3)
		+blobSize(image, label_h, row, col+3)
		+blobSize(image, label_h, row-1, col+3)
		+blobSize(image, label_h, row-1, col)
		+blobSize(image, label_h, row-1, col-3);
}


void CImgPrcsTestDlg::OnBnClickedButtonAdaptiveThreshold()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}

	m_adapThrImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	cvAdaptiveThreshold(m_valImgBuf, m_adapThrImgBuf, 250, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 31, 0);

	DisplayImage(m_adapThrImgBuf);


	// adaptive threshold �̹��� ����
	cvSaveImage("C:\\Users\\user\\Pictures\\Saved Pictures\\adapThr_QR.jpg", m_adapThrImgBuf);
}



void CImgPrcsTestDlg::OnBnClickedButtonQrCode()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	CImage image;
	CFileDialog fd(TRUE);
	CString strFileName = " ";
	if(fd.DoModal() != IDOK)
	{
		AfxMessageBox(_T("������ �������� �ʾҽ��ϴ�."));
		return;
	}
	
	strFileName = fd.GetPathName();

	image.Load(strFileName);
	CClientDC dc(this);
	CRect rtRect(100,100,image.GetWidth() + 100,image.GetHeight() + 100);
	image.BitBlt(dc.m_hDC,rtRect,CPoint(0,0));

	CBitmap* pBitmap = CBitmap::FromHandle(image);   //��ü�� ���� ������ ��ȯ
	
	if(pBitmap)
	{
		BITMAP bmp;
		pBitmap->GetBitmap(&bmp);   //��Ʈ�� �̹��� �Ӽ� �˻�
		DWORD dwBitCount = bmp.bmHeight * bmp.bmWidthBytes+1000;
		BYTE *bData = new BYTE[dwBitCount];
		dwBitCount = pBitmap->GetBitmapBits(dwBitCount, bData);
		RGBTRIPLE* p = (RGBTRIPLE*)bData;
		BYTE *bGraData = new BYTE[dwBitCount];

			int nImageIndex =   (dwBitCount / bmp.bmHeight);
			for(int iter = 0; iter <bmp.bmHeight; iter++ )
			{
				if(bmp.bmBitsPixel == 8)
				{
					memcpy(bGraData,bData,dwBitCount);
					break;
				}
				for(int iterA = 0; iterA < bmp.bmWidth; iterA++)
				{
				
					if(bmp.bmBitsPixel == 24)
					{
						int nIndex = iter * (bmp.bmWidth) + iterA;
						int nIndexRGB = iter * (nImageIndex) + iterA*3;
						int nRGB = bData[nIndexRGB ]*0.299 +bData[nIndexRGB +1]*0.587+ bData[nIndexRGB +2]*0.114;
						bGraData[nIndex] = nRGB;
						if(bGraData[nIndex] > 130)
						{
							//TRACE("X");
						}else
						{
							//TRACE(" ");
						}
					}
				}
				TRACE("\n");
			}

			
			// �� �Ʒ� �κ� ���� Ȱ�� 

			/*  Edit
			// m_adapThreImgBuf -> QR �ν�
			// IplImage to byte
			
			BYTE *bGraData;
			BITMAP bmp;
			bGraData = new BYTE[m_adapThrImgBuf->widthStep*m_adapThrImgBuf->height];
			memcpy(bGraData, m_adapThrImgBuf->imageData, m_adapThrImgBuf->imageSize);
			*/	
			

			GreyscaleLuminanceSource*  GLS = new GreyscaleLuminanceSource(bGraData, bmp.bmWidth, bmp.bmHeight, 0, 0, bmp.bmWidth, bmp.bmHeight);
			//LuminanceSource* pLs = (LuminanceSource* )&GLS;

			Ref<LuminanceSource> tLs;
			Ref<Binarizer> Br;
			Ref<BinaryBitmap> BinaryBit;
			Ref<Result> RefResult;
		
			//Ref<LuminanceSource> tLs = (Ref<LuminanceSource>)pLs;
		
			tLs = GLS;
			GlobalHistogramBinarizer *GHB = new GlobalHistogramBinarizer (tLs);
		
			Br = GHB;
			BinaryBitmap* BB = new BinaryBitmap(Br);		
		
			BinaryBit = BB;
			MultiFormatReader MRF;
			try
			{
				double dMax = fmax(10,100);  // ū ��
				dMax = fminl(10,100);		 // ���� ��
				dMax = fmaxl(10,100);		 // ū ��

				QRCodeReader qrReader;
				DecodeHints dh;
				dh.addFormat(BarcodeFormat_QR_CODE);		// ���ڴ� �غ�
		
				RefResult = qrReader.decode(BinaryBit,dh);	// ���ڵ� ���
				//MultiFormatReader MFR;					// ���ڵ� ���� ���ڵ�
				//RefResult  = MFR.decode(BinaryBit);
				AfxMessageBox(CString(RefResult->getText()->getText().c_str()));
				//break;

			}catch(zxing::Exception e)
			{
				CString strTemp;
				strTemp.Format(_T("%s"), CA2W(e.what()));
				AfxMessageBox(_T("QR code�� ã�� �� �����ϴ�."));
				TRACE("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				//continue;
			}

		

		//BinaryBit->release();
		//Br->release();
		//tLs->release();
		
		
		pBitmap->DeleteObject();
		delete[] bData;
		delete[] bGraData;
		

		//Br->release();
		
		//RefResult->release();
		//BinaryBit->release();
		
		//strTemp.Format(_T("%s"),RefResult->getText()->getText());	
	}

}
