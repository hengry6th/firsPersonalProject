#pragma once
#include<vector>

using std::vector;

class Point
{
private:
	double x;
	double y;
	vector<int> linesID;
public:
	Point(double x_in, double y_in);
	double getX();
	double getY();
	void addId(int id);
	void releaseID(vector<int>* lines);
};

