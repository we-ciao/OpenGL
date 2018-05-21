
// PointView.h : CPointView 类的接口
//

#pragma once

#include "BmpLoader.h"

class CPointView : public CView
{
protected: // 仅从序列化创建
	CPointView();
	DECLARE_DYNCREATE(CPointView)


public:
	void DrawCirclea(int r,int a,int b);
	void norm(float v1[], float v2[], float v3[], float* nor);
// 特性
public:
	CPointDoc* GetDocument() const;
	
    CBmpLoader Texture;
// 操作
public:
	int move;
	int angle;
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPointView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CClientDC * m_pDC;
	void Init(void);
	bool bSetupPixelFormat(void);
	void DrawScence(void);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // PointView.cpp 中的调试版本
inline CPointDoc* CPointView::GetDocument() const
   { return reinterpret_cast<CPointDoc*>(m_pDocument); }
#endif

