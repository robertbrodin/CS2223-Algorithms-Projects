//
//  main.cpp
//  DoubleTrouble
//
//  Created by Robert Brodin on 10/23/19.
//  My version of the popular game Nim
//  Algorithms, B Term 2019, Engling
//

/*
 “Double Trouble” is really a particular instantiation of the fundamental combinatorial game. What is the real name of the game, who “solved” it, and
 when? Where does it show up in popular culture? [2 bonus points]
 
 The real name of the game is Nim, and Nim theory (how to win Nim)was developed by Charles L. Boulton in 1901. Nim often appears in Algorthims class and as a popular childrens game. I had trouble finding many popular variations of the game. There are hundreds of variations though, which each take a slightly different approach.
 
 */
#include <iostream>
#include <list>
#include <cmath>
#include "DoubleTroubleBoard.cpp"

// Class Move is used to contain a color and number to remove. Is referenced in DoubleTroubleGameBoard.
class Move{
public:
    std::string color;
    int toRemove;
    Move(std::string colorToRemove, int numberToRemove){
        color = colorToRemove;
        toRemove = numberToRemove;
    }
};

// Class DoubleTroubleGameBoard is used to store the current size of each color.
// DoubleTroubleGameBoard is referenced in the main function.
class DoubleTroubleGameBoard{
    public:
        int greenSize;
        int yellowSize;
        int orangeSize;
        std::string lastPlayerString;
    // The class constructor:
    // initializes green (greenSize), as 3
    // initializes yellow (yellowSize), as 7
    // initializes orange (orangeSize), as 5
    DoubleTroubleGameBoard(){
        greenSize = 3;
        yellowSize = 7;
        orangeSize = 5;
    }
    
    // changeColorSize subtracts numberToRemove (an int) from the current value of the corresponding color given.
    // colorString is either green, yellow, or orange. Otherwise, the function does nothing.
    // TODO: Should produce an error! Maybe change the return value! Could possibly change it to a boolean and if it returns true the color is changed, if not, it is false. That would make sense.
    void changeColorSize(std::string colorString, int numberToRemove){
        // If a move is possible (meaning that the subtraction is greater than 0 and the color exists), then, change the variable
        if(movePossible(getNumberOfPieces(colorString), numberToRemove)){
            if(colorString == "green"){
                greenSize = greenSize - numberToRemove;
            }
            else if(colorString == "yellow"){
                yellowSize = yellowSize - numberToRemove;
            }
            else if(colorString == "orange"){
                orangeSize = orangeSize - numberToRemove;
            }
            else{
                // Do nothing. (meaning it stays the same)
            }
        }
    }
    
    // movePossible returns true if a move is possible (meaning that pieces - number > 0)
    bool movePossible(int currentNumberOfPieces, int numberToSubtract){
        return (currentNumberOfPieces - numberToSubtract >= 0);
    }
    
    // getNumberOfPieces returns the size of the given color (either "green", "yellow", or "orange")
    int getNumberOfPieces(std::string colorString){
        if(colorString == "green"){
            return greenSize;
        }
        else if(colorString == "yellow"){
            return yellowSize;
        }
        else if(colorString == "orange"){
            return orangeSize;
        }
        else{
            return 0;
        }
    }
    
    // isGameOver returns true if the game is over (meaning that there are no pieces left)
    bool isGameOver(){
        return (greenSize == 0 and yellowSize == 0 and orangeSize == 0);
    }
    
    // returns whether the given combinationOfPieces is present (for computer algorithm)
    // TODO: MY FUNCTION IS FLAWED
    bool certainCombinationOfPieces(int greenPieceTotal, int yellowPieceTotal, int orangePieceTotal){
        return (greenSize == greenPieceTotal and yellowSize == yellowPieceTotal and orangeSize == orangePieceTotal);
    }
    
    // winningMovePossible takes void and returns an empty move if non of the xor statements work.
    // If one of the xor statements is true, it returns a move with the (color - (other two colors xor).
    // This is using the nim-sum = 0 strategy.
     Move winningMovePossible(){
         if(greenSize > (yellowSize ^ orangeSize)){
             Move green("green", (greenSize - (yellowSize ^ orangeSize)));
         }
         else if(yellowSize > (greenSize ^ orangeSize)){
             Move yellow("yellow", (yellowSize - (greenSize ^ orangeSize)));
             return yellow;
         }
         else if(orangeSize > (greenSize ^ yellowSize)){
             Move orange("orange", (orangeSize - (greenSize ^ yellowSize)));
             return orange;
         }
         // If the position is not a xorsum
         else{
             Move n("n", 0);
             return n;
         }
         // Needed to include this line because of C++ requirements. Java would not require this, I think.
         Move n("n", 0);
         return n;
     }
};

// bool colorIsValid takes a color and returns true if the color is either green, yellow, or orange.
bool colorIsValid(std::string givenColor){
    return (givenColor == "green" or givenColor == "yellow" or givenColor == "orange");
}

// checkPossibleMove takes a board, a color, and a move (int) and returns true if the move is possible (if it is >= 0).
bool checkPossibleMove(DoubleTroubleGameBoard gameBoard, std::string color, int move){
    return (gameBoard.getNumberOfPieces(color) - move >= 0);
}

// Class Player is used to store information about who is playing the game and contains functions to test whether or not moves are possible.
class Player{
public:
    std::string userType;
    std::string name;
    bool isFirst;
    
    // Constructor for Player.
    Player(std::string type, std::string userName, bool first){
        userType = type;
        name = userName;
        isFirst = first;
    }
    
    // randomNum takes lower bound, a, and upper bound, b, and returns a random number in [a,b]
    int randomNum(int a, int b){
        return (rand() % a + b);
    }
    
    // setName sets the name of the player. Is used in the main() function.
    void setName(std::string nameToSet){
        name = nameToSet;
    }
    // playerTurn is used to get the user input and run a turn.
    // playerTurn checks whether a user is a human, or a computer.
    // playerTurn returns an updated gameBoard, with the new number of pieces (after a turn).
    DoubleTroubleGameBoard playerTurn(DoubleTroubleGameBoard gameBoard){
        // If the user is a human, take a color input and a number input,
        // then, subtract that number from the current number of pieces in the specified color.
        
        if(userType == "human"){
            // Gets the color that the user would like to remove (based on user input)
            std::string color;
            // While loop is used to make sure that the color the user inputs is correct.
            while(!colorIsValid(color)){
                std::cout << "\nWhat color would you like to remove?";
                std::cin >> color;
                if(!colorIsValid(color)){
                    std::cout << "Invalid color! Please give green, yellow, or orange!";
                }
            }
            std::cout << "\nColor: " << color << "\n";
            // Gets the number of pieces that the user would like to remove (based on user input)
            int numberToRemove = 8;
            
            // While loop is used to make sure that the number the user inputs is correct.
            while(!(gameBoard.getNumberOfPieces(color) - numberToRemove >= 0)){
                std::cout << "\nHow many of " << color << " would you like to remove?";
                std::cin >> numberToRemove;
                if(!(gameBoard.getNumberOfPieces(color) - numberToRemove >= 0)){
                    std::cout << "Choose a number less than or equal to: " << gameBoard.getNumberOfPieces(color) << " - Please, I'm begging you!!!!";
                }
            }
            // This line changes the number of the piece.
            gameBoard.changeColorSize(color, numberToRemove);
            // Makes the first chwracter of the color uppercase (for the ease of eyes)
            color[0] = toupper(color[0]);
            std::cout << "\n" << color << " is now set to " << gameBoard.getNumberOfPieces(color) << "\n";
            // Lastly, gameBoard is returned.
            return gameBoard;
        }
        /*
        Otherwise, if the user is a computer, then:
          1. The function generates a random number between one and three, which is used to select a color.
          2. The function then checks which color the random number is:
              0 - Green
              1 - Yellow
              2 - Orange
          3. The function also checks if there are any pieces of that color left. If not, the function uses a while loop and calls itself again, to calculate a new random number.
          4. If the function finds the color and there are pieces left, the computer generates a random number between one and the number of pieces left.
                 Example: if there are three pieces left in green, a number between one and three is generated.
          5. That number is then subtracted from the correct variable, using changeColorSize (part of the DoubleTroubleGameBoard class).
          6. Lastly, the updated gameBoard is returned.
         */
        else{
            bool isFinished = false;
            // While loop is used to check whether or not a mvoe is valid or calculated.
            while(!isFinished){
                
                Move n("n", 0);
                // If a winningMove is possible (meaning it does not equal "n", which the function returns when a winning move is not possible), make the winning move.
                if(gameBoard.winningMovePossible().color != n.color){
                    std::cout << "\nI see a winning move, human... " << gameBoard.winningMovePossible().color << ", " << gameBoard.winningMovePossible().toRemove;
                    gameBoard.changeColorSize(gameBoard.winningMovePossible().color, gameBoard.winningMovePossible().toRemove);
                    
                    isFinished = true;
                }
                // If a winning move is not possible, then make a random move.
                else{
                    // Generate a random color:
                    int colorRandomInt = randomNum(3, 0);
                    int subtractionRandomInt;
                    // If the color is green:
                    if(colorRandomInt == 0 and !(gameBoard.greenSize == 0)){
                        // Generates the subtraction from one to the size of green.
                        subtractionRandomInt = randomNum(gameBoard.greenSize, 1);
                        gameBoard.changeColorSize("green", subtractionRandomInt);
                        std::cout << "\nThe computer has removed " << subtractionRandomInt << " from green!\n";
                        isFinished = true;
                    }
                    // If the color is yellow:
                    else if(colorRandomInt == 1 and !(gameBoard.yellowSize == 0)){
                        subtractionRandomInt = randomNum(gameBoard.yellowSize, 1);
                        gameBoard.changeColorSize("yellow", subtractionRandomInt);
                        std::cout << "\nThe computer has removed " << subtractionRandomInt << " from yellow!\n";
                        isFinished = true;

                    }
                    // If the color is orange:
                    else if(colorRandomInt == 2 and !(gameBoard.orangeSize == 0)){
                        subtractionRandomInt = randomNum(gameBoard.orangeSize, 1);
                        gameBoard.changeColorSize("orange", subtractionRandomInt);
                        std::cout << "\nThe computer has removed " << subtractionRandomInt << " from orange!\n";
                        isFinished = true;
                  }
                    }
                }
            // return an updated gameBoard, which will be used to update the gameBoard in the main function.
                return gameBoard;
            }
    }
};

// Class Game will be used to check whether a Game is still going.
// Game will also store the person who goes first (a Player)
class Game {
public:
    bool isOver;
    Game(){
        isOver = false;
        //firstPlayer = player;
    }
};

int main(int argc, const char * argv[]){
    DoubleTroubleGameBoard doubleTroubleGameBoard;
    
    // Defines four variables used for either human v human, human v computer, or computer v computer.
    Player humanOne("human", "", false);
    Player humanTwo("human", "", false);
    Player computerOne("computer", "Hal", true);
    Player computerTwo("computer", "The Matrix", true);
    
    Game game;

    // Entering the first players' names/type.
    std::string firstPlayer;
    std::cout << "Type the first player (name or computer): "; // Type a number and press enter
    std::cin >> firstPlayer; // Get user input from the keyboard
    std::cout << "\nThe first player is: " << firstPlayer; // Display the input value
    std::list<Player> playerOrder;
    
    // Entering the second players' names/type.
    std::string secondPlayer;
    std::cout << "\nType the second player (name or computer): "; // Type a number and press enter
    std::cin >> secondPlayer; // Get user input from the keyboard
    std::cout << "\nThe second player is: " << secondPlayer; // Display the input value
    
    
    // Checks what the name or type of the user is. Unless the string is equal to computer, the user is a human.
    if(firstPlayer != "computer"){
        humanOne.isFirst = true;
        humanOne.setName(firstPlayer);
        playerOrder.push_front(humanOne);
    }
    else if(firstPlayer == "computer"){
        computerOne.isFirst = true;
        playerOrder.push_front(computerOne);
    }
    if(secondPlayer != "computer"){
        humanTwo.isFirst = false;
        humanTwo.setName(secondPlayer);
        playerOrder.push_back(humanTwo);
    }
    else if(secondPlayer == "computer"){
        computerTwo.isFirst = true;
        playerOrder.push_back(computerTwo);
    }

    std::cout << "\nGreen: " << doubleTroubleGameBoard.greenSize << " - Yellow: " << doubleTroubleGameBoard.yellowSize << " - Orange: " << doubleTroubleGameBoard.orangeSize;
    
    // While loop runs until the game is over, the players switch turns.
    while(!doubleTroubleGameBoard.isGameOver()){
        
        // Player one's move.
        doubleTroubleGameBoard = playerOrder.front().playerTurn(doubleTroubleGameBoard);
        std::cout << "\n" << playerOrder.back().name << "'s turn: ";
        std::cout << "Green: " << doubleTroubleGameBoard.greenSize << " - Yellow: " << doubleTroubleGameBoard.yellowSize << " - Orange: " << doubleTroubleGameBoard.orangeSize << "\n";
        if(doubleTroubleGameBoard.isGameOver()){
            doubleTroubleGameBoard.lastPlayerString = playerOrder.front().name;
            break;
        }
        
        // Player two's move.
        doubleTroubleGameBoard = playerOrder.back().playerTurn(doubleTroubleGameBoard);
        std::cout << "\n" << playerOrder.front().name << "'s turn: ";
        std::cout << "Green: " << doubleTroubleGameBoard.greenSize << " - Yellow: " << doubleTroubleGameBoard.yellowSize << " - Orange: " << doubleTroubleGameBoard.orangeSize << "\n";
        if(doubleTroubleGameBoard.isGameOver()){
            doubleTroubleGameBoard.lastPlayerString = playerOrder.back().name;
            break;
        }
    }
    std::cout << "\n-**********************-\n";
    std::cout << "The winner is: \n" << doubleTroubleGameBoard.lastPlayerString << "";
    std::cout << "\n-**********************-\n";

    return 0;
};
