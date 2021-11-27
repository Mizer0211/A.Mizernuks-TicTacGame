#include <iostream>
#include<list>
#include <cstdlib>
#include<string>
#include <ctime>

using namespace std;
 
typedef struct{
    int *row;
}WinList;
 
 
class Player {
private:
    string name;
    int score;
public:
    Player() :Player {""}{}
    Player(string n) :score{0}, name{n}{}
 
    void won(){
        score++;
    }
    int getScore(){ return this->score;}
 
    string getName(){ return this->name;}
};
 
class Spele {
private:
    char board[9];
    int emptyIndex[9];
    int gameOn, againstComputer;
    int emptyCount;
    WinList winlist[8];
 
    void displayBoard(){
        cout <<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[0] <<" | "<<board[1]<<" | "<<board[2]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[3] <<" | "<<board[4]<<" | "<<board[5]<<endl;
        cout << "   |   |   "<<endl;
        cout << "-----------"<<endl;
        cout << "   |   |   "<<endl;
        cout << " "<< board[6] <<" | "<<board[7]<<" | "<<board[8]<<endl;
        cout << "   |   |   "<<endl;
        cout <<endl;
    }
 
    void computerInput(){
        int pos;
        pos = rand()%10;
        if(emptyIndex[pos] == 1){
            if(emptyCount < 0)
                return;
            computerInput();
        } else {
            cout<< "Darota izvēle : " << pos+1 << endl;
            emptyIndex[pos] =1;
            emptyCount-=1;
            board[pos] = 'O';
        }
 
    }
 
    void playerInput(Player &player){
        int pos;
        cout << endl;
        cout << "\t" << player.getName() <<" Kārta: ";
        cout <<"\t Izvēleties pozīciju " << endl;
        cin >> pos;
        pos -=1;
        if(emptyIndex[pos] == 1){
            cout << "-----Pozīcija ir iazņemta-------"<< endl;
            playerInput(player);
        } else {
            emptyIndex[pos] =1;
            emptyCount-=1;
            player.getName().compare("Spēlētājs I") == 0 ? board[pos] ='X': board[pos] ='O';
        }
 
    }
 
    void checkWin(Player &p1,Player &p2){
        int i,j,k;
        bool flag = false;
        char first_symbol;
        for(i=0; i<8; i++){
            first_symbol = board[winlist[i].row[0]];
 
            if((first_symbol != 'X') && (first_symbol != 'O')){
                flag = false;
                continue;
            }
            flag = true;
            for(j=0;j<3;j++){
                if(first_symbol != board[winlist[i].row[j]]){
                    flag = false;
                    break;
                }
            }
            if(flag){
                gameOn = 0;
                if(first_symbol == 'X'){
                    cout << "---------------------------"<< endl;
                    cout << "  Spēlētājs 1 uzvarēja ! 🎉 🎉 🎉"<< endl;
                    cout << "---------------------------"<< endl;
                    p1.won();
                } else {
                    p2.won();
                    if(againstComputer){
                        cout << "-----------------------------"<< endl;
                        cout << "    Dators uzvarēja ! 🎉 🎉 🎉"<< endl;
                        cout << "-----------------------------"<< endl;
                    } else {
                        cout << "-----------------------------"<< endl;
                        cout << "\t Spēlētājs 2 uzvarēja ! 🎉 🎉 🎉"<< endl;
                        cout << "-----------------------------"<< endl;
 
                    }
                }
                displayScore(p1,p2);
                break;
            }
        }
    }
 
        void play(Player &p1,Player &p2){
            char rematch ='\0';
            int hand = 0;
            gameOn =1;
            displayBoard();
            while((emptyCount > 0) && (gameOn != 0)){
 
                if(againstComputer)
                    hand == 1 ? computerInput(): playerInput(p2);
                else
                    hand == 1 ? playerInput(p1): playerInput(p2);
                hand= !hand;
                displayBoard();
                checkWin(p1,p2);
            }
            if (emptyCount <=0){
                cout << "      -----------------------"<< endl;
                cout << "\t    Nav uzvarētāja"<< endl;
                cout << "      -----------------------"<< endl;
            }
            cout<< endl;
            cout << "Grībi atspēlēties ? J/N: ";
            cin >> rematch;
            if((rematch == 'J')||(rematch == 'j')){
                init();
                play(p1,p2);
            }
 
        }
    void displayScore(Player &p1, Player &p2){
        cout << endl;
        cout << "\t Punktu skaits: \t";
        if(againstComputer)
            cout<<" Spēlētājs I: " <<p1.getScore()<<" \t Dators: "<<p2.getScore()<< endl;
        else
            cout<<" Spēlētājs I: " <<p1.getScore()<<" \t Spēlētājs II: "<<p2.getScore()<< endl;
    }
 
public:
    Spele(): emptyCount{0}, gameOn{1}, againstComputer{0}{
        init();
        winlist[0].row = new int[3]{0,1,2};
        winlist[1].row = new int[3]{3,4,5};
        winlist[2].row = new int[3]{6,7,8};
        winlist[3].row = new int[3]{0,3,6};
        winlist[4].row = new int[3]{1,4,7};
        winlist[5].row = new int[3]{2,5,8};
        winlist[6].row = new int[3]{0,4,8};
        winlist[7].row = new int[3]{2,4,6};
    }
 
    void init(){
        gameOn = 1;
 
        emptyCount =0;
        srand(time(0));
        for(size_t i=0; i<10; i++){
            emptyIndex[i] = 0;
            board[i] = (i+1) +'0';
            emptyCount++;
        }
        emptyCount--;
    }
 
    void onePlayerGame(){
        Player p("Spēlētājs I");
        Player c("Dators");
        cout << "       -----------------------"<< endl;
        cout << "\t Spēlētājs I: X \t Dators: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 1;
        play(c,p);
 
    }
 
    void twoPlayerGame(){
        Player p("Spēlētājs I");
        Player c("Spēlētājs II");
        cout << "       -----------------------"<< endl;
        cout << "\t Spēlētājs I: X \t Spēlētājs II: O"<< endl;
        cout << "       -----------------------"<< endl;
        cout << endl;
        againstComputer = 0;
        play(c,p);
    }
};
 
int main()
{
    int ch;
 
    while(1){
        cout << "      ----------Izvēlne----------" << endl;
        cout << "\t 1. 1 Spēlētāju spēle" <<endl;
        cout << "\t 2. 2 Spēlētāju spēle" <<endl;
        cout << "\t 3. Iziet " <<endl;
        cout <<"      ------------------------" << endl;
        cout << endl;
        cout <<"\t Izvēlieties opciju :" << endl;
        cin >> ch;
        switch(ch){
        case 1:{
            Spele *game = new Spele;
            game->init();
            game->onePlayerGame();
            }
            break;
        case 2:{
            Spele *game = new Spele;
            game->init();
            game->twoPlayerGame();
            }
            break;
        case 3:
            return 0;
        default:
            cout << "Kaut kas nogāja nepareizi🙁, mēģiniet vēlreiz.";
        }
 
    }
    return 0;
}