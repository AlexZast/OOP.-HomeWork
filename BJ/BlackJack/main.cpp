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
    }
    friend ostream& operator<< (ostream &out, const Card& card);
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
                hand.clear();
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

class GenericPlayer : virtual public Hand{
protected:
    string m_Name;
public:
    GenericPlayer(string n): m_Name(n) { }
    virtual ~GenericPlayer() { }

    virtual bool IsHitting() const = 0;
    bool IsBoosted() {
        if (getValue() > 21) return true;
        return false;
    }
    void Bust(string n, bool s) const {
        if(s) cout << "Player "<< n << " BUST!" << endl;
    }
    friend ostream& operator<< (ostream &out, const GenericPlayer& player);
};

// Выполнение ДЗ по лекции №6
/* Задание №3 Реализовать класс Player, который наследует от класса GenericPlayer.
 * У этого класса будет 4 метода:
 * virtual bool IsHitting() const - реализация чисто виртуальной функции базового класса. Метод спрашивает у пользователя, нужна ли ему еще одна карта и возвращает ответ пользователя в виде true или false.
 * void Win() const - выводит на экран имя игрока и сообщение, что он выиграл.
 * void Lose() const - выводит на экран имя игрока и сообщение, что он проиграл.
 * void Push() const - выводит на экран имя игрока и сообщение, что он сыграл вничью*/

class Player : public GenericPlayer{
//protected:

public:
    Player(string s) : GenericPlayer(s){}
    virtual ~Player() {}


    virtual bool IsHitting() const {
        cout << m_Name << ", do you want a hit? (Y/N): ";
            char response;
            cin >> response;
            return (response == 'y' || response == 'Y');
        }
    void Win() const{
        cout << m_Name << ", YOU WIN!!!" << endl;
    }
    void Lose() const {
        cout << m_Name << ", sorry, but you lose." << endl;
    }
    void Push() const {
        cout << m_Name << "Ooooops it`s dead heat in this game! Try again "<< m_Name << "!" << endl;
    }

};

/* Задание №4
 * Реализовать класс House, который представляет дилера.
 * Этот класс наследует от класса GenericPlayer. У него есть 2 метода:
 * virtual bool IsHitting() const - метод указывает, нужна ли дилеру еще одна карта. Если у дилера не больше 16 очков, то он берет еще одну карту.
 * void FlipFirstCard() - метод переворачивает первую карту дилера.*/

class House : public GenericPlayer{
protected:
public:
    virtual bool IsHitting() const {
        return (this->getValue() <= 16);     // Если меньше 16 то вернуть true, иначе false

    }
    void FlipFirstCard(){
       if (!hand[0]->getStatus()){      // Если карта не перевернута, то перевернуть
           hand[0]->Flip();
       }
    }
};


/* Задание №5 Написать перегрузку оператора вывода для класса Card.
 * Если карта перевернута рубашкой вверх (мы ее не видим), вывести ХХ, если мы ее видим, вывести масть и номинал карты.
 * Также для класса GenericPlayer написать перегрузку оператора вывода,
 * который должен отображать имя игрока и его карты, а также общую сумму очков его карт.
*/

ostream& operator<< (ostream &out, const Card& card){
    if (card.getStatus() == true){
    out << PrintValue[card.value];
    out << static_cast<char>(card.suit) << " |";
    } else cout << " XX |";
    return out;
}

ostream& operator<< (ostream &out, const GenericPlayer& player){
    out << player.m_Name << endl;
    out << "You`s card: ";
    int ed = player.hand.size();
    for(int i = 0 ; i < ed;  ++i){
        out << *player.hand[i];
    }
    out << endl;
    out << "You`s total score: " << player.getValue();
    out << endl;
    return out;
}


int main()
{
    // Проверка работы в main
    Card card(hearts, A);
    cout << card;
    Card card2(static_cast<Suit>(5), static_cast<Value>(14));
    cout << card2;
    card2.Flip();
    cout << card2;
    cout << endl;
    Hand hand1;
    hand1.addCard(card2);
    hand1.addCard(card);
    //hand1.clearHand();
    cout << hand1.getValue() << endl;
    Player pl("Alex");
    pl.addCard(card2); pl.addCard(card);
    cout << pl;

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
