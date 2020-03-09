#include "point.h"

Point::Point(double x_in, double y_in)
{
	x = x_in;
	y = y_in;
}

double Point::getX()
{
	return x;
}

double Point::getY()
{
	return y;
}

void Point::addId(int id)
{
	linesID.push_back(id);
}

void Point::releaseID(vector<int>* lines)
{
	for (auto id : linesID) {
		(*lines)[id] = 0;
	}
}
