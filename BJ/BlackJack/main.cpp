#include <iostream>
#include <string>
#include <vector>

using namespace std;



/*
Игра БлэкДжек
*/

enum Suit {clubs = 5, diamonds = 4, hearts =6, spades=3};
enum Value  {two = 2, three, four, fife, six, seven, eight, nine, ten , J, Q, K, A};
string PrintValue[15] = {"", "", " 2", " 3", " 4", " 5", " 6", " 7", "8", "9", "10", "J", "Q", " K", " A"};

class Card{
protected:
   Suit suit;
   Value value; // if value = 11 / J, 12 / Q, 13 / K, 14 /A
   bool status = false;

public:
   Card(Suit s, Value v) : suit(s), value(v){}
   ~Card(){}

   Value getValue() const{
       //подсчет суммы карт в руке
       return value;
   }
   bool getStatus() {
       return status;
   }

   void Flip(){
       status? status = false : status = true;
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
    vector<Card> hand;
public:
    void addCard(Card &card){                       // Переворачиваем карту для руки если она была скрыта
        if (card.getStatus() != true) card.Flip();
        hand.push_back(card);
    }

    void clearHand(){                    // Странно что данная команда обнуляет только длинну и оставляет данные (если выйти за пределы вектора, доступ к данным сохранится)
        hand.clear();
    }

    void drawHand() const{               // Прорисовка руки
        int size = hand.size();
        for (int i = 0; i < size; i++){
            hand[i].drawCard();
        }
    }
    int getValue() const{
        int value = 0;
        int aceCounter = 0;
        int size = hand.size();
        for (int i=0; i < size; i++){
            if (hand[i].getValue() < 11){
                value += hand[i].getValue();
            } else if (hand[i].getValue() < 14 && hand[i].getValue()>10) {
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


int main()
{
    //Desk desk;
    //desk.makeDeck();
    //desk.printDeck();

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
