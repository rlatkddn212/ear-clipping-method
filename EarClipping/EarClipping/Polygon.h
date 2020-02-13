#pragma once
#include <vector>
#include "Vector2D.h"
class CPolygon
{
public:
	std::vector<CVector2D>	polygon;

							CPolygon();
						   ~CPolygon();
	
	CVector2D				getCentroid();
	size_t					getSize();
	double					getArea();
	void					pushBack(const CVector2D& v);
};
