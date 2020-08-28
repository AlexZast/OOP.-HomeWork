/*
 * HW1.ccp
 * OOP. HomeWork 1.
 * Created by Zastupnevich Aleksey
 * Qt Creator 4.13.0 (Qt 5.15.0)
 * 2020-08-28
 * github -
 */

#include <iostream>
#include <math.h>
#include <cstdint>

using namespace std;

// Часть 1. класс Power и возведение в квадрат
class Power{
private:
    float a;
    float b;

public:
    Power(){        //Конструктор по умолчанию
      a=2;
      b=2;
    };

    void setA(float s){
      a = s;
    };
    void setB(float x){
      b = x;
    };
    float calculate(){
    return pow(a,b);
    };

    ~Power(){       //Деструктор
    };
};

//  Часть 2. Класс RGBA

class RGBA{
private:
    std::uint8_t m_red;
    std::uint8_t m_green;
    std::uint8_t m_blue;
    std::uint8_t m_alpha;

public:
    RGBA(){         //Конструктор по умолчанию
    m_red = 0;
    m_green = 0;
    m_blue = 0;
    m_alpha = 255;
    };

    RGBA(std::uint8_t red, std::uint8_t green, //конструктор с инициализацией по параметрам
    std::uint8_t blue,std::uint8_t alpha){
    m_red = red;
    m_green = green;
    m_blue = blue;
    m_alpha = alpha;
    };

    ~RGBA(){        //Деструктор
    };
    //методы получения значений из области private
    std::uint8_t getR(){
       return m_red;
    }
    std::uint8_t getB(){
       return m_blue;
    }
    std::uint8_t getG(){
       return m_green;
    }
    std::uint8_t getA(){
       return m_alpha;
    }
};

void printRGBA(RGBA f){                 //функция для печати значений класса RGBA
    int r = f.getR();
    int g = f.getG();
    int b = f.getB();
    int a = f.getA();
    cout << "Red color = " << r << ", blue color = " << b << ", green color = " << g << ", alpha = " << a << endl;
}

//Часть 3. Класс Stack

class Stack{
private:
    int arr[10];
    int lenth;

public:
    int flag = 0;
    void reset(){
        for (int i=0; i<10; i++){
            arr[i]=0;
        };
        lenth = 0;
    }
    void print(){
    cout << "( ";
    for (int i=0; i<lenth; i++){
        cout << arr[i] << " ";
        }
    cout << ")" << endl;
    }
    bool push(int a){
        if (lenth>10){
           return false;
        }
        arr[lenth] = a;
        lenth++;
        flag=1;
        return true;
    }
    int pop(){
    if(lenth == 1 && flag == 1){
         flag = 0;
         return arr[lenth--];
    } else if (lenth == 0 && flag == 0) {
          cout << "stack is empty" << endl;
          return 0;
    } else {
        return arr[lenth--];
        }
    };
};

int main()
{
    // Часть 1. Проверка в функции main
    cout << "*******************Path 1*************" << endl;
    Power power;
    power.setA(5);
    power.setB(2);
    float v = power.calculate();
    cout << v << endl;

    // Часть 2. Проверка в функции main
    cout << "*******************Path 2*************" << endl;
    RGBA j;
    printRGBA(j);
    RGBA s(30,7,8,25);
    printRGBA(s);

    //Часть 3. Проверка в функции main
    cout << "*******************Path 3*************" << endl;
    Stack stack;
    stack.reset();
    stack.print();

    stack.push(3);
    stack.push(7);
    stack.push(5);
    stack.print();

    stack.pop();
    stack.print();

    stack.pop();
    stack.pop();
    stack.print();

    return 0;
}
