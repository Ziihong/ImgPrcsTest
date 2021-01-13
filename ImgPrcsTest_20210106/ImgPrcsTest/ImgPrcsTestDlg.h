
// ImgPrcsTestDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"


// CImgPrcsTestDlg ��ȭ ����
class CImgPrcsTestDlg : public CDialog
{
// �����Դϴ�.
public:
	CImgPrcsTestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_IMGPRCSTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
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
	
	// �ʱ�ȭ
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
