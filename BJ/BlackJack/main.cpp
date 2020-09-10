#include <iostream>

using namespace std;



/*
Игра БлэкДжек
*/

enum Suit {clubs, diamonds, hearts, spades};
enum Value  {two = 2, three, four, fife, six, seven, eight, nine, ten , J, Q, K, A};
class Card{
protected:
   Suit suit;
   Value value; // if value = 11 / J, 12 / Q, 13 / K, 14 /A
   bool status;

public:
   Card(Suit s, Value v) : suit(s), value(v){}
   Card(){
       suit = clubs;
       value = two;
   }
   ~Card(){}

   void setSuit(Suit s){
       suit = s;
   }
   void setValue(Value v){
       value = v;
   }

   string getSuit() const {
       string a="";
       switch (suit) {
       case clubs: a =  "C "; break;
       case diamonds: a = "D "; break;
       case hearts: a = "H "; break;
       case spades: a =  "S "; break;
       default: a = "?";
       }
        return a;
    }

   Value getValue() const{
       return value;
   }

   bool Flip(bool s){
       if (s) {return false;}
       return true;
   }
//   Хотел добавить прорисовку карты но статик_чар выводит знаки вопросов в консоль :(
//   void drawCard() const{
//        if (value <=10){
//            cout << value;}
//        else {
//            switch (value){
//            case J: cout << "J";break;
//            case Q: cout << "Q";break;
//            case K: cout << "K";break;
//            case A: cout << "A";break;
//            }
//        }
//        switch (suit) {
//        case clubs: cout << static_cast<char>(3) ;break;
//        case diamonds: cout << static_cast<char>(4) ; break;
//        case hearts: cout << static_cast<char>(5) ; break;
//        case spades: cout << static_cast<char>(6) ; break;
//        }
//        }
};

class Desk{
protected:
   Card arr[52];
public:
   Desk(){};
   ~Desk(){}

   void makeDeck(){
       int n = 0;
       for (int i=0; i< 4; i++){
           for(int j = 0; j<13; j++){
               n=j+i*13;
               switch (i) {
               case 0: arr[n].setSuit(clubs); break;
               case 1: arr[n].setSuit(diamonds); break;
               case 2: arr[n].setSuit(hearts); break;
               case 3: arr[n].setSuit(spades); break;
               };
               switch (j) {
               case 0: arr[n].setValue(two);break;
               case 1: arr[n].setValue(three);break;
               case 2: arr[n].setValue(four);break;
               case 3: arr[n].setValue(fife);break;
               case 4: arr[n].setValue(six);break;
               case 5: arr[n].setValue(seven);break;
               case 6: arr[n].setValue(eight);break;
               case 7: arr[n].setValue(nine);break;
               case 8: arr[n].setValue(ten);break;
               case 9: arr[n].setValue(J);break;
               case 10: arr[n].setValue(K);break;
               case 11: arr[n].setValue(Q);break;
               case 12: arr[n].setValue(A);break;
               };


            };
        }
   };

    void printDeck() const{
       for (int i = 0; i<52; i++){
          if (i%13 == 0) {cout << endl;}
           cout << arr[i].getSuit() << " " << arr[i].getValue() << " | ";
       }
    }

};

int main()
{
    Desk desk;
    desk.makeDeck();
    desk.printDeck();

    return 0;
}
