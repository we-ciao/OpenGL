
// BOMBERMANView.cpp : implementation of the CBOMBERMANView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BOMBERMAN.h"
#endif

#include "BOMBERMANDoc.h"
#include "BOMBERMANView.h"

#include"gl/gl.h"
#include"gl/glu.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBOMBERMANView

IMPLEMENT_DYNCREATE(CBOMBERMANView, CView)

BEGIN_MESSAGE_MAP(CBOMBERMANView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CBOMBERMANView construction/destruction

CBOMBERMANView::CBOMBERMANView()
{
	// TODO: add construction code here

}

CBOMBERMANView::~CBOMBERMANView()
{
}

BOOL CBOMBERMANView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

// CBOMBERMANView drawing

void CBOMBERMANView::OnDraw(CDC* /*pDC*/)
{
	CBOMBERMANDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	player.maze = &maze;
	maze.Texture = Texture;
	maze.DrawMaze();
}


// CBOMBERMANView printing

BOOL CBOMBERMANView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBOMBERMANView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBOMBERMANView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBOMBERMANView diagnostics

#ifdef _DEBUG
void CBOMBERMANView::AssertValid() const
{
	CView::AssertValid();
}

void CBOMBERMANView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBOMBERMANDoc* CBOMBERMANView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBOMBERMANDoc)));
	return (CBOMBERMANDoc*)m_pDocument;
}
#endif //_DEBUG


// CBOMBERMANView message handlers

void CBOMBERMANView::Init(void)
{
	HGLRC hrc;
	m_pDC = new CClientDC(this);
	if (!bSetupPixelFormat())
		return;

	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);

	glEnable(GL_TEXTURE_2D);

	loadTexture();
}
bool CBOMBERMANView::bSetupPixelFormat(void)
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
	{
		MessageBox("ChoosePixelFormat failed");
		return FALSE;
	}
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		MessageBox("SetPixelFormat failed");
		return FALSE;
	}
	return TRUE;


}

int CBOMBERMANView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	Init();
	return 0;
}


void CBOMBERMANView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	int w = cx;  int h = cy;
	glViewport(0, 0, w, h); //设置视口与窗口匹配
	glMatrixMode(GL_PROJECTION); //重新设置坐标系统
	glLoadIdentity();
	//建立正交变换下的剪切体
	gluPerspective(45.0, (float)w / h, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void CBOMBERMANView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	player.move(nChar);
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//加载材质
void CBOMBERMANView::loadTexture()
{

	loadBmp("res/normal.bmp", normal);
	loadBmp("res/obstacle.bmp", obstacle);
}

//加载bmp
void CBOMBERMANView::loadBmp(char * freName, int type)
{

	/**< 启用纹理映射 */
	if (!Texture[type].LoadBitmap(freName))             /**< 载入位图文件 */
	{
		MessageBox("装载位图文件失败！", "错误", MB_OK);  /**< 如果载入失败则弹出对话框 */
		return;
	}
	glGenTextures(1, &Texture[type].ID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, Texture[type].ID);

	//定义二维纹理
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Texture[type].imageWidth,
		Texture[type].imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
		Texture[type].image);



	//控制滤波
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//说明映射方式
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

}