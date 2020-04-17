// ds18b20Dlg.h : header file
//

#if !defined(AFX_DS18B20DLG_H__8CF520BF_6470_4DDC_A4B8_27A170492CC1__INCLUDED_)
#define AFX_DS18B20DLG_H__8CF520BF_6470_4DDC_A4B8_27A170492CC1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDs18b20Dlg dialog

class CDs18b20Dlg : public CDialog
{
// Construction
public:
	CDs18b20Dlg(CWnd* pParent = NULL);	// standard constructor
	CString SelectFile();
// Dialog Data
	//{{AFX_DATA(CDs18b20Dlg)
	enum { IDD = IDD_DS18B20_DIALOG };
	CString	m_CmdFileStr;
	UINT	m_ChNum;
	UINT	m_RomNum;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDs18b20Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDs18b20Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton2();
	afx_msg void OnButton1();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DS18B20DLG_H__8CF520BF_6470_4DDC_A4B8_27A170492CC1__INCLUDED_)
