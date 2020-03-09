#include <iostream>
#include<vector>
#include"Line.h"
#include"Circle.h"
#include"point.h"
#include"Geo.h"
#include<iostream>
#include<fstream>
using namespace std;
int main(int argc, char* argv[])
{
    int n;
    int count = 0;
    int c_count = 0;
    vector<Geo*> geos;
    ifstream in_file;
    ofstream out_file;
    in_file.open(argv[2]);
    out_file.open(argv[4]);
    in_file >> n;
    int x1, y1, x2, y2;
    char c;
    Geo* g;
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
    if (c_count == 0) {
        vector<Point> points;
        vector<int> linesID;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < count;j++) {
                if (geos[i]->goThrough(points[j].getX(), points[j].getY())) {
                    points[j].releaseID(&linesID);
                    points[j].addId(i);
                }
            }
            for (int j = 0; j < i; j++) {
                if (linesID[j] == 0) {
                    linesID[j] = 1;
                    continue;
                }
                ((Line*)geos[j])->cross((Line*)geos[i], &points, &count);
            }
            linesID.push_back(1);
        }
    }
    else {
            for (int i = 0; i < n; i++) {
                if (geos[i]->getType() == 'L') {
                    ((Line*)geos[i])->preComput();
                }
                for (int j = 0; j < i; j++) {
                    geos[j]->cross(geos[i],&count);
                }
            }
    }
    out_file << count << endl;
}
