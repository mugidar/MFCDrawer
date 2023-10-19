
// MFCDrawerView.cpp: реализация класса CMFCDrawerView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "MFCDrawer.h"
#endif

#include "MFCDrawerDoc.h"
#include "MFCDrawerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "./PropsDiag.h"


// CMFCDrawerView

IMPLEMENT_DYNCREATE(CMFCDrawerView, CView)

BEGIN_MESSAGE_MAP(CMFCDrawerView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_RESET_BUTTON, &CMFCDrawerView::OnResetClick)
	ON_COMMAND(ID_PROPS, &CMFCDrawerView::OnProps)
END_MESSAGE_MAP()

// Создание или уничтожение CMFCDrawerView

void CMFCDrawerView::OnResetClick() {
	CMFCDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->Points.clear();
	Invalidate();
}

CMFCDrawerView::CMFCDrawerView() noexcept
{
	// TODO: добавьте код создания

}

// Удалаем кнопку
CMFCDrawerView::~CMFCDrawerView()
{
	CMFCDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->ResetButton.DestroyWindow();
}

BOOL CMFCDrawerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CMFCDrawerView
// Рисуем линии по точкам, если флаг connect_draw == true, то соеденяем первую и последнюю
// Когда соеденяем первую и последнюю, то заливаем цветом который получили с диалога
void CMFCDrawerView::OnDraw(CDC* pDC)
{
	CMFCDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen pen(PS_SOLID, pDoc->line_width, pDoc->view_line_color);
	CBrush brush(pDoc->brush_color);
	CPen* old_pen = pDC->SelectObject(&pen);
	pDC->Polyline(pDoc->Points.data(), pDoc->Points.size());
	if (pDoc->connect_draw) {
		if (pDoc->Points.size() == 0) {
			pDoc->connect_draw = false;
			return;
		}
		CPoint points[2] = { pDoc->Points.front(), pDoc->Points.back() };
		pDC->Polyline(points, 2);

		CRgn reg;
		reg.CreatePolygonRgn(pDoc->Points.data(), pDoc->Points.size(), ALTERNATE);
		pDC->FillRgn(&reg, &brush);
		reg.DeleteObject();

		pDoc->connect_draw = false;
	}
	pDC->SelectObject(old_pen);
}


// Печать CMFCDrawerView

BOOL CMFCDrawerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CMFCDrawerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CMFCDrawerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CMFCDrawerView

#ifdef _DEBUG
void CMFCDrawerView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCDrawerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCDrawerDoc* CMFCDrawerView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCDrawerDoc)));
	return (CMFCDrawerDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CMFCDrawerView

// Создаем кнопку(один раз) для сброса рисунка
void CMFCDrawerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CMFCDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);

	CDC* dc = GetDC();

	LPCTSTR but_text = L"Reset";
	CSize text_size = dc->GetTextExtent(but_text);
	int text_hw = text_size.cx / 2;
	int text_hh = text_size.cy / 2;
	int mid_w = rect.Width() / 2;

	CRect but_rect(mid_w - text_hw - pDoc->button_padding_x,
		pDoc->button_top,
		mid_w + text_hw + pDoc->button_padding_x,
		pDoc->button_top + text_hh + (pDoc->button_padding_y * 2));
	pDoc->ResetButton.Create(but_text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, but_rect, this, IDC_RESET_BUTTON);

	// TODO: добавьте специализированный код или вызов базового класса
}

// Добавляем точку в массив точек для дальнейшей рисовки
// Если было нажатие с зажатым Ctrl, то ставим флаг connect_draw в true(см. OnDraw)
void CMFCDrawerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CMFCDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (nFlags & MK_CONTROL) {
		pDoc->connect_draw = true;
	}
	else {
		pDoc->Points.push_back(point);
	}
	Invalidate();

	//CView::OnLButtonDown(nFlags, point);
}

// При нажатии на кнопку в меню, или при команде открываем диалог
// Если в диалоге нажали ОК то переносим толщину и цвет в документ
void CMFCDrawerView::OnProps()
{
	CMFCDrawerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	PropsDiag diag(this);
	INT_PTR res = diag.DoModal();
	if (res == 1) {
		pDoc->line_width = diag.line_width;
		pDoc->brush_color = diag.paint_color;
		Invalidate();
	}
}
