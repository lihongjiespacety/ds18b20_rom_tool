// ds18b20Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "ds18b20.h"
#include "ds18b20Dlg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/**
 * crc8 x^8+x^5+x^4+x^0 查表
 *
 */
BYTE s_crc8_x8540_au8[256] =
{
    0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
    157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
    35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
    190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
    70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
    219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
    101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
    248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
    140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
    17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
    175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
    50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
    202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
    87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
    233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
    116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53
};

/**
********************************************************************************
* \fn          uint8_t crc8_x8540(uint8_t init,uint8_t *p, uint32_t len)
* \brief       查表法计算x^8+x^5+x^4+x^0 CRC8值.
* \param[in]   init 初始值
* \param[in]   p 待计算的缓冲区
* \param[in]   len 缓冲区长度
* \note        .
* \return      uint8_t 计算值
********************************************************************************
*/
BYTE crc8_x8540(BYTE init, BYTE* p, WORD len)
{
    BYTE crc8 = init;

    for(; len > 0; len--)
    {
        crc8 = s_crc8_x8540_au8[crc8^*p];
        p++;
    }

    return crc8;
}

/////////////////////////////////////////////////////////////////////////////
// CDs18b20Dlg dialog

char DigToChar(unsigned char val)
{
	if((val>=0) && (val<=9))
	{
	    return (val+'0');
	}
	else if((val>9) && (val<=15))
	{
	    return (val-10 +'A');
	}
	else
	{
	    return ' ';
	}
}

BYTE CharToHex(char val)
{
	if((val>='0') && (val<='9'))
	{
	    return (val-'0');
	}
	else if((val>='A') && (val<='F'))
	{
	    return (val-'A' + 10);
	}
	else if((val>='a') && (val<='f'))
	{
	    return (val-'a' + 10);
	}
	else
	{
	    return 0;
	}
}
CDs18b20Dlg::CDs18b20Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDs18b20Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDs18b20Dlg)
	m_CmdFileStr = _T("");
	m_ChNum = 0;
	m_RomNum = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDs18b20Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDs18b20Dlg)
	DDX_Text(pDX, IDC_EDIT3, m_CmdFileStr);
	DDX_Text(pDX, IDC_EDIT1, m_ChNum);
	DDX_Text(pDX, IDC_EDIT2, m_RomNum);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDs18b20Dlg, CDialog)
	//{{AFX_MSG_MAP(CDs18b20Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDs18b20Dlg message handlers

BOOL CDs18b20Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
	m_ChNum = 4;
    m_RomNum = 10;
	UpdateData(FALSE); // 变量 -> 控件
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDs18b20Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDs18b20Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

CString CDs18b20Dlg::SelectFile()
{
    CString strFile = _T("");

    CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.csv)|*.csv|Describe Files (*.txt)|*.txt|All Files (*.*)|*.*||"), NULL);

    if (dlgFile.DoModal())
    {
        strFile = dlgFile.GetPathName();
    }

    return strFile;
}

char CmdFileName[256]={0};
CFile SaveFile;         // CFile对象 
CStdioFile CmdFile;      // CFile对象 

void CDs18b20Dlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE); // 变量 -> 控件
	m_CmdFileStr = this->SelectFile();
	strcpy(CmdFileName,m_CmdFileStr.GetBuffer(m_CmdFileStr.GetLength()));
	UpdateData(FALSE); // 变量 -> 控件	
}


void CDs18b20Dlg::OnButton1() 
{
	CString linestr;
	char linebuff[256]={0};
	UINT index;
	char rom[256]={0};
	int res = 1;
	int getnum = 0;
	BYTE hexbuff[256];
	BYTE calbuff[512];
	UINT hexlen=0;
	UINT i;
    UINT len;
	UINT filelen;
	BYTE temp=0xFF;
	CString   resstr; 
    UpdateData(TRUE); /*控件->变量*/
	// TODO: Add your control notification handler code here
	/*打开文件*/
	if(CmdFile.Open(CmdFileName, CFile::modeRead))
	{
		/*成功*/

	}
	else
	{
		/*失败*/
		resstr.Format( "打开文件%s失败",CmdFileName); 
		AfxMessageBox(resstr);
		return;
	}
	if(SaveFile.Open("ds18b20.bin", CFile::modeReadWrite|CFile::modeCreate))
	{
		/*成功*/

	}
	else
	{
		/*失败*/
		CmdFile.Close();
		resstr.Format( "打开文件%s失败","ds18b20.bin"); 
		AfxMessageBox(resstr);
		return;
	}
	/*填充文件大小*/
	SaveFile.Seek(0,CFile::begin);
	filelen = m_ChNum * (m_RomNum*8+2);
	filelen=(1024+512);
	for(i=0;i<filelen;i++)
	{
		SaveFile.Write(&temp,1);
	}
	SaveFile.Seek(0,CFile::begin);

	/*加载*/
	do
	{
		if((CmdFile.ReadString(linestr)==0))
		{
			if(getnum==0)
			{
				resstr.Format("读文件%s失败",CmdFileName); 
				AfxMessageBox(resstr);
			}
			res = 1;
		}
		else
		{
			/*文件没有结束*/
			memset(rom,0,sizeof(rom));
			strcpy(linebuff,linestr.GetBuffer(linestr.GetLength()));
			if(linebuff[0] == '#')
			{
				res = 0;
				continue;
			}
			len=0;  /*检查空行 无意义行*/
			for(i=0;i<(UINT)linestr.GetLength();i++)
			{
				if(isxdigit(linebuff[i]))
				{
					len++;
				}
			}
			if((linebuff[0] == '#') || (len<16))
			{
				res = 0;
				continue;
			}
			for(i=0;i<sizeof(linebuff);i++)
			{
				if(isxdigit(linebuff[i]))
				{
				
				}
				else
				{
					linebuff[i] = ' ';
				}
			}

			sscanf(linebuff,"%d %s",&index,rom);
			if(index<1)
			{
				AfxMessageBox("序号必须大于等于0");
				break;
			}
			else if(index>m_ChNum*m_RomNum)
			{
				AfxMessageBox("序号必须小于总的rom个数");
				break;
			}else{}
			/*16进制转换*/
			memset(hexbuff,0,sizeof(hexbuff));
			len = strlen((char*)rom);
			hexlen=0;
			for(i=0;i<len-1;i++)
			{
				if(isxdigit(rom[i]) && isxdigit(rom[i+1]))
				{
					hexbuff[hexlen++] = (CharToHex(rom[i])<<4) + CharToHex(rom[i+1]);
					i++;
				}
				else
				{

				}
			}
			if(hexlen == 8)
			{
				SaveFile.Seek(((index-1)/m_RomNum)* (m_RomNum*8+2)+8*((index-1)%m_RomNum),CFile::begin);
				SaveFile.Write(&hexbuff,hexlen);
			}
			else
			{
				AfxMessageBox("rom必须是8字节");
				break;
			}
			getnum++;
			res = 0;
		}
	}while(res==0);

	/*计算校验和 拷贝3份*/
#if 1
	for(i=0;i<m_ChNum;i++)
	{ 
		SaveFile.Seek(i*(m_RomNum*8+2),CFile::begin);  /*定位到通道处*/
		SaveFile.Read(calbuff,m_RomNum*8+2);           /*读出一个通道计算校验和*/
		calbuff[m_RomNum*8+0] = crc8_x8540(0,calbuff,m_RomNum*8);
		calbuff[m_RomNum*8+1] = 0;

		SaveFile.Seek(i*(m_RomNum*8+2),CFile::begin);  /*定位到通道处*/
		SaveFile.Write(calbuff,m_RomNum*8+2);                /*写第一份*/
		SaveFile.Seek(i*(m_RomNum*8+2)+512,CFile::begin);    /*写第二份*/
		SaveFile.Write(calbuff,m_RomNum*8+2);    
		SaveFile.Seek(i*(m_RomNum*8+2)+1024,CFile::begin);   /*写第三份*/
		SaveFile.Write(calbuff,m_RomNum*8+2);          
	}
#endif

	resstr.Format( "转换完%d路",getnum); 
	AfxMessageBox(resstr);
	CmdFile.Close();
	SaveFile.Close();
	return;
}

void CDs18b20Dlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	m_ChNum = 4;   
    m_RomNum = 10;
	UpdateData(FALSE); // 变量 -> 控件
}

void CDs18b20Dlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_ChNum = 5;
    m_RomNum = 10;
	UpdateData(FALSE); // 变量 -> 控件
}
