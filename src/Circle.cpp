#include "Circle.h"
#include "Line.h"
Circle::Circle(char type_in, int id_in, int x_in, int y_in, int r_in)
{
	set(type_in, id_in);
	x = x_in;
	y = y_in;
	r = r_in;
	r2 = r * r;
}

int Circle::getX()
{
	return x;
}

int Circle::getY()
{
	return y;
}

int Circle::getR()
{
	return r;
}

double Circle::getR2()
{
	return r2;
}

bool Circle::goThrough(double x_in, double y_in)
{
	return pow(x_in - x,2) + pow(y_in - y,2) == r2;
}

void Circle::cross(Geo* g, int* p_count)
{
	if (g->getType() == 'L') {
		double A = ((Line*)g)->getA();
		double B = ((Line*)g)->getB();
		double C = ((Line*)g)->getC();
		double d = pow((A * x + B * y + C), 2)/((Line*)g)->getSq();
		double s = r2 - d;
		if (s >= 0) {
			double C2 = B * x - A * y;
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
	else {
		int x2 = ((Circle*)g)->getX();
		int y2 = ((Circle*)g)->getY();
		int R = ((Circle*)g)->getR();
		double a =  (double)x2- x;
		double b = (double)y2- y;
		double r3 = (double)R - r;
		double r4 = (double)R + r;
		double d2 = a * a + b * b;
		double l1 = r3 * r3;
		double l2 = r4 * r4;
		if (d2 > l1&& d2 < l2) {
			double d = sqrt(d2);
			double s1 = (r2 - ((Circle*)g)->getR2() + d2) / 2 * d;
			double h = sqrt(r2 - a*a);
			double x0 = x + a / d * ((double)x2 - x);
			double y0 = y + a / d * ((double)y2 - y);
			double cx = h / d * ((double)y2 - y);
			double cy = h / d * ((double)x2 - x);
			pair<double, double>p1(x0 - cx, y0 - cy);
			g->addPointOnly(p1);
			if (addPoint(p1)) {
				(*p_count)++;
			}
			pair<double, double>p2(x0 + cx, y0 + cy);
			g->addPointOnly(p2);
			if (addPoint(p2)) {
				(*p_count)++;
			}
		}
		else if (d2 == l1) {
			double d = sqrt(d2);
			if (r < R) {
				pair<double, double>p(x + ((double)x - x2) * r / d, y + ((double)y - y2) * r / d);
				g->addPointOnly(p);
				if (addPoint(p)) {
					(*p_count)++;
				}
			}
			else {
				pair<double, double>p(x2 + ((double)x2 - x) * R / d, y2 + ((double)y2 - y) * R / d);
				g->addPointOnly(p);
				if (addPoint(p)) {
					(*p_count)++;
				}
			}
		}
		else if (d2 == l2) {
			double d = sqrt(d2);
			pair<double, double>p(x + ((double)x2 - x) * r / d, y + ((double)y2 - y) * r / d);
			g->addPointOnly(p);
			if (addPoint(p)) {
				(*p_count)++;
			}
		}
	}
}
