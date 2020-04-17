// ds18b20.h : main header file for the DS18B20 application
//

#if !defined(AFX_DS18B20_H__208AB3D9_8CB5_461B_9574_CD5BA08B5177__INCLUDED_)
#define AFX_DS18B20_H__208AB3D9_8CB5_461B_9574_CD5BA08B5177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDs18b20App:
// See ds18b20.cpp for the implementation of this class
//

class CDs18b20App : public CWinApp
{
public:
	CDs18b20App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDs18b20App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDs18b20App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DS18B20_H__208AB3D9_8CB5_461B_9574_CD5BA08B5177__INCLUDED_)
