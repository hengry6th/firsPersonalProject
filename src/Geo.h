#pragma once
#include <vector>
#include <utility>
#include<unordered_set>
using std::vector;
using std::pair;
class Geo
{
protected:
	char type='n';
	int id=0;
	vector<pair<double, double> > intersecs;
public:
	void set(char type_in, int id_in);
	char getType();
	int getID();
	bool addPoint(pair<double, double> p_in);
	void addPointOnly(pair<double, double> p_in);
	virtual bool goThrough(double x, double y)=0;
	virtual void cross(Geo* g, int* p_count)=0;
};

