#pragma once


// Диалоговое окно PropsDiag

class PropsDiag : public CDialogEx
{
	DECLARE_DYNAMIC(PropsDiag)

public:
	PropsDiag(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~PropsDiag();

	int line_width = 1;
	COLORREF paint_color = RGB(0, 0, 0);

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SLC_PROPS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
private:
	CComboBox WidthCombo;
public:
	afx_msg void OnSelchangeLineWidth();
private:
	CSliderCtrl RSlider;
	CSliderCtrl GSlider;
	CSliderCtrl BSlider;
	int r_color = 0;
	int g_color = 0;
	int b_color = 0;
public:
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
