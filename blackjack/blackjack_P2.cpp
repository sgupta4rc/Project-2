#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include<ctime>
#include <fstream>
#include <vector>

using namespace std;

void gameintro(vector<string>& log, int& balance, string& playername) {
    string str;

    cout << "This is Suhaani's blackjack game. You play against the dealer" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "What is your name?" << endl;
    getline(cin, playername);
    cout << endl;
    cout << "Welcome " << playername << " to Suhaani's Blackjack game" << endl;
    cout << "How many chips do you want to buy? (Each is worth one dollar)" << endl << endl;
    cin >> balance;
    cout << playername << " is playing Suhaani's blackjack with " << to_string(balance) << " dollars" << endl;
    cout << "-------------------------------------------------------------------" << endl << endl;
    str = playername + " is playing with " + to_string(balance) + " Dollars";
    cout << "New game session of blackjack started by dealer "<<endl;
    cout << "---------------------------------------------------------------------" <<endl;
    log.push_back(str);//pushing log to log vector
}

void gamebegin(vector <string>& log, int& playersum, int& dealersum, string& playercards,string& dealercards) {

    int firstcard;
    int secondcard;
    int dealercard;
    string str;
   
   
    srand(time(NULL));
    str = "Dealer serving your first two cards. Here it goes... \n";
    cout << str;   
    log.push_back(str);
    
    firstcard = 1 + (rand() % 13);//generating different values using rand ranging from 1 to 13
    if (firstcard >= 11 && firstcard <= 13) //it is face card. Assume it 10
        firstcard = 10;

    secondcard = 1 + (rand() % 13);//generating different values using rand ranging from 1 to 13
    if (secondcard >= 11 && secondcard <= 13) //second card is face card. Assume it 10
        secondcard = 10;

    if (firstcard == 1) { //if ace card
        firstcard = 11; //assume 11
        cout << "your first card is 1. Hence it is treated as 11" << endl;
        // bjfile<<"your first card is 1. hence it is treated as 11"<<endl;//writing log to file
    }

    if (firstcard != 11 && secondcard == 1) { //if first not Ace, then assume second 11
        cout << "Your second card is 1. Hence it is treated as 11" << endl;
        log.push_back("Your second card is 1. Hence it is treated as 11 \n");   
        secondcard = 11;
    }

    playersum += firstcard;
    playersum += secondcard;
    playercards = to_string(firstcard) + ", " + to_string(secondcard);

    cout << "Your cards : " << playercards << endl << "Total= " << playersum << endl << endl;
    str= "Your cards : " + playercards + "\n Total= " + to_string(playersum) + "\n \n";
    log.push_back(str);

    if (playersum == 21) {//it is blackjack for player 
        cout << "Wow! you hit a blackjack.." << endl;
        log.push_back("Wow! you hit a blackjack..\n");
    }

    //Now dealer will open his first card
    //.....................................................................
    cout << "Dealer's Turn..Dealer open her first card..." << endl<<endl;
    log.push_back("Dealer's Turn..Dealer open her first card...\n \n");

    dealercard = 1 + (rand() % 13);//generating different values using rand ranging from 1 to 13

    if (dealercard >= 11 && firstcard <= 13) {//dealer got face card,make it 10
        dealercard = 10;
    }
    if (dealercard == 1) {
        dealercard = 11;
        cout << "Dealer first card is 1, hence it is treated as 11" << endl;
        log.push_back("Dealer first card is 1, hence it is treated as 11\n");
    }
    cout << dealercard << endl;
    str = dealercards + "\n";
    log.push_back(str);
    dealersum += dealercard;
    dealercards = to_string(dealercard);
    cout << endl;
    cout << "Dealer Total is : " << dealersum << endl << endl;
    str = "Dealer Total is : " + dealersum + '\n';
    log.push_back(str);

    //................................................................................
    cout << "------------------------------------------------------" << endl;
}

bool playermove(vector<string>& log, int& playersum, string& playercards, int balance[][2], bool& playerBust, int const BET, int const session) {
    
    char response;
    int newcard;
    string str;
    cout << "Your turn now............"<<endl;
    cout << "do you want stand or hit? (h for hit / s for stand) " << endl;
    log.push_back("do you want stand or hit? (h for hit / s for stand) \n");
    cin >> response;

    if (response == 'h' || response == 'H') { //player wants to takeout another card
        newcard = 1 + (rand() % 13);//generating different values using rand ranging from 0to13
        if (newcard >= 11 && newcard <= 13)//face card. So make it 10
            newcard = 10;

        if (newcard == 1 && (playersum + 11) <= 21)//assume new card 11 if sum is less than 21, otherwise be it 1
            newcard = 11;
        playersum += newcard;
        playercards = playercards + ", " + to_string(newcard);

        cout << "Your cards : " << playercards << " total = " << playersum << endl<<endl;
        str = "Your cards : " + playercards + " total = " + to_string(playersum)+ " \n \n";
        log.push_back(str);


        if (playersum == 21) { //blackjack for player
            cout << "Wow! you hit a blackjack.." << endl;
            log.push_back("Wow! you hit a blackjack..\n");
            return false;//stop game inner innerloop
        }

        if (playersum > 21) { //player is busted and dealer wins
            playerBust = true;
            return false; //stop game inner loop

        }
    }//end of response if

    else { //player choses to stand. No more cards
        cout << "You chose to stand..., Now dealer will take the turn" << endl << endl;
        log.push_back("You chose to stand..., Now dealer will take the turn \n \n");
        return false;//stop inner loop
    }

} //end of player move function

void dealermove(vector<string>& log, int& dealersum, string& dealercards, int balance[][2], bool& dealerBust, int const BET, int const session) {

    int dealercard;
    bool dealerflag = true;
    string str;
    cout << "Now dealer is opening her second card..." << endl<<endl;
    log.push_back("Now dealer is opening her second card...\n \n");

    do {
        dealercard = 1 + (rand() % 13);//generating different values using rand ranging from 0to13

       if (dealercard >= 11 && dealercard <= 13) //dealer got face card. make it 10
            dealercard = 10;

       if (dealercard == 1 && ((dealersum + 11) <= 21)) //dealer will treat 1 as 11 only when is less than 21
            dealercard = 11;

        dealersum += dealercard;
        dealercards = dealercards + ", " + to_string(dealercard);
        cout << "Dealer cards are " << dealercards << endl;
        cout << "Dealer total is : " << dealersum << endl;
        str = "Dealer cards are " + dealercards+"\n \n";
        log.push_back(str);
        str = "Dealer total is : " + dealersum + '\n';
        log.push_back(str);

        if (dealersum > 21){ 
            dealerflag = false;
            dealerBust = true;
        }

        else if ((dealersum >= 17) && (dealersum <= 21)) { //dealer has to stand                             
            cout << "(Dealer total is 17 or more. Hence dealer will have to stand)" << endl << endl;
            log.push_back("Dealer total is 17 or more. Hence dealer will have to stand \n \n");
            dealerflag = false;

            if (dealersum == 21)
            cout << "Dealer got blackjack!!" << endl;      
        }

        else {
            cout << "(Dealer total is 16 or less. Hence dealer will have to hit)" << endl;  //must for dealer to take out new card
            log.push_back("Dealer total is 16 or less. Hence dealer will have to hit \n \n");
        }

    } while (dealerflag);

}

void gameresult(vector<string>& log, int playersum, int dealersum,int balance[][2],int session, int BET, bool playerBust,bool dealerBust) {
    string str;
    if (dealerBust) {
        cout << "dealer busted out, you WON!" << endl;
        log.push_back("dealer busted out, you WON! \n");
        balance[0][0] += BET;
        balance[0][1] -= BET;

        cout << "Dealer lost her " << BET << " dollar bet to you" << endl;
        str = "Dealer lost her " + to_string(BET) + " dollar bet to you \n";
        log.push_back(str);
        cout << "Your new balance is : $" << balance[0][0] << endl;
        str = "Your new balance is : $" + to_string(balance[0][0])+ '\n';
        log.push_back(str);
    }

    else if (playerBust) {
        cout << "Player busted out, Dealer WON!" << endl;
        log.push_back("Player busted out, Dealer WON! \n");
        balance[0][0] -= BET;
        balance[0][1] += BET;

        cout << "Player lost her " << BET << " dollar bet to dealer" << endl;
        str = "Dealer Won " + to_string(BET) + " dollar bet from you \n";
        log.push_back(str);
        cout << "Your new balance is : $" << balance[0][0] << endl;
        str = "Your new balance is : $" + to_string(balance[0][0]) + '\n';
        log.push_back(str);

    }

    else if (dealersum > playersum) {
        cout << "Dealer Won!. Your " << BET << " $ bet went to the dealer" << endl;
        str = "Dealer Won!. Your " + to_string(BET) + " $ bet went to the dealer \n";
        log.push_back(str);
        balance[0][0] -= BET;
        balance[0][1] += BET;
        cout << "Your new balance is : $" << balance[0][0] << endl;
        str = "Your new balance is : $" + to_string(balance[0][0]) + '\n';
        log.push_back(str);
    }
    else if (playersum > dealersum) {
        cout << "You Won" << endl;
        cout << "Dealer paid you $" << BET << endl;
        //  bjfile<<"You Won"<<endl;//writing log to file
        //  bjfile<<"Dealer paid you $"<<BET<<endl;//writing log to file
        balance[0][0] += BET;
        balance[0][1] -= BET;
        cout << "Your new balance is : $" << balance[0][0] << endl;
        // bjfile<<"Your new balance is : $"<<balance<<endl;//writing log to file

    }
    else if (playersum == 21 && dealersum == 21)
    {
        cout << "Both dealer and you got blackjacks. Hence it is draw. Your bet is returned" << endl;
    }
    else {
        cout << "Your total is equal to that of dealer's. Game draws. You get your bet back" << endl << endl;
        // bjfile<<"Your total is equal to that of builder's. Game draws. You get your bet back"<<endl<<endl;//writing log to file

    }
}

bool newgame(int pbalance) {
    char response;
    std::cout << "--------------------------------------" << endl;
    std::cout << "Do you want to continue playing? yes(y)/No(n)" << endl;
    std::cin >> response;
    if (response == 'n' || response == 'N') {
        cout << "Thanks for playing Suhaani's blackjack" << endl;
        cout << "Your current balance is " << pbalance << " dollars" << endl;
        cout << "Return counters and take your money back" << endl;
        cout << "--------------------------------------------";
        return false;
    }
    else if (response == 'y' || response == 'Y')
        if (pbalance == 0) {
            cout << "Your balance is zero. Hnece you cannot play more. Buy more counters" << endl;
            return false;
        }
        else
            return true;

    else {
        cout << "Wrong key is selected. Terminating game session" << endl;
            return false;

    }

}



int main() {
    //variables definition
    int const ROWMAX = 100; //assume player will play maximum 100 sessions in the play

    bool gameloop = true;
    bool dealerflag = true;
    bool playerBust = false;
    bool gamemasterloop = true;
    bool dealerBust = false;
    bool playmore = true;

    int playersum = 0;
    int dealersum = 0;
    int BET = 1;
    int session = 1;

    string playercards;
    string dealercards;
    string playername;

    vector <string> log;
    int balance[ROWMAX][2] = { {} }; //array to save current balance points. 

    gameintro(log, balance[0][0], playername);
   
    
    while (gamemasterloop) {
        gamebegin(log, playersum, dealersum, playercards, dealercards);

        while (gameloop) { //execute player has no blackjack. loop for player to takeout more cards untill stand, burst or blackjack
            gameloop=playermove(log, playersum, playercards, balance, playerBust, BET, session);
            }
        if (!playerBust) {
            dealermove(log, dealersum, dealercards, balance, dealerBust, BET, session);
        }
        gameresult(log, playersum, dealersum, balance, session, BET, playerBust,dealerBust);

        playmore=newgame(balance[0][0]);
        
        if (playmore){
            playersum = 0;
            dealersum = 0;
            dealerflag = true;
            gameloop = true;
            playerBust = false;
            dealerBust = false;
            session++;
        }
        else {
            gamemasterloop = false;
        }
    }
    return 0;
}
