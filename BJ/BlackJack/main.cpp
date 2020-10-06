#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <iomanip>

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
   bool status = true;

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

   friend ostream& operator<< (ostream &out, const Card& card);
};

class Hand{
protected:
    vector<Card*> hand;
public:
    Hand() { }
    virtual ~Hand() { }

    void addCard(Card* card){                       // Переворачиваем карту для руки если она была скрыта
         hand.push_back(card);
    }

    void clearHand(){
        vector<Card*>::iterator iter = hand.begin();
            for (iter = hand.begin(); iter != hand.end(); ++iter)
            {
                delete *iter;
                *iter = 0;
             }
            hand.clear();
    }

    void drawHand() const {               // Прорисовка руки
        int size = hand.size();
        for (int i = 0; i < size; ++i){
           // if (i%13 == 0) cout << endl;
            cout << setw(2)<< *hand[i];
        }
    }
    Card* shovBack(){
        return hand.back();
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
    void Bust(bool s) const {
        if(s) cout << "Player "<< m_Name << " BUST!" << endl;
    }
    friend ostream& operator<< (ostream &out, const GenericPlayer& player);
};

class Player : public GenericPlayer{
//protected:

public:
    Player(string s) : GenericPlayer(s){}
    virtual ~Player() {}


    virtual bool IsHitting() const {
        cout << m_Name << ", do you want a hit? (Y/N): " << endl;
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

class House : public GenericPlayer{
protected:
public:
    House() :GenericPlayer("House"){}
    virtual ~House(){}
    virtual bool IsHitting() const {
        return (this->getValue() <= 16);     // Если меньше 16 то вернуть true, иначе false

    }
    void FlipFirstCard(){
         hand[0]->Flip();
    }
};

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

/* Лекция 7 - Задание №3 Создать класс Deck, который наследует от класса Hand и представляет собой колоду карт.
 * Класс Deck имеет 4 метода:
 * vold Populate() - Создает стандартную колоду из 52 карт, вызывается из конструктора.
 * void Shuffle() - Метод, который тасует карты, можно использовать функцию из алгоритмов STL random_shuffle
 * vold Deal (Hand& aHand) - метод, который раздает в руку одну карту
 * void AddltionalCards (GenericPlayer& aGenerlcPlayer) - раздает игроку дополнительные карты до тех пор, пока он может и хочет их получать*/

class Deck : virtual public Hand{
protected:
public:
    Deck(){}
    virtual ~Deck() {}

    void Populate(){
        for (int i = 0 ; i < 4; ++i){
            for (int j=0; j<13; ++j){
                addCard(new Card(static_cast<Suit>(i+3), static_cast<Value>(j+2)));
//                int n = j + i*13;
//                hand[n]->Flip();
//                cout<< setw(2) << *hand[n];
            }
           // cout << endl;
        }
    }
    void Shuffle() {
        srand(time(0));  // Для случайной рандомизации, иначе при повторной генерации положение карт всегда одно и то же
        random_shuffle(hand.begin(), hand.end());
    }
    void Deal(Hand& aHand){
        if(hand.size()>0){              // Тут можно поставить условие что если карт меньше 20 то следующая партия с новой колоды а не опускать карты до 0
            aHand.addCard(hand.back());
            hand.pop_back();
        } else cout << "Nothing to deal.";
    }
    void AdditionalCard(GenericPlayer& aGenericPlayer){
        if(aGenericPlayer.IsHitting()&& !aGenericPlayer.IsBoosted()){
            Deal(aGenericPlayer);
        }
    }
};

class Game {
private:
    Deck deck;
    House diller;
    vector<Player> players;
public:
    Game(vector<string> names) {
        int n = names.size();

        for (int i = 0; i < n ; ++i){
            //Player *a = new Player(names[i]);
            players.push_back(Player(names[i]));
        }

        deck.Populate();
        deck.Shuffle();
    }
    virtual ~Game(){}

    void Play(){
        /*Также класс имеет один метод play().
         * В этом методе раздаются каждому игроку по две стартовые карты,
         * а первая карта дилера прячется. Далее выводится на экран информация о картах каждого игра, в т.ч. и для дилера.
         * Затем раздаются игрокам дополнительные карты. Потом показывается первая карта дилера и дилер набирает карты, если ему надо.
         *  После этого выводится сообщение, кто победил, а кто проиграл. В конце руки всех игроков очищаются.*/

        //Раздача карт
        int n = players.size();
        for(int i=0; i<n; ++i){
            deck.Deal(players[i]);
            deck.Deal(players[i]);
        }
        deck.Deal(diller);
        deck.Deal(diller);
        diller.FlipFirstCard();

        cout << diller << endl;

          for(int i=0; i<n; ++i){
              cout << players[i];
          }

            // Ход игроков
            for(int i=0; i<n; ++i){
                while(!players[i].IsBoosted() && players[i].IsHitting()){
                    deck.Deal(players[i]);
                    cout << "You take: " << *players[i].shovBack() << endl;
                    cout << players[i];
                    if (!players[i].IsBoosted());
                    else players[i].Bust(players[i].IsBoosted());
                }
            }

            // Ход диллера
            diller.FlipFirstCard();
            while(diller.IsHitting()){
                deck.Deal(diller);
            }
            cout << diller << endl;
            // Игроки у которых больше очков чем у диллера или у которых нет перебора когда у диллира есть выигрывают
            for(int i=0; i<n; ++i){
                if((players[i].getValue()>diller.getValue() && !players[i].IsBoosted()) || (!players[i].IsBoosted() && diller.IsBoosted())){
                    players[i].Win();
            // Если нет перебора и очки одинаковые то ничья
                } else if (players[i].getValue()==diller.getValue() && !players[i].IsBoosted()){
                    players[i].Push();
                } else players[i].Lose();
            }
            // Очистка
            for(int i=0; i<n; ++i){
                players[i].clearHand();
            }
            diller.clearHand();
            //Пересоздание коллоды для новой игры
            deck.Populate();
            deck.Shuffle();
    }
};

int main()
{
    /* Задание №5
     * Написать функцию main() к игре Блекджек. В этой функции вводятся имена игроков.
     * Создается объект класса Game и запускается игровой процесс. Предусмотреть возможность повторной игры.*/

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

   Game aGame(names);
   char again = 'y';
   while (again != 'n' && again != 'N')
    {
       aGame.Play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }
    return 0;
}
