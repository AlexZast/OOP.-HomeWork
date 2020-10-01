/*
 * HW4.ccp
 * OOP. HomeWork 4.
 * Отношения между объектами в С++
 * Created by Zastupnevich Aleksey
 * Qt Creator 4.13.0 (Qt 5.15.0)
 * 2020-09-21
 */

#include <iostream>
#include <cassert>
#include <vector>


using namespace std;

class ArrayInt{
private:
    int m_length;
    int *m_data;
public:
    // Конструкторы и деструкторы класса
    ArrayInt() : m_length(0), m_data(nullptr){}
    ArrayInt (int length) : m_length(length){
        assert(length >= 0);
        if(length > 0) m_data = new int[length];
        else m_data = nullptr;
    }
    ~ArrayInt(){
        delete [] m_data;
    }

    // Методы
    // Очистка массива:
    void erase(){
        delete [] m_data;
        m_data = nullptr;
        m_length = 0;
    }
    // Получение длины
    int getLength() const{
        return m_length;
    }
    // Перегрузка оператора индексации
    int& operator[] (int index){
        assert(index>=0 && index < m_length);
        return m_data[index];
    }
    // Изменение длинны
    void resize(int newLength){
        if (newLength == m_length) return;
        if (newLength <=0) {
            erase();
            return;
        }
        int *data = new int[newLength];
        if (m_length > 0){
            int elementsToCopy = newLength > m_length ? m_length : newLength;
            for (int i=0; i<elementsToCopy; i++){
                data[i] = m_data[i];
            }
        }
        delete [] m_data;
        m_data = data;
        m_length = newLength;
    }
    // Вставка элемента
    void insertBefore(int value, int index){
        assert(index >=0 && index <=m_length);
        int *data = new int[m_length+1];
        //УТОЧНЕИТЬ ПО БЕФО ++
        for (int before = 0; before < index; ++before){
            data[before] = m_data[before];
            }

        data[index] = value;

        for (int after = index; after < m_length; ++after){
            data[after] = m_data[after];
        }
        delete [] m_data;
        m_data = data;
        ++m_length;
    }

    void pushBack(int value){
        insertBefore(value, m_length);
    }
    // Удаление элемента - реализуем удаление элемента с индексом и потом реализуем pop через вызовы данной функции
    void popIndex(int index){
        assert(index>=0 && index <= m_length);
        if (m_length == 0) return; // нечего удалять

        int *data = new int[m_length];
        //перепишем элементы до, если индекс = 0 цикл не сработает и будет писать после игнорируя 1й элемент
        for (int i=0; i<index; i++){
            data[i] = m_data[i];
        }
        // Перепишем элементы после
        for (int i = index; i< m_length-1; i++){
            data[i] = m_data[i+1];
        }
        delete [] m_data;
        m_data = data;
        --m_length;
    }
    void popFront(){ // Данные функции можно было реализовать перезаписав массив с 1 по n элемент для Front и сделав resine m_length-1 для Back
        popIndex(0);
    }
    void popBack(){
        popIndex(m_length-1);
    }

    void sortArr(){ // сделам сортировку пузырьковым методом
        int indx = 0;
        int tmp = 0;
        for (int j = 0; j< m_length; j++){
            tmp = m_data[j];
            for (int i = j; i < m_length-1; i++){
                if (tmp > m_data[i+1]){ // Находим минимальное значение
                    tmp = m_data[i+1];
                    indx = i+1;         // и записываем его индекс
                }
                tmp = m_data[j];        // Осуществляем перестановку мин влево
                m_data[j] = m_data[indx];
                m_data[indx] = tmp;
            }
        }
    }

    void printElement(int index){
        assert(index < m_length);
        cout << m_data[index] << " |";
    }

    void printArr(){
        for (int i = 0; i < m_length; i++){
            printElement(i);
        }
        cout << endl;
    }
};

    /*
     * Задание №2. Дан вектор чисел, требуется выяснить, сколько среди них различных.
     * Постараться использовать максимально быстрый алгоритм
     * Сделаем перебор с созданием "маски" чисел которые были
     *
     */

int uniqueValue(vector<int> vctr){
    int s = vctr.size();        // количесвто элементов в векторе
    assert(s>0);
    vector<int> mask;           // маска проверки
    mask.push_back(vctr[0]);    // первое число вектора всегда будет уникальным, добавим в маску
    int j = 1;                  // кол-во чисел, одно уже есть
    for (int i = 1; i < s; i++){ // начнем с 1-го индекса, т.к. 0 уже есть в маске
        int flag = 1;       // установим флаг уникальности в 1
        for (int k=0; k < j;k++){   // сделаем проверку по маске
            if (mask[k] == vctr[i]){ // если есть совпадение то сбросим флаг в 0 и прервем проверку
                flag=0;
                break;
            }
        }
        if (flag == 1) {            // если флаг не сброшен, значение уникально и можно записать его в маску и увеличить счетчик на 1
            mask.push_back(vctr[i]);
            j++;
        }
    }
    return j;
}

    /*
     * Задание №3 с игрой BJ реализовано в отельной ветке и pull-request github.
     */

int main(){
    // Задание №1. Проверка контейнерного класса в мейне
    ArrayInt arr(5);
    cout << arr.getLength() << endl;
    for (int i = 0; i < 5; i++){    // заполнение
        arr[i] = 10-i;}
    arr.printArr();
    arr.popIndex(0);                // удаление элемента по индексу
    arr.printArr();
    arr.sortArr();                  // сортировка
    arr.printArr();


    // Задание №2. Проверка
    vector<int> check = {5, 54, 4, 4, 54, 8, 9, 8, 65};
    cout << "Unique value = " << uniqueValue(check) << endl;

    return 0;
}
