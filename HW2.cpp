/*
 * HW2.ccp
 * OOP. HomeWork 2. Наследование
 * Created by Zastupnevich Aleksey
 * Qt Creator 4.13.0 (Qt 5.15.0)
 * 2020-09-22
 * github -
 */

#include <iostream>
#include <string.h>
//#include <iomanip>

using namespace std;

/* Часть 1. Создать класс Person (человек) с полями: имя, возраст, пол и вес.
 * Определить методы переназначения имени, изменения возраста и веса. Создать производный класс
 * Student (студент), имеющий поле года обучения. Определить методы переназначения и увеличения этого значения.
 * Создать счетчик количества созданных студентов. В функции main() создать несколько студентов.
 * По запросу вывести определенного человека.
*/

class Person{
private:
protected:                  //для возможности доступа через другой класс
    string name, gender;
    int age, weight;
public:
    //Конструкторы и деструктор Person
    Person(){}
    Person(string name, string gender, int age, int weight){
        this->name = name;
        this->gender = gender;
        this->age = age;
        this->weight = weight;
    }
    ~Person(){}

    //Методы для изменения значений
    void getName(string NewName){
        name = NewName;
    }
    void getAge(int NewAge){
        age = NewAge;
    }
    void getWeight(int NewWeight){
        weight = NewWeight;
    }
    // Методы для печати значений
    void printP() const{
    cout << name<< " " << gender << " " << age << " " << weight << endl;
    }
};
class Student : public Person{
protected:
    static int c;
    int year;
public:
    //конструкторы и деструкторы Student
    Student(){ c++;
    }
    Student(string name, string gender, int age, int weight, int y) :  Person(name, gender, age, weight), year(y){c++;}
    ~Student(){c--;}
    //метод для изменения года
    void getYear(int NewYear){
        year = NewYear;
    }
    void plusYear(){
        year++;
    }
    // Методы для печати значений
    void printS() const{
        cout << name<< " " << gender << " " << age << " " << weight << " " << year << endl;
    }
    void printC() const{
        cout << "Numbers of students - " << c << endl << endl;
    }
};
int Student::c=0;

/* Часть 2. Создать классы Apple (яблоко) и Banana (банан), которые наследуют класс Fruit (фрукт).
 * У Fruit есть две переменные-члена: name (имя) и color (цвет).
 * Добавить новый класс GrannySmith, который наследует класс Apple.

int main()
{
Apple a("red");
Banana b;
GrannySmith c;

std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

return 0;
}

Код, приведенный выше, должен давать следующий результат:
My apple is red.
My banana is yellow.
My Granny Smith apple is green.

*/

class Fruit{
protected:
    string name, color;
public:
    string getName() const {return name;}
    string getColor() const {return color;}
};
class Apple: public Fruit {
protected:

public:
    Apple(){
        name = "apple";
        color="green";
    }
    Apple(string clr){
        name = "apple";
        color=clr;
    }
    ~Apple(){}


};
class Banana : public Fruit{

public:
    Banana(){
        name = "banana";
        color = "yellow";
    }
    Banana(string clr){
        name = "banana";
        color=clr;
    }
    ~Banana(){}
};
class GrannySmith : public Apple{
public:
    GrannySmith(){
        name = "Granny Smith apple";
    }
    GrannySmith(string clr){
        color = clr;
    }
    ~GrannySmith(){}
};

int main()
{
// Часть 1. Проверка main().
    Person person ("Ivan", "Man", 30, 60);
    Student student ("Alex", "Man", 30, 80, 1);
    Student student2("Masha", "Female", 25, 60, 3);
    person.printP();
    student.printS();
    student.printP();
    student2.plusYear();
    student2.printS();
    student.printC();
//Часть 2. Проверка в main().
    Apple a("red");
    Banana b;
    GrannySmith c;

    std::cout << "My " << a.getName() << " is " << a.getColor() << ".\n";
    std::cout << "My " << b.getName() << " is " << b.getColor() << ".\n";
    std::cout << "My " << c.getName() << " is " << c.getColor() << ".\n";

    return 0;
}
// Часть 3.
/*

Игра БлэкДжек

Для реализации игры может потребоваться следующее:

Классы:
Сами карты - объект с 2мя полями - масть и значение
Колода - массив объектов типа "Карта"  52 вариации расположенных в случайном порядке
Рука Игрока/Диллера - массив Карт выданных с Колоды

Получается можно обойтись 2-мя классами - карта и стопка карт (колода/рука) или 3мя если мы разделим колоду и руки.
Рука должна быть производным классом и наследовать свойства от Колоды.

Методы:
Для Колоды - сформировать массив и перемешать его в рандомном порядке
выдать карту - игроку/диллеру

Для рук - подсчитать очки, сообщить о возможности дальнейше игры, выйгрыше (БлекДжек) или прогигрыше (перебор)

ЗАГОТОВКА


enum Suit {clubs, diamonds, hearts, spades};
enum Value  {two, three, four, fife, six, seven, eight, nine, ten , J, Q, K, A}; // При вводе числ и значений выдает ошибку
class Card{
protected:
   Suit suit;
   Value value;
public:
   void setSuit(Suit s){
       suit = s;
   }
   void setValue(Value v){
       value = v;
   }
   Suit getSuit() const{    //не корректно возвращает значение
       return suit;
   }
   Value getValue() const{ //некорректно возвращает значение
       return value;
   }
};

class Desk{
protected:
   Card arr[52];
public:
   void makeDeck(){
       int n = 0;
       for (int i=0; i< 4; i++){
           for(int j = 0; j<13; j++){
               switch (i) {
               case 0: arr[j*i].setSuit(clubs); cout << "* ";
               case 1: arr[j+i*13].setSuit(diamonds);
               case 2: arr[j+i*13].setSuit(hearts);
               case 3: arr[j+i*13].setSuit(spades);
               };
               switch (j) {
               case 0: arr[j+i*13].setValue(two);
               case 1: arr[j+i*13].setValue(three);
               case 2: arr[j+i*13].setValue(four);
               case 3: arr[j+i*13].setValue(fife);
               case 4: arr[j+i*13].setValue(six);
               case 5: arr[j+i*13].setValue(seven);
               case 6: arr[j+i*13].setValue(eight);
               case 7: arr[j+i*13].setValue(nine);
               case 8: arr[j+i*13].setValue(ten);
               case 9: arr[j+i*13].setValue(J);
               case 10: arr[j+i*13].setValue(K);
               case 11: arr[j+i*13].setValue(Q);
               case 12: arr[j+i*13].setValue(A);
               };
               n++;
               cout << arr[j+i*13].getSuit() << " " << arr[j+i*13].getValue() << " | ";
           }
       }
   }
   void printDeck() const{
       for (int i = 0; i<52; i++)
           cout << arr[i].getSuit() << " " << arr[i].getValue() << " | ";
   }
};


*/



