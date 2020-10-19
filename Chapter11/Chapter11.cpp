#include <iostream>
#include <Windows.h>
#include <string>

class Shape {
protected:
	int x;
	int y;
public:
	Shape(int x, int y) { this->x = x; this->y = y; }
	void SetX(int x) { this->x = x; }
	void SetY(int y) { this->y = y; }
};
class Rect :public Shape {
protected:
	int width;
	int height;
public:
	Rect(int x, int y, int width, int height) : Shape(x, y) { this->width = width; this->height = height; }
	void SetWidth(int width)	{ this->width = width; }
	void SetHeight(int height)	{ this->height = height; }

	int GetArea() { return width * height; }

	void Draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		Rectangle(hdc, x, y, x + width, y + height);
	}
};
class ColoredRect :public Rect {
	int red;
	int green;
	int blue;
public:
	ColoredRect(int x, int y, int width, int height, int r, int g, int b) : Rect(x, y, width, height) { red = r; green = g; blue = b; }

	void SetColor(int r, int g, int b) { red = r; green = g; blue = b; }

	void Draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(red, green, blue));
		Rectangle(hdc, x, y, x + width, y + height);
	}
};

class Sprite {
protected:
	int x;
	int y;
	std::string image;
public:
	Sprite(int x, int y, std::string image) {
		this->x = x;
		this->y = y;
		this->image = image;
	}
	void Draw()	{}
	void Move() {}
};
class Alien : public Sprite{
protected:
	int speed;
public:
	Alien(int x, int y, std::string image, int speed) : Sprite(x, y, image) {
		this->speed = speed;
	}
	void Move() {}
};
class Player :public Sprite {
protected:
	std::string name;
public :
	Player(int x, int y, std::string image, std::string name) : Sprite(x, y, image)
	{
		this->name = name;
	}

	void Move() {}
};

class Person {
protected:
	std::string name;
	int birthYear;
public:
	Person(std::string name, int birthYear)
	{
		this->name = name;
		this->birthYear = birthYear;
	}

	void Print()
	{
		printf("성명: %s\n", name.c_str());
		printf("출생연도: %d\n", birthYear);
	}
};
class Student : public Person{
protected:
	std::string university;
public:
	Student(std::string name, int birthYear, std::string university) : Person(name, birthYear)
	{
		this->university = university;
	}
	void Print()
	{
		Person::Print();
		printf("대학교: %s\n", university.c_str());
	}
};
class ITStudent : public Student {};
class MathStudent : public Student {};
class Employee : public Person {};
class Driver : public Employee {};
class Engineer : public Employee {};

class Fruit {};
class Apple : public Fruit {};
class Banana : public Fruit {};

class TwoDimension {
protected:
	double x, y;
public:
	TwoDimension(double i, double j) :x(i), y(j) {}
};
class ThreeDimension : public TwoDimension {
protected:
	double z;
public:
	ThreeDimension(double i, double j, double k) : TwoDimension(i, j), z(k) {}
};

class Phone {
	void Call();
	void Receive();
	void SendSMS();
};
class Computer {
	void DoInternet();
};
class SmartPhone :public Phone, public Computer {};

class Box {
protected:
	double width;
};
class SmallBox : Box {
public:
	void setWidth(double w) { width = w; }
};

class Human {
	std::string name;
	int age;
public:
	Human(std::string name, int age) {
		this->name = name;
		this->age = age;
	}

	void SetName(std::string name)	{ this->name = name; }
	void SetAge(int age)			{ this->age = age; }

	std::string GetName()			{ return name; }
	int GetAge()					{ return age; }
	void Print()
	{
		printf("이름: %s\n", name.c_str());
		printf("나이: %d\n", age);
	}
};
class HStudent : public Human {
	std::string major;
public:
	HStudent(std::string name, int age, std::string major) : Human(name, age), major(major) {}
};

class Point {
protected:
	int x, y;
public:
	Point(int x, int y) : x(x), y(y) {}
};
class ThreeDPoint : public Point {
	int z;
public:
	ThreeDPoint(int x = 0, int y = 0, int z = 0) : Point(x, y), z(z) {}
	void Print()
	{
		printf("(%d,%d,%d)\n", x, y, z);
	}

	ThreeDPoint& operator+(const ThreeDPoint tdp2)
	{
		ThreeDPoint tdp;
		tdp.x = this->x + tdp2.x;
		tdp.y = this->y + tdp2.y;
		tdp.z = this->z + tdp2.z;
		return tdp;
	}
};

class Circle {
protected:
	int x, y, radius;
public:
	Circle(int x, int y, int radius) :x(x), y(y), radius(radius) {}
	void Draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		Ellipse(hdc, x, y, x + radius * 2, y + radius * 2);
	}
};
class ColoredCircle : public Circle {
	int red;
	int green;
	int blue;
public:
	ColoredCircle(int x, int y, int radius, int r, int g, int b) : Circle(x, y, radius) { red = r; green = g; blue = b; }

	void SetColor(int r, int g, int b) { red = r; green = g; blue = b; }

	void Draw() {
		HDC hdc = GetWindowDC(GetForegroundWindow());
		SelectObject(hdc, GetStockObject(DC_BRUSH));
		SetDCBrushColor(hdc, RGB(red, green, blue));
		Ellipse(hdc, x, y, x + radius * 2, y + radius * 2);
	}
};

class Employee2 {
	std::string name;
	int salary;
public:
	Employee2(std::string name, int salary) : name(name), salary(salary) {}

	void SetName(std::string name)	{ this->name = name; }
	void SetSalary(int salary)		{ this->salary = salary; }

	std::string GetName()	{ return name; }
	int GetSalary()			{ return salary; }

	int ComputeSalary() { return salary; }
};
class Manager : public Employee2 {
	int bonus;
public:
	Manager(std::string name, int salary, int bonus) : Employee2(name, salary), bonus(bonus) {}
	void SetBonus(int bonus) { this->bonus = bonus; }
	int GetBonus() { return bonus; }
	int ComputeSalary() { return Employee2::ComputeSalary() + bonus; }
};

class Person2 {
	std::string name;
	std::string address;
	std::string tel;
public:
	Person2(std::string name, std::string address, std::string tel) : name(name), address(address), tel(tel) {}
	void SetName(std::string name) { this->name = name; }
	void SetAddress(std::string address) { this->address = address; }
	void SetTel(std::string tel) { this->tel = tel; }
	std::string GetName() { return name; }
	std::string GetAddress() { return address; }
	std::string GetTel() { return tel; }
};
class Customer : public Person2 {
	int id;
	int mileage;
public:
	Customer(std::string name, std::string address, std::string tel, int id, int mileage) : Person2(name, address, tel), id(id), mileage(mileage) {}
	void SetId(int id) { this->id = id; }
	void SetMileage(int mileage) { this->mileage = mileage; }
	int GetId() { return id; }
	int GetMileage() { return mileage; }
};

class Shape2 {
	int x, y;
	std::string color;
public:
	double GetArea() {}
};
class Circle2 : public Shape2 {
	int radius;
public:
	double GetArea() {
		return 3.14 * radius * radius;
	}
};

class Person3 {
	std::string job;
	int age;
public:
	Person3(std::string job, int age) : job(job), age(age) {}
	std::string GetJobString() { return job; }
	int GetAge() { return age; }
	void Eat() { std::cout << "먹을 수 있음." << std::endl; }
	void Talk() { std::cout << "말할 수 있음." << std::endl; }
	void Run() { std::cout << "달릴 수 있음." << std::endl; }
};
class Professor :public Person3 {
public:
	Professor(int age) : Person3("교수", age) {}
	void Teach() { std::cout << "가르칠 수 있음." << std::endl; }
};
class TennisPlayer :public Person3 {
public:
	TennisPlayer(int age) : Person3("테니스 선수", age) {}
	void PlayTennis() { std::cout << "테니스 경기를 할 수 있음." << std::endl; }
};
class Businessman :public Person3 {
public:
	Businessman(int age) : Person3("비지니스맨", age) {}
	void RunBusiness() { std::cout << "비지니스를 할 수 있음." << std::endl; }
};

int main()
{
	Rect rect(100, 100, 80, 80);
	ColoredRect coloredRect(200, 200, 80, 80, 255, 0, 0);

	rect.Draw();
	coloredRect.Draw();

	std::cout << "사각형의 면적: " << rect.GetArea() << std::endl;
	std::cout << std::endl;

	Alien a(0, 100, "image1.jpg", 5);
	Player p(0, 100, "image1.jpg", "player");

	Student s("홍길동", 1994, "순천향대학교");
	s.Print();
	std::cout << std::endl;

	ThreeDimension td(1.1, 2.2, 3.3);

	Human ch("춘향", 18), mr("몽룡", 21), sd("사또", 50);
	ch.Print();
	mr.Print();
	sd.Print();
	std::cout << std::endl;

	ThreeDPoint tdp1(10, 20, 30);
	ThreeDPoint tdp2(3, 4, 5);
	ThreeDPoint tdp3;
	tdp3 = tdp1 + tdp2;
	tdp3.Print();
	std::cout << std::endl;

	Circle circle(100, 200, 80);
	ColoredCircle coloredCircle(200, 300, 80, 255, 0, 0);

	circle.Draw();
	coloredCircle.Draw();

	Manager kcs("김철수", 200, 100);
	std::cout << "이름: " << kcs.GetName() << std::endl;
	std::cout << "월급: " << kcs.GetSalary() << std::endl;
	std::cout << "보너스: " << kcs.GetBonus() << std::endl;
	std::cout << "전체 급여: " << kcs.ComputeSalary() << std::endl;
	std::cout << std::endl;

	Customer cKcs("김철수", "서울시 종로구", "010-1111-2222", 1, 1000);
	std::cout << "이름: " << cKcs.GetName() << std::endl;
	std::cout << "주소: " << cKcs.GetAddress() << std::endl;
	std::cout << "전화번호: " << cKcs.GetTel() << std::endl;
	std::cout << "아이디: " << cKcs.GetId() << std::endl;
	std::cout << "마일리지: " << cKcs.GetMileage() << std::endl;
	std::cout << std::endl;

	Professor pro(39);
	std::cout << "나의 직업: " << pro.GetJobString() << std::endl;
	std::cout << "나의 나이: " << pro.GetAge() << std::endl;
	pro.Run();
	pro.Talk();
	pro.Teach();
	std::cout << std::endl;

	TennisPlayer tp(23);
	std::cout << "나의 직업: " << tp.GetJobString() << std::endl;
	std::cout << "나의 나이: " << tp.GetAge() << std::endl;
	tp.Run();
	tp.Talk();
	tp.PlayTennis();
	std::cout << std::endl;

	return 0;
}
