#include <iostream>
#include <cstdlib> //for rand and srand
#include <cstdio>
#include <string>
#include<ctime>
#include <fstream>
#include <vector>

using namespace std;

void gameintro(vector<string>& log, int balance[][], string& playername) {

    cout << "File to write log could not be open. So, no log of the session will be written" << endl;
    cout << "This is Suhaani's blackjack game. You play against the dealer" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "What is your name?" << endl;
    getline(cin, playername);
    cout << "Welcome " << playername << " to Suhaani's Blackjack game" << endl;
    cout << "How many chips do you want to buy? (Each is worth one dollar)" << endl << endl;
    cin >> balance[0][0];
    cout << playername << " is playing Suhaani's blackjack with " << balance << " dollars" << endl;
    cout << "-------------------------------------------------------------------" << endl << endl;

    cout << "new Session for play started by started by " << playername << endl;
    log.push_back(playername + " is playing with " + balance + " Dollars");//pushing log to log vector
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
    int firstcard;
    int secondcard;
    int dealercard;
    int newcard;
    int sum = 0;
    int dealersum = 0;
    int BET = 1;
    int balance;
    balance = 100;
    string cards;
    string dealercards;
    string playername;
    ofstream bjfile;
    int const ROWMAX = 100; //assume player will play maximum 100 sessions in the play

    vector <string> log;
    int balance[ROWMAX][2] = {}; //array to save current balance points. 

    //open a txt file to write the session log as it is important to write log in casino


    while (gamemasterloop) {

        srand(time(NULL));
        cout << "Dealer serving your first two cards. Here it goes... " << endl << endl;
        bjfile << "Dealer serving your first two cards. Here it goes... " << endl << endl; //writing to log file
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
            //bjfile<<"Your second card is 1. Hence it is treated as 11"<<endl;//writing log to file
            secondcard = 11;
        }
        sum += firstcard;
        sum += secondcard;
        cards = to_string(firstcard) + ", " + to_string(secondcard);

        cout << "Your cards : " << cards << endl << "Total= " << sum << endl << endl;
        //bjfile<<"Your cards : "<<cards<<endl<<"Total= "<<sum<<endl<<endl; //writing to log file

        if (sum == 21) {//it is blackjack for player 
            cout << "Wow! you hit a blackjack.." << endl;
            //bjfile<<"Wow! you hit a blackjack.."<<endl;//writing log to file
        }
        //Now dealer will open his first card
        //.....................................................................
        cout << "Dealer's Turn..Dealer open her first card..." << endl;
        //bjfile<<"Dealer's Turn..Dealer open her first card..."<<endl;//writing log to file 

        dealercard = 1 + (rand() % 13);//generating different values using rand ranging from 1 to 13

        if (dealercard >= 11 && firstcard <= 13) {//dealer got face card,make it 10
            dealercard = 10;
        }
        if (dealercard == 1) {
            dealercard = 11;
            cout << "Dealer first card is 1, hence it is treated as 11" << endl << endl;
            // bjfile<<"Dealer first card is 1, hence it is treated as 11"<<endl<<endl;  //writing log to file   
        }
        cout << dealercard << endl;
        //bjfile<<dealercard<<endl;//writing log to file
        dealersum += dealercard;
        dealercards = to_string(dealercard);

        cout << "Dealer Total is : " << dealersum << endl << endl;
        //bjfile<<"Dealer Total is : "<<dealersum<<endl<<endl;//writing log to file

        //................................................................................
        cout << "------------------------------------------------------" << endl;
        cout << "Your turn now.....";

        while (gameinnerloop) { //execute player has no blackjack. loop for player to takeout more cards untill stand, burst or blackjack
            cout << "do you want stand or hit? (h for hit / s for stand) " << endl << endl;
            // bjfile<<"do you want stand or hit? (h for hit / s for stand) "<<endl<<endl;//writing log to file
            cin >> response;

            if (response == 'h' || response == 'H') { //player wants to takeout another card
                newcard = 1 + (rand() % 13);//generating different values using rand ranging from 0to13
                if (newcard >= 11 && newcard <= 13)//face card. So make it 10
                    newcard = 10;

                if (newcard == 1 && (sum + 11) <= 21)//assume new card 11 if sum is less than 21, otherwise be it 1
                    newcard = 11;
                sum += newcard;
                cards = cards + ", " + to_string(newcard);
                cout << "Your cards : " << cards << " total = " << sum << endl;
                // bjfile<<"Your cards : "<<cards<<" total = "<<sum<<endl;//writing log to file

                if (sum == 21) { //blackjack for player
                    cout << "Wow! you hit a blackjack.." << endl;
                    //bjfile<<"Wow! you hit a blackjack.."<<endl;//writing log to file
                    gameinnerloop = false;
                }

                if (sum > 21) { //player is busted and dealer wins
                    cout << "You are bursted. You lose $" << BET << " to the dealer" << endl << endl;
                    //bjfile<<"You are bursted. You lose $"<<BET<<" to the dealer"<<endl<<endl;//writing log to file
                    balance = balance - BET;
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

                if (dealercard >= 11 && firstcard <= 13) //dealer got face card. make it 10
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
                    //balance += BET;
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

                else if (dealersum == 21 && sum != 21) {
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
                balance += BET;
                cout << "Dealer lost her " << BET << " dollar bet to you" << endl;
                cout << "Your new balance is : $" << balance << endl;
            }

            else if (dealersum > sum) {
                cout << "Dealer Won!. Your " << BET << " $ bet went to the dealer" << endl;
                // bjfile<<"Dealer Won!. Your "<<BET<<" $ bet went to the dealer"<<endl;//writing log to file
                balance -= BET;
                cout << "Your new balance is : $" << balance << endl;
                // bjfile<<"Your new balance is : $"<<balance<<endl;//writing log to file
            }
            else if (sum > dealersum) {
                cout << "You Won" << endl;
                cout << "Dealer paid you $" << BET << endl;
                //  bjfile<<"You Won"<<endl;//writing log to file
                //  bjfile<<"Dealer paid you $"<<BET<<endl;//writing log to file
                balance += BET;
                cout << "Your new balance is : $" << balance << endl;
                // bjfile<<"Your new balance is : $"<<balance<<endl;//writing log to file

            }
            else if (sum == 21 && dealersum == 21)
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
            cout << "Your current balance is " << balance << " dollars" << endl;
            cout << "Return counters and take your money back" << endl;
            cout << "--------------------------------------------";
            gamemasterloop = false;
        }//end of if
        else {
            sum = 0;
            dealersum = 0;
            dealerflag = true;
            gameloop = true;
            gameinnerloop = true;
            playerBust = false;
            dealerBust = false;
        }

    }// end of mastergameloop

    bjfile.close();
    return 0;
}//end of main
