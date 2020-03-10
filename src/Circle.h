#pragma once

#include "Geo.h"
class Circle :
	public Geo
{
private:
	int x;
	int y;
	int r;
	int r2;
public:
	Circle(char type_in, int id_in, int x_in, int y_in, int r_in);
	int getX();
	int getY();
	int getR();
	double getR2();
	bool goThrough(double x_in, double y_in);
	void cross(Geo* g, unordered_set<Point, PointHash, PointCmp>* set);
};
