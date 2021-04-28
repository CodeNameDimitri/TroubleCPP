//
//  main.cpp
//  CS151_ProjectB
//
//  Created by Dimitri Labissiere on 4/13/21.
//  Copyright © 2021 Dimitri Labissiere. All rights reserved.
//

#include <iostream> //used for input and output
#include <cstdlib> //used for rand()/srand() for dice roll
#include <string> //used for to_string
#include <ctime> //used for seeding rand() with system time
using namespace std;

struct player //creates all players and their required params for manipulation
{
    bool isStartingPlayer, isCurrentPlayer, isFinished, isWinner; //determines player's state, whether it's their turn, they've won or finished, et cetera
    bool peg1Finished, peg2Finished, peg3Finished, peg4Finished; //determines if player's peg location is over the finish line playerPos[23]
    int peg1Position, peg2Position, peg3Position, peg4Position; //used to move players around the board's slots
} Red, Green, Blue, Yellow;

void Game(); //required func; calls display, setup, can create new game and more
void SetupGame(); //chooses starting player and lets them make their first move
void Display(bool gameStarted, int dieRoll, int currPlayer, int selection, player& Red, player& Blue, player& Green, player& Yellow); //required func; display board, moves pegs and displays player turn and game status
int PegSelection(); //prompts users to select their peg
void MoveSelectedPeg(player& currPlayer, player& player2, player& player3, player& player4, int Selection, int numOfMoves); //main logic of gameplay; used to move peg a given number of places around the board if it match a certain condition
int rollDie(); //randomly returns int; simulates die roll
void NewGamePrompt(); // allows for new game to be started without restarting application

int main(int argc, const char * argv[]){
    Game(); //required call
    return 0;
}

void Game()
{
    //create random seed using system time
    srand((unsigned int)time(NULL));
    
    //display project info
     cout << "Name: Dimitri Labissiere" << endl
         << "Assignment: Project - Part B" << endl
        << "Category: Trouble" << endl
        << "Game Rules: https://www.ultraboardgames.com/trouble/game-rules.php (Not definitive)\n\n" << endl;
    
    cout << "To determine starting player, your turn must be 6. Note: You can end game by entering, \'0\', when prompted for an selection." << endl;
    SetupGame();
    
    bool isGameOver = false; //used to end func once all players have finished
    bool shouldDisplayWinnersPrompt = true; //determines one sole winner
    int selectedPeg; //stores user peg selection
    int die; //stores die roll value
    while(!isGameOver)
    {
        
        if (Red.isCurrentPlayer && Red.isFinished == false) //checks if its the players turn and if they haven't crossed the finish line
        {
            selectedPeg = PegSelection();
            die = rollDie();
            MoveSelectedPeg(Red, Green, Blue, Yellow, selectedPeg, die); //moves selected peg a randomly determine number of spaces
            
            Display(true, die, 1, selectedPeg, Red, Blue, Green, Yellow); //displays board with the selected peg at appropriate location
            
            if (die == 6) //according Trouble's rules if user rolls a 6, they get an extra turn
            {
                cout << endl << "Red: Since you rolled a 6, you get one extra turn!" << endl;
                selectedPeg = PegSelection();
                die = rollDie();
                MoveSelectedPeg(Red, Green, Blue, Yellow, selectedPeg, die);
            }
            
            //makes following player the current player and relinquishes current privelege from red pegs
            Red.isCurrentPlayer = false;
            Green.isCurrentPlayer = true;
            
        }
        
        else if (Green.isCurrentPlayer && Green.isFinished == false) //checks if its the players turn and if they haven't crossed the finish line
        {
            selectedPeg = PegSelection();
            die = rollDie();
            MoveSelectedPeg(Green, Red, Blue, Yellow, selectedPeg, die); //moves selected peg a randomly determine number of spaces
            
            Display(true, die, 2, selectedPeg, Red, Blue, Green, Yellow); //displays board with the selected peg at appropriate location
            
            if (die == 6) //according Trouble's rules if user rolls a 6, they get an extra turn
            {
                cout << endl << "Green: Since you rolled a 6, you get one extra turn!" << endl;
                selectedPeg = PegSelection();
                die = rollDie();
                MoveSelectedPeg(Green, Red, Blue, Yellow, selectedPeg, die);
            }
            
            //makes following player the current player and relinquishes current privelege from green pegs
            Green.isCurrentPlayer =  false;
            Blue.isCurrentPlayer = true;
        }
        
        else if (Blue.isCurrentPlayer && Blue.isFinished == false) //checks if its the players turn and if they haven't crossed the finish line
        {
            selectedPeg = PegSelection();
            die = rollDie();
            MoveSelectedPeg(Blue, Red, Green, Yellow, selectedPeg, die); //moves selected peg a randomly determine number of spaces
            
            Display(true, die, 3, selectedPeg, Red, Blue, Green, Yellow); //displays board with the selected peg at appropriate location
            
            if (die == 6) //according Trouble's rules if user rolls a 6, they get an extra turn
            {
                cout << endl << "Blue: Since you rolled a 6, you get one extra turn!" << endl;
                selectedPeg = PegSelection();
                die = rollDie();
                MoveSelectedPeg(Blue, Red, Green, Yellow, selectedPeg, die);
            }
            
            //makes following player the current player and relinquishes current privelege from blue pegs
            Blue.isCurrentPlayer =  false;
            Yellow.isCurrentPlayer = true;
        }
        
        else if (Yellow.isCurrentPlayer && Yellow.isFinished == false) //checks if its the players turn and if they haven't crossed the finish line
        {
            selectedPeg = PegSelection();
            die = rollDie();
            MoveSelectedPeg(Yellow, Red, Green, Blue, selectedPeg, die); //moves selected peg a randomly determine number of spaces
            
            Display(true, die, 4, selectedPeg, Red, Blue, Green, Yellow); //displays board with the selected peg at appropriate location
            
            if (die == 6) //according Trouble's rules if user rolls a 6, they get an extra turn
            {
                cout << endl << "Yellow: Since you rolled a 6, you get one extra turn!" << endl;
                selectedPeg = PegSelection();
                die = rollDie();
                MoveSelectedPeg(Yellow, Red, Green, Blue, selectedPeg, die);
            }
            
            //makes following player the current player and relinquishes current privelege from yellow pegs
            Yellow.isCurrentPlayer =  false;
            Red.isCurrentPlayer = true;
        }
        
        
           if (shouldDisplayWinnersPrompt) //determines if code should crown a winner, if possible; only one user is allowed to be a winner, no rank positions [1st, 2nd, 3rd... etc]
           {
               if (Red.isWinner)
               {
                   cout << endl << "RED IS THE FIRST TO THE FINISH! THEY ARE THE WINNERS!"
                   << "But the game isn't over yet, keep playing until all your pegs have reached the finish!" << endl;
                   shouldDisplayWinnersPrompt = false;
               }
               else if (Green.isWinner)
               {
                   cout << endl << "GREEN IS THE FIRST TO THE FINISH! THEY ARE THE WINNERS!"
                   << "But the game isn't over yet, keep playing until all your pegs have reached the finish!" << endl;
                   shouldDisplayWinnersPrompt = false;
               }
               else if (Blue.isWinner)
               {
                   cout << endl << "BLUE IS THE FIRST TO THE FINISH! THEY ARE THE WINNERS!"
                   << "But the game isn't over yet, keep playing until all your pegs have reached the finish!" << endl;
                   shouldDisplayWinnersPrompt = false;
               }
               else if (Yellow.isWinner)
               {
                   cout << endl << "RED IS THE FIRST TO THE FINISH! THEY ARE THE WINNERS!"
                   << "But the game isn't over yet, keep playing until all your pegs have reached the finish!" << endl;
                   shouldDisplayWinnersPrompt = false;
               }
           }
        
        if (Red.isFinished && Red.isWinner == false) //announces finish, if not the first to win
        {
            cout << endl << "RED HAS REACHED THE FINISH!!" << endl;
        }
        
        if (Green.isFinished && Green.isWinner == false) //announces finish, if not the first to win
        {
            cout << endl << "GREEN HAS REACHED THE FINISH!!" << endl;
        }
        
        if (Blue.isFinished && Blue.isWinner == false) //announces finish, if not the first to win
        {
            cout << endl << "BLUE HAS REACHED THE FINISH!!" << endl;
        }
        
        if (Yellow.isFinished && Yellow.isWinner == false) //announces finish, if not the first to win
        {
            cout << endl << "YELLOW HAS REACHED THE FINISH!!" << endl;
        }
        
        if (Red.isFinished && Green.isFinished && Blue.isFinished && Yellow.isFinished) //announces game over, when all player have crossed the finished & ends loop
        {
            cout << endl << "ALL PLAYERS HAVE REACHED THE FINISH!! GAME IS OVER :)" << endl;
            isGameOver = true;
        }
    }
    
    NewGamePrompt(); //asks users if they want to start a new game
    
}

void SetupGame()
{
    int selectedPeg;
    Display(false, 0, 0, 0, Red, Blue, Green, Yellow); //displays blank board with no player selected or pegs on game board
    
    int die;
    bool playerSelected = false;
    
    while (!playerSelected) //loop while player has not been selected
    {
        die = rollDie();
        if (die != 6) //according to Trouble's rules, only the first play to get a die roll of six may go first
        {
            cout << "Red: " << die << endl;
        }
        else if (die == 6) //if die rolls a 6, this player is the player who makes the first move
        {
            cout << "Red: " << die << " >!STARTING PLAYER!<" << endl;
            Red.isStartingPlayer = true;
            playerSelected = true;
            break; //leave loop after starting player is selected
        }
        
        die = rollDie();
        if (die != 6) //according to Trouble's rules, only the first play to get a die roll of six may go first
       {
           cout << "Blue: " << die << endl;
       }
       else if (die == 6) //if die rolls a 6, this player is the player who makes the first move
       {
           cout << "Blue: " << die << " >!STARTING PLAYER!<" << endl;
           Blue.isStartingPlayer = true;
           playerSelected = true;
           break; //leave loop after starting player is selected
       }
        
        die = rollDie();
        if (die != 6) //according to Trouble's rules, only the first play to get a die roll of six may go first
       {
           cout << "Green: " << die << endl;
       }
       else if (die == 6) //if die rolls a 6, this player is the player who makes the first move
       {
           cout << "Green: " << die << " >!STARTING PLAYER!<" << endl;
           Green.isStartingPlayer = true;
           playerSelected = true;
           break; //leave loop after starting player is selected
       }
    
        die = rollDie();
        if (die != 6) //according to Trouble's rules, only the first play to get a die roll of six may go first
       {
           cout << "Yellow: " << die << endl;
       }
       else if (die == 6) //if die rolls a 6, this player is the player who makes the first move
       {
           cout << "Yellow: " << die << " >!STARTING PLAYER!<" << endl;
           Yellow.isStartingPlayer = true;
           playerSelected = true;
           break; //leave loop after starting player is selected
       }
    }

    if (Red.isStartingPlayer) //allows starting player to select their desired peg to move a random number of spaces on board
    {
        cout << endl << "Red: Since you rolled a 6, you get to go first!" << endl;
        selectedPeg = PegSelection();
        die = rollDie();
        MoveSelectedPeg(Red, Green, Blue, Yellow, selectedPeg, die);
        
        Display(true, die, 1, selectedPeg, Red, Blue, Green, Yellow);
        
        Green.isCurrentPlayer = true; //makes next player current, necessary for handoff to while loop in game()
    }
    
    else if (Green.isStartingPlayer) //allows starting player to select their desired peg to move a random number of spaces on board
    {
        cout << endl << "Green: Since you rolled a 6, you get to go first!" << endl;
        selectedPeg = PegSelection();
        die = rollDie();
        MoveSelectedPeg(Green, Red, Blue, Yellow, selectedPeg, die);
        
        Display(true, die, 2, selectedPeg, Red, Blue, Green, Yellow);
        
        Blue.isCurrentPlayer = true; //makes next player current, necessary for handoff to while loop in game()
    }
    
    else if (Blue.isStartingPlayer) //allows starting player to select their desired peg to move a random number of spaces on board
    {
        cout << endl << "Blue: Since you rolled a 6, you get to go first!" << endl;
        selectedPeg = PegSelection();
        die = rollDie();
        MoveSelectedPeg(Blue, Red, Green, Yellow, selectedPeg, die);
        
        Display(true, die, 3, selectedPeg, Red, Blue, Green, Yellow);
        
        Yellow.isCurrentPlayer = true; //makes next player current, necessary for handoff to while loop in game()
    }
    
    else if (Yellow.isStartingPlayer) //allows starting player to select their desired peg to move a random number of spaces on board
    {
        cout << endl << "Yellow: Since you rolled a 6, you get to go first!" << endl;
        selectedPeg = PegSelection();
        die = rollDie();
        MoveSelectedPeg(Yellow, Red, Green, Blue, selectedPeg, die);
        
        Display(true, die, 4, selectedPeg, Red, Blue, Green, Yellow);
        
        Red.isCurrentPlayer = true; //makes next player current, necessary for handoff to while loop in game()
    }
}

void Display(bool gameStarted, int dieRoll, int currPlayer, int selection, player& Red, player& Blue, player& Green, player& Yellow)
{
    string playerPos[24]; //creates string array with all possible space on board
    
    if (gameStarted) //only start placing pegs on board once game has begun
    {
        switch (currPlayer)
        {
            case 1: //red pegs
                if(selection == 1) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Red.peg1Position] = "R";
                }
                
                else if(selection == 2) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Red.peg2Position] = "R";
                }
                
                else if(selection == 3) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Red.peg3Position] = "R";
                }
                
                else if(selection == 4) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Red.peg4Position] = "R";
                }
            break;

            case 2: //green pegs
                if(selection == 1) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Green.peg1Position] = "G";
                }
                
                else if(selection == 2) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Green.peg2Position] = "G";
                }
                
                else if(selection == 3) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Green.peg3Position] = "G";
                }
                
                else if(selection == 4) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Green.peg4Position] = "G";
                }
            break;
                
            case 3: //blue pegs
                if(selection == 1) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Blue.peg1Position] = "B";
                }
                else if(selection == 2) //if players selects peg, move the pegs the provided number of places
                {
                    
                    playerPos[Blue.peg2Position] = "B";
                }
                else if(selection == 3) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Blue.peg3Position] = "B";
                }
                else if(selection == 4) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Blue.peg4Position] = "B";
                }
            break;

            case 4: //yellow pegs
                if(selection == 1) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Yellow.peg1Position] = "Y";
                }
                
                if(selection == 2) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Yellow.peg2Position] = "Y";
                }
                
                if(selection == 3) //if players selects peg, move the pegs the provided number of places
                {
                    
                    playerPos[Yellow.peg3Position] = "Y";
                }
                
                if(selection == 4) //if players selects peg, move the pegs the provided number of places
                {
                    playerPos[Yellow.peg4Position] = "Y";
                }
            break;
                
            default:
                //clears board due to no available selection
                for (int i = 0; i < 24; i++)
                {
                    playerPos[i] = "";
                }
                break;
        }
        
        cout << "Player: " << currPlayer << endl; //displays current player
    }

//    for (int i = 0; i < 24; i++) //removes residual pegs from any space they are currently not supposed to be occupying
//    {
//        //if current position is not filled by player peg, clear space on board; prevents board being filled with "R", "G", "B" and "Y" after player makes a move
//        if(playerPos[i] != playerPos[Red.peg1Position] || playerPos[i] != playerPos[Red.peg2Position] || playerPos[i] != playerPos[Red.peg3Position] || playerPos[i] != playerPos[Red.peg4Position]
//           || playerPos[i] != playerPos[Green.peg1Position] || playerPos[i] != playerPos[Green.peg2Position] || playerPos[i] != playerPos[Green.peg3Position] || playerPos[i] != playerPos[Green.peg4Position]
//           || playerPos[i] != playerPos[Blue.peg1Position] || playerPos[i] != playerPos[Blue.peg2Position] || playerPos[i] != playerPos[Blue.peg3Position] || playerPos[i] != playerPos[Blue.peg4Position]
//           || playerPos[i] != playerPos[Yellow.peg1Position] || playerPos[i] != playerPos[Yellow.peg2Position] || playerPos[i] != playerPos[Yellow.peg3Position] || playerPos[i] != playerPos[Yellow.peg4Position])
//        {
//            playerPos[i] = "";
//        }
//    }

    
    cout << "S/F" << endl; //depicts this space is the start and finish
    cout << "[" << playerPos[0] << "]" << "[" << playerPos[1] << "]" << "[" << playerPos[2] << "]" << "[" << playerPos[3] << "]" << "[" << playerPos[4] << "]" << "[" << playerPos[5] << "]" << "[" << playerPos[6] << "]" << endl;
    cout << "[" << playerPos[23] << "]" << "___________" << "[" << playerPos[7] << "]" << endl;
    cout << "[" << playerPos[22] << "]" << "___________" << "[" << playerPos[8] << "]" << endl;
    cout << "[" << playerPos[21] << "]" << "____[" << dieRoll << "]____" << "[" << playerPos[9] << "]" << endl;
    cout << "[" << playerPos[20] << "]" << "___________" << "[" << playerPos[10] << "]" << endl;
    cout << "[" << playerPos[19] << "]" << "___________" << "[" << playerPos[11] << "]" << endl;
    cout << "[" << playerPos[18] << "]" << "[" << playerPos[17] << "]" << "[" << playerPos[16] << "]" << "[" << playerPos[15] << "]" << "[" << playerPos[14] << "]" << "[" << playerPos[13] << "]" << "[" << playerPos[12] << "]\n" << endl;
    
    switch (currPlayer) //shows current player they can make a peg selection {**unfinished**}
    {
        case 1:
            cout << "S: [1][2][3][4] F: [][][][]" << endl;
            cout << "S: [G][G][G][G] F: [][][][]" << endl;
            cout << "S: [B][B][B][B] F: [][][][]" << endl;
            cout << "S: [Y][Y][Y][Y] F: [][][][]" << endl;
            break;
            
        case 2:
            cout << "S: [R][R][R][R] F: [][][][]" << endl;
            cout << "S: [1][2][3][4] F: [][][][]" << endl;
            cout << "S: [B][B][B][B] F: [][][][]" << endl;
            cout << "S: [Y][Y][Y][Y] F: [][][][]" << endl;
            break;
        
        case 3:
            cout << "S: [R][R][R][R] F: [][][][]" << endl;
            cout << "S: [G][G][G][G] F: [][][][]" << endl;
            cout << "S: [1][2][3][4] F: [][][][]" << endl;
            cout << "S: [Y][Y][Y][Y] F: [][][][]" << endl;
            break;
            
        case 4:
            cout << "S: [R][R][R][R] F: [][][][]" << endl;
            cout << "S: [G][G][G][G] F: [][][][]" << endl;
            cout << "S: [B][B][B][B] F: [][][][]" << endl;
            cout << "S: [1][2][3][4] F: [][][][]" << endl;
            break;
            
        default:
            cout << "S: [R][R][R][R] F: [][][][]" << endl;
            cout << "S: [G][G][G][G] F: [][][][]" << endl;
            cout << "S: [B][B][B][B] F: [][][][]" << endl;
            cout << "S: [Y][Y][Y][Y] F: [][][][]" << endl;
            break;
    }
    
    cout << endl << "Die Rolling...\n" << endl;
}

int PegSelection()
{
    int response;
    
    //prompts user to select peg, they can also end game/program
    cout << endl << "Select your peg: ";
    cin >> response;
    
    switch (response) {
        case 1: //player chooses peg 1
            return response;
            break;
        case 2: //player chooses peg 2
            return response;
            break;
        case 3: //player chooses peg 3
            return response;
            break;
        case 4: //player chooses peg 4
            return response;
            break;
        case 0: //player chooose to end game, so end program
            exit(0);
            break;
            
        default: //if response is invalid, display error message & allow user to try again
           cout << endl << "Err: Invalid Entry!" << endl;
            
            //prevent user input from causing an infinite loop due to response staying in buffer
            cin.clear();
            cin.ignore(10000, '\n');
            PegSelection();
            break;
    }
    
    return 0;
}

void MoveSelectedPeg(player& currPlayer, player& player2, player& player3, player& player4, int Selection, int numOfMoves)
{
    //array contains all pegs that not current player's
    int InactivePlayersPegPositions[12] = {player2.peg1Position, player2.peg2Position, player2.peg3Position, player2.peg4Position,
        player3.peg1Position, player3.peg2Position, player3.peg3Position, player3.peg4Position,
        player4.peg1Position, player4.peg2Position, player4.peg3Position, player4.peg4Position};
    
    bool isCurrentPlayerFinished = currPlayer.peg1Finished && currPlayer.peg2Finished && currPlayer.peg3Finished && currPlayer.peg4Finished; //determines if all of current player's pegs have crossed the finish line
    bool isPlayer2Finished = player2.peg1Finished && player2.peg2Finished && player2.peg3Finished && player2.peg4Finished; //determines if all of other player's pegs have crossed the finish line
    bool isPlayer3Finished = player3.peg1Finished && player3.peg2Finished && player3.peg3Finished && player3.peg4Finished; //determines if all of other player's pegs have crossed the finish line
    bool isPlayer4Finished = player4.peg1Finished && player4.peg2Finished && player4.peg3Finished && player4.peg4Finished; //determines if all of other player's pegs have crossed the finish line
    
    switch (Selection) {
    case 1:
            
        if (currPlayer.peg1Position += numOfMoves > 23) //according to Trouble's rule, player's can only finish if final move is exact amount spaces not more
        {
            cout << endl << "Cannot move peg. Move Exceeds Board Limits! Moves needed to reach finish: " << 23 - currPlayer.peg1Position << "." << endl;
        }
        else if (currPlayer.peg1Position += numOfMoves < 23) //allows player's peg to move a randomly provided number of spaces as long as space do not exceed board's/array size
        {
            currPlayer.peg1Position += numOfMoves;
        }
        else if (currPlayer.peg1Position += numOfMoves == 23) //player's peg has reached the finish line
        {
            currPlayer.peg1Position += numOfMoves;
            currPlayer.peg1Finished = true;
        }

        for (int i = 0; i < 12; i++) //according to Trouble's rules, player that overtake or share a space with an opponent, the current player send opponent(s) back to the starting position; loops checks if current player's peg has overtaken (greater than) or shares space (equal to) another opponent and sends them back to square one
        {
            if (currPlayer.peg1Position >= InactivePlayersPegPositions[i] && (InactivePlayersPegPositions[i] != 0 && InactivePlayersPegPositions[i] != 23))
            {
                InactivePlayersPegPositions[i] = 0;
            }
        }
        break;
    case 2:
        if (currPlayer.peg2Position += numOfMoves > 23) //according to Trouble's rule, player's can only finish if final move is exact amount spaces not more
        {
            cout << endl << "Cannot move peg. Move Exceeds Board Limits! Moves needed to reach finish: " << 23 - currPlayer.peg2Position << "." << endl;
        }
        else if (currPlayer.peg2Position += numOfMoves < 23) //allows player's peg to move a randomly provided number of spaces as long as space do not exceed board's/array size
        {
            currPlayer.peg2Position += numOfMoves;
        }
        else if (currPlayer.peg2Position += numOfMoves == 23) //player's peg has reached the finish line
        {
            currPlayer.peg2Position += numOfMoves;
            currPlayer.peg2Finished = true;
        }

        for (int i = 0; i < 12; i++)//according to Trouble's rules, player that overtake or share a space with an opponent, the current player send opponent(s) back to the starting position; loops checks if current player's peg has overtaken (greater than) or shares space (equal to) another opponent and sends them back to square one
        {
            if (currPlayer.peg2Position >= InactivePlayersPegPositions[i] && (InactivePlayersPegPositions[i] != 0 && InactivePlayersPegPositions[i] != 23))
            {
                InactivePlayersPegPositions[i] = 0;
            }
        }
        break;
    case 3:
        if (currPlayer.peg3Position += numOfMoves > 23) //according to Trouble's rule, player's can only finish if final move is exact amount spaces not more
        {
            cout << endl << "Cannot move peg. Move Exceeds Board Limits! Moves needed to reach finish: " << 23 - currPlayer.peg3Position << "." << endl;
        }
        else if (currPlayer.peg3Position += numOfMoves < 23) //allows player's peg to move a randomly provided number of spaces as long as space do not exceed board's/array size
        {
            currPlayer.peg3Position += numOfMoves;
        }
        else if (currPlayer.peg3Position += numOfMoves == 23) //player's peg has reached the finish line
        {
            currPlayer.peg3Position += numOfMoves;
            currPlayer.peg3Finished = true;
        }

        for (int i = 0; i < 12; i++)//according to Trouble's rules, player that overtake or share a space with an opponent, the current player send opponent(s) back to the starting position; loops checks if current player's peg has overtaken (greater than) or shares space (equal to) another opponent and sends them back to square one
        {
            if (currPlayer.peg3Position >= InactivePlayersPegPositions[i] && (InactivePlayersPegPositions[i] != 0 && InactivePlayersPegPositions[i] != 23))
            {
                InactivePlayersPegPositions[i] = 0; //returns other player's peg to starting line
            }
        }
       break;
    case 4:
        if (currPlayer.peg4Position += numOfMoves > 23) //according to Trouble's rule, player's can only finish if final move is exact amount spaces not more
        {
            cout << endl << "Cannot move peg. Move Exceeds Board Limits! Moves needed to reach finish: " << 23 - currPlayer.peg4Position << "." << endl;
        }
        else if (currPlayer.peg4Position += numOfMoves < 23) //allows player's peg to move a randomly provided number of spaces as long as space do not exceed board's/array size
        {
            currPlayer.peg4Position += numOfMoves;
        }
        else if (currPlayer.peg4Position += numOfMoves == 23) //player's peg has reached the finish line
        {
            currPlayer.peg4Position += numOfMoves;
            currPlayer.peg4Finished = true;
        }
            
        for (int i = 0; i < 12; i++)//according to Trouble's rules, player that overtake or share a space with an opponent, the current player send opponent(s) back to the starting position; loops checks if current player's peg has overtaken (greater than) or shares space (equal to) another opponent and sends them back to square one
        {
            if (currPlayer.peg4Position >= InactivePlayersPegPositions[i] && (InactivePlayersPegPositions[i] != 0 && InactivePlayersPegPositions[i] != 23))
            {
                InactivePlayersPegPositions[i] = 0;
            }
        }
        break;
        
    default:
            //do nothing, i guess ¯\_(ツ)_/¯
        break;
    }
    
    if (!currPlayer.isWinner || !player2.isWinner || !player3.isWinner || !player4.isWinner) //check if any player has won
    {
        if (isCurrentPlayerFinished == true && isPlayer2Finished == false && isPlayer3Finished == false && isPlayer4Finished == false ) //crowns current player as winner if all their pegs have crossed the finish before all other players
        {
            currPlayer.isFinished = true;
            currPlayer.isWinner = true;
        }
        else
        {
            currPlayer.isFinished = false;
            currPlayer.isWinner = false;
        }
    }
    else if (isCurrentPlayerFinished) //changes player status to finish, makes them unable to take a turn in game()'s while loop
    {
        currPlayer.isFinished = true;
    }
    else if (isPlayer2Finished) //changes player status to finish, makes them unable to take a turn in game()'s while loop
    {
        player2.isFinished = true;
    }
    else if (isPlayer3Finished) //changes player status to finish, makes them unable to take a turn in game()'s while loop
    {
        player3.isFinished = true;
    }
    else if (isPlayer4Finished) //changes player status to finish, makes them unable to take a turn in game()'s while loop
    {
        player4.isFinished = true;
    }

}

int rollDie()
{
    //randomly generates a number between 1 and 6, simulating a 6-sided die
    int numberRolled = rand() % 6 + 1;
    return numberRolled;
}

void NewGamePrompt()
{
    
    char response;
    
    //prompts player to determine if a new game is desired, otherwise ends program
    cout << endl << "Do you want to start a new game? Y or N" << endl << "Enter: ";
    cin >> response;
    
    switch (response) {
           case 'y':
           case 'Y':
                Game();
                 break;
                             
           case 'n':
           case 'N':
                exit(0);
                 break;
             
           default:
               cout << endl << "Err: Invalid Entry!" << endl;
                cin.clear();
                cin.ignore(10000, '\n');
               NewGamePrompt();
             break;
       }
}
