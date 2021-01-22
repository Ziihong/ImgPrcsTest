
// ImgPrcsTestDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"


// CImgPrcsTestDlg 대화 상자
class CImgPrcsTestDlg : public CDialog
{
// 생성입니다.
public:
	CImgPrcsTestDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_IMGPRCSTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	virtual BOOL DestroyWindow();
	afx_msg void OnDestroy();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	IplImage* m_pMainImgBuf;
	IplImage* m_hueImgBuf;
	IplImage* m_satImgBuf;
	IplImage* m_valImgBuf;
	IplImage* m_detectImgBuf;  // hsv로 변환 후 색 검출
	IplImage* m_blobImgBuf;    // hsv로 변환 후 이미지 blob labeling
	IplImage* m_adapThrImgBuf;
	CStatic m_DispCtrl;
	int isFileOpen;
	int hue_rangeLower, hue_rangeUpper;
	int sat_rangeLower, sat_rangeUpper; 
	int	val_rangeLower, val_rangeUpper;
	int val_rangeBlob;
	int* checkBlob;  // iplimage->1차원 배열 형태로
	int center_x, center_y;

public:
	void DisplayImage(IplImage* pImage);//, CDC *pDC, CRect& rect);
	IplImage* Mat_toIpl(Mat img);
	Mat Ipl_toMat(IplImage* img);
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonHue();
	afx_msg void OnBnClickedButtonSat();
	afx_msg void OnBnClickedButtonVal();
	afx_msg void OnBnClickedButtonOrigin();
	afx_msg void OnBnClickedButtonDetect();
	afx_msg void OnBnClickedButtonAdaptiveThreshold();
	afx_msg void OnBnClickedButtonBlobLabeling();
	afx_msg void OnEnChangeEditHueLower();
	afx_msg void OnEnChangeEditHueUpper();
	afx_msg void OnEnChangeEditSatLower();
	afx_msg void OnEnChangeEditSatUpper();
	afx_msg void OnEnChangeEditValLower();
	afx_msg void OnEnChangeEditValUpper();
	afx_msg void OnEnChangeEditBlobVal();
	afx_msg void OnBnClickedButtonQrCode();
	int blobSize(IplImage* image, int h_idx, int row, int col);
};
