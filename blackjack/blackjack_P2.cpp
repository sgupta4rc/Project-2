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

    cout << "File to write log could not be open. So, no log of the session will be written" << endl;
    cout << "This is Suhaani's blackjack game. You play against the dealer" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "What is your name?" << endl;
    getline(cin, playername);
    cout << "Welcome " << playername << " to Suhaani's Blackjack game" << endl;
    cout << "How many chips do you want to buy? (Each is worth one dollar)" << endl << endl;
    cin >> balance;
    cout << playername << " is playing Suhaani's blackjack with " << to_string(balance) << " dollars" << endl;
    cout << "-------------------------------------------------------------------" << endl << endl;
    str = playername + " is playing with " + to_string(balance) + " Dollars";
    cout << "new Session for play started by started by " << playername << endl;
    log.push_back(str);//pushing log to log vector
}

void gamebegin(vector <string>& log, int& playersum, int& dealersum, string& playercards,string& dealercards) {

    int firstcard;
    int secondcard;
    int dealercard;
    string str;
    string cards;
   

    srand(time(NULL));
    cout << "Dealer serving your first two cards. Here it goes... " << endl << endl;
    str = "Dealer serving your first two cards. Here it goes... \n \n";
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
    cards = to_string(firstcard) + ", " + to_string(secondcard);

    cout << "Your cards : " << cards << endl << "Total= " << playersum << endl << endl;
    str= "Your cards : " + cards + "\n Total= " + to_string(playersum) + "\n \n";
    log.push_back(str);

    if (playersum == 21) {//it is blackjack for player 
        cout << "Wow! you hit a blackjack.." << endl;
        log.push_back("Wow! you hit a blackjack..\n");
    }

    //Now dealer will open his first card
    //.....................................................................
    cout << "Dealer's Turn..Dealer open her first card..." << endl;
    log.push_back("Dealer's Turn..Dealer open her first card...\n");

    dealercard = 1 + (rand() % 13);//generating different values using rand ranging from 1 to 13

    if (dealercard >= 11 && firstcard <= 13) {//dealer got face card,make it 10
        dealercard = 10;
    }
    if (dealercard == 1) {
        dealercard = 11;
        cout << "Dealer first card is 1, hence it is treated as 11" << endl << endl;
        log.push_back("Dealer first card is 1, hence it is treated as 11\n");
    }
    cout << dealercard << endl;
    str = dealercards + "\n";
    log.push_back(str);
    dealersum += dealercard;
    dealercards = to_string(dealercard);

    cout << "Dealer Total is : " << dealersum << endl << endl;
    str = "Dealer Total is : " + dealersum + '\n \n';

    //................................................................................
    cout << "------------------------------------------------------" << endl;
    cout << "Your turn now.....";
}


int main() {
    //variables definition
    bool gameloop = true;
    bool gameinnerloop = true;
    bool dealerflag = true;
    bool playerBust = false;
    bool gamemasterloop = true;
    bool dealerBust = false;
    char response;
    
    int newcard;
    int playersum = 0;
    int dealersum = 0;
    int BET = 1;
    int dealercard;
 
    string playercards;
    string dealercards;
    string playername;
    ofstream bjfile;

    int const ROWMAX = 100; //assume player will play maximum 100 sessions in the play

    vector <string> log;
    int balance[ROWMAX][2] = { {} }; //array to save current balance points. 
    int session = 1;
    //open a txt file to write the session log as it is important to write log in casino

    gameintro(log, balance[session][0], playername);
    gamebegin(log, playersum, dealersum, playercards, dealercards);
    
    while (gamemasterloop) {
        while (gameinnerloop) { //execute player has no blackjack. loop for player to takeout more cards untill stand, burst or blackjack
            cout << "do you want stand or hit? (h for hit / s for stand) " << endl << endl;
            // bjfile<<"do you want stand or hit? (h for hit / s for stand) "<<endl<<endl;//writing log to file
            cin >> response;

            if (response == 'h' || response == 'H') { //player wants to takeout another card
                newcard = 1 + (rand() % 13);//generating different values using rand ranging from 0to13
                if (newcard >= 11 && newcard <= 13)//face card. So make it 10
                    newcard = 10;

                if (newcard == 1 && (dealersum + 11) <= 21)//assume new card 11 if sum is less than 21, otherwise be it 1
                    newcard = 11;
                playersum += newcard;
                playercards = playercards + ", " + to_string(newcard);
                cout << "Your cards : " << playercards << " total = " << playersum << endl;
                // bjfile<<"Your cards : "<<cards<<" total = "<<sum<<endl;//writing log to file

                if (playersum == 21) { //blackjack for player
                    cout << "Wow! you hit a blackjack.." << endl;
                    //bjfile<<"Wow! you hit a blackjack.."<<endl;//writing log to file
                    gameinnerloop = false;
                }

                if (playersum > 21) { //player is busted and dealer wins
                    cout << "You are bursted. You lose $" << BET << " to the dealer" << endl << endl;
                    //bjfile<<"You are bursted. You lose $"<<BET<<" to the dealer"<<endl<<endl;//writing log to file
                    balance[session][0]-= BET;
                    balance[session][1] += BET;
                    gameinnerloop = false;
                    playerBust = true;
                }
            }//end of if
            else { //player choses to stand. No more cards
                cout << "You chose to stand..., Now dealer will take the turn" << endl << endl;
                //bjfile<<"You chose to stand..., Now dealer will take the turn"<<endl<<endl;//writing log to file
                gameinnerloop = false;
            }

        }//end of innergameloop

        //dealer will draw more card for herself....

        if (!playerBust) {//execute when player has not busted
            cout << "Now dealer is opening her second card..." << endl;
            //bjfile<<"Now dealer is opening her second card..."<<endl;//writing log to file

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
                //bjfile<<"Dealer cards are "<<dealercards<<endl;//writing log to file
                 //bjfile<<"Dealer total is : "<<dealersum<<endl;//writing log to file

                if (dealersum > 21) { //dealer busted out
                    //cout << "Dealer bursted out... Hence you won the game" << endl;
                    //cout << "Dealer paid you $" << BET << endl;
                    //  bjfile<<"Dealer bursted out... Hence you won the game"<<endl;//writing log to file
                    //  bjfile<<"Dealer paid you $"<<BET<<endl;//writing log to file
                    //balance[session] += BET;
                    //cout << "Your new balance is : $" << balance << endl;
                    //   bjfile<<"Your new balance is : $"<<balance<<endl;//writing log to file
                    dealerflag = false;
                    dealerBust = true;

                }
                else if ((dealersum >= 17) && (dealersum <= 21)) { //dealer has to stand                             
                    cout << "Dealer total is 17 or more. Hence dealer will have to stand" << endl;
                    //    bjfile<<"Dealer total is 17 or more. Hence dealer will have to stand"<<endl;//writing log to file
                    dealerflag = false;
                }

                else if (dealersum == 21 && playersum != 21) {
                    cout << "Dealer got blackjack!" << endl;
                    // bjfile<<"Dealer got blackjack!"<<endl;//writing log to file
                    //balance = balance - BET;
                    //cout << "Your new balance is : $" << balance << endl;
                    //cout << "Your new balance is : $" << balance << endl;//writing to log file
                    //dealerflag = false;      
                }

                else {
                    cout << "Dealer total is 16 or less. Hence dealer will have to hit" << endl;  //must for dealer to take out new card
                 //   bjfile<<"Dealer total is 16 or less. Hence dealer will have to hit"<<endl;  //writing log to file
                }
            } while (dealerflag);

            if (dealerBust) {
                cout << "dealer busted out, you WON!" << endl;
                balance[session][0] += BET;
                balance[session][1] -= BET;

                cout << "Dealer lost her " << BET << " dollar bet to you" << endl;
                cout << "Your new balance is : $" << balance[session][0] << endl;
            }

            else if (dealersum > playersum) {
                cout << "Dealer Won!. Your " << BET << " $ bet went to the dealer" << endl;
                // bjfile<<"Dealer Won!. Your "<<BET<<" $ bet went to the dealer"<<endl;//writing log to file
                balance[session][0] -= BET;
                balance[session][1] += BET;
                cout << "Your new balance is : $" << balance[session][0] << endl;
                // bjfile<<"Your new balance is : $"<<balance<<endl;//writing log to file
            }
            else if (playersum > dealersum) {
                cout << "You Won" << endl;
                cout << "Dealer paid you $" << BET << endl;
                //  bjfile<<"You Won"<<endl;//writing log to file
                //  bjfile<<"Dealer paid you $"<<BET<<endl;//writing log to file
                balance[session][0] += BET;
                balance[session][1] -= BET;

                cout << "Your new balance is : $" << balance[session][0] << endl;
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

        } //end of if


        std::cout << "--------------------------------------" << endl;
        std::cout << "Do you want to continue playing? yes(y)/No (n)" << endl;
        std::cin >> response;

        if (response == 'n' || response == 'n') {
            cout << "Thanks for playing Suhaani's blackjack" << endl;
            cout << "Your current balance is " << balance[session][0] << " dollars" << endl;
            cout << "Return counters and take your money back" << endl;
            cout << "--------------------------------------------";
            gamemasterloop = false;
        }//end of if
        else {
            playersum = 0;
            dealersum = 0;
            dealerflag = true;
            gameloop = true;
            gameinnerloop = true;
            playerBust = false;
            dealerBust = false;
            session++;
        }

    }// end of mastergameloop

    bjfile.close();
    return 0;
}//end of main
