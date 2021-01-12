
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
	
	afx_msg void OnBnClickedButtonDetectYellow();
	afx_msg void OnBnClickedButtonOrigin();
};
