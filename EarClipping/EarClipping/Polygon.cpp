#include "StdAfx.h"
#include "Polygon.h"

CPolygon::CPolygon()
{
}

CPolygon::~CPolygon()
{
}

CVector2D CPolygon::getCentroid()
{
	double px = 0.0;
	double py = 0.0;
	for (size_t i = 0; i < polygon.size(); ++i)
	{
		size_t next = (i + 1) % polygon.size();

		px += (polygon[i].x + polygon[next].x) * (polygon[i].x * polygon[next].y - polygon[next].x * polygon[i].y);
		py += (polygon[i].y + polygon[next].y) * (polygon[i].x * polygon[next].y - polygon[next].x * polygon[i].y);
	}

	double area = getArea();
	px = px / (6 * area);
	py = py / (6 * area);
	return CVector2D(px, py);
}

void CPolygon::pushBack(const CVector2D & v)
{
	polygon.push_back(v);
}

size_t CPolygon::getSize()
{
	return polygon.size();
}

double CPolygon::getArea()
{
	double area = 0;
	int j = polygon.size() - 1;
	for (int i = 0; i < polygon.size(); i++)
	{
		area += (polygon[j].x + polygon[i].x) * (polygon[j].y - polygon[i].y);
		j = i;
	}

	return abs(area / 2);
}
