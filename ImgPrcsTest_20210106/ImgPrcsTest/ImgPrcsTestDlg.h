
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
	IplImage* m_hueImgBuf;
	IplImage* m_satImgBuf;
	IplImage* m_valImgBuf;
	IplImage* m_detectImgBuf;  // hsv�� ��ȯ �� �� ����
	IplImage* m_blobImgBuf;    // hsv�� ��ȯ �� �̹��� blob labeling
	IplImage* m_adapThrImgBuf;
	CStatic m_DispCtrl;
	int isFileOpen;
	int hue_rangeLower, hue_rangeUpper;
	int sat_rangeLower, sat_rangeUpper; 
	int	val_rangeLower, val_rangeUpper;
	int val_rangeBlob;
	int* checkBlob;  // iplimage->1���� �迭 ���·�
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
