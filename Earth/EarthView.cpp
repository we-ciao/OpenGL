// PointView.cpp : CPointView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Earth.h"
#endif

#include "EarthDoc.h"
#include "EarthView.h"
#include"gl/gl.h"
#include"gl/glu.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.1415926



/** 再定义一个默认的光源 */
static float diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };	 
static float specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };	 
static float lightPosition[] = { 0.0f, 0.0f, 10.0f, 1.0f };


IMPLEMENT_DYNCREATE(CPointView, CView)

	BEGIN_MESSAGE_MAP(CPointView, CView)
		// 标准打印命令
		ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
		ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPointView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
		ON_WM_RBUTTONUP()
		ON_WM_CREATE()
		ON_WM_DESTROY()
		ON_WM_ERASEBKGND()
		ON_WM_SIZE()
		ON_WM_TIMER()
	END_MESSAGE_MAP()

	// CPointView 构造/析构

	CPointView::CPointView()
		: m_pDC(NULL)
	{
		// TODO: 在此处添加构造代码
		move = -7;
		angle = 0;
	}

	CPointView::~CPointView()
	{
	}

	BOOL CPointView::PreCreateWindow(CREATESTRUCT& cs)
	{
		// TODO: 在此处通过修改
		//  CREATESTRUCT cs 来修改窗口类或样式
		cs.style |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

		return CView::PreCreateWindow(cs);
	}

	// CPointView 绘制

	void CPointView::OnDraw(CDC* /*pDC*/)
	{
		CPointDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;

		// TODO: 在此处为本机数据添加绘制代码

		DrawScence();

	}


	// CPointView 打印


	void CPointView::OnFilePrintPreview()
	{
#ifndef SHARED_HANDLERS
		AFXPrintPreview(this);
#endif
	}

	BOOL CPointView::OnPreparePrinting(CPrintInfo* pInfo)
	{
		// 默认准备
		return DoPreparePrinting(pInfo);
	}

	void CPointView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加额外的打印前进行的初始化过程
	}

	void CPointView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
	{
		// TODO: 添加打印后进行的清理过程
	}

	void CPointView::OnRButtonUp(UINT /* nFlags */, CPoint point)
	{
		ClientToScreen(&point);
		OnContextMenu(this, point);
	}

	void CPointView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
	{
#ifndef SHARED_HANDLERS
		theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
	}


	// CPointView 诊断

#ifdef _DEBUG
	void CPointView::AssertValid() const
	{
		CView::AssertValid();
	}

	void CPointView::Dump(CDumpContext& dc) const
	{
		CView::Dump(dc);
	}

	CPointDoc* CPointView::GetDocument() const // 非调试版本是内联的
	{
		ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPointDoc)));
		return (CPointDoc*)m_pDocument;
	}
#endif //_DEBUG


	// CPointView 消息处理程序


	void CPointView::Init(void)
	{
		HGLRC hrc;
		m_pDC=new CClientDC(this);
		if(!bSetupPixelFormat())
			return;

		hrc=wglCreateContext(m_pDC->GetSafeHdc());
		wglMakeCurrent(m_pDC->GetSafeHdc(),hrc);

		SetTimer(1,100,0);

		//glEnable(GL_CULL_FACE);
		//glPolygonMode(GL_FRONT,GL_FILL);
		//glFrontFace(GL_CCW);
		//glShadeModel(GL_SMOOTH);

		/** 设置0号光源 */
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);


		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0); /**< 启用0号灰色光源,让物体可见 */

		/**< 启用纹理映射 */
		if(!Texture.LoadBitmap("image.bmp"))              /**< 载入位图文件 */
		{
			MessageBox(L"装载位图文件失败！",L"错误",MB_OK);  /**< 如果载入失败则弹出对话框 */
			return ;
		}
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);

		//定义二维纹理
		glTexImage2D(GL_TEXTURE_2D,0,3,Texture.imageWidth,
			Texture.imageHeight,0,GL_RGB,GL_UNSIGNED_BYTE,
			Texture.image);
		//控制滤波
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

		//说明映射方式
		glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);


		glEnable(GL_TEXTURE_2D); 

	}


	bool CPointView::bSetupPixelFormat(void)
	{
		static PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |
			PFD_SUPPORT_OPENGL|
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
		if((pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == 0)
		{
			MessageBox(L"ChoosePixelFormat failed");
			return FALSE;
		}
		if(SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
		{
			MessageBox(L"SetPixelFormat failed");
			return FALSE;
		}
		return TRUE;


	}


	void CPointView::DrawScence(void)
	{

		//设置清屏颜色为黑色
		glClearColor(1.0f,1.0f,1.0f,0.0f);
		//清除颜色缓冲区和深度缓冲区
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();//单位矩阵

		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	

		glEnable(	GL_DEPTH_TEST);

		glTranslatef(0,0,-30);


		//太阳
		glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glRotatef(angle,0,1,0);
		DrawCirclea(8,30,30);
		glPopMatrix();

		////地球
		//glPushMatrix();
		//glColor3f(0.0, 0.0, 1.0);
		//glRotatef(angle,0,1,0);
		//glTranslatef(10,0,0);
		//DrawCirclea(2,30,30);
		//glPopMatrix();


		////月亮
		//glPushMatrix();
		//glColor3f(1.0, 1.0, 0.0); 
		//// 将坐标系绕Y轴旋转fEarthOrbit角度,控制月亮跟随地球
		//glRotatef(angle,0,1,0);
		//glTranslatef(5,0,0);
		////// 将坐标系绕Y轴旋转fMoonOrbit角度,控制月亮公转
		////glRotatef(angle,0,1,0);
		////glTranslatef(4,0,0);



		DrawCirclea(1,30,30);
		glPopMatrix();



		glFinish();

		SwapBuffers(wglGetCurrentDC());

	}


	int CPointView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;

		// TODO:  在此添加您专用的创建代码
		Init();
		return 0;
	}


	void CPointView::OnDestroy()
	{
		CView::OnDestroy();

		// TODO: 在此处添加消息处理程序代码
		HGLRC hrc;
		hrc = ::wglGetCurrentContext();
		::wglMakeCurrent(NULL,NULL);
		if(hrc)
			::wglDeleteContext(hrc);
		if(m_pDC)
			delete m_pDC;

	}

	BOOL CPointView::OnEraseBkgnd(CDC* pDC)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值


		//return CView::OnEraseBkgnd(pDC);
		return true;
	}


	void CPointView::OnSize(UINT nType, int cx, int cy)
	{
		CView::OnSize(nType, cx, cy);

		// TODO: 在此处添加消息处理程序代码

		int w=cx;  int h=cy;
		glViewport(0,0,w,h); //设置视口与窗口匹配
		glMatrixMode(GL_PROJECTION); //重新设置坐标系统
		glLoadIdentity();
		//建立正交变换下的剪切体
		gluPerspective(45.0,(float)w/h,1,100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

	}


	void CPointView::OnTimer(UINT_PTR nIDEvent)
	{
		// TODO: Add your message handler code here and/or call default
		angle +=5;

		if(angle>=360)angle = 0;
		move+=0.05;



		Invalidate();
		CView::OnTimer(nIDEvent);
	}



	void CPointView::norm(float v1[], float v2[], float v3[], float* nor)
	{
		GLfloat vc1[3],vc2[3];
		GLfloat a,b,c;
		GLdouble r;
		vc1[0]= v2[0] - v1[0]; 
		vc1[1]= v2[1] - v1[1]; 
		vc1[2]= v2[2] - v1[2];
		vc2[0]= v3[0] - v1[0]; 
		vc2[1]= v3[1] - v1[1]; 
		vc2[2]= v3[2] - v1[2];

		a = vc1[1] * vc2[2] - vc2[1] * vc1[2];
		b = vc2[0] * vc1[2] - vc1[0] * vc2[2];
		c = vc1[0] * vc2[1] - vc2[0] * vc1[1];

		r = sqrt( a * a + b* b + c * c);
		nor[0] = a / r;nor[1] = b / r;nor[2] = c / r;

	}
	//r 半径 a 横向切分  b 纵向切分
	void  CPointView::DrawCirclea(int r,int a,int b){

		float di = PI/b;
		float dj = 2*PI/a;
		for(float i = 0;i<=PI;i+=di){
			for(float j = 0;j<=2*PI;j+=dj){

				float x1 = r*sin(i)*cos(j);
				float y1 = r*sin(i)*sin(j);
				float z1 = r*cos(i);

				float x2 = r*sin(i+di)*cos(j);
				float y2 = r*sin(i+di)*sin(j);
				float z2 = r*cos(i+di);

				float x3 = r*sin(i+di)*cos(j+dj);
				float y3 = r*sin(i+di)*sin(j+dj);
				float z3 = r*cos(i+di);

				float x4 = r*sin(i)*cos(j+dj);
				float y4 = r*sin(i)*sin(j+dj);
				float z4 = r*cos(i);


				float v1[] = {x1,y1,z1};
				float v2[] = {x2,y2,z2};
				float v3[] = {x3,y3,z3};
				float v4[] = {x4,y4,z4};
				float nor1[] = {0,0,0};
				float nor2[] = {0,0,0};
				norm(v1,v2,v3,nor1);
				norm(v1,v3,v4,nor2);
				glBegin(GL_TRIANGLES); 
				glNormal3f(nor1[0],nor1[1],nor1[2]);
				glTexCoord2f( j/(2*PI),i/PI);glVertex3f(x1,y1,z1);
				glTexCoord2f(j/(2*PI),(i+di)/PI);glVertex3f(x2,y2,z2);
				glTexCoord2f( (j+dj)/(2*PI),(i+di)/PI);glVertex3f(x3,y3,z3);
				glEnd();


				glBegin(GL_TRIANGLES); 
				glNormal3f(nor2[0],nor2[1],nor2[2]);
				glTexCoord2f( j/(2*PI),i/PI);glVertex3f(x1,y1,z1);
				glTexCoord2f( (j+dj)/(2*PI),(i+di)/PI);glVertex3f(x3,y3,z3);
				glTexCoord2f((j+dj)/(2*PI),i/PI);glVertex3f(x4,y4,z4);
				glEnd();
			}
		}

	}