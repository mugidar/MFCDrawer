
// MFCDrawerView.h: интерфейс класса CMFCDrawerView
//

#pragma once


class CMFCDrawerView : public CView
{
protected: // создать только из сериализации
	CMFCDrawerView() noexcept;
	DECLARE_DYNCREATE(CMFCDrawerView)

// Атрибуты
public:
	CMFCDrawerDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CMFCDrawerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnResetClick();
	afx_msg void OnProps();
};

#ifndef _DEBUG  // версия отладки в MFCDrawerView.cpp
inline CMFCDrawerDoc* CMFCDrawerView::GetDocument() const
   { return reinterpret_cast<CMFCDrawerDoc*>(m_pDocument); }
#endif

