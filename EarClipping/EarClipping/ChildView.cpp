
// ChildView.cpp: CChildView 클래스의 구현
//

#include "stdafx.h"
#include "EarClipping.h"
#include "ChildView.h"

#include <iostream>
#include <vector>
#include "Polygon.h"
#include "Vector2D.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


struct Triangle
{
	CVector2D p0;
	CVector2D p1;
	CVector2D p2;

	Triangle(CVector2D p0_, CVector2D p1_, CVector2D p2_)
	{
		p0 = p0_;
		p1 = p1_;
		p2 = p2_;
	}
};

vector<Triangle> triangulate(vector<CVector2D> polygon)
{
	vector<Triangle> ret;

	vector<CVector2D> polygonClone = polygon;
	int p1;
	int p2;
	int p3;
	while(polygonClone.size() >= 3)
	{
		bool isTriangulation = false;
		for (int i = 0; i < polygonClone.size(); ++i)
		{
			p1 = i;
			p2 = (i + 1) % polygonClone.size();
			p3 = (i + 2) % polygonClone.size();

			if (ccw(polygonClone[p1], polygonClone[p2], polygonClone[p3]))
			{
				bool isInsidePoint = false;
				for (int j = 0; j < polygon.size(); ++j)
				{
					//if (j == p1 || j == p2 || j == p3) continue;
					if (ccw(polygonClone[p2] - polygonClone[p1], polygon[j] - polygonClone[p1]) > 0.0 &&
						ccw(polygonClone[p3] - polygonClone[p2], polygon[j] - polygonClone[p2]) > 0.0 &&
						ccw(polygonClone[p1] - polygonClone[p3], polygon[j] - polygonClone[p3]) > 0.0)
					{
						isInsidePoint = true;
						break;
					}
				}

				if (! isInsidePoint)
				{
					ret.push_back(Triangle(polygonClone[p1], polygonClone[p2], polygonClone[p3]));
					polygonClone.erase(polygonClone.begin() + p2);
					isTriangulation = true;
					break;
				}
			}
		}

		if (!isTriangulation)
		{
			AfxMessageBox(L"삼각화 실패"); 
			break;
		}
	}

	return ret;
}

// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CVector2D newPos = CVector2D(point.x, point.y);

	for (int i = 0; i < pointsList.size(); ++i)
	{
		if (pointsList[i].Equal(newPos))
			return;
	}

	pointsList.push_back(newPos);
	ret = triangulate(pointsList);
	Invalidate();
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	pointsList.clear();
	ret.clear();
	Invalidate();
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	// 그리기 메시지에 대해서는 CWnd::OnPaint()를 호출하지 마십시오.

	for (int i = 0; i < pointsList.size(); i++)
	{
		dc.SetPixel(pointsList[i].x, pointsList[i].y, RGB(255, 0, 0));
	}

	CPen pen(PS_SOLID, 1, RGB(0, 255, 0));
	dc.SelectObject(&pen);
	for (int i = 0; i < ret.size(); ++i)
	{
		dc.MoveTo(ret[i].p0.x, ret[i].p0.y);
		dc.LineTo(ret[i].p1.x, ret[i].p1.y);
		dc.LineTo(ret[i].p2.x, ret[i].p2.y);
		dc.LineTo(ret[i].p0.x, ret[i].p0.y);
	}
}

