/*
Виртуальные функции и полиморфизм. Домашняя работа.
HW3.cpp
Created by Zastupnevich Aleksey
2020-09-09
*/

#include <iostream>
#include <math.h>

using namespace std;

// Часть 1. Создать абстрактный класс Figure (фигура).
//Его наследниками являются классы Parallelogram (параллелограмм) и Circle (круг).
//Класс Parallelogram — базовый для классов Rectangle (прямоугольник), Square (квадрат), Rhombus (ромб).
//Для всех классов создать конструкторы. Для класса Figure добавить чисто виртуальную функцию area() (площадь).
//Во всех остальных классах переопределить эту функцию, исходя из геометрических формул нахождения площади.

class Figure{
public:
    virtual ~Figure(){}
    virtual void area() = 0;
};

class Parallelogramm: virtual public Figure{
protected:
    string name = "Parallelogramm";
    int lenght;
    int height;
    double angle;
    double areas;
public:
    Parallelogramm(int a, int b, int c) : lenght(a), height(b), angle(c) {} //Для параллелограмма
    Parallelogramm(int a, int b) : lenght(a), height(b), angle(b){}         //Для прямоугольника и ромба
    Parallelogramm(int a) : lenght(a){}                                     //Для квадрата
    virtual ~Parallelogramm(){}
    void area() override{
        areas = lenght * height * sin((angle*3.1415/180));}                  //площадь Параллел. через 2 стороны и угол между ними, перевод из град. в рад.
    void getAreas() const{
        cout << "Area of " << name << " is " << areas << endl;}
};

class Circle : virtual public Figure{
protected:
    int rad;
    double areas;
    string name = "Circle";
public:
    Circle(int a) : rad(a){}
    ~Circle(){}
    void area() override{
        areas = 3.1415 * rad * rad;}
    void getAreas() const{
         cout << "Area of " << name << " is " << areas << endl;}
};

class Rectangle : public Parallelogramm {
public:
    Rectangle(int a, int b): Parallelogramm(a, b) { name = "Rectangle";}
    ~Rectangle(){}
    void area() override {
        areas = lenght * height;}
};

class Square: public Parallelogramm{
public:
    Square(int a): Parallelogramm(a) { name = "Square";}
    ~Square(){}
    void area() override {
        areas = lenght * lenght;}
};

class Rhombus: public Parallelogramm{
public:
    Rhombus (int a, int b) : Parallelogramm(a,b){name = "Rhombus";}
    ~Rhombus(){}
    void area() override{
        areas = lenght * lenght * sin((angle*3.1415/180));}
};

/*Часть 2. Создать класс Car (автомобиль) с полями company (компания) и model (модель).
Классы-наследники: PassengerCar (легковой автомобиль) и Bus (автобус).
От этих классов наследует класс Minivan (минивэн).
Создать конструкторы для каждого из классов, чтобы они выводили данные о классах.
Создать объекты для каждого из классов и посмотреть,
в какой последовательности выполняются конструкторы. Обратить внимание на проблему «алмаз смерти».
Примечание: если использовать виртуальный базовый класс,
то объект самого "верхнего" базового класса создает самый "дочерний" класс.*/

class Car{
protected:
string company;
int model;
public:
    Car(string c, int m): company(c), model(m){
        cout << "Data of class Car - " << company << " model " << model << endl;
}
    ~Car(){}

};

class PassengerCar : public Car{
public:
    PassengerCar(string n, int m):Car(n,m){
    cout << "Data of class PassCar - " << company << " model " << model << endl;
    }
    ~PassengerCar(){}
};

class Bus : public Car{
public:
    Bus(string n, int m):Car(n,m){
    cout << "Data of class Bus - " << company << " model " << model << endl;
    }
    ~Bus(){}

};

class Minivan: public Bus, public PassengerCar{
public:
    Minivan(string n, int m): Bus(n,m),PassengerCar(n,m){
    cout << "Data of class Minivan - " << Bus::company << " model " << PassengerCar::model << endl; // в данном случае система без указания пространства не понимает из какого класса брать model и company
    }
    ~Minivan(){}
};

/*Часть 3. Создать класс: Fraction (дробь). Дробь имеет числитель и знаменатель (например, 3/7 или 9/2).
Предусмотреть, чтобы знаменатель не был равен 0.
Перегрузить: математические бинарные операторы (+, -, *, /) для выполнения действий с дробями унарный оператор (-)
логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).
Примечание: Поскольку операторы < и >=, > и <= — это логические противоположности,
попробуйте перегрузить один через другой.
Продемонстрировать использование перегруженных операторов*/

class Fraction{
protected:
    int numerator, denominator;
public:
    Fraction(int a, int b): numerator(a){
    if (b == 0) {
        cout << "mistake - denominator cat`t be zero" << endl << "Enter denominator, not is zero: " << endl;  //
        while (b==0){
          cin >> b;
        }
    }
    denominator = b;
    }

    ~Fraction(){}
    void printFr() const {cout << numerator << "/" << denominator << endl;}

    friend Fraction operator- (const Fraction &f1);
    friend Fraction operator+ (const Fraction &f1, const Fraction &f2);
    friend Fraction operator- (const Fraction &f1, const Fraction &f2);
    friend Fraction operator* (const Fraction &f1, const Fraction &f2);
    friend Fraction operator/ (const Fraction &f1, const Fraction &f2);
    friend bool operator> (const Fraction &f1, const Fraction &f2);
    friend bool operator<= (const Fraction &f1, const Fraction &f2);
    friend bool operator== (const Fraction &f1, const Fraction &f2);
    friend bool operator!= (const Fraction &f1, const Fraction &f2);
    friend bool operator>= (const Fraction &f1, const Fraction &f2);
    friend bool operator< (const Fraction &f1, const Fraction &f2);
};

//Унарыне операторы
Fraction operator- (const Fraction &f1){
return Fraction(-f1.numerator, f1.denominator);
}

//Банирные операторы
Fraction operator+ (const Fraction &f1, const Fraction &f2){
    if (f1.denominator != f2.denominator){
        int tempdenom = f1.denominator * f2.denominator;
        int f1n = f1.numerator * f2.denominator;
        int f2n = f2.numerator * f1.denominator;
        return Fraction(f1n + f2n, tempdenom);
    }else return Fraction(f1.numerator + f2.numerator, f1.denominator);
}
Fraction operator- (const Fraction &f1, const Fraction &f2){  //перегрузим оператор вычитание через оператора сложения с унарным "-"
    return f1 + (-f2);
}
Fraction operator* (const Fraction &f1, const Fraction &f2){
return Fraction(f1.numerator * f2.numerator, f1.denominator * f2.denominator);
}
Fraction operator/ (const Fraction &f1, const Fraction &f2){
return Fraction(f1.numerator * f2.denominator, f1.denominator * f2.numerator);
}

//Операторы сравнеия
bool operator> (const Fraction &f1, const Fraction &f2){
    if (f1.numerator * f2.denominator > f2.numerator * f1.denominator) return true;
    return false;
}
bool operator<= (const Fraction &f1, const Fraction &f2){
    if (f1>f2) return false;
    return true;
}
bool operator< (const Fraction &f1, const Fraction &f2){
    if (f1.numerator * f2.denominator < f2.numerator * f1.denominator) return true;
    return false;
}
bool operator>= (const Fraction &f1, const Fraction &f2){
    if (f1<f2) return false;
    return true;
}
bool operator== (const Fraction &f1, const Fraction &f2){
    if (f1.numerator * f2.denominator == f2.numerator * f1.denominator) return true;
    return false;
}
bool operator!= (const Fraction &f1, const Fraction &f2){
    if (f1==f2) return false;
    return true;
}

int main()
{
//Часть 1. Проверка в main
    Parallelogramm p(10,5,30);
    p.area();
    p.getAreas();
    Rectangle r(10,5);
    r.area();
    r.getAreas();
    Circle c(10);
    c.area();
    c.getAreas();
//Часть 2. Проверка в main
    Minivan m("Volvo", 54978);

// Часть 3. Проверка в main
    Fraction f1(1,4);
    Fraction f2(2,5);
    Fraction f3 = f1 + f2;
    f3.printFr();
    Fraction f4 = f1 * f2;
    f4.printFr();
    bool s;
    s = f1 <= f2;
    cout << s << endl;

//Часть 4. Создать класс Card - выполнено отдельным реквестом(веткой) на GitHub, ссылка в коментарии.

    return 0;
}
