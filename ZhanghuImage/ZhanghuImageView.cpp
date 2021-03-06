
// ZhanghuImageView.cpp: CZhanghuImageView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "ZhanghuImage.h"
#endif

#include "ZhanghuImageDoc.h"
#include "ZhanghuImageView.h"

#include "Algorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZhanghuImageView

IMPLEMENT_DYNCREATE(CZhanghuImageView, CView)

BEGIN_MESSAGE_MAP(CZhanghuImageView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CZhanghuImageView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_HISTEQUAL, &CZhanghuImageView::OnHistequal)
	ON_COMMAND(ID_SMOOTHING, &CZhanghuImageView::OnSmoothing)
	ON_COMMAND(ID_SHARPING, &CZhanghuImageView::OnSharping)
	ON_COMMAND(ID_FFT, &CZhanghuImageView::OnFft)
	ON_COMMAND(ID_FUNLENGT, &CZhanghuImageView::OnFunlengt)
	ON_COMMAND(ID_ENCODE, &CZhanghuImageView::OnEncode)
END_MESSAGE_MAP()

// CZhanghuImageView 构造/析构

CZhanghuImageView::CZhanghuImageView()
{
	// TODO: 在此处添加构造代码

}

CZhanghuImageView::~CZhanghuImageView()
{
}

BOOL CZhanghuImageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CZhanghuImageView 绘图

void CZhanghuImageView::OnDraw(CDC* pDC)
{
	// TODO: 在此处为本机数据添加绘制代码
	CZhanghuImageDoc* pDoc = GetDocument();
	if (NULL == pDoc)
		return;
	if (NULL == pDoc->m_pCurBitmap)
		return;

	Graphics g(pDC->m_hDC);
	g.DrawImage(pDoc->m_pCurBitmap, 0, 0, pDoc->m_pCurBitmap->GetWidth(), pDoc->m_pCurBitmap->GetHeight());

	if (NULL == pDoc->m_pSecondBitmap)
		return;

	g.DrawImage(pDoc->m_pSecondBitmap, pDoc->m_pCurBitmap->GetWidth() + 10, 0);
}


// CZhanghuImageView 打印


void CZhanghuImageView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CZhanghuImageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CZhanghuImageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CZhanghuImageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CZhanghuImageView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CZhanghuImageView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CZhanghuImageView 诊断

#ifdef _DEBUG
void CZhanghuImageView::AssertValid() const
{
	CView::AssertValid();
}

void CZhanghuImageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CZhanghuImageDoc* CZhanghuImageView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CZhanghuImageDoc)));
	return (CZhanghuImageDoc*)m_pDocument;
}
#endif //_DEBUG


// CZhanghuImageView 消息处理程序


void CZhanghuImageView::OnHistequal()
{
	// TODO: 在此添加命令处理程序代码
	CZhanghuImageDoc* pDoc = GetDocument();
	if (NULL == pDoc)
		return;
	if (NULL == pDoc->m_pCurBitmap)
		return;

	Algorithm alg(pDoc->m_pCurBitmap);
	alg.HistEqual(pDoc->m_pSecondBitmap);
	this->Invalidate();

}


void CZhanghuImageView::OnSmoothing()
{
	// TODO: 在此添加命令处理程序代码
	CZhanghuImageDoc* pDoc = GetDocument();
	if (NULL == pDoc)
		return;
	if (NULL == pDoc->m_pCurBitmap)
		return;

	Algorithm alg(pDoc->m_pCurBitmap);
	double temp[] = { 1.0 / 9,1.0 / 9,1.0 / 9,1.0 / 9,1.0 / 9,1.0 / 9,1.0 / 9,1.0 / 9,1.0 / 9 };
	alg.ImageSmoothingSharping(temp, 1, pDoc->m_pSecondBitmap);
	this->Invalidate();
}


void CZhanghuImageView::OnSharping()
{
	// TODO: 在此添加命令处理程序代码
	CZhanghuImageDoc* pDoc = GetDocument();
	if (NULL == pDoc)
		return;
	if (NULL == pDoc->m_pCurBitmap)
		return;

	Algorithm alg(pDoc->m_pCurBitmap);
	double temp[] = { 0,-1,0,-1,0,1,0,1,0 };
	alg.ImageSmoothingSharping(temp, 1, pDoc->m_pSecondBitmap);
	this->Invalidate();
}


void CZhanghuImageView::OnFft()
{
	// TODO: 在此添加命令处理程序代码
	CZhanghuImageDoc* pDoc = GetDocument();
	if (NULL == pDoc)
		return;
	if (NULL == pDoc->m_pCurBitmap)
		return;

	Algorithm alg(pDoc->m_pCurBitmap);

	alg.FFT2D(pDoc->m_pSecondBitmap);
	this->Invalidate();

}


void CZhanghuImageView::OnFunlengt()
{
	// TODO: 在此添加命令处理程序代码
	CZhanghuImageDoc* pDoc = GetDocument();
	if (NULL == pDoc)
		return;
	if (NULL == pDoc->m_pCurBitmap)
		return;

	Algorithm alg(pDoc->m_pCurBitmap);

	CString filename;// = _T("D:\\image\\runlength.txt");

					 // 构造打开文件对话框    
	CFileDialog fileDlg(FALSE, _T(""), NULL, 0);
	// 显示打开文件对话框      
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里
		filename = fileDlg.GetPathName();
		//SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
		alg.RunlengthCode(filename);

	}

}


void CZhanghuImageView::OnEncode()
{
	// TODO: 在此添加命令处理程序代码
	CZhanghuImageDoc* pDoc = GetDocument();
	if (NULL == pDoc)
		return;


	Algorithm alg(pDoc->m_pCurBitmap);

	//CString filename = _T("D:\\image\\runlength.txt");

	//alg.RunlengthRecode(filename,pDoc->m_pCurBitmap);

	CString filename;// = _T("D:\\image\\runlength.txt");

					 // 构造打开文件对话框    
	CFileDialog fileDlg(TRUE, _T(""), NULL, 0);
	// 显示打开文件对话框      
	if (IDOK == fileDlg.DoModal())
	{
		// 如果点击了文件对话框上的“打开”按钮，则将选择的文件路径显示到编辑框里
		filename = fileDlg.GetPathName();
		//SetDlgItemText(IDC_OPEN_EDIT, strFilePath);
		alg.RunlengthRecode(filename, pDoc->m_pCurBitmap);

	}

	if (NULL == pDoc->m_pCurBitmap)
		return;

	this->Invalidate();

}
