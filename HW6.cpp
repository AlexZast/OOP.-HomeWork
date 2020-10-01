#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


// Задание №2 вариант 1 - создание манипулятора
ostream &endll(ostream &stream)
{
  cout << "\n" << endl;
  return stream;
}

// Задание №2 вариант 2 - кривой через перегрузку оператора :)
class Endll{
public:
    friend ostream& operator<< (ostream &out, const Endll &a);
};
ostream& operator<< (ostream &out, Endll &){
    out << "\n" << endl;
    return out;
}
Endll endlll;

// Задания №3 - №5 по BlackJack как всегда в отельной ветке

int main()
{
// Задание №1
    int out;
    cin.fail();
    bool flag;

    do {
        cout << "Enter integer number: ";
        cin >> out;                         // Запрос и ввод значения
        if (cin.fail()){                    // Если ошибка записи (char в int вызывает такую ошибку, то ...
            flag = 1;                       // Флаг исполнения в true - уходим на повторный цикл
            cin.clear();                    // Чистим состояние в cin
            cin.ignore(37500, '\n');        // убираем все символы в данном потоке
            continue;
        }
       flag = 0;                            // Если ошибки не было, то ставим влаг выхода из цикла while
    } while(flag);
    cout << "You enter:" << out << endl;

// Задание №2

    cout << "1" << endll << "2" << endl;
    cout << "3" << endlll << "4" << endl;

    return 0;
}
