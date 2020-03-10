#include <iostream>
#include<vector>
#include"Line.h"
#include"Circle.h"
#include"Geo.h"
#include<iostream>
#include<fstream>
#include<unordered_set>
using namespace std;
int main(/*int argc, char* argv[]*/)
{
    int n;
    int count = 0;
    int c_count = 0;
    vector<Geo*> geos;
    ifstream in_file;
    ofstream out_file;
    in_file.open(/*argv[2]*/"D:\\QNMDGIT\\firsPersonalProject\\src\\input.txt");
    out_file.open(/*argv[4]*/"D:\\QNMDGIT\\firsPersonalProject\\src\\output.txt");
    in_file >> n;
    int x1, y1, x2, y2;
    char c;
    for (int i = 0; i < n; i++) {
        in_file >> c;
        if (c == 'L') {
            in_file >> x1;
            in_file >> y1;
            in_file >> x2;
            in_file >> y2;
            geos.push_back(new Line(i, x1, y1, x2, y2));
        } else{
            c_count++;
            in_file >> x1;
            in_file >> y1;
            in_file >> x2;
            geos.push_back(new Circle('C', i, x1, y1, x2));
        }
    }
    std::unordered_set<Point, PointHash, PointCmp> set;
    if (c_count == 0) {
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                ((Line*)geos[j])->cross((Line*)geos[i], &set);
            }
        }
    }
    else {
            for (int i = 0; i < n; i++) {
                if (geos[i]->getType() == 'L') {
                    ((Line*)geos[i])->preComput();
                }
                for (int j = 0; j < i; j++) {
                    geos[j]->cross(geos[i],&set);
                }
            }
    }
    out_file << set.size() << endl;
}
