#include <iostream>
#include <string>
#include <vector>

using namespace std;



/*
Игра БлэкДжек
*/

enum Suit {clubs = 5, diamonds = 4, hearts =6, spades=3};
enum Value  {cls = 0, two = 2, three, four, fife, six, seven, eight, nine, ten , J, Q, K, A}; // если тут испльзовать enum class то мы получим запрет неявного приведения типа и придется переоформлять все методы

static string PrintValue[15] = {"", "", " 2", " 3", " 4", " 5", " 6", " 7", "8", "9", "10", "J", "Q", " K", " A"}; // данное поле нельзя статично реализовать в class Card выводит ошибку error: non-const static data member must be initialized out of line. А если реализовывать не статично то для каждой карты будут создаваться клоны данных данных

class Card{
protected:
   Suit suit;
   Value value; // if value = 11 / J, 12 / Q, 13 / K, 14 /A
   bool status = false;


public:
   Card(Suit s, Value v) : suit(s), value(v){}
   ~Card(){}

   Value getValue() const{
       // Передача карты в фукнцию подсчета в случае если карта открыта - 81-строка getValue, иначе, если закрыта передать 0
       Value  a = cls ;
       if (status) return value;
       return a;
   }
   bool getStatus() const {
       return status;
   }

   void Flip(){
       status = !(status);
   }

    void drawCard() const{
        if (status == true){
        cout << PrintValue[value];
        cout << static_cast<char>(suit) << " |";
        } else cout << " XX |";
    }
};


class Hand{
protected:
    vector<Card*> hand;
public:

    Hand() { }
    virtual ~Hand() { }

    void addCard(Card &card){                       // Переворачиваем карту для руки если она была скрыта
        if (card.getStatus() != true) card.Flip();
        hand.push_back(&card);
    }

    void clearHand(){
        vector<Card*>::iterator iter = hand.begin();
            for (iter = hand.begin(); iter != hand.end(); ++iter)
            {
                delete *iter;
                *iter = 0;
        }
    }

    void drawHand() const {               // Прорисовка руки
        int size = hand.size();
        for (int i = 0; i < size; i++){
            hand[i]->drawCard();
        }
    }

    int getValue() const {
        int value = 0;
        int aceCounter = 0;
        int size = hand.size();
        for (int i=0; i < size; i++){
            if (hand[i]->getValue() < 11){
                value += hand[i]->getValue();
            } else if (hand[i]->getValue() < 14 && hand[i]->getValue()>10) {
                value += 10;
            } else {
                aceCounter++;
                value += 11;
            }
        }
        while (aceCounter>0 && value > 21){     // Если сумма очков больше чем надо и в руке есть тузы, каждый туз считать как 1 до тех пор, пока сумма не станет "удобной"
            value -= 10;
            aceCounter--;
        }
        return value;
    }

};


/* ВЫполнени ДЗ по BJ к лекции №5
 * Согласно иерархии классов, которая представлена в методичке к уроку 3, от класса Hand наследует класс GenericPlayer,
 * который обобщенно представляет игрока, ведь у нас будет два типа игроков - человек и компьютер.
 * Создать класс GenericPlayer, в который добавить поле name - имя игрока. Также добавить 3 метода:
 * IsHitting() - чисто виртуальная функция, возвращает информацию, нужна ли игроку еще одна карта.
 * IsBoosted() - возвращает bool значение, есть ли у игрока перебор
 * Bust() - выводит на экран имя игрока и объявляет, что у него перебор.
 */

class GenericPlayer : virtual Hand{
protected:
    string name;
public:
    GenericPlayer(string n): name(n) { }
    virtual ~GenericPlayer() { }

    virtual bool IsHitting(/*условие для функции(граничные условия для компьютера)*/) {
        if (/*граничное условие getValue < 15 -> true иначе false*/ int i = 0 == 0) return true;
        return false;
    }
    bool IsBoosted() {
        if (getValue() > 21) return true;
        return false;
    }
    void Bust(string n, bool s) const {
        if(s) cout << "Player "<< n << " BUST!" << endl;
    }
};

int main()
{
    // Проверка работы в main
    Card card(hearts, A);
    card.drawCard();
    Card card2(static_cast<Suit>(5), static_cast<Value>(14));
    card2.Flip();
    card2.drawCard();
    cout << endl;
    Hand hand1;
    hand1.addCard(card2);
    hand1.addCard(card);
    //hand1.clearHand();
    cout << hand1.getValue() << endl;
    hand1.drawHand();



    cout << "\t\tWelcome to Blackjack!\n\n";

    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }

    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << endl;

//    // игровой цикл - закоммитил т.к. нет пока класса Game
//    Game aGame(names);
//    char again = 'y';
//    while (again != 'n' && again != 'N')
//    {
//        aGame.Play();
//        cout << "\nDo you want to play again? (Y/N): ";
//        cin >> again;
//    }

    return 0;
}
