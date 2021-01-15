
// ImgPrcsTestDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "ImgPrcsTest.h"
#include "ImgPrcsTestDlg.h"


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
	hueBuf = NULL;
	satBuf = NULL;
	valBuf = NULL;
	convertImgBuf = NULL;	 // bgr to hsv Image	
	displayImgBuf = NULL;	 // hsv to bgr Image
	isFileOpen = 0;
	hue_rangeLower = 0; hue_rangeUpper = 180; 
	sat_rangeLower = 0; sat_rangeUpper = 255; 
	val_rangeLower = 0; val_rangeUpper = 255; 
	val_rangeBlob = 0; 
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
	ON_EN_CHANGE(IDC_EDIT_HUE_LOWER, &CImgPrcsTestDlg::OnEnChangeEditHueLower)
	ON_EN_CHANGE(IDC_EDIT_HUE_UPPER, &CImgPrcsTestDlg::OnEnChangeEditHueUpper)
	ON_EN_CHANGE(IDC_EDIT_SAT_LOWER, &CImgPrcsTestDlg::OnEnChangeEditSatLower)
	ON_EN_CHANGE(IDC_EDIT_SAT_UPPER, &CImgPrcsTestDlg::OnEnChangeEditSatUpper)
	ON_EN_CHANGE(IDC_EDIT_VAL_LOWER, &CImgPrcsTestDlg::OnEnChangeEditValLower)
	ON_EN_CHANGE(IDC_EDIT_VAL_UPPER, &CImgPrcsTestDlg::OnEnChangeEditValUpper)
	ON_EN_CHANGE(IDC_EDIT_BLOB_VAL, &CImgPrcsTestDlg::OnEnChangeEditBlobVal)
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
	if(m_pMainImgBuf) cvReleaseImage(&m_pMainImgBuf);
	if(hueBuf) cvReleaseImage(&hueBuf);
	if(satBuf) cvReleaseImage(&satBuf);
	if(valBuf) cvReleaseImage(&valBuf);
	if(convertImgBuf) cvReleaseImage(&convertImgBuf);

	m_pMainImgBuf = cvLoadImage((char*)(LPCTSTR)dlg.GetPathName());

	DisplayImage(m_pMainImgBuf);

	hueBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	satBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	valBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 1);
	cvSplit(m_pMainImgBuf, hueBuf, satBuf, valBuf, NULL);

	isFileOpen = 1;

	// m_pMainImgBuf -> hsv Image
	convertImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 3);
	cvCvtColor(m_pMainImgBuf, convertImgBuf, CV_BGR2HSV);

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
	DisplayImage(hueBuf);
	
}

void CImgPrcsTestDlg::OnBnClickedButtonSat()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	DisplayImage(satBuf);
}

void CImgPrcsTestDlg::OnBnClickedButtonVal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	DisplayImage(valBuf);
}

BOOL CImgPrcsTestDlg::DestroyWindow(){
	
	cvReleaseImage( &m_pMainImgBuf );
	cvReleaseImage( &hueBuf );
	cvReleaseImage( &satBuf );
	cvReleaseImage( &valBuf );
	cvReleaseImage( &displayImgBuf );
	cvReleaseImage( &convertImgBuf );

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
	
	cvReleaseImage(&convertImgBuf);
	convertImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 3);
	cvCvtColor(m_pMainImgBuf, convertImgBuf, CV_BGR2HSV);

	for(int col=0; col<convertImgBuf->widthStep; col+=convertImgBuf->nChannels){
		for (int row=0; row<convertImgBuf->height; row++){
			
			int idx = col + row*convertImgBuf->widthStep;
			unsigned char h = convertImgBuf->imageData[idx];
			unsigned char s = convertImgBuf->imageData[idx+1];
			unsigned char v = convertImgBuf->imageData[idx+2];
			
			//yellow->!(20<=h && h<=32)
			//blue->!(90<h && h<120)
			//green->!(30<h && h<80)
			if(!(hue_rangeLower<=h && h<=hue_rangeUpper && sat_rangeLower<=s && s<=sat_rangeUpper && val_rangeLower<=v && v<=val_rangeUpper)){
				convertImgBuf->imageData[idx] = 0;
				convertImgBuf->imageData[idx+1] = 0; 
				convertImgBuf->imageData[idx+2] = 0;
			}
			else{
				/*
				convertImgBuf->imageData[idx+1] = 0; 
				convertImgBuf->imageData[idx+2] = -1;*/
			}
		}
	}
	
	displayImgBuf = cvCreateImage(cvGetSize(convertImgBuf), IPL_DEPTH_8U, 3);
	cvCvtColor(convertImgBuf, displayImgBuf, CV_HSV2BGR);

	DisplayImage(displayImgBuf);
}


void CImgPrcsTestDlg::OnBnClickedButtonBlobLabeling()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(!isFileOpen){
		AfxMessageBox(_T("���õ� �̹����� �����ϴ�."));
		return;
	}
	/*
	cvReleaseImage(&convertImgBuf);
	convertImgBuf = cvCreateImage(cvGetSize(m_pMainImgBuf), IPL_DEPTH_8U, 3);
	cvCvtColor(m_pMainImgBuf, convertImgBuf, CV_BGR2HSV);
	*/
	int countRow = convertImgBuf->height;
	int countCol = convertImgBuf->widthStep;
	
	checkBlob = new int[countCol + countRow*countCol];


	// checkBlob �ʱ�ȭ
	for(int col=0; col<countCol; col++){
		for (int row=0; row<countRow; row++){
			int idx = col + row*countCol;
			checkBlob[idx] = 0;
		}
	}
	
	int label_h = 10;
	for(int col=0; col<countCol; col+=convertImgBuf->nChannels){
		for (int row=0; row<countRow; row++){
			
			int idx = col + row*countCol;
			unsigned char h = convertImgBuf->imageData[idx];
			unsigned char s = convertImgBuf->imageData[idx+1];
			unsigned char v = convertImgBuf->imageData[idx+2];
			
			if(!(val_rangeBlob < v)){
				convertImgBuf->imageData[idx] = 0;
				convertImgBuf->imageData[idx+1] = 0; 
				convertImgBuf->imageData[idx+2] = 0;
			}
			else{
				convertImgBuf->imageData[idx] = 255;
				convertImgBuf->imageData[idx+1] = 255;
				convertImgBuf->imageData[idx+2] = 255;
				
				checkBlob[idx] = 1;

			} 
		}
	}
	

	// labeling ���� ����
	for(int col=0; col<countCol; col+=convertImgBuf->nChannels){
		for(int row=0; row<countRow; row++){
			int blobPixel;
			int idx = col + row*countCol;

			if(checkBlob[idx] == 1){
				
				blobPixel = blobSize(convertImgBuf, label_h, row, col);
				/*
				CString msg;
				msg.Format(_T("label: %d", blobPixel));
				AfxMessageBox(msg);
				*/
				label_h += 10;
			
			}
		}	
	}
	

	displayImgBuf = cvCreateImage(cvGetSize(convertImgBuf), IPL_DEPTH_8U, 3);
	cvCvtColor(convertImgBuf, displayImgBuf, CV_HSV2BGR);

	DisplayImage(displayImgBuf);

	delete[] checkBlob;

}

int CImgPrcsTestDlg::blobSize(IplImage* image, int label_h, int row, int col){
	int countRow = image->height;
	int countCol = image->widthStep;
	int idx = col + row*countCol;

	if(col<0 || row<0 || col>countCol-1 || row>countRow-1){
		return 0;
	}
	
	if(checkBlob[idx] == 2 || checkBlob[idx] == 0) return 0;

	checkBlob[idx] = 2;

	convertImgBuf->imageData[idx] = label_h;
	convertImgBuf->imageData[idx+1] = 255;
	convertImgBuf->imageData[idx+2] = 255;

	return 1+blobSize(image, label_h, row, col-3)
		+blobSize(image, label_h, row+1, col-3)
		+blobSize(image, label_h, row+1, col)
		+blobSize(image, label_h, row+1, col+3)
		+blobSize(image, label_h, row, col+3)
		+blobSize(image, label_h, row-1, col+3)
		+blobSize(image, label_h, row-1, col)
		+blobSize(image, label_h, row-1, col-3);
}



void CImgPrcsTestDlg::OnEnChangeEditHueLower()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	hue_rangeLower = GetDlgItemInt(IDC_EDIT_HUE_LOWER);
	if(hue_rangeLower < 0) hue_rangeLower = 0;
	
}

void CImgPrcsTestDlg::OnEnChangeEditHueUpper()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	hue_rangeUpper = GetDlgItemInt(IDC_EDIT_HUE_UPPER);
	if(hue_rangeUpper > 180) hue_rangeUpper = 180;
	
}

void CImgPrcsTestDlg::OnEnChangeEditSatLower()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	sat_rangeLower = GetDlgItemInt(IDC_EDIT_SAT_LOWER);
	if(sat_rangeLower < 0) sat_rangeLower = 0;
	
}

void CImgPrcsTestDlg::OnEnChangeEditSatUpper()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	sat_rangeUpper = GetDlgItemInt(IDC_EDIT_SAT_UPPER);
	if(sat_rangeUpper > 255) sat_rangeUpper = 255;
	
}

void CImgPrcsTestDlg::OnEnChangeEditValLower()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	val_rangeLower = GetDlgItemInt(IDC_EDIT_VAL_LOWER);
	if(val_rangeLower < 0) val_rangeLower = 0;

}

void CImgPrcsTestDlg::OnEnChangeEditValUpper()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	val_rangeUpper = GetDlgItemInt(IDC_EDIT_VAL_UPPER);
	if(val_rangeUpper > 255) val_rangeUpper = 255;
}

void CImgPrcsTestDlg::OnEnChangeEditBlobVal()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	val_rangeBlob = GetDlgItemInt(IDC_EDIT_BLOB_VAL);
	if(val_rangeBlob < 0) val_rangeBlob = 0;
}
