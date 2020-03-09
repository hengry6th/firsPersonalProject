# firsPersonalProject
The first personal project of 2020 BUAA Software Engineering.
# 使用方法

./jiaoDian.exe -i input.txt -o output.txt

input.txt是输入文件路径，output.txt是输出结果的路径

## 类

#### Geo 

性质：抽象父类，下含Line直线类和Circle圆类；

##### 属性：

int id：序号标识

char type: 区分直线和圆

vector<pair<double, double> > intersecs： 该图形上的交点集，由于后续查找是否有重合的点。

##### 方法：

void set(char type_in, int id_in);

功能：设置初始化的类型和初始化的id；

输入：图的类型type_in，图的id；

输出：无

char getType();

功能：读取图的类型

int getID();

功能：读取图的id；

bool addPoint(pair<double, double> p_in);
功能：查询交点集中是否有输入的点p_in，如果没有则将其加入交点集中。

输入：交点p_in

输出：若交点集中存在该点则输出false，表示插入失败，否则输出true，表示插入成功。

void addPointOnly(pair<double, double> p_in);

功能：直接将输入的点插入交点集中，不检查是否存在。

输入：交点p_in

输出：无

virtual bool goThrough(double x, double y)=0;

功能： 判断该图形是否经过输入的点（x，y），接口;

输入：点的横坐标x，纵坐标y，都为double 类型;

输出：如果经过该点则输出true，否则输出false;

virtual void cross(Geo* g, int* p_count)=0;

功能：判断当前图形与输入图形是否相交，如果相交则将交点保存在intersecs中，使计数增加；

输入：图形geo的指针p，指向计数的变量的指针p_count；

输出：无；



#### Line

直线的类

直线以$Ax+By+C=0$的形式记录

##### 属性：

int x1，y1, x2, y2:输入的点；

double A：方程式中x的系数；

double B：方程式中y的系数；

double C: 方程式中常数项；

double sq：$sq = A^2 + B^2$用于后续计算直线与圆的距离；

pair<double, double> e:单位向量，用于后续计算直线与圆的交点；

##### 方法：

Line(int id_in, int x1_in, int y1_in, int x2_in, int y2_in);
功能：构造函数，保存输入的(x1, y1), (x2, y2)，并计算方程式中的系数A，B, C；

输入：int id_in图形id， int x1_in第一个点的横坐标， int y1_in 第一个点的纵坐标, int x2_in 第二个点的横坐标, int y2_in第二个点的纵坐标。

void preComput();
功能：计算sq，e，仅直线与直线相交的时候不需要sq和e，所以只有在输入有圆的情况下才会使用；

输入：无

输出：无

double getA();
功能：读取A的值；

double getB();
功能：读取B的值；

double getC();
功能：读取C的值；

double getSq();
功能：读取sq的值；

bool goThrough(double x, double y);
功能：从父类继承的接口，使用方程式$Ax+By+C = 0$ 来判断该直线是否过输入的点

输入：点的横坐标x，纵坐标y；

输出：过该点则输出true，否则输出false；

void cross(Geo* g, int* p_count);
功能：从父类继承的接口，用来计算与输入的指针g所指向的图形的交点，并改变计数

输入: 指向图形的指针g，指向计数的变量的指针p_count;

输出：无

void cross(Line* l, vector\<Point\>* points, int* p_count);
功能：重载，用来计算与输入的指针l所指向的直线的交点，将其加入到点集points中，并改变计数

输入: 指向直线的指针l，指向点集的指针points，指向计数的变量的指针p_count;

输出：无

double getEx();
功能：读取单位向量的横坐标；

double getEy();

功能：读取单位向量的纵坐标；

#### Circle 

圆类

圆的公式$(x-x_0)^2+(y-y_0)^2+r^2$,其中圆心$(x_0,y_0)$半径r

##### 属性：

int x, y：圆心的横纵坐标坐标；

int r：半径；

double r2: $r2=r^2$ 记录半径的平方，用来后续计算与圆，与直线的交点。

##### 方法：

Circle(int x_in, int y_in, int r_in);

功能： 构造方法，保存输入的圆心和半径，并计算r2；

输入：圆心(x_in, y_in),半径r_in;

int getX();
功能：读取圆心的横坐标x

int getY();
功能: 读取圆心的纵坐标y

int getR();

功能：读取圆的半径r

double getR2();

功能：读取半径的平方r2；

bool goThrough(double x, double y)；

功能：对父类方法的实现，使用圆的公式$(x-x_0)^2+(y-y_0)^2+r^2$,其中圆心$(x_0,y_0)$半径r判断是否过输入的点

输入：点横坐标x，纵坐标y；

void cross(Geo* g, int* p_count);

功能：对父类方法的实现，计算与输入的指针p所指向的图形的交点，并改变p_count所指向的计数变量的值



#### Point

点类

##### 属性：

double x：横坐标

double y：纵坐标

vector\<int\> linesID：过该点的直线的id；

##### 方法：

Point(double x_in, double y_in);

功能：构造函数，保存输入的横纵坐标

输入：横坐标x_in, 纵坐标y_in；

double getX();

功能：读取横坐标

double getY();

功能：读取纵坐标

void addId(int id);

功能：将输入的id添加到linesID中；

输入：要添加的直线的id

void releaseID(vector\<int\>* lines);

功能：lines是标记数组，lines[i]=0表示id=i的直线不需要被计算。这个函数是用来将lines上过该点的直线的标记位记为0，从而达到剪枝的目的。

输入：指向lines的指针。
