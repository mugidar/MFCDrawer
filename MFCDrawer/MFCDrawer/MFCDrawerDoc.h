
// MFCDrawerDoc.h: интерфейс класса CMFCDrawerDoc 
//


#pragma once

#include <vector>


class CMFCDrawerDoc : public CDocument
{
protected: // создать только из сериализации
	CMFCDrawerDoc() noexcept;
	DECLARE_DYNCREATE(CMFCDrawerDoc)

// Атрибуты
public:
	std::vector<CPoint> Points;

	CButton ResetButton;
	int button_padding_x = 30;
	int button_padding_y = 10;
	int button_top = 15;
	int connect_draw = false;

	COLORREF view_line_color = RGB(211, 211, 211);
	int line_width = 1;
	COLORREF brush_color = RGB(255, 255, 255);

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CMFCDrawerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
