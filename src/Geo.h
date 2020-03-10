#pragma once
#include <vector>
#include <utility>
#include<unordered_set>
using std::vector;
using std::pair;
using std::hash;
using std::unordered_set;
struct Point {
	double x;
	double y;
};

struct PointHash
{
	size_t operator()(const Point& p) const {
		return hash<double>()(p.x) ^ hash<double>()(p.y);
	}
};

struct PointCmp
{
	bool operator()(const Point& p1, const Point& p2) const {
		return p1.x == p2.x && p1.y == p2.y;
	}
};

class Geo
{
protected:
	char type='n';
	int id=0;
	//vector<pair<double, double> > intersecs;
public:
	void set(char type_in, int id_in);
	char getType();
	int getID();
	//bool addPoint(pair<double, double> p_in);
	//void addPointOnly(pair<double, double> p_in);
	virtual bool goThrough(double x, double y)=0;
	//virtual void cross(Geo* g, int* p_count)=0;
	virtual void cross(Geo* g, unordered_set<Point,PointHash, PointCmp> *set) = 0;
};

