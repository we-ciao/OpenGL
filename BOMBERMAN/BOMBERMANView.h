
// BOMBERMANView.h : interface of the CBOMBERMANView class
//

#pragma once
#include "Maze.h"
#include "Player.h"

class CBOMBERMANView : public CView
{
protected: // create from serialization only
	CBOMBERMANView();
	DECLARE_DYNCREATE(CBOMBERMANView)

	// Attributes
public:
	CBOMBERMANDoc * GetDocument() const;
	Maze maze;
	Player player;
	CBmpLoader Texture[50];
	// Operations
public:

	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CBOMBERMANView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void loadBmp(char * freName, int type);
	void loadTexture();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:





	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);


public:
	CClientDC * m_pDC;
	void Init(void);
	bool bSetupPixelFormat(void);


	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in BOMBERMANView.cpp
inline CBOMBERMANDoc* CBOMBERMANView::GetDocument() const
{
	return reinterpret_cast<CBOMBERMANDoc*>(m_pDocument);
}
#endif

