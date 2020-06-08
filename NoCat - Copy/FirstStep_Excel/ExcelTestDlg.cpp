﻿
#include "stdafx.h"
#include "ExcelTest.h"
#include "ExcelTestDlg.h"
#include "Excel_enums.h"
#include <iostream>
#include <string>
//
#include <afx.h>

//

//

#include <stdlib.h>


#include "atlbase.h"
#include "atlstr.h"
#include "comutil.h"



//
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define OL(x) (COleVariant(long(x)))
#define OS(x) (COleVariant(_T(x)))
//#define _UNICODE



CExcelTestDlg::CExcelTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExcelTestDlg::IDD, pParent)
	, LInt(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExcelTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_GIFFIRST, m_Picture);

	DDX_Control(pDX, IDB_MYNAME, My_Name);
}

BEGIN_MESSAGE_MAP(CExcelTestDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_TEST, OnBnClickedTest)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
//	ON_EN_UPDATE(IDC_MFCEDITBROWSE2, &CExcelTestDlg::OnUpdateMfceditbrowse2)
//ON_BN_CLICKED(IDC_BUTTONOUT2, &CExcelTestDlg::OnBnClickedButtonout2)
//ON_BN_CLICKED(IDC_BUTTONIN, &CExcelTestDlg::OnBnClickedButtonin)
END_MESSAGE_MAP()


// CExcelTestDlg message handlers

BOOL CExcelTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	if (m_Picture.Load(MAKEINTRESOURCE(IDR_GIF2),_T("GIF")))
		m_Picture.Draw();
	if (My_Name.Load(MAKEINTRESOURCE(IDR_GIF3),_T("GIF")))
		My_Name.Draw();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CExcelTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CExcelTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExcelTestDlg::OnBnClickedTest()
{
//--------------------------чтение----------------------------------
	if(!app.CreateDispatch(_T("Excel.Application"))) //запустить сервер
	{
		AfxMessageBox(_T("Ошибка при старте Excel!"));
		return;
	}
	else
	app.put_Visible(FALSE); //и сделать его Невидимым
	CWorkbooks oBooks;
 	CWorkbook oBook;
	CWorksheets oSheets;
	CWorksheet oSheet;
	CRange oRange1;	
	oBooks = app.get_Workbooks();
	COleVariant  covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	COleVariant covTrue((short)TRUE, VT_BOOL), covFalse((short)FALSE, VT_BOOL);
	COleVariant covBOOL((short)FALSE, VT_BOOL);
	try
		{
			//CString m_Text;	// создание стандартной панели выбора файла Open
  			CFileDialog DlgOpen(TRUE,(LPCSTR)"xls",NULL, 
 			OFN_HIDEREADONLY,(LPCSTR)" Text Files (*.xls) |*.xls||"); 
   			// отображение стандартной панели выбора файла Open 
 			if(DlgOpen.DoModal()==IDOK) 
			{	// создание объекта и открытие файла для чтения
					oBooks.Open(DlgOpen.GetPathName(),
					covOptional, covOptional, covOptional, covOptional, covOptional,
					covOptional, covOptional, covOptional, covOptional, covOptional,
					covOptional, covOptional, covOptional, covOptional );
			}
		}
		catch (...)
		{
			MessageBox("Ошибка при открытии файла Excel","Ошибка", MB_OK);
			return;
		}	
	oBook= oBooks.get_Item(COleVariant(long(1)));
	oSheets = oBook.get_Worksheets();
	oSheet=oSheets.get_Item(COleVariant(long(1)));
	oRange1 = oSheet.get_Range(COleVariant(_T("A1")),COleVariant(_T("A100")));
	COleSafeArray ObjectMask(oRange1.get_Value(covOptional));
	COleVariant vData;
	long iRows;
    ObjectMask.GetUBound(1, &iRows);
	long index[2];
	int i = 1;
	index[1]=1;
	CString ObjectMassiv[100];
	for (int rowCounter = 1; rowCounter <= iRows; rowCounter++) {
			index[0]=rowCounter;
			ObjectMask.GetElement(index,vData);
			CString szdata(vData);
			ObjectMassiv[rowCounter-1] = szdata;
	}	
	oBook.Close(covFalse, covOptional, covOptional); 
	oBook.ReleaseDispatch(); 
	oBooks.Close(); 
	oBooks.ReleaseDispatch();


//--------------------------чтение----------------------------------

//--------------------------поиск----------------------------------


CFileDialog DlgOpen1(TRUE,(LPCSTR)"txt",NULL, OFN_HIDEREADONLY,(LPCSTR)" Text Files (*.txt) |*.txt||"); 
DlgOpen1.DoModal();

char *BuffFile = NULL;

size_t dwLength;


try
{    

    CFile myFile(DlgOpen1.GetPathName(),CFile::modeRead|CFile::typeBinary);
	dwLength = myFile.GetLength();
    BuffFile = new char[dwLength];
    myFile.Read(BuffFile, dwLength);
//-----------------------------------------------------------------------
	 CFile destFile;
	DWORD dwRead;
	 do
      {
         destFile.Write(BuffFile, dwRead);
      }
      while (dwRead > 0);










   
//--------------------------------------------------------------------

}
catch (CFileException* pEx)
{
	AfxMessageBox("Файл не выбран");
   pEx->Delete();
}
catch(CMemoryException* pEx)
{
   pEx->ReportError();
   pEx->Delete();
   AfxAbort();
}

if (BuffFile!=NULL)
{
   delete BuffFile;
   BuffFile = nullptr;
}



}


void CExcelTestDlg::OnBnClickedCancel()
{
		
	// --- Выход из программы без закрытия Excel, просто отсоединяемся от него
	app.DetachDispatch();

	OnCancel();
}

