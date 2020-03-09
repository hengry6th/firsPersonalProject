#include "Line.h"
#include"Circle.h"
#include <cmath>
#include"point.h"

Line::Line(int id_in, int x1_in, int y1_in, int x2_in, int y2_in)
{
	x1 = x1_in;
	x2 = x2_in;
	y1 = y1_in;
	y2 = y2_in;
	set('L', id_in);
	A = (double)y2 - y1;
	B = (double)x1 - x2;
	C = (double)y1 * ((double)x2 - x1) - (double)x1 * ((double)y2 - y1);
}

void Line::preComput()
{	
	sq = A * A + B * B;
	double d = sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
	e.first = ((double)x2 - x1) / d;
	e.second = ((double)y2 - y1) / d;
}



double Line::getA()
{
	return A;
}

double Line::getB()
{
	return B;
}

double Line::getC()
{
	return C;
}

double Line::getSq()
{
	return sq;
}


bool Line::goThrough(double x, double y)
{
	return A * x + B * y + C == 0;
}

void Line::cross(Geo* g, int* p_count)
{
	if (g->getType() == 'L') {
		double A2 = ((Line*)g)->getA();
		double B2 = ((Line*)g)->getB();
		double C2 = ((Line*)g)->getC();
		if (A * B2 != B * A2) {
			double temp_x = (C2 * B - C * B2) / (A * B2 - A2 * B);
			double temp_y = (C2 * A - C * A2) / (B * A2 - B2 * A);
			pair<double, double> p(temp_x,temp_y);
			g->addPointOnly(p);
			if (addPoint(p)) {
				(*p_count)++;
			}
		}
	} else{
		double x = ((Circle*)g)->getX();
		double y = ((Circle*)g)->getY();
		double d = pow((A * x + B * y + C), 2)/sq;
		double s = ((Circle*)g)->getR2() - d;
		if (s >= 0) {
			double C2 = A * y - B * x;
			double temp_x = (C2 * B - C * A) / (A * A + B * B);
			double temp_y = (C2 * A - C * B) / (A * A + B * B);
			if (s == 0) {
				pair<double, double> p(temp_x, temp_y);
				g->addPointOnly(p);
				if (addPoint(p)) {
					(*p_count)++;
				}
			}
			else {
				double l = sqrt(s);
				double ex = ((Line*)g)->getEx();
				double ey = ((Line*)g)->getEy();
				pair<double, double> p1(temp_x + ex * l, temp_y + ex * l);
				g->addPointOnly(p1);
				if (addPoint(p1)) {
					(*p_count)++;
				}
				pair<double, double> p2(temp_x - ex * l, temp_y - ex * l);
				g->addPointOnly(p2);
				if (addPoint(p2)) {
					(*p_count)++;
				}
			}
		}
	}
}

void Line::cross(Line* l, vector<Point>* points, int* p_count)
{
	double A2 = l->getA();
	double B2 = l->getB();
	double C2 = l->getC();
	if (A * B2 != B * A2) {
		(*p_count)++;
		double temp_x = (C2 * B - C * B2) / (A * B2 - A2 * B);
		double temp_y = (C2 * A - C * A2) / (B * A2 - B2 * A);
		Point p(temp_x, temp_y);
		p.addId(id);
		p.addId(l->getID());
		(*points).push_back(p);
	}
}


double Line::getEx()
{
	return e.first;
}

double Line::getEy()
{
	return e.second;
}


