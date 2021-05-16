
// PO1Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "PO1.h"
#include "PO1Dlg.h"
#include "ParamsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define IMG_WND_ID_IN	100
#define IMG_WND_ID_OUT	101


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPODlg dialog



CPODlg::CPODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPODlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pImgIN = m_pImgOUT = NULL;
	m_imgH = m_imgW = -1;
}

void CPODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
}

BEGIN_MESSAGE_MAP(CPODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CPODlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_PROCESS, &CPODlg::OnBnClickedButtonProcess)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPODlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_PARAMS, &CPODlg::OnBnClickedButtonParams)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPODlg message handlers

BOOL CPODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);


	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CRect rDlg(7,7,407,407);
	MapDialogRect(rDlg);

	m_imgWndIN.Create(rDlg, this, IMG_WND_ID_IN);
		
	rDlg = CRect(530, 7, 930, 407);
	MapDialogRect(rDlg);

	m_imgWndOUT.Create(rDlg, this, IMG_WND_ID_OUT);
	
	// OPCJE

	//Lab1
	m_combo1.AddString(L"convert to greyscale");
	m_combo1.AddString(L"histogram alignment");
	m_combo1.AddString(L"iterative binarization");
	m_combo1.AddString(L"gradient binarization");

	//Lab2
	m_combo1.AddString(L"filtracja usredniajaca");
	m_combo1.AddString(L"filtracja Gaussa");
	m_combo1.AddString(L"filtracja Sobela pion");
	m_combo1.AddString(L"filtracja Sobela poziom");
	m_combo1.AddString(L"filtracja Lapsjan");
	m_combo1.AddString(L"filtracja wyostrzajaca");

	m_combo1.AddString(L"filtracja medianowa 3x3");
	m_combo1.AddString(L"filtracja medianowa 5x5");
	m_combo1.AddString(L"filtracja medianowa krzy¿ 5x5");

	m_combo1.AddString(L"LoG");

	//Lab3
	m_combo1.AddString(L"Dylatacja");
	m_combo1.AddString(L"Erozja");
	m_combo1.AddString(L"Otwarcie");
	m_combo1.AddString(L"Zamkniêcie");

	m_combo1.AddString(L"Kontur wewnêtrzny");
	m_combo1.AddString(L"Kontur zewnêtrzny");

	m_combo1.SelectString(0, L"convert to greyscale");



	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPODlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPODlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPODlg::OnBnClickedButtonLoad()
{
	WCHAR strFilter[] = { L"Image Files (*.bmp; *.jpg; *.tiff; *.gif; *.png)|*.bmp; *.jpg; *.tiff; *.gif; *.png|All Files (*.*)|*.*||" };

	CFileDialog FileDlg(TRUE, NULL, NULL, 0, strFilter);

	if (FileDlg.DoModal() == IDOK)
	{
		delete m_pImgIN;
		::delete m_pImgOUT;
		m_pImgOUT = NULL;

		m_pImgIN = Bitmap::FromFile(FileDlg.GetPathName());
		m_imgWndIN.SetImg(m_pImgIN);
		m_imgW = m_pImgIN->GetWidth();
		m_imgH = m_pImgIN->GetHeight();

		m_pImgOUT = ::new Bitmap(m_imgW, m_imgH, PixelFormat32bppARGB);// PixelFormat16bppGrayScale);
		
		m_imgWndOUT.SetImg(m_pImgOUT);
	
		Invalidate();
	}

	
}


void CPODlg::OnBnClickedButtonProcess()
{
	CString sOption;
	m_combo1.GetLBText(m_combo1.GetCurSel(), sOption);
	BeginWaitCursor();

	if (sOption == L"convert to greyscale")
	{
		for (int x = 0; x < m_imgW; x++)
			for (int y = 0; y < m_imgH; y++)
			{
				BYTE J = GetPixel(x, y);
				SetPixel(x, y, J);
			}

	}

	if (sOption == L"histogram alignment")
	{
		float colorCount[256] = { 0 };
		for (int x = 0; x < m_imgW; x++)
		{
			for (int y = 0; y < m_imgH; y++)
			{
				BYTE J = GetPixel(x, y);
				colorCount[J] = colorCount[J] + 1;
			}
		}


		for (int x = 0; x < m_imgW; x++)
		{
			for (int y = 0; y < m_imgH; y++)
			{
				BYTE J = GetPixel(x, y);
				float newColor = 0;
				for (int i = 0; i < J; i++)
				{
					newColor += colorCount[i] / (m_imgH * m_imgW);
				}
				newColor *= 255;
				SetPixel(x, y, newColor);
			}
		}

	}

	if (sOption == L"iterative binarization")
	{
		float colorCount[256] = { 0 };
		for (int x = 0; x < m_imgW; x++)
		{
			for (int y = 0; y < m_imgH; y++)
			{
				BYTE J = GetPixel(x, y);
				colorCount[J] = colorCount[J] + 1;
			}
		}

		int threshold = 255 / 2;
		int oldThreshold = 0;

		do
		{
			oldThreshold = threshold;
			float mi0 = 0;
			float mi1 = 0;
			float p0 = 0;
			float p1 = 0;

			for (int i = 0; i < threshold; i++)
				p0 += colorCount[i] / (m_imgH * m_imgW) * 255;

			for (int i = 255; i > threshold; i--)
				p1 += colorCount[i] / (m_imgH * m_imgW) * 255;

			for (int i = 0; i < threshold; i++)
				mi0 += (i * colorCount[i] / (m_imgH * m_imgW) * 255) / p0;

			for (int i = 255; i > threshold; i--)
				mi1 += (i * colorCount[i] / (m_imgH * m_imgW) * 255) / p1;

			threshold = (mi0 + mi1) / 2;
		} while (abs(oldThreshold - threshold) >= 2);

		for (int x = 0; x < m_imgW; x++)
		{
			for (int y = 0; y < m_imgH; y++)
			{
				BYTE J = GetPixel(x, y);
				if (J > threshold)
					SetPixel(x, y, 255);
				else
					SetPixel(x, y, 0);
			}
		}

	}

	if (sOption == L"gradient binarization")
	{

		unsigned int G = 0;
		unsigned int GJ = 0;
		
		for (int x = 0; x < m_imgW; x++)
		{
			for (int y = 1; y < m_imgH; y++)
			{
				int Gx = GetPixel(x + 1, y) - GetPixel(x - 1, y);
				int Gy = GetPixel(x, y + 1) - GetPixel(x, y - 1);

				int temp = max(abs(Gx), abs(Gy));

				G += temp;
				GJ += temp * GetPixel(x, y);
			}
		}

		int threshold = (float)GJ / G;

		for (int x = 0; x < m_imgW; x++)
		{
			for (int y = 0; y < m_imgH; y++)
			{
				BYTE J = GetPixel(x, y);
				if (J > threshold)
					SetPixel(x, y, 255);
				else
					SetPixel(x, y, 0);
			}
		}
	}

	if (sOption == L"filtracja usredniajaca")
	{
		int mask[3][3] = { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } };
		AddMask(mask);
	}

	if (sOption == L"filtracja Gaussa")
	{
		int mask[3][3] = { { 1, 4, 1 }, { 4, 12, 4 }, { 1, 4, 1 } };
		AddMask(mask);
	}

	if (sOption == L"filtracja Sobela pion")
	{
		int mask[3][3] = { { 1, 2, 1 }, { 0, 0, 0 }, { -1, -2, -1 } };
		AddMask(mask);
	}

	if (sOption == L"filtracja Sobela poziom")
	{
		int mask[3][3] = { { -1, 0, 1 }, { -2, 0, 2 }, { -1, 0, 1 } };
		AddMask(mask);
	}

	if (sOption == L"filtracja Lapsjan")
	{
		int mask[3][3] = { { -2, 1, -2 }, { 1, 4, 1 }, { -2, 1, -2 } };
		AddMask(mask);
	}

	if (sOption == L"filtracja wyostrzajaca")
	{
		int mask[3][3] = { { 0, -1, 0}, { -1, 5, -1 }, { 0, -1, 0 } };
		AddMask(mask);
	}

	if (sOption == L"filtracja medianowa 3x3")
	{

		BYTE** tempTab = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			tempTab[i] = new BYTE[m_imgH];
		}

		for (int y = 1; y < m_imgH - 1; y++) 
		{
			for (int x = 1; x < m_imgW - 1; x++) 
			{
				std::vector<int> vNeighbors;
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						vNeighbors.push_back(GetPixel(x - i - 1, y - j - 1));
					}
				}

				std::sort(vNeighbors.begin(), vNeighbors.end());
				tempTab[x][y] = vNeighbors[4];
			}
		}

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				SetPixel(x, y, tempTab[x][y]);
			}
		}
	}

	if (sOption == L"filtracja medianowa 5x5")
	{

		BYTE** tempTab = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			tempTab[i] = new BYTE[m_imgH];
		}

		for (int y = 1; y < m_imgH - 1; y++)
		{
			for (int x = 1; x < m_imgW - 1; x++)
			{
				std::vector<int> vNeighbors;
				for (int i = -2; i <= 2; i++)
				{
					for (int j = -2; j <= 2; j++)
					{
						vNeighbors.push_back(GetPixel(x - i, y - j));
					}
				}

				std::sort(vNeighbors.begin(), vNeighbors.end());
				tempTab[x][y] = vNeighbors[4];
			}
		}

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				SetPixel(x, y, tempTab[x][y]);
			}
		}
	}

	if (sOption == L"filtracja medianowa krzy¿ 5x5")
	{

		BYTE** tempTab = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			tempTab[i] = new BYTE[m_imgH];
		}

		for (int y = 1; y < m_imgH - 1; y++)
		{
			for (int x = 1; x < m_imgW - 1; x++)
			{
				std::vector<int> vNeighbors;
				for (int i = -2; i <= 2; i++)
				{
					if (i != 0)
						vNeighbors.push_back(GetPixel(x - i, y));
					else
					{
						for (int j = -2; j <= 2; j++)
						{
							vNeighbors.push_back(GetPixel(x - i, y - j));
						}
					}
				}

				std::sort(vNeighbors.begin(), vNeighbors.end());
				tempTab[x][y] = vNeighbors[4];
			}
		}

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				SetPixel(x, y, tempTab[x][y]);
			}
		}
	}

	if (sOption == L"LoG") {
		float sig = 0.6f;
		int maskSize = 1 + (2 * ceil(2.5 * sig));
		int maskCenter = maskSize / 2;

		float** mask = new float* [maskSize];
		for (int i = 0; i < maskSize; i++)
		{
			mask[i] = new float[maskSize];
		}

		for (int x = -1 * maskCenter; x <= maskCenter; x++)
		{
			for (int y = -1 * maskCenter; y <= maskCenter; y++)
			{
				float log = ((x * x) + (y * y) - (2 * sig * sig)) / (sig * sig * sig * sig);
				float expr = -1 * (((x * x) + (y * y)) / (2 * sig * sig));

				mask[x + maskCenter][y + maskCenter] = log * exp(expr);
			}
		}

		for (int x = maskCenter; x < m_imgW - maskCenter; x++)
		{
			for (int y = maskCenter; y < m_imgH - maskCenter; y++)
			{
				float JsSum = 0;
				for (int i = -1 * maskCenter; i <= maskCenter; i++)
				{
					for (int j = -1 * maskCenter; j <= maskCenter; j++)
					{
						BYTE Js = GetPixel(x - i, y - j);
						JsSum += Js * mask[i + maskCenter][j + maskCenter];
					}
				}

				float newJs = JsSum + 80;

				if (newJs < 0) newJs = 0;
				else newJs = 255;
				SetPixel(x, y, newJs);
			}
		}


		for (int i = 0; i < maskSize; i++)
		{
			delete[] mask[i];
		}
		delete[] mask;
	}

	if (sOption == L"Dylatacja")
	{

		BYTE** obraz = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			obraz[i] = new BYTE[m_imgH];
			for (int j = 0; j < m_imgH; j++)
			{
				obraz[i][j] = GetPixel(i, j);
			}
		}

		BYTE** tempTab = dylatacja(obraz);

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				SetPixel(x, y, tempTab[x][y]);
			}
		}
	}

	if (sOption == L"Erozja")
	{
		BYTE** obraz = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			obraz[i] = new BYTE[m_imgH];
			for (int j = 0; j < m_imgH; j++)
			{
				obraz[i][j] = GetPixel(i, j);
			}
		}

		BYTE** tempTab = erozja(obraz);

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				SetPixel(x, y, tempTab[x][y]);
			}
		}
	}

	if (sOption == L"Otwarcie")
	{
		BYTE** obraz = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			obraz[i] = new BYTE[m_imgH];
			for (int j = 0; j < m_imgH; j++)
			{
				obraz[i][j] = GetPixel(i, j);
			}
		}

		BYTE** tempTab = erozja(obraz);
		BYTE** tempTab2 = dylatacja(tempTab);

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				SetPixel(x, y, tempTab2[x][y]);
			}
		}
	}

	if (sOption == L"Zamkniêcie")
	{
		BYTE** obraz = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			obraz[i] = new BYTE[m_imgH];
			for (int j = 0; j < m_imgH; j++)
			{
				obraz[i][j] = GetPixel(i, j);
			}
		}

		BYTE** tempTab = dylatacja(obraz);
		BYTE** tempTab2 = erozja(tempTab);

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				SetPixel(x, y, tempTab2[x][y]);
			}
		}
	}

	if (sOption == L"Kontur wewnêtrzny")
	{
		BYTE** obraz = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			obraz[i] = new BYTE[m_imgH];
			for (int j = 0; j < m_imgH; j++)
			{
				obraz[i][j] = GetPixel(i, j);
			}
		}

		BYTE** tempTab = erozja(obraz);

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				if(GetPixel(x, y) != tempTab[x][y])
					SetPixel(x, y, 0);
				else
					SetPixel(x, y, 255);
			}
		}
	}

	if (sOption == L"Kontur zewnêtrzny")
	{
		BYTE** obraz = new BYTE * [m_imgW];
		for (int i = 0; i < m_imgW; ++i)
		{
			obraz[i] = new BYTE[m_imgH];
			for (int j = 0; j < m_imgH; j++)
			{
				obraz[i][j] = GetPixel(i, j);
			}
		}

		BYTE** tempTab = dylatacja(obraz);

		for (int y = 0; y < m_imgH; y++)
		{
			for (int x = 0; x < m_imgW; x++)
			{
				if (GetPixel(x, y) != tempTab[x][y])
					SetPixel(x, y, 0);
				else
					SetPixel(x, y, 255);
			}
		}
	}



	/*********************************************************************************************************************************
	TU NALE¯Y WSTAWIC OBS£UGÊ POZOSTA£YCH OPCJI
	
	Zmienne m_imgH i m_imgW zawieraj¹ informacje o wysokoœci i szerokoœci przetwarzanego obrazu.

	Funkcja GetPixel(x,y) zwraca wartoœæ jasnoœci piksela o wspó³rzêdnych (x,y) w obrazie Ÿród³owym (w przypadku obrazów RGB nastêpuje 
	automatyczna konwersja na poziom szaroœci).
	
	Funkcja SetPixel(x,y,J) ustawia w obrazie wynikowym jasnoœæ piksela o wspó³rzêdnych (x,y) na wartoœæ J. 

	Wartoœci jasnoœci s¹ typu BYTE (0..255).
	
	Dodawanie opcji do listy rozwijanej zrealizowane jest na koñcu kodu metody OnInitDialog(). 
	
	W metodzie OnBnClickedButtonParams() pobierany jest ³añcuch znaków wpisany przez u¿ytkownika w oknie pojawiaj¹cym siê po naciœniêciu
	przycisku "Params".
		
	***********************************************************************************************************************************
	TO DO: ADD THE IMPLEMENTATION OF OTHER IMAGE PROCESSING OPERATIONS HERE

	Variables m_imgH and m_imgW store the information about the height and the width of the image which should be processed.

	GetPixel(x,y) returns the intensity of the pixel located at (x,y) position within the source image (in the case of RGB images the 
	conversion to grey level value is performed automatically).

	SetPixel(x,y,J) sets the intensity of the pixel located at (x,y) position within the output image to J.
	The intensity values are of type BYTE (0..255).

	New options can be added to the drop-down list by using m_combo1.AddString() method (see the last lines of OnInitDialog() implementation). 
	
	OnBnClickedButtonParams() retrieves the string of parameters entered in the window that appears after clicking the "Params" button.  
	
	***********************************************************************************************************************************/

	Invalidate();
	EndWaitCursor();
}

void CPODlg::AddMask(int mask[3][3]) {
	
	int sumW = 0;
	bool containsNegative = false; 

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (mask[i][j] < 0)
				containsNegative = true;
			sumW += mask[i][j];
		}
	}

	for (int x = 1; x < m_imgW - 1; x++)
	{
		for (int y = 1; y < m_imgH - 1; y++)
		{
			int sumJ = 0;
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					sumJ += GetPixel(x - i - 1, y - j - 1) * mask[i][j];
				}
			}

			if (containsNegative)
				sumJ += 127;
			else
				sumJ /= sumW;

			if (sumJ < 0)
				sumJ = 0;
			if (sumJ > 255)
				sumJ = 255;

			SetPixel(x, y, sumJ);
		}
	}
}

BYTE** CPODlg::dylatacja(BYTE** obraz)
{
	/*
	//Dla czarno-bialych
	BYTE** tempTab = new BYTE * [m_imgW];
	for (int i = 0; i < m_imgW; ++i)
	{
		tempTab[i] = new BYTE[m_imgH];
		for (int j = 0; j < m_imgH; j++)
		{
			tempTab[i][j] = 255;
		}
	}

	for (int x = 0; x < m_imgW; x++)
	{
		for (int y = 0; y < m_imgH; y++)
		{
			BYTE c = obraz[x][y];

			if (c == 0)
			{
				tempTab[x][y] = 0;

				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if(x+i >= 0 && x+i < m_imgW && y+j >=0 && y+j < m_imgH)
							tempTab[x+i][y+j] = 0;
					}
				}
			}
		}
	}

	return tempTab;  */

	//odcienie szaroœci + czarno biale
	BYTE** tempTab = new BYTE * [m_imgW];
	for (int i = 0; i < m_imgW; ++i)
	{
		tempTab[i] = new BYTE[m_imgH];
	}

	for (int x = 0; x < m_imgW; x++)
	{
		for (int y = 0; y < m_imgH; y++)
		{
			int max = 255;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (x + i >= 0 && x + i < m_imgW && y + j >= 0 && y + j < m_imgH)
					{
						if (obraz[x + i][y + j] < max)
							max = obraz[x + i][y + j];
					}
				}
			}
			tempTab[x][y] = max;
		}
	}

	return tempTab;
}

BYTE** CPODlg::erozja(BYTE** obraz)
{
	/*
	//czarno-biale 
	BYTE** tempTab = new BYTE * [m_imgW];
	for (int i = 0; i < m_imgW; ++i)
	{
		tempTab[i] = new BYTE[m_imgH];
		for (int j = 0; j < m_imgH; j++)
		{
			tempTab[i][j] = 255;
		}
	}

	for (int x = 0; x < m_imgW; x++)
	{
		for (int y = 0; y < m_imgH; y++)
		{
			BYTE c = obraz[x][y];

			if (c == 0)
			{
				bool wyszlo = false;
				for (int i = -1; i <= 1; i++)
				{
					for (int j = -1; j <= 1; j++)
					{
						if (x + i >= 0 && x + i < m_imgW && y + j >= 0 && y + j < m_imgH)
						{
							if (obraz[x+i][y+j] > 0)
								wyszlo = true;
						}
					}
				}
				if (wyszlo == false)
					tempTab[x][y] = 0;
			}
		}
	}

	return tempTab;*/
	//odcienie szaroœci + czarno biale
	BYTE** tempTab = new BYTE * [m_imgW];
	for (int i = 0; i < m_imgW; ++i)
	{
		tempTab[i] = new BYTE[m_imgH];
	}

	for (int x = 0; x < m_imgW; x++)
	{
		for (int y = 0; y < m_imgH; y++)
		{
			int max = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (x + i >= 0 && x + i < m_imgW && y + j >= 0 && y + j < m_imgH)
					{
						if (obraz[x + i][y + j] > max)
							max = obraz[x + i][y + j];
					}
				}
			}
			tempTab[x][y] = max;
		}
	}

	return tempTab;
}


void CPODlg::OnBnClickedButtonSave()
{
	WCHAR strFilter[] = { L"Bitmap (*.bmp)|*.bmp|JPEG (*.jpg)|*.jpg||" };

	CFileDialog FileDlg(FALSE, NULL, NULL, 0, strFilter);

	if (FileDlg.DoModal() == IDOK)
	{
		CLSID Clsid;
		CString sClsId;
		CString sPath = FileDlg.GetPathName();
		CString sExt = (FileDlg.GetFileExt()).MakeUpper();

		if (sExt == "")
		{
			switch (FileDlg.m_ofn.nFilterIndex)
			{
			case 2:
				sExt = "JPG";
				break;
			default:
				sExt = "BMP";
			}
			
			sPath += L"." + sExt;
		}
		
		if (sExt == "BMP")
			sClsId = "image/bmp";

		if (sExt == "JPG")
			sClsId = "image/jpeg";
				
		GetEncoderClsid(sClsId, &Clsid);
		m_pImgOUT->Save(sPath, &Clsid, NULL);
	}
}


void CPODlg::OnBnClickedButtonParams()
{
	CParamsDlg paramsDlg;
	CString s;
	
	if (paramsDlg.DoModal() == IDOK)
	{
		s = paramsDlg.m_sParams;
	}
}


void CPODlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_pImgIN;
	::delete m_pImgOUT;

	GdiplusShutdown(m_gdiplusToken);

	// TODO: Add your message handler code here
}


BYTE CPODlg::GetPixel(int x, int y)
{
	Color pixelColor;
	m_pImgIN->GetPixel(x, y, &pixelColor);

	double r = pixelColor.GetR();
	double g = pixelColor.GetG();
	double b = pixelColor.GetB();
	double J = 0.299*r + 0.587*g + 0.114*b;

	return (BYTE)J;
}

void CPODlg::SetPixel(int x, int y, BYTE J)
{
	Color pixelColor(J,J,J);
	Status s = m_pImgOUT->SetPixel(x, y, pixelColor);
}

int CPODlg::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}
