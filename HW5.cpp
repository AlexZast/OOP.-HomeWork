#include <iostream>
#include <string>

using namespace std;

/* Задание 1.
 * Реализовать шаблон класса Pair1, который позволяет пользователю передавать данные одного типа парами. */

template <typename T>
class Pair1{
private:
    T ft;
    T sd;
public:

    Pair1(T f, T s) : ft(f), sd(s) { }
    ~Pair1(){ }

    T first() const{
        return ft;
    }
    T second() const{
        return sd;
    }

};

/* Задание 2.
 * Реализовать класс Pair, который позволяет использовать разные типы данных в передаваемых парах. */

template <typename T, typename S>
class Pair{
private:
    T ft;
    S sd;
public:

    Pair(T f, S s) : ft(f), sd(s) { }
    ~Pair(){ }

    T first() const{
        return ft;
    }
    S second() const{
        return sd;
    }

};

/* Задание 3.
 * Написать шаблон класса StringValuePair, в котором первое значение всегда типа string, а второе — любого типа.
 * Этот шаблон класса должен наследовать частично специализированный класс Pair,
 * в котором первый параметр — string, а второй — любого типа данных. */

// Частичная спциализация шаблона класса Pair где первый параметр string, а второй парамет любой тип данных - T
template <typename T>
class Pair<string, T>{
protected:
    string ft;          // Перове значение
    T sd;               // Второе значение

public:
   // Конструктор и деструктор
     Pair(string s, T a): ft(s), sd(a) { /*cout << "Pair constructor" << endl;*/ }
    ~Pair(){}
     string first() const{
         return ft;
     }
     T second() const{
         return sd;
     }
};


//создание класса StringValuePair наследующего от Pair
template<typename T>
class StringValuePair : virtual public Pair<string, T> {

public:
    StringValuePair(string s, T a) : Pair<string, T>(s, a) { /*cout << "StringValuePair constructor" << endl;*/ }
};


int main()
{
    // Заданием 1. Проверка в main()
    Pair1<int> p1(6, 9);
    cout << "Pair: " << p1.first() << ' ' << p1.second() << '\n';

    const Pair1<double> p2(3.4, 7.8);
    cout << "Pair: " << p2.first() << ' ' << p2.second() << '\n';

    // Заданием 2. Проверка в main()
    Pair<int, double> p3(6, 7.8);
    cout << "Pair: " << p3.first() << ' ' << p3.second() << '\n';

    const Pair<double, int> p4(3.4, 5);
    cout << "Pair: " << p4.first() << ' ' << p4.second() << '\n';

    // Задание 3. Проверка в main()

    Pair<string, double> p5("Jon", 25.8);
    cout << "Pair: " << p5.first() << ' ' << p5.second() << '\n';

    StringValuePair<int> svp("Amazing", 7);
    std::cout << "Pair: " << svp.first() << ' ' << svp.second() << '\n';

    return 0;



};
