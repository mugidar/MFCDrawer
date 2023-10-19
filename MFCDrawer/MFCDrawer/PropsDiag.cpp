// PropsDiag.cpp: файл реализации
//

#include "pch.h"
#include "MFCDrawer.h"
#include "PropsDiag.h"
#include "afxdialogex.h"


// Диалоговое окно PropsDiag

IMPLEMENT_DYNAMIC(PropsDiag, CDialogEx)

PropsDiag::PropsDiag(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SLC_PROPS, pParent)
{

}

PropsDiag::~PropsDiag()
{
}

void PropsDiag::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LINE_WIDTH, WidthCombo);
	DDX_Control(pDX, IDC_COLOR_R, RSlider);
	DDX_Control(pDX, IDC_COLOR_G, GSlider);
	DDX_Control(pDX, IDC_COLOR_B, BSlider);
}


BEGIN_MESSAGE_MAP(PropsDiag, CDialogEx)
	ON_CBN_SELCHANGE(IDC_LINE_WIDTH, &PropsDiag::OnSelchangeLineWidth)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDOK, &PropsDiag::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений PropsDiag


void PropsDiag::OnSelchangeLineWidth()
{
	line_width = WidthCombo.GetCurSel();
}


void PropsDiag::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CSliderCtrl* pScroll = reinterpret_cast<CSliderCtrl*>(pScrollBar);

	if (pScroll == &RSlider) {
		r_color = RSlider.GetPos();
	}
	else if (pScroll == &GSlider) {
		g_color = GSlider.GetPos();
	}
	else if (pScroll == &BSlider) {
		b_color = BSlider.GetPos();
	}
	else {
		CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	}
}


BOOL PropsDiag::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	RSlider.SetRangeMax(255);
	GSlider.SetRangeMax(255);
	BSlider.SetRangeMax(255);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}


void PropsDiag::OnBnClickedOk()
{
	paint_color = RGB(r_color, g_color, b_color);
	CDialogEx::OnOK();
}
