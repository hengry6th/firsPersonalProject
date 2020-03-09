#pragma once
#include <string>
#include "Geo.h"
#include"point.h"
using std::string;
using std::pair;
class Line: public Geo
{
private:
	int x1, x2, y1, y2;
	double A = 0;
	double B = 0;
	double C = 0;
	double sq=0;
	pair<double, double> e;
public:
	Line(int id_in, int x1_in, int y1_in, int x2_in, int y2_in);
	void preComput();
	double getA();
	double getB();
	double getC();
	double getSq();
	bool goThrough(double x, double y);
	void cross(Geo* g, int* p_count);
	void cross(Line* l, vector<Point>* points, int* p_count);
	double getEx();
	double getEy();
};

