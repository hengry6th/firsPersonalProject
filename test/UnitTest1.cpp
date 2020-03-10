#include "pch.h"
#include "CppUnitTest.h"
#include"../src/Line.h"
#include "../src/Circle.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			Line* l = new Line(0, 0, 0, 1, 1);
			l->preComput();
			double A = l->getA();
			double B = l->getB();
			double C = l->getC();
			double sq = l->getSq();
			Assert::AreEqual(C,0.0);
			Assert::AreEqual(A, -B);
			Assert::AreEqual(2.0, sq);
			double ex = l->getEx();
			double ey = l->getEy();
			double te = 1/sqrt(2);
			Assert::AreEqual(ex, ey);
			Assert::AreEqual(ex,te);
		}
		TEST_METHOD(TestMethod2) {
			Line* l1 = new Line(0, 1, 2, 1, 5);
			Line* l2 = new Line(1, 2, 5, 2, 0);
			int count = 0;
			std::unordered_set<Point, PointHash, PointCmp> set;
			l1->cross(l2, &set);
			count = set.size();
			Assert::AreEqual(count, 0);
		}
		TEST_METHOD(TestMethod3) {
			Line* l1 = new Line(0, 1, 0, 1, 1);
			Line* l2 = new Line(1, 1, 1, 2, 1);
			Line* l3 = new Line(2, 1, 1, 3, 3);
			Line* l4 = new Line(3, 0, 2, 2, 0);
			vector<Point> p;
			vector<Geo*> geos;
			geos.push_back(l1);
			geos.push_back(l2);
			geos.push_back(l3);
			geos.push_back(l4);
			int count = 0;
			std::unordered_set<Point, PointHash, PointCmp> set;
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < i; j++) {
					((Line*)geos[j])->cross((Line*)geos[i], &set);
				}
			}
			count = set.size();
			Assert::AreEqual(count, 1);
		}
		TEST_METHOD(TestMethod4) {
			Line* l1 = new Line(0, -10, -11, -10, -10);
			Line* l2 = new Line(1, -10, -10, -12, -10);
			Line* l3 = new Line(2, -10, -10, -13, -13);
			Line* l4 = new Line(3, 0, -20, -20, 0);
			int count = 0;
			vector<Line*> que;
			que.push_back(l1);
			que.push_back(l2);
			que.push_back(l3);
			que.push_back(l4);
			std::unordered_set<Point, PointHash, PointCmp> set;
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < i; j++) {
					que[j]->cross(que[i],&set);
				}
			}
			count = set.size();
			Assert::AreEqual(1, count);
			Assert::AreEqual(true, l1->goThrough(-10.0,-10.0));
			Assert::AreEqual(true, l2->goThrough(-10.0, -10.0));
			Assert::AreEqual(true, l3->goThrough(-10.0, -10.0));
			Assert::AreEqual(true, l4->goThrough(-10.0, -10.0));
		}
		TEST_METHOD(TestMethod5) {
			Line* l1 = new Line(0, 0, 0, 1, 0);
			Line* l2 = new Line(1, 0, 1, 0, 2);
			Line* l3 = new Line(2, 1, 0, 1, 3);
			Line* l4 = new Line(3, 0, 2, 1, 2);
			int count = 0;
			vector<Line*> que;
			que.push_back(l1);
			que.push_back(l2);
			que.push_back(l3);
			que.push_back(l4);
			std::unordered_set<Point, PointHash, PointCmp> set;
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < i; j++) {
					que[j]->cross(que[i], &set);
				}
			}
			count = set.size();
			Assert::AreEqual(4, count);
		}
		TEST_METHOD(TestMethod6) {
			Line* l1 = new Line(0, 0, 99999, 1, -99999);
			Line* l2 = new Line(1, 0, 0, 0, 2);
			Line* l3 = new Line(2, -99999, 0, 99999, 1);
			Line* l4 = new Line(3, 1, 0, 999, 2);
			int count = 0;
			vector<Line*> que;
			que.push_back(l1);
			que.push_back(l2);
			que.push_back(l3);
			que.push_back(l4);
			std::unordered_set<Point, PointHash, PointCmp> set;
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < i; j++) {
					que[j]->cross(que[i], &set);
				}
			}
			count = set.size();
			Assert::AreEqual(6, count);
		}
	};
	TEST_CLASS(CircleLineTest) {
	public:
		TEST_METHOD(TestMethod1)
		{
			Circle* c = new Circle('C',0, 0, 1, 2);
			Assert::AreEqual(0, c->getX());
			Assert::AreEqual(1, c->getY());
			Assert::AreEqual(2, c->getR());
			Assert::AreEqual(4.0, c->getR2());
			
		}
		TEST_METHOD(TestMethod2) {
			Circle* c = new Circle('C', 0, 0, 2, 2);
			Line* l = new Line(1, 0, 0, 1, 0);
			std::unordered_set<Point, PointHash, PointCmp> set;
			l->preComput();
			int count = 0;
			c->cross(l, &set);
			count = set.size();
			Assert::AreEqual(1, (int)set.size());
			l->cross(c, &set);
			Assert::AreEqual(1, count);
			Line* l2 = new Line(2, 0, 2, 2, 0);
			l2->preComput();
			Line* l3 = new Line(3, 0, -1, 3, 2);
			l3->preComput();
			c->cross(l2, &set);
			Assert::AreEqual(3, (int)set.size());
			l->cross(l2, &set);
			Assert::AreEqual(4, (int)set.size());
			c->cross(l3, &set);
			Assert::AreEqual(4, (int)set.size());
			l->cross(l3, &set);
			Assert::AreEqual(5, (int)set.size());
			l2->cross(l3, &set);
			Assert::AreEqual(6, (int)set.size());
		}
		TEST_METHOD(TestMethod3) {
			vector<Circle*> que;
			Circle* c = new Circle('C', 0, 0, 0, 4);
			que.push_back(c);
			Circle* c1 = new Circle('C', 1, 2, 0, 2);
			que.push_back(c1);
			Circle* c2 = new Circle('C', 1, 6, 0, 2);
			que.push_back(c2);
			Circle* c3 = new Circle('C', 1, 2, 0, 2);
			que.push_back(c3);
			int count = 0;
			std::unordered_set<Point, PointHash, PointCmp> set;
			for (int i = 1; i < 4; i++) {
				for (int j = 0; j < i; j++) {
					(que[j])->cross(que[i], &set);
				}
			}
			Assert::AreEqual(5, (int)set.size());
		}
	};
}
