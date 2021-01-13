
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
	IplImage* hueBuf;
	IplImage* satBuf;
	IplImage* valBuf;
	IplImage* convertImgBuf;
	IplImage* displayImgBuf;
	CStatic m_DispCtrl;
	int isFileOpen;
	

public:
	void DisplayImage(IplImage* pImage);//, CDC *pDC, CRect& rect);
	IplImage* Mat_toIpl(Mat img);
	Mat Ipl_toMat(IplImage* img);
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonHue();
	afx_msg void OnBnClickedButtonSat();
	afx_msg void OnBnClickedButtonVal();
	afx_msg void OnBnClickedButtonOrigin();

	afx_msg void OnBnClickedButtonDetectYellowFun();
	afx_msg void OnBnClickedButtonDetectYellowPixel();
	
	// 초기화
	int hue_rangeLower, hue_rangeUpper, hue_EditLower, hue_EditUpper;
	int sat_rangeLower, sat_rangeUpper, sat_EditLower, sat_EditUpper; 
	int	val_rangeLower, val_rangeUpper, val_EditLower, val_EditUpper;
	afx_msg void OnEnChangeEditHueLower();
	afx_msg void OnEnChangeEditHueUpper();
	afx_msg void OnEnChangeEditSatLower();
	afx_msg void OnEnChangeEditSatUpper();
	afx_msg void OnEnChangeEditValLower();
	afx_msg void OnEnChangeEditValUpper();
	afx_msg void OnBnClickedButtonDetect();
};
