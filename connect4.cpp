
// CONNECT4 by Joaquin Paolo Pacete | CPE231
// Finals Project for PROGLOD
// Mr. Einstein Yong

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream> 
#include <climits> // for flushing input buffer for all char[1] inputs
#include <limits> // for flushing input buffer
#include <fstream> // for file streaming
#include <string.h> // for advanced data types like strlen(), etc.
#include <stdlib.h> // for random function
#include <time.h> // for time, associated with random function

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Player {
    char nickname[30];
    int score;
    char powerUp[2][10] = {"[W]hiten", "[B]lock"};
    char powerUpPlaceHolder[2] = {'w', 'b'};
    int blockMoves = 2;
};

void titleScreen();
void playerInfo(Player& player1, Player& player2);
void homeScreen(char& optionHomeScreen, Player& player1, Player& player2);
    void sub_LP(Player& player1, Player& player2);
        void connect4(bool& player1Turn, bool& player2Turn, Player& player1, Player& player2, char gameArray[6][7],
                    int gameArrayIterate[7], int gameArrayColMoves[7], int& moves, char& player1Pick, 
                    char& player2Pick, bool& hasWinner, int& row, int& col, char& input);
        void blockPowerUp(bool& player1Turn, bool& player2Turn, Player& player1, Player& player2, int& moves);
        void printBoard(int& row, int& col, char gameArray[6][7], Player& player1, Player& player2);
        void printWinner(bool& player1Turn, int& row, int& col, 
                        char gameArray[6][7], Player& player1, Player& player2);
        void continueGame(bool& continueLP, bool& hasWinner, int& row, int& col, 
                        char gameArray[6][7], int& moves, int gameArrayIterate[7], int gameArrayColMoves[7], Player& player1, Player& player2);
        void playerLog(Player& player1, Player& player2);
    void sub_GM();
    void sub_ABT();
    void sub_FB();
    void sub_EXT(bool& gameContinue);
    
// main function
int main() {

    Player player1, player2;

    bool gameContinue = true;
    titleScreen();
    system("cls");

    // Main Do-While Loop for Home Page
    do {
        playerInfo(player1, player2); //run player info 

        // HOME PAGE
        char optionHomeScreen;

        while ((optionHomeScreen != 'L' || optionHomeScreen != 'l') && (optionHomeScreen != 'G' || optionHomeScreen != 'g')
            && (optionHomeScreen != 'A' || optionHomeScreen != 'a') && (optionHomeScreen != 'E' || optionHomeScreen != 'e')) {
            
            homeScreen(optionHomeScreen, player1, player2);

            switch (optionHomeScreen) {
                case 'L':
                case 'l':
                    system("cls");
                    sub_LP(player1, player2);
                    break;     
                case 'G':
                case 'g':
                    system("cls");
                    sub_GM();
                    break;
                    
                case 'A':
                case 'a':
                    system("cls");
                    sub_ABT();
                    break;
                case 'F':
                case 'f':
                    system("cls");
                    sub_FB();
                    break;
                case 'E':
                case 'e':
                    system("cls");
                    sub_EXT(gameContinue);
                    return 0;
                default:
                    system("cls");
            }

        } // while loop for home page
         
    } while (gameContinue != false);

}

// TITLE SCREEN
void titleScreen() {
    system("cls");
    cout << "\n\n\n\n\t\t>>=========================================================================================<<\n";
    cout << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t__| |___________________________________________________| |__\n"
            "\t\t\t\t__   ___________________________________________________   __\n"
            "\t\t\t\t  | |                                                   | |  \n"
            "\t\t\t\t  | |  ____                            _     _  _     _ | |  \n"
            "\t\t\t\t  | | / ___|___  _ __  _ __   ___  ___| |_  | || |   | || |  \n"
            "\t\t\t\t  | || |   / _ \\| '_ \\| '_ \\ / _ \\/ __| __| | || |_  | || |  \n"
            "\t\t\t\t  | || |__| (_) | | | | | | |  __/ (__| |_  |__   _| |_|| |  \n"
            "\t\t\t\t  | | \\____\\___/|_| |_|_| |_|\\___|\\___|\\__|    |_|   (_)| |  \n"
            "\t\t\t\t__| |___________________________________________________| |__\n"
            "\t\t\t\t__   ___________________________________________________   __\n"
            "\t\t\t\t  | |                                                   | |  \n\n";
    cout << "\t\t\t\t\t\t   Welcome to Connect 4!" << endl
         << endl << endl;

    cout << "\n\n\n\n\t\t>>=========================================================================================<<\n";
    cout << "\n\t\t\t\t\t     "; system("pause"); cout << endl; // press any key to continue
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

// NICKNAME GET
void playerInfo(Player& player1, Player& player2) {
    cout << "\n\n\n\n"
         << "\t\t\t__| |_________________________________________________________________________| |__" << endl
         << "\t\t\t__   _________________________________________________________________________   __" << endl
         << "\t\t\t  | |                                                                         | |  " << endl
         << "\t\t\t  | | _____       _              _   _ _      _                               | |  " << endl
         << "\t\t\t  | || ____|_ __ | |_ ___ _ __  | \\ | (_) ___| | ___ __   __ _ _ __ ___   ___ | |  " << endl
         << "\t\t\t  | ||  _| | '_ \\| __/ _ \\ '__| |  \\| | |/ __| |/ / '_ \\ / _` | '_ ` _ \\ / _ \\| |  " << endl
         << "\t\t\t  | || |___| | | | ||  __/ |    | |\\  | | (__|   <| | | | (_| | | | | | |  __/| |  " << endl
         << "\t\t\t  | ||_____|_| |_|\\__\\___|_|    |_| \\_|_|\\___|_|\\_\\_| |_|\\__,_|_| |_| |_|\\___|| |  " << endl
         << "\t\t\t__| |_________________________________________________________________________| |__" << endl
         << "\t\t\t__   _________________________________________________________________________   __" << endl
         << "\t\t\t  | |                                                                         | |  " << endl;
    cout << endl << endl;
    cout << "\033[1;32m\t\t\t\t\t Enter Player 1 Nickname: \033[0m"; cin.getline(player1.nickname, sizeof(player1.nickname));
    cout << endl;
    cout << "\t\t\t***********************************************************************************\n" << endl;
    cout << "\033[1;33m\t\t\t\t\t Enter Player 2 Nickname: \033[0m"; cin.getline(player2.nickname, sizeof(player2.nickname)); 
    system("cls");
}

// HOME SCREEN
void homeScreen(char& optionHomeScreen, Player& player1, Player& player2) {
    // Connect 4 ASCII Display

    cout << "\n\n\n\t\t>>=========================================================================================<<\n";
    cout << endl << endl << endl << endl << endl;
    
    cout << "\t\t\t\t__| |___________________________________________________| |__\n"
            "\t\t\t\t__   ___________________________________________________   __\n"
            "\t\t\t\t  | |                                                   | |  \n"
            "\t\t\t\t  | |  ____                            _     _  _     _ | |  \n"
            "\t\t\t\t  | | / ___|___  _ __  _ __   ___  ___| |_  | || |   | || |  \n"
            "\t\t\t\t  | || |   / _ \\| '_ \\| '_ \\ / _ \\/ __| __| | || |_  | || |  \n"
            "\t\t\t\t  | || |__| (_) | | | | | | |  __/ (__| |_  |__   _| |_|| |  \n"
            "\t\t\t\t  | | \\____\\___/|_| |_|_| |_|\\___|\\___|\\__|    |_|   (_)| |  \n"
            "\t\t\t\t__| |___________________________________________________| |__\n"
            "\t\t\t\t__   ___________________________________________________   __\n"
            "\t\t\t\t  | |                                                   | |  \n\n";

    // Welcome Player Nicknames
    cout << "\t\t\t\t\t\tWelcome, \033[1;32m" << player1.nickname << "\033[0m and \033[1;33m" << player2.nickname << "\033[0m!\n\n" << endl;
    
    // Home Screen Options
    cout << "\t\t\t\t\t\t\e[1m[L]\e[0met's Play!\n" 
         << "\t\t\t\t\t\t\e[1m[G]\e[0mame Mechanics\n" 
         << "\t\t\t\t\t\t\e[1m[A]\e[0mbout\n" 
         << "\t\t\t\t\t\t\e[1m[F]\e[0meedback\n"
         << "\t\t\t\t\t\t\e[1m[E]\e[0mxit" << endl;

    cout << "\n\n\n\t\t>>=========================================================================================<<\n";
    
    cout << "\n\t\t\t\t\t\tEnter option here: "; cin >> optionHomeScreen; cin.ignore(INT_MAX, '\n');
}

// LETS PLAY OPTION
void sub_LP(Player& player1, Player& player2) {

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

    bool continueLP = true;
    bool player1Turn = false;
    bool player2Turn = false;
    bool hasWinner = false;

    player1.score = 0;
    player2.score = 0;
    
    char input; // user input
    char player1Pick = 'X';
    char player2Pick = 'O';
    char gameArray[6][7] = {
        '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-', 
        '-', '-', '-', '-', '-', '-', '-'
    }; // game board

    int moves = 0; // at max 42 moves
    int gameArrayIterate[7] = {5,5,5,5,5,5,5}; // to check if previous slot is full and put the pick on top instead
    int gameArrayColMoves[7] = {0,0,0,0,0,0,0}; // to check if columns are full
    int row, col; // declaration for displaying the 2D array

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Loop for "Let's Play" Option
    do {
        // input option for decide player1
        cout << "\n\n\n";   

        cout << "\t\t\t\t _____                                                                          _____ " << endl;
        cout << "\t\t\t\t( ___ )                                                                        ( ___ )" << endl;
        cout << "\t\t\t\t |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   | " << endl;
        cout << "\t\t\t\t |   |   ____ _                            _          ____                      |   | " << endl;
        cout << "\t\t\t\t |   |  / ___| |__   ___   ___  ___  ___  | |_ ___   |  _ \\ _ __ __ ___      __ |   | " << endl;
        cout << "\t\t\t\t |   | | |   | '_ \\ / _ \\ / _ \\/ __|/ _ \\ | __/ _ \\  | | | | '__/ _` \\ \\ / /  / |   | " << endl;
        cout << "\t\t\t\t |   | | |___| | | | (_) | (_) \\__ \\  __/ | || (_) | | |_| | | | (_| |\\ V  V /  |   | " << endl;
        cout << "\t\t\t\t |   |  \\____|_| |_|\\___/ \\___/|___/\\___|  \\__\\___/  |____/|_|  \\__,_| \\_/\\_/   |   | " << endl;
        cout << "\t\t\t\t |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___| " << endl;
        cout << "\t\t\t\t(_____)                                                                        (_____) " << endl;

        char playerDecide; 
        cout << "\n\n\n\t\t\t****************************************************************************************************\n\n";
        cout << "\t\t\t\t\t   Who will be drawing first? ( \033[1;32m" << player1.nickname << "[1]\033[0m | \033[1;33m" << player2.nickname << 
            "[2]\033[0m |\e[1m Random[R] \e[0m): "; 
        cin >> playerDecide;
        cout << "\n\t\t\t****************************************************************************************************\n\n";

        cin.ignore(INT_MAX, '\n');
        
        
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// [OPTION 1 for playerDecide]

        if (playerDecide == '1') {
            player2Turn = false;
            player1Turn = true;
            system("cls");

            // run the connect4 game
            connect4(player1Turn, player2Turn, player1, player2, gameArray,
                    gameArrayIterate, gameArrayColMoves, moves, player1Pick, 
                    player2Pick, hasWinner, row, col, input);

            // print continueGame void
            continueGame(continueLP, hasWinner, row, col, gameArray, moves, gameArrayIterate, gameArrayColMoves, player1, player2);

        } // end of '1 option for who will be the first

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// [OPTION 2 for playerDecide]

        else if (playerDecide == '2') {
            player1Turn = false;
            player2Turn = true;
            system("cls");
            // run the connect4 game
            connect4(player1Turn, player2Turn, player1, player2, gameArray,
                    gameArrayIterate, gameArrayColMoves, moves, player1Pick, 
                    player2Pick, hasWinner, row, col, input);

            // print continueGame void
            continueGame(continueLP, hasWinner, row, col, gameArray, moves, gameArrayIterate, gameArrayColMoves, player1, player2);

        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// [OPTION R for playerDecide]

        else if (playerDecide == 'R' || playerDecide == 'r') {
            srand(time(NULL));
            int randomNumber = (rand() % 2) + 1;
            
            switch (randomNumber) {
                case 1:
                    cout << "\t\t\t\t\t\tSystem chose: \033[1;32m" << player1.nickname << "\033[0m";
                    cout << "\n\n\t\t\t\t\t\t"; system("pause");
                    system("cls");
                    break;
                case 2:
                    cout << "\t\t\t\t\t\tSystem chose: \033[1;33m" << player2.nickname << "\033[0m";
                    cout << "\n\n\t\t\t\t\t\t"; system("pause");
                    system("cls");
                    break;
                default:
                    cout << "Error.";
                    break;

            }

            switch (randomNumber) {
                case 1:
                    player2Turn = false;
                    player1Turn = true;
                    system("cls");

                    // run the connect4 game
                    connect4(player1Turn, player2Turn, player1, player2, gameArray,
                        gameArrayIterate, gameArrayColMoves, moves, player1Pick, 
                        player2Pick, hasWinner, row, col, input);
                    
                    // print continueGame void
                    continueGame(continueLP, hasWinner, row, col, gameArray, moves, gameArrayIterate, gameArrayColMoves, player1, player2);
                    break;
                
                case 2: 
                    player1Turn = false;
                    player2Turn = true;
                    system("cls");

                    // run the connect4 game
                    connect4(player1Turn, player2Turn, player1, player2, gameArray,
                        gameArrayIterate, gameArrayColMoves, moves, player1Pick, 
                        player2Pick, hasWinner, row, col, input);
                    
                    // print continueGame void
                    continueGame(continueLP, hasWinner, row, col, gameArray, moves, gameArrayIterate, gameArrayColMoves, player1, player2);
                    break;
                default:
                    cout << "Random number function error";
                    break;
            }
                
        }

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// [ELSE for playerDecide]

        else {
            cout << "\t\t\t\t\t\tInvalid input. ";
            system("pause"); system("cls");
        }

    } while (continueLP != false);

}

void connect4(bool& player1Turn, bool& player2Turn, Player& player1, Player& player2, char gameArray[6][7],
            int gameArrayIterate[7], int gameArrayColMoves[7], int& moves, char& player1Pick, char& player2Pick, 
            bool& hasWinner, int& row, int& col, char& input) {

    do {

        // PLAYER 1 TURN
        if (player1Turn == true) {
            printBoard(row, col, gameArray, player1, player2);

            cout << "\033[1;32m\n\t\t\t\t\t\t\t" << player1.nickname << "[X]'s Turn!\033[0m" << endl; 
            cout << "\t\t\t\t\t\t\tPower-ups: \e[1m" << player1.powerUp[0] << "\e[0m | \e[1m" << player1.powerUp[1] << "\e[0m"<< endl;
            cout << "\n\t\t\t\t\t\t\tPlease input valid column number/Power-up: "; 
            cin >> input; cin.ignore(INT_MAX, '\n');

            switch(input) {
                case '1': 
                    if (gameArrayColMoves[0] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }
                    else {
                        if (gameArray[gameArrayIterate[0]+1][0] == 'X' || gameArray[gameArrayIterate[0]+1][0] == 'O') {
                            gameArray[gameArrayIterate[0]][0] = player1Pick;
                        
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[0]--;
                            gameArrayColMoves[0]++;
                            break;
                            
                        }

                        else {
                            gameArray[5][0] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[0]--;
                            gameArrayColMoves[0]++;
                            break;
                        }
                    }
                    
                case '2':
                    if (gameArrayColMoves[1] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[1]+1][1] == 'X' || gameArray[gameArrayIterate[1]+1][1] == 'O') {
                            gameArray[gameArrayIterate[1]][1] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[1]--;
                            gameArrayColMoves[1]++;
                            break;
                        }

                        else {
                            gameArray[5][1] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[1]--;
                            gameArrayColMoves[1]++;
                            break;
                        }
                    }

                case '3':
                    if (gameArrayColMoves[2] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[2]+1][2] == 'X' || gameArray[gameArrayIterate[2]+1][2] == 'O') {
                            gameArray[gameArrayIterate[2]][2] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[2]--;
                            gameArrayColMoves[2]++;
                            break;
                        }


                        else {
                            gameArray[5][2] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[2]--;
                            gameArrayColMoves[2]++;
                            break;
                        }
                    }

                case '4':
                    if (gameArrayColMoves[3] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[3]+1][3] == 'X' || gameArray[gameArrayIterate[3]+1][3] == 'O') {
                            gameArray[gameArrayIterate[3]][3] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[3]--;
                            gameArrayColMoves[3]++;
                            break;
                        }

                        else {
                            gameArray[5][3] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[3]--;
                            gameArrayColMoves[3]++;
                            break;
                        }
                    }

                case '5':
                    if (gameArrayColMoves[4] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[4]+1][4] == 'X' || gameArray[gameArrayIterate[4]+1][4] == 'O') {
                            gameArray[gameArrayIterate[4]][4] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[4]--;
                            gameArrayColMoves[4]++;
                            break;
                        }

                        else {
                            gameArray[5][4] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[4]--;
                            gameArrayColMoves[4]++;
                            break;
                        }
                    }

                case '6':
                    if (gameArrayColMoves[5] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[5]+1][5] == 'X' || gameArray[gameArrayIterate[5]+1][5] == 'O') {
                            gameArray[gameArrayIterate[5]][5] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[5]--;
                            gameArrayColMoves[5]++;
                            break;
                        }

                        else {
                            gameArray[5][5] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[5]--;
                            gameArrayColMoves[5]++;
                            break;
                        }
                    }

                case '7':
                    if (gameArrayColMoves[6] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[6]+1][6] == 'X' || gameArray[gameArrayIterate[6]+1][6] == 'O') {
                            gameArray[gameArrayIterate[6]][6] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[6]--;
                            gameArrayColMoves[6]++;
                            break;
                        }

                        else {
                            gameArray[5][6] = player1Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[6]--;
                            gameArrayColMoves[6]++;
                            break;
                        }
                    }

                case 'W':
                case 'w':
                    if (player1.powerUp[0][1] == 'W') {
                        player1Turn = false;
                        player2Turn = true;
                        // player1.powerUp[0] = "-";
                        strcpy(player1.powerUp[0], "-");
                        player1.powerUpPlaceHolder[0] = '-';
                        system("cls");
                        break;
                    }

                    else {
                        cout << "\n\n\t\t\t\t\t\t\tPower-up has been used. ";
                        system("pause");
                        system("cls");
                        break;
                    }
                
                case 'B':
                case 'b':
                    if (player1.powerUp[1][1] == 'B') {
                        player1Turn = true;
                        player2Turn = false;
                        player1.blockMoves = 1;
                        // player1.powerUp[0] = "-";
                        strcpy(player1.powerUp[1], "-");
                        player1.powerUpPlaceHolder[1] = '-';
                        system("cls");
                        break;
                    }

                    else {
                        cout << "\n\n\t\t\t\t\t\t\tPower-up has been used. ";
                        system("pause");
                        system("cls");
                        break;
                    }

                default:
                    cout << "\n\t\t\t\t\t\t\tInvalid input." << endl;
                    cout << "\t\t\t\t\t\t\t"; system("pause");
                    system("cls");
                    break;

            }

        } // end of player 1 turn

        // PLAYER 2 TURN
        else {
            printBoard(row, col, gameArray, player1, player2);

            cout << "\033[1;33m\n\t\t\t\t\t\t\t" << player2.nickname << "[O]'s Turn!\033[0m" << endl;
            cout << "\t\t\t\t\t\t\tPower-ups: \e[1m" << player2.powerUp[0] << "\e[0m | \e[1m" << player2.powerUp[1] << "\e[0m"<< endl;
            cout << "\n\t\t\t\t\t\t\tPlease input valid column number/Power-up: "; cin >> input; cin.ignore(INT_MAX, '\n');

            // column no. checker
            switch(input) {
                case '1':
                    if (gameArrayColMoves[0] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[0]+1][0] == 'X' || gameArray[gameArrayIterate[0]+1][0] == 'O') {
                            gameArray[gameArrayIterate[0]][0] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[0]--;
                            gameArrayColMoves[0]++;
                            break;
                        }

                        else {
                            gameArray[5][0] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[0]--;
                            gameArrayColMoves[0]++;
                            break;
                        }                           
                    }

                case '2':
                    if (gameArrayColMoves[1] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[1]+1][1] == 'X' || gameArray[gameArrayIterate[1]+1][1] == 'O') {
                            gameArray[gameArrayIterate[1]][1] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[1]--;
                            gameArrayColMoves[1]++;
                            break;
                        }

                        else {
                            gameArray[5][1] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[1]--;
                            gameArrayColMoves[1]++;
                            break;
                        }
                    }

                case '3':
                    if (gameArrayColMoves[2] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[2]+1][2] == 'X' || gameArray[gameArrayIterate[2]+1][2] == 'O') {
                            gameArray[gameArrayIterate[2]][2] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[2]--;
                            gameArrayColMoves[2]++;
                            break;
                        }

                        else {
                            gameArray[5][2] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[2]--;
                            gameArrayColMoves[2]++;
                            break;
                        }
                    }
                case '4':
                    if (gameArrayColMoves[3] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[3]+1][3] == 'X' || gameArray[gameArrayIterate[3]+1][3] == 'O') {
                            gameArray[gameArrayIterate[3]][3] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[3]--;
                            gameArrayColMoves[3]++;
                            break;
                        }

                        else {
                            gameArray[5][3] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[3]--;
                            gameArrayColMoves[3]++;
                            break;
                        }
                    }

                case '5':
                    if (gameArrayColMoves[4] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[4]+1][4] == 'X' || gameArray[gameArrayIterate[4]+1][4] == 'O') {
                            gameArray[gameArrayIterate[4]][4] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[4]--;
                            gameArrayColMoves[4]++;
                            break;
                        }

                        else {
                            gameArray[5][4] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[4]--;
                            gameArrayColMoves[4]++;
                            break;
                        }
                    }

                case '6':
                    if (gameArrayColMoves[5] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[5]+1][5] == 'X' || gameArray[gameArrayIterate[5]+1][5] == 'O') {
                            gameArray[gameArrayIterate[5]][5] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[5]--;
                            gameArrayColMoves[5]++;
                            break;
                        }

                        else {
                            gameArray[5][5] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[5]--;
                            gameArrayColMoves[5]++;
                            break;
                        }
                    }

                case '7':
                    if (gameArrayColMoves[6] == 6) {
                        cout << "\n\t\t\t\t\tThe column number you have entered is full. Please enter another column number.\n";
                        cout << "\t\t\t\t\t\t\t\t"; system("pause");
                        system("cls");
                        break;
                    }

                    else {
                        if (gameArray[gameArrayIterate[6]+1][6] == 'X' || gameArray[gameArrayIterate[6]+1][6] == 'O') {
                            gameArray[gameArrayIterate[6]][6] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[6]--;
                            gameArrayColMoves[6]++;
                            break;
                        }

                        else {
                            gameArray[5][6] = player2Pick;
                            blockPowerUp(player1Turn, player2Turn, player1, player2, moves);
                            gameArrayIterate[6]--;
                            gameArrayColMoves[6]++;
                            break;
                        }
                    }
                
                case 'W':
                case 'w':
                    if (player2.powerUp[0][1] == 'W') {
                        player2Turn = false;
                        player1Turn = true;
                        // player2.powerUp[0] = "-";
                        strcpy(player2.powerUp[0], "-");
                        player2.powerUpPlaceHolder[0] = '-';
                        system("cls");
                        break;
                    }

                    else {
                        cout << "\n\n\t\t\t\t\t\t\tPower-up has been used. ";
                        system("pause");
                        system("cls");
                        break;
                    }
                
                case 'B':
                case 'b':
                    if (player2.powerUp[1][1] == 'B') {
                        player2Turn = true;
                        player1Turn = false;
                        player2.blockMoves = 1;
                        strcpy(player2.powerUp[1], "-");
                        player2.powerUpPlaceHolder[1] = '-';
                        system("cls");
                        break;
                    }

                    else {
                        cout << "\n\n\t\t\t\t\t\t\tPower-up has been used. ";
                        system("pause");
                        system("cls");
                        break;
                    }

                default:
                    cout << "\n\t\t\t\t\t\t\tInvalid input." << endl;
                    cout << "\t\t\t\t\t\t\t"; system("pause");
                    system("cls");
                    break;

            } // end of switch input
            
        } // end of player 2 turn

        ////////////////////////////////////////////////////////////////////////////////////////////////////// [ CHECK FOR WINNER]

        int a, b;
        ////////////////////////////////////////////////////////////////////////////////////// [CHECK ROW]

        for (a = 5; a >= 0; a--) {
            for (b = 0; b <= 3; b++) {
                if ((gameArray[a][b] == 'X') && (gameArray[a][b+1] == 'X') &&
                    (gameArray[a][b+2] == 'X') && (gameArray[a][b+3] == 'X')) {

                        hasWinner = true;
                        printWinner(player1Turn, row, col, gameArray, player1, player2);
                        break;

                }
                
                /////////////////////////////////////////////////

                if ((gameArray[a][b] == 'O') && (gameArray[a][b+1] == 'O') &&
                    (gameArray[a][b+2] == 'O') && (gameArray[a][b+3] == 'O')) {

                        hasWinner = true;
                        printWinner(player1Turn, row, col, gameArray, player1, player2);
                        break;

                }
            }
        }

        ///////////////////////////////////////////////////////////////////////////////////// [CHECK COLUMN]

        for (a=5; a >=3; a--) {
            for (b=0; b<=6; b++) {
                
                if ((gameArray[a][b] == 'X') && (gameArray[a-1][b] == 'X') &&
                    (gameArray[a-2][b] == 'X') && (gameArray[a-3][b] == 'X')) {

                    hasWinner = true;
                    printWinner(player1Turn, row, col, gameArray, player1, player2);
                    break;

                }

                /////////////////////////////////////////////

                if ((gameArray[a][b] == 'O') && (gameArray[a-1][b] == 'O') &&
                    (gameArray[a-2][b] == 'O') && (gameArray[a-3][b] == 'O')) {

                    hasWinner = true;
                    printWinner(player1Turn, row, col, gameArray, player1, player2);
                    break;

                }

            }

        }

        /////////////////////////////////////////////////////////////////////////////// [CHECK DIAGONALS]

        bool diagonalWinner = false;

        // left to right
        for (a = 5; a >= 3; a--) {
            for (b = 0; b <= 3; b++) {
                if ((gameArray[a][b] == 'X') && (gameArray[a-1][b+1] == 'X') &&
                    (gameArray[a-2][b+2] == 'X') && (gameArray[a-3][b+3] == 'X')) {
                        
                        // to cancel other diagonal patterns
                        if (diagonalWinner == false) {
                            hasWinner = true;
                            diagonalWinner = true;
                            printWinner(player1Turn, row, col, gameArray, player1, player2);
                            break;
                        }

                }
                
                /////////////////////////////////////////////////

                if ((gameArray[a][b] == 'O') && (gameArray[a-1][b+1] == 'O') &&
                    (gameArray[a-2][b+2] == 'O') && (gameArray[a-3][b+3] == 'O')) {
                        
                        // to cancel other diagonal patterns
                        if (diagonalWinner == false) {
                            hasWinner = true;
                            diagonalWinner = true;
                            printWinner(player1Turn, row, col, gameArray, player1, player2);
                            break;
                        }

                }
            }
        } // end of diagonals (l-r)
        
        // right to left
        for (a = 5; a >= 3; a--) {
            for (b = 6; b >= 0; b--) {
                if ((gameArray[a][b] == 'X') && (gameArray[a-1][b-1] == 'X') &&
                    (gameArray[a-2][b-2] == 'X') && (gameArray[a-3][b-3] == 'X')) {

                        // to cancel other diagonal patterns
                        if (diagonalWinner == false) {
                            hasWinner = true;
                            diagonalWinner = true;
                            printWinner(player1Turn, row, col, gameArray, player1, player2);
                            break;
                        }

                }
                
                /////////////////////////////////////////////////

                if ((gameArray[a][b] == 'O') && (gameArray[a-1][b-1] == 'O') &&
                    (gameArray[a-2][b-2] == 'O') && (gameArray[a-3][b-3] == 'O')) {

                        if (diagonalWinner == false) {
                            hasWinner = true;
                            diagonalWinner = true;
                            printWinner(player1Turn, row, col, gameArray, player1, player2);
                            break;
                        }
                }
            }
        } // end of diagonals (r-l)

        // DRAW
        if (moves == 42 && hasWinner == false) {
            cout << endl;
            cout << "\t\t\t\t\t\t---------------------------------------------------------\n\n";
            cout << "\t\t\t\t\t\t\t\t\t" << "\e[1mIt's a draw!\e[0m\n";
            cout << "\t\t\t\t\t\t\t\t\t" << player1.nickname << "'s Score: " << player1.score << endl;
            cout << "\t\t\t\t\t\t\t\t\t" << player2.nickname << "'s Score: " << player2.score;
            cout << "\n\n\t\t\t\t\t\t---------------------------------------------------------\n";
            printBoard(row, col, gameArray, player1, player2);
            cout << "\n\t\t\t\t\t\t\t\t"; system("pause"); system("cls"); 
            hasWinner = true; // just for the sake to end the game...
            break;
        }

    } while (hasWinner != true);

}

// For block power up; if not activated, it will just run the else statement.
void blockPowerUp(bool& player1Turn, bool& player2Turn, Player& player1, Player& player2, int& moves) {

    if (player1Turn == true && player2Turn == false) {
        if (player1.blockMoves != 2) {
            player1Turn = true;
            player2Turn = false;
            player1.blockMoves++;
            moves++;
            player1.powerUpPlaceHolder[0] = 'w'; player2.powerUpPlaceHolder[0] = 'w'; // to show the color after turn
            system("cls");
        }

        else {
            player1Turn = false;
            player2Turn = true;
            moves++;
            player1.powerUpPlaceHolder[0] = 'w'; player2.powerUpPlaceHolder[0] = 'w'; // to show the color after turn
            system("cls");
        }
    }

    else {
        if (player2.blockMoves != 2) {
            player2Turn = true;
            player1Turn = false;
            player2.blockMoves++;
            moves++;
            player1.powerUpPlaceHolder[0] = 'w'; player2.powerUpPlaceHolder[0] = 'w'; // to show the color after turn
            system("cls");
        }

        else {
            player2Turn = false;
            player1Turn = true;
            moves++;
            player1.powerUpPlaceHolder[0] = 'w'; player2.powerUpPlaceHolder[0] = 'w'; // to show the color after turn
            system("cls");
        }
    }
}

void printBoard(int& row, int& col, char gameArray[6][7], Player& player1, Player& player2) {

    cout << "\n\t\t\t\t>>=====================================================================================<<\n\n";

    // this will run after assigning the char '-' to w of player1/player2
    if (player1.powerUpPlaceHolder[0] == '-' || player2.powerUpPlaceHolder[0] == '-') {
        cout << "\n\t\t\t\t\t\t----1-------2-------3-------4-------5-------6-------7----\n";
        for (row = 0; row < 6; row++) {
            cout << "\n\t\t\t\t\t\t|   ";

            for (col = 0; col < 7; col++) {
                cout << gameArray[row][col] << "   |   ";
            }
            cout << "\n\t\t\t\t\t\t---------------------------------------------------------";
            cout << endl;

        }

    }

    else {
        cout << "\n\t\t\t\t\t\t----1-------2-------3-------4-------5-------6-------7----\n";
        for (row = 0; row < 6; row++) {
            cout << "\n\t\t\t\t\t\t|   ";

            for (col = 0; col < 7; col++) {

                if (gameArray[row][col] == 'X') {
                    cout << "\033[1;32m" << gameArray[row][col] << "\033[0m   |   ";
                }

                else if (gameArray[row][col] == 'O') {
                    cout << "\033[1;33m" << gameArray[row][col] << "\033[0m   |   ";
                }
 
                else {
                    cout << gameArray[row][col] << "   |   ";
                }

            }
            cout << "\n\t\t\t\t\t\t---------------------------------------------------------";
            cout << endl;
        }
    }

    cout << "\n\n\t\t\t\t>>=====================================================================================<<\n";
}

void printWinner(bool& player1Turn, int& row, int& col, char gameArray[6][7], 
        Player& player1, Player& player2) {
        if (player1Turn == false) {
            player1.score++;
            cout << endl;
            cout << "\t\t\t\t\t\t\033[1;32m---------------------------------------------------------\033[0m\n\n";
            cout << "\033[1;32m\t\t\t\t\t\t\t\t\t" << player1.nickname << " wins!\033[0m\n"; 
            cout << "\t\t\t\t\t\t\t\t\t" << player1.nickname << "'s Score: " << player1.score << endl;
            cout << "\t\t\t\t\t\t\t\t\t" << player2.nickname << "'s Score: " << player2.score;
            cout << "\n\n\t\t\t\t\t\t\033[1;32m---------------------------------------------------------\033[0m\n";
            printBoard(row, col, gameArray, player1, player2);
            cout << "\n\t\t\t\t\t\t\t\t"; system("pause"); system("cls");
        }
        
        else {
            player2.score++;
            cout << endl;
            cout << "\t\t\t\t\t\t\033[1;33m---------------------------------------------------------\033[0m\n\n";
            cout << "\033[1;33m\t\t\t\t\t\t\t\t\t" << player2.nickname << " wins!\033[0m\n";
            cout << "\t\t\t\t\t\t\t\t\t" << player1.nickname << "'s Score: " << player1.score << endl;
            cout << "\t\t\t\t\t\t\t\t\t" << player2.nickname << "'s Score: " << player2.score;
            cout << "\n\n\t\t\t\t\t\t\033[1;33m---------------------------------------------------------\033[0m\n";
            printBoard(row, col, gameArray, player1, player2);
            cout << "\n\t\t\t\t\t\t\t\t"; system("pause"); system("cls"); 
        }        
}

void continueGame(bool& continueLP, bool& hasWinner, int& row, int& col, char gameArray[6][7], 
                int& moves, int gameArrayIterate[7], int gameArrayColMoves[7], Player& player1, Player& player2) {

    // Loop for "Another Game" Option
    char decideLP;
    do {   
        cout << "\n\n\n"
                << "\t\t\t\t\t  ____            _   _                    ___ " << endl 
                << "\t\t\t\t\t / ___|___  _ __ | |_(_)_ __  _   _  ___  |__ \\" << endl
                << "\t\t\t\t\t| |   / _ \\| '_ \\| __| | '_ \\| | | |/ _ \\   / /" << endl 
                << "\t\t\t\t\t| |__| (_) | | | | |_| | | | | |_| |  __/  |_| " << endl 
                << "\t\t\t\t\t \\____\\___/|_| |_|\\__|_|_| |_|\\__,_|\\___|  (_)" << endl;
        
        cout << "\n\n\t\t\t\t\tDo you want another game? [Y/N]: "; cin >> decideLP; cin.ignore(INT_MAX, '\n');

        if (decideLP == 'N' || decideLP == 'n') {
            continueLP = false;
            playerLog(player1, player2); // log player info

            // reset moves
            moves = 0;
            
            // reset blockmoves
            player1.blockMoves = 2;  player2.blockMoves = 2; 

            // reset powerups
            strcpy(player1.powerUp[0], "[W]hiten"); strcpy(player2.powerUp[0], "[W]hiten"); // whiten powerup
            strcpy(player1.powerUp[1], "[B]lock"); strcpy(player2.powerUp[1], "[B]lock"); // block powerup

            // reset bool
            hasWinner = false;

            // reset gameArray
            for (row = 0; row < 6; row++) {
                for (col = 0; col < 7; col++) {
                    gameArray[row][col] = '-';
                }
            }
            
            // reset gameArrayIterate and Moves
            int reset;
            for (reset = 0; reset < 7; reset++) {
                gameArrayIterate[reset] = 5;
                gameArrayColMoves[reset] = 0;
            }

            system("cls");
            break;
        }

        else if (decideLP == 'Y' || decideLP == 'y') {
            // reset moves
            moves = 0;
            
            // reset blockmoves
            player1.blockMoves = 2;  player2.blockMoves = 2; 

            // reset powerups
            strcpy(player1.powerUp[0], "[W]hiten"); strcpy(player2.powerUp[0], "[W]hiten"); // whiten powerup
            strcpy(player1.powerUp[1], "[B]lock"); strcpy(player2.powerUp[1], "[B]lock"); // block powerup

            // reset bool
            hasWinner = false;

            // reset gameArray
            for (row = 0; row < 6; row++) {
                for (col = 0; col < 7; col++) {
                    gameArray[row][col] = '-';
                }
            }
            
            // reset gameArrayIterate and Moves
            int reset;
            for (reset = 0; reset < 7; reset++) {
                gameArrayIterate[reset] = 5;
                gameArrayColMoves[reset] = 0;
            }
            
            system("cls");
            break;
        }

        else {
            cout << "\t\t\t\t\tInvalid input. " << endl;
            cout << "\n\t\t\t\t\t"; system("pause"); system("cls");
            continueLP = true;
        }

    } while ((decideLP != 'Y' || decideLP != 'y') && (decideLP != 'N' || decideLP != 'n'));
}

// PLAYER LOG [BACKEND]
void playerLog(Player& player1, Player& player2) {

    ofstream logPlayerScores;

    logPlayerScores.open("C:\\Users\\pacet\\OneDrive\\Documents\\GitHub\\connect4\\playerLog.txt", ios::app);

    // appending to file
    if (!logPlayerScores.is_open()) {
        cout << "Error while logging player scores.";
    }

    else {
        time_t t = time(NULL);
        char* string_t = ctime(&t);

        logPlayerScores << string_t;
        logPlayerScores << player1.nickname << ": " << player1.score << "|" << player2.nickname << ": " << player2.score << endl << endl;
    }

    logPlayerScores.close();
}

// GAME MECHANICS OPTION
void sub_GM() {
    cout << "\n\n\n";
    cout << "\t\t\t\t\t  ____                        __  __           _                 _          \n"
         << "\t\t\t\t\t / ___| __ _ _ __ ___   ___  |  \\/  | ___  ___| |__   __ _ _ __ (_) ___ ___ \n"
         << "\t\t\t\t\t| |  _ / _` | '_ ` _ \\ / _ \\ | |\\/| |/ _ \\/ __| '_ \\ / _` | '_ \\| |/ __/ __|\n"
         << "\t\t\t\t\t| |_| | (_| | | | | | |  __/ | |  | |  __/ (__| | | | (_| | | | | | (__\\__ \\ \n"
         << "\t\t\t\t\t \\____|\\__,_|_| |_| |_|\\___| |_|  |_|\\___|\\___|_| |_|\\__,_|_| |_|_|\\___|___/\n\n";

    cout << "\t\t\t\t\t\e[1m What is Connect4?\e[0m\n\n";
    cout << "\t\t\t\t\t Connect4 is a two-player game with the objective of winning by connecting discs \n"
            "\t\t\t\t\t vertically, horizontally, or diagonally. This game is based on the traditional game \n"
            "\t\t\t\t\t \"four in a row,\" . Other than being a fun game, Connect4 requires \n "
            "\t\t\t\t\t problem-solving skills and tactics for players to win." << endl;

    cout << "\n\t\t\t\t\t As a text-based game using C++, discs are represented with 'X' and 'O' ('X' for player one, \n"
            "\t\t\t\t\t 'O' for player two). Each slot is represented by '-'s, making it easier for the players to \n"
            "\t\t\t\t\t see the empty slots. Moreover, these slots are separated using the \"|\" symbol. In terms \n"
            "\t\t\t\t\t of the game mechanics, players are able to enter their nicknames before starting to determine \n"
            "\t\t\t\t\t player one and player two. They may choose who will be the first one to draw. However, they \n"
            "\t\t\t\t\t may also choose the random feature that will let the game decide who will be the first to draw. \n"

            "\n\t\t\t\t\t\e[1m [MUST READ] \e[0m \n"
            "\t\t\t\t\t The unique thing is that this game contains power-ups. If player chooses [W]hiten, the color of \n"
            "\t\t\t\t\t of the board will turn white for the next player that will be drawing. Then, it will go back to \n"
            "\t\t\t\t\t a colored bored after drawing. On the other hand, choosing [B]lock will block the other player \n"
            "\t\t\t\t\t from drawing his pick. This means that the player who used this power-up will draw 2 times. \n"
            "\t\t\t\t\t The first one to connect slots vertically, horizontally, or diagonally wins." << endl;

    cout << "\n\t\t\t\t\t "; system("pause");
    system("cls");

    cout << "\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\e[1m Point System\e[0m\n\n";
    cout << "\t\t\t\t\t The player who wins each round will automatically receive 1 point.\n";
    cout << "\t\t\t\t\t Players have the option to continue the game by choosing the 'continue' option.\n";
    cout << "\t\t\t\t\t The scores of each player will be saved via file streaming.\n";

    cout << "\n\t\t\t\t\t "; system("pause");
    system("cls");

    cout << "\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\e[1m Game Process\e[0m\n\n";
    cout << "\t\t\t\t\t At the start of the game, Player 1 and Player 2 will be able to enter their nicknames. \n"
            "\t\t\t\t\t After entering, they will be greeted with a home page that contains a set of options such as \n"
            "\t\t\t\t\t \"Let's play!\", \"Game Mechanics\", \"About\", and \"Exit\".\n\n";

    cout << "\t\t\t\t\t \"Let's Play\" is the option to play the actual game. Players can start by choosing who will be \n"
            "\t\t\t\t\t the first to draw, or select \"random\" to let the program choose randomly. To win, players must \n"
            "\t\t\t\t\t connect four slots with their discs vertically, horizontally, or diagonally. After each round, \n"
            "\t\t\t\t\t players can choose to continue the game by starting a new round while keeping the scores intact, \n"
            "\t\t\t\t\t or end the game, which will redirect them to the home page.\n";

    cout << "\n\t\t\t\t\t "; system("pause");
    system("cls");
}

// HELP OPTION
void sub_ABT() {
    cout << "\n\n\n\n\n";
    cout << "\t\t\t\t\t    _    _                 _     _   _             ____                      " << endl
         << "\t\t\t\t\t   / \\  | |__   ___  _   _| |_  | |_| |__   ___   / ___| __ _ _ __ ___   ___ " << endl
         << "\t\t\t\t\t  / _ \\ | '_ \\ / _ \\| | | | __| | __| '_ \\ / _ \\ | |  _ / _` | '_ ` _ \\ / _ \\" << endl
         << "\t\t\t\t\t / ___ \\| |_) | (_) | |_| | |_  | |_| | | |  __/ | |_| | (_| | | | | | |  __/" << endl
         << "\t\t\t\t\t/_/   \\_\\_.__/ \\___/ \\__,_|\\__|  \\__|_| |_|\\___|  \\____|\\__,_|_| |_| |_|\\___|" << endl;
    
    cout << "\n\t\t\t\t\t The Connect4 project, developed in the C++ language, is the brainchild of \e[1mJoaquin Paolo Pacete\e[0m, a student \n"
            "\t\t\t\t\t enrolled in CpE231. This undertaking represents a significant milestone in the fulfillment of the Finals  \n"
            "\t\t\t\t\t for the course 'Programming Logic and Design', overseen by the esteemed Professor Einstein D. Yong." << endl;

    cout << "\n\t\t\t\t\t Through this project, Joaquin showcases proficiency in both C++ programming and logical design, delivering \n"
            "\t\t\t\t\t an interactive and engaging rendition of the classic Connect Four game." << endl;

    cout << "\n\t\t\t\t\t "; system("pause");
    system("cls");
}

// FEEDBACK OPTION
void sub_FB() {

    char feedbackInput[500];
    ofstream feedbackOutFile;

    do {
        cout << "\n\n\n\t\t\t\t   _____                                             _____ \n"
             << "\t\t\t\t  ( ___ )                                           ( ___ )\n"
             << "\t\t\t\t   |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   |\n"
             << "\t\t\t\t   |   |  _____             _ _                _     |   |\n"
             << "\t\t\t\t   |   | |  ___|__  ___  __| | |__   __ _  ___| | __ |   |\n"
             << "\t\t\t\t   |   | | |_ / _ \\/ _ \\/ _` | '_ \\ / _` |/ __| |/ / |   |\n"
             << "\t\t\t\t   |   | |  _|  __/  __/ (_| | |_) | (_| | (__|   <  |   |\n"
             << "\t\t\t\t   |   | |_|  \\___|\\___|\\__,_|_.__/ \\__,_|\\___|_|\\_\\ |   |\n"
             << "\t\t\t\t   |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___|\n"
             << "\t\t\t\t  (_____)                                           (_____)\n"
             << "\t\t\t\t\t\t" << "We'd like to know your side." << endl; 

    // input file stream here (ofstream)

        cout << "\n\n\t\t\e[1mType here (Up to 150 characters only): \e[0m"; 
        cin.getline(feedbackInput, sizeof(feedbackInput));

        if (strlen(feedbackInput) > 150) {
            cout << "\n\t\tYou have entered more than 150 characters. Press \e[1mENTER\e[0m to continue." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores all characters exceeding 150
            system("cls");
        }

        else if (strlen(feedbackInput) == 0) {
            cout << "\n\t\tInput is empty. Press \e[1mENTER\e[0m to continue." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');// ignores all characters exceeding 150
            system("cls");

        }

        else {
            // accessing feedback.txt file
            feedbackOutFile.open("C:\\Users\\pacet\\OneDrive\\Documents\\GitHub\\connect4\\playerFeedback.txt", ios::app);

            // appending to file
            if (!feedbackOutFile.is_open()) {
                cout << "\n\t\terror while opening the file." << endl;
            }
            else {
                feedbackOutFile << "FEEDBACK: ";
                feedbackOutFile << feedbackInput << endl << endl;
                cout << "\n\t\tThank you for your feedback!" << endl;
            }

            feedbackOutFile.close();
            cout << endl << endl; 
            cout << "\n\t\t"; system("pause");
            system("cls");
        }

    } while (strlen(feedbackInput) > 150 || strlen(feedbackInput) == 0);
    
}

//  EXIT OPTION
void sub_EXT(bool& gameContinue) {
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "\t\t\t\t\t\t" << "\e[1mThank you for playing Connect 4!\e[0m" << endl; 
    cout << "\t\t\t\t\t   ____                 _   _                _" << endl
        << "\t\t\t\t\t  / ___| ___   ___   __| | | |__  _   _  ___| |" << endl
        << "\t\t\t\t\t | |  _ / _ \\ / _ \\ / _` | | '_ \\| | | |/ _ \\ |" << endl
        << "\t\t\t\t\t | |_| | (_) | (_) | (_| | | |_) | |_| |  __/_|" << endl
        << "\t\t\t\t\t  \\____|\\___/ \\___/ \\__,_| |_.__/ \\__, |\\___(_)" << endl
        << "\t\t\t\t\t                                  |___/        ";
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl;

    // Change Boolean to False
    gameContinue = false;
}
