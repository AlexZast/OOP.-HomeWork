#include <iostream>

using namespace std;

class Date{
protected:
    int m_day;
    int m_month;
    int m_year;
public:
    Date(int day, int month, int year): m_day(day), m_month(month), m_year(year) {    }
    Date() {}
    ~Date(){
    }
    // Конструктор копирования для Date
    Date(const Date& a) : Date(a.m_day, a.m_month, a.m_year) { }
    // Методы взаимодействия и установки значений. методы Get добавлять не стал.
    void setDay(int day){
        m_day = day;
    }
    void setMonth(int month){
        m_month = month;
    }
    void setYear(int year){
        m_year = year;
    }
    // перегрузка оператора для вывода в консоль
    friend ostream& operator<<(ostream& out, Date date){
        out << date.m_day << "/"<< date.m_month << "/" << date.m_year;
    return out;
    }
   // Перегрпузка оператора сравления для Date последовательно сравнение от года к месяцу до момента когда одно занчение не будет больше другого -> вызов return. если равны то любое
    friend bool operator> (Date d1, Date d2){
        if (d1.m_year > d2.m_year ) return true;
        else if (d1.m_year < d2.m_year)  return false;
        if (d1.m_month> d2.m_month ) return true;
        else if (d1.m_month < d2.m_month)  return false;
        if (d1.m_day > d2.m_day ) return false;
        else if (d1.m_day < d2.m_day)  return true;
        return false; //  если значения равны то можно вернуть любо
    }
};

// Создание примитивного умного указателя
template<typename T>
class SmartPointer{
private:
    T *ptr;
public:
    SmartPointer(T *pointer)
    {
        ptr = pointer;
     //   cout << "pointer costruct" << endl; // Для отслеживания работы с памятью
    }
    ~SmartPointer(){
        delete ptr;
       // cout << "pointec deconstruct. Memore free" << endl; // Для отслеживания работы с памятью
    }
    // Убираем возомжность копирования
    SmartPointer(const SmartPointer& a) = delete ;
    SmartPointer operator=(const SmartPointer& a) = delete;
    // добавляем конструктор перемещения
    SmartPointer(SmartPointer &&a) {
        ptr = a.ptr;
        a.ptr = nullptr;
    }
    SmartPointer& operator=(SmartPointer &a) {
        delete ptr;
        ptr = a.ptr;
        a.ptr = nullptr;
        return *this;
    }

    T& operator*() { return *ptr; }
    T* operator->() { return ptr; }

    // Перегрузим оператор boolean для определения пустой  указатель или нет
     operator bool (){
         return ptr != nullptr;
    }
};

// Сравнение дат и возврат объекта типа Date
Date comparison(Date a, Date b){
    if (a > b) return a;
    return b ;
}

// Перемещение ресурсов для Date
void exchange(Date &a, Date &b){
   Date temp = a;
   a = b;
   b = temp;
}

int main()
{
   // Задание №1
    SmartPointer<Date> today = new Date ();
    today->setDay(06);
    today->setMonth(10);
    today->setYear(2020);
   cout << *today << endl;
    SmartPointer<Date> date = new Date();
    date = today;
    if (date){
        cout << "date is not empety" << endl;
    } else cout << "date is empyty" << endl;

    if (today){
        cout << "today is not empety" << endl;
    } else cout << "today is empyty" << endl;
    // ... работает

    // Задание №2 Создайте функцию, которая принимает в качестве параметра два умных указателя типа
    // Date и сравнивает их между собой (сравнение происходит по датам).
    // Функция должна вернуть более позднюю дату

    SmartPointer<Date> date1 = new Date(15,12,2022);
    SmartPointer<Date> date2 = new Date(17,11,2019);
    SmartPointer<Date> datec = new Date();

    // Через конструктор класса и новый умный указателя и разыменовывания через *. Напрямую через умный указатель мозгов не хватает пока
    *datec = comparison(*date1, *date2);
    cout << *date1 <<  " "  << *date2 << " "<< *datec << endl;

    // Ч2. Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в функцию в качестве параметров.
    exchange(*date1, *date2);
    cout << *date1 << "  " << *date2 << endl;
    // Если второе задание не корректно огромная просьба дать развренутый комментарий, спасибо.

    // задания по BlackJack отдельной веткой

    return 0;
}
