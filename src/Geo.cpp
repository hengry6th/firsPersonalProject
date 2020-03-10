#include "Geo.h"

void Geo::set(char type_in, int id_in)
{
	type = type_in;
	id = id_in;
}

char Geo::getType()
{
	return type;
}

int Geo::getID()
{
	return id;
}
/*
bool Geo::addPoint(pair<double, double> p_in)
{
	for (auto iter : intersecs)
	{
		if (iter == p_in) {
			return false;
		}
	}
	intersecs.push_back(p_in);
	return true;
}

void Geo::addPointOnly(pair<double, double> p_in)
{
	intersecs.push_back(p_in);
}
*/

