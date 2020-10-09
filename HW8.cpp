#include <iostream>
#include <typeinfo>

using namespace std;

/* Задание №1 Написать функцию div, которая должна вычислять результат деления двух целых чисел и запускать исключение
 * DivisionByZero, если делитель равен 0. В функции main ввести два целых числа и вывести их неполное частное,
 * если делитель не равен нулю, и сообщение об ошибке, если равен.
 */

/*  В связи с тем , что этот механизм не ловит аппаратные ошибки (деление на 0, переполнение и прочие радости)
 * и системные ошибки (чтение/запись по левому адресу, проблемы безопасности). необходимо в код добавить throw при условии деления на 0.*/

int divs(int a, int b){
    try
    {
        if (b==0) throw "Division by zerro";
        double c = a/b;
        return c;
    }
    catch( char const* str){
        cerr << str << endl;}
return 0; // если было поймано исключение вернем 0.
}

/*Задание №2 Написать класс Ex, хранящий вещественное число x и имеющий конструктор по вещественному числу, инициализирующий x значением параметра.
 * Написать класс Bar, хранящий вещественное число y (конструктор по умолчанию инициализирует его нулем)
 * и имеющий метод set с единственным вещественным параметром a. Если y + a > 100, возбуждается исключение типа Ex с данными ay,
 * иначе в y заносится значение a. В функции main завести переменную класса Bar и в цикле в блоке try вводить с клавиатуры целое n.
 * Использовать его в качестве параметра метода set до тех пор, пока не будет введено 0.
 * В обработчике исключения выводить сообщение об ошибке, содержащее данные объекта исключения.
 */

class Ex{
protected:
    float x;
public:
    Ex(float s_x){
        x = s_x;
    }
    float getX(){
        return x;
    }
};

class Bar{
protected:
    float y;
public:
    Bar(): y(0) { }
    void set(float a){
        if (a+y > 100) throw Ex(a+y);
        y = a;
    }

};

/* Задание №3 Написать класс «робот», моделирующий перемещения робота по сетке 10x10,
 * у которого есть метод, означающий задание переместиться на соседнюю позицию.
 * Эти методы должны запускать исключение OffTheField, если робот должен уйти с сетки, и IllegalCommand, если подана неверная команда
 * (направление не находится в нужном диапазоне).
 * Объект исключения должен содержать всю необходимую информацию — текущую позицию и направление движения.
 * Написать функцию main, пользующуюся этим классом и перехватывающую все исключения от его методов,
 * а также выводящую подробную информацию о всех возникающих ошибках.
 */

class Error{
private:
    int x,y;
    string messenge;
public:
    Error(int n, int p_x, int p_y): x(p_x), y(p_y){
        if (n == 1) messenge = "Off The Field ";
       else if (n == 2) messenge = "Illegal Command";
       else messenge = "Unnow Error";
    }
    string showMessenge(){
        return messenge;
    }
    void showPozition(){
        cout << "X pozition = " << x << " Y pozition = " << y << endl;
    }
};

class Robot{
protected:
    int poz_x, poz_y;

public:

    Robot(): poz_x(4), poz_y(4){};
    void robotMove(string s , int i){  // метод движения робота - перобразуем string s и int i в движение
        if(s == "up") {
            if (poz_y+i > 10) throw Error(1, poz_x, poz_y);
                poz_y += i; //Если есть движение двигаем вверх
        } else if (s == "down"){
            if (poz_y-i <1 ) throw Error(1, poz_x, poz_y);
                poz_y -= i; //Если не ошибка движемся вниз
        }else if(s == "left"){
            if (poz_x+i >1 ) throw Error(1, poz_x, poz_y);
                poz_x += i; //Если не ошибка движемся вправо
        }else if(s == "right"){
            if (poz_x-i <1 ) throw Error(1, poz_x, poz_y);
                poz_x -= i; //Если не ошибка движемся влево
        }else if(s== "stop") cout << "Stop Robot" << endl;
         else throw Error(2, poz_x, poz_y); // команда не распознана и выводим ошибку
    }
    void showPozition(){
        cout << "X pozition = " << poz_x << " Y pozition = " << poz_y << endl;
    }
};





int main()
{
    // Задание №1 проверка в main
    int c = divs(2, 0);
    cout << c << endl;

    // Задание №2 работа в main
    Bar b;
    int n =1;
    while(n!= 0){
        cout << "Enter the integer number or 0 to escape: ";
        cin >> n;
        try{
        b.set(n);
        }
        catch(Ex p){
            cerr << "Error a+y > 100 and = " << p.getX() << endl;

        }
    }
    // Задание №3 работа в main
    Robot a;
    a.showPozition(); // по умолчанию помещается примерно в цент поля на поз x4-y4.
    string s;
    int i;
    while(1){ //бесконечный цикл пока не напишем stop
        // запрашиваем направление и количесвто шагов, если что то введено не верно будет вызван throw с разными последствиями при вызове метода Robot.move
        cin.clear(); // на случай, если предыдущий ввод завершился с ошибкой
        cin.ignore(375000, '\n');
        cout << "Enter direction of move (up, down, left, right or stop): ";
        cin >> s;
        if (s=="stop") break;
        cout << "Enter number of step:";
        cin >> i;
        try{
            a.robotMove(s,i);
            a.showPozition();
        }
        catch(Error n){
           cout << n.showMessenge() << endl;
           n.showPozition();
        }
    }

    cout << "THE END" << endl;
    return 0;
}
