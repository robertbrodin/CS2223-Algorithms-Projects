//
//  main.cpp
//  Arkenstone
//
//  Created by Robert Brodin on 11/19/19.
//  Algorithms, B Term 2019, Knapsack Problem
//

#include <iostream>
#include <vector>

using namespace std;


// Vault is used to store the matrix of gems.
class Vault{
public:
    // vaultPieces contains the matrix of number of gems for each column and row. The format is {vault0-{0, 1, 2, 3 (row values)}, vault-1{0, 1, 2, 3 (row values)}}
    vector<vector<int>> vaultPieces = {};
    
    // addColumnToVault takes a vector of integers and adds that vector to vault pieces (this is a column, considered vertical)
    void addColumnToVault(vector<int> column){
        vaultPieces.push_back(column);
    }
};

// Class SquareValue is used to hold all information for each square that is a vault.
class SquareValue{
public:
    int value = 0;
    int previous;
    vector<int> path;
    int xCoordinate;
    int yCoordinate;
    vector<int> squareValues = {};
    vector<SquareValue> possibleSquares = {};
    vector<SquareValue> finalSquare;
    SquareValue(int val){
        value = val;
        previous = 0;
        
    }
    
    // Displays the pieces in the matrix/square.
    vector<int> getPieces(){

        int last = squareValues[0];
        vector<int> pieces = {last};
        for(int i = 1; i < squareValues.size();i++){
            pieces.push_back(squareValues[i] - last);
            last = squareValues[i];
        }
        return pieces;
    }
    
};

// Class KnapsackArrayWith is used to store the information solve the knapsack problem.
class KnapsackArrayWith{
public:
    vector<vector<vector<SquareValue>>> knapsackArray = {};
    int matrixSizeX;
    int matrixSizeY;
    // Initializes an empty array that will hold square values.
    KnapsackArrayWith(int sizeX, int sizeY){
        matrixSizeX = sizeX;
        matrixSizeY = sizeY;
        for(int z=0;z<sizeX;z++){
            knapsackArray.push_back({});
            for(int b=0;b<sizeY;b++){
                // TODO: I think the issue is because of the class and having a list of empty classes.
                SquareValue temp(0);
                temp.path = {};
                temp.value = 0;
                vector<SquareValue> a = {};
                knapsackArray[z].push_back({});
                }
        }
    }
    
    // insertSquareIntoArray() takes a square to insert and sets the specified position equal to that.
    void insertSquareIntoArray(SquareValue squareToInsert, int xPosition, int yPosition){
        //knapsackArray[xPosition][0].push_back(positionDataVector);
        knapsackArray[xPosition][yPosition].push_back(squareToInsert);
    }
    
    // displayArray() displays all values in the knapsack problem.
    void displayArray(){
        for(int i = 0; i < knapsackArray.size(); i++){
            for(int j = 0; j < matrixSizeX; j++){
                for(int k = 0; k < knapsackArray[i][j].size(); k++){
                    cout << "Knapsack display: ";
                    cout << "Value: " << knapsackArray[i][j][k].value << " - " << knapsackArray[i][j][k].xCoordinate << "," << knapsackArray[i][j][k].yCoordinate << " - ";
                    }
                   cout << "\n";
            }
        }
    }
    
};

// Class KnapsackArrayWith is used to solve the knapsack problem.
class TreasurePath{
public:
    
    int matrixSizeX = 3;
    int matrixSizeY = 3;
    vector<int> startingLocation = {};
    vector<int> currentLocation;
    vector<vector<int>> path;
    int gemsCollected = 0;
    
    // Constructor is used to init the path, number of gems collected, and starting locations.
    TreasurePath(int xDimension, int yDimension, int startingColumn, Vault vault){
        matrixSizeX = xDimension;
        matrixSizeY = yDimension;
        startingLocation = {startingColumn, matrixSizeY - 1};
        currentLocation = {startingLocation[0], startingLocation[1]};
        path = {startingLocation};
        gemsCollected = gemsCollected + vault.vaultPieces[startingLocation[0]][startingLocation[1]];
    }
    
    // currentLocation is initialized as startingLocation. Will be changed as the program runs on.
    // atEnd is set to false once moved to row eight. moveToPiece will not work once it is true.
    bool atEnd = false;
    
    
    // generateKnapsackArray takes a vault and returns void.
    // generateKnapsackArray is used to solve the knapsack problem.
    // The function creates an empty matrix of squares and then does the knapsack problem (my iteration of it, ignoring weights and with the special moves).
    KnapsackArrayWith generateKnapsackArray(Vault vault, KnapsackArrayWith knapsackArray){
        
        
        KnapsackArrayWith finalKnapsack(8, 8);

        // Creating empty matrix.
        for(int column = 0;column < vault.vaultPieces.size(); column++){
            for(int row = 0;row < vault.vaultPieces[column].size();row++){
                SquareValue squareVaultPiece(vault.vaultPieces[column][row]);
                squareVaultPiece.xCoordinate = column;
                squareVaultPiece.yCoordinate = row;
                finalKnapsack.insertSquareIntoArray(squareVaultPiece, column, row);
            }
        }

        // Finding the max pieces of the child's parent. It's a top-down design where the max parent is the path. The row number is increased each time and the process is repeated. It gets larger and larger everytime.
        for(int columnCounter = 0; columnCounter < finalKnapsack.knapsackArray.size(); columnCounter++){
            for(int rowCounter = finalKnapsack.knapsackArray[columnCounter].size() - 1; rowCounter > 0; rowCounter--){
                int upVal = finalKnapsack.knapsackArray[columnCounter][rowCounter - 1][0].value;

                SquareValue hold = finalKnapsack.knapsackArray[columnCounter][rowCounter][0];
                //hold.currentPieceValue = hold.value;
                finalKnapsack.knapsackArray[columnCounter][rowCounter - 1][0].possibleSquares.push_back(hold);
                
                // Meaning going left is possible.
                if(!(columnCounter == 0)){
                    finalKnapsack.knapsackArray[columnCounter - 1][rowCounter - 1][0].possibleSquares.push_back(hold);
                }
                // Meaning going right is possible.
                if(!(columnCounter == finalKnapsack.knapsackArray.size() - 1)){
                    finalKnapsack.knapsackArray[columnCounter + 1][rowCounter - 1][0].possibleSquares.push_back(hold);

                }
            }
        }
        int row = finalKnapsack.knapsackArray[0].size() - 1;
        // Loops used to iterate through everything in the matrix.
        while(row > -1){
            int column = 0;
            while(column < finalKnapsack.knapsackArray.size()){
                SquareValue temp = finalKnapsack.knapsackArray[column][row][0];
                // If the possibleSquare is not empty, then find the highest possible parent.
                    if(!temp.possibleSquares.empty()){
                        vector<SquareValue> highestSquare = {temp.possibleSquares[0]}; // will this work? Comparing it to size of zero
                        for(int maxCount = 0; maxCount < temp.possibleSquares.size(); maxCount++){
                           // Arguably the most difficult part of the code, the following conditional checks the knapsack array's value at the index from possible squares. This needs to be done because the knapsack array is updated every time.
                            if(finalKnapsack.knapsackArray[temp.possibleSquares[maxCount].xCoordinate][temp.possibleSquares[maxCount].yCoordinate][0].value >= highestSquare[0].value){
                                highestSquare = {finalKnapsack.knapsackArray[temp.possibleSquares[maxCount].xCoordinate][temp.possibleSquares[maxCount].yCoordinate][0]};
                                
                            }
                             
                        }
                        // Adding important information for each square, such as the path, etc.
                        SquareValue newSquare = finalKnapsack.knapsackArray[highestSquare[0].xCoordinate][highestSquare[0].yCoordinate][0];
                        newSquare.squareValues.push_back(highestSquare[0].value);
                        highestSquare = {newSquare};
                        temp.finalSquare = {highestSquare};
                        vector<int> tempFinalPath = highestSquare[0].path;
                        vector<int> tempPath = {temp.xCoordinate, temp.yCoordinate};
                        tempPath.insert(tempPath.end(), tempFinalPath.begin(), tempFinalPath.end() );
                        temp.path = tempPath;
                        temp.squareValues = highestSquare[0].squareValues;
                        temp.value = temp.value + highestSquare[0].value;
                        
                        if(row == 0){
                            temp.squareValues.push_back(temp.value);
                        }

                        finalKnapsack.knapsackArray[column][row][0] = temp;
                    }
                    // If it's the first row
                    else{
                        SquareValue temp = finalKnapsack.knapsackArray[column][row][0];

                        finalKnapsack.knapsackArray[column][row][0] = temp;
                    }
        
                column++;
            }
 
                row--;
        }

        for(int please = 0; please < finalKnapsack.knapsackArray.size(); please++){
            cout << "\nMax values are: " << finalKnapsack.knapsackArray[please][0][0].value;
            vector<int> pieces = finalKnapsack.knapsackArray[please][0][0].getPieces();
            cout << "\nPieces: {";
            for(int k = 0; k < pieces.size();k++){
                cout << pieces[k] << ", ";
            }
            cout << "}\n";
        }
         
        return finalKnapsack;

    // Need a move function, takes a vault
        
    }
};


int main() {
    vector<TreasurePath> allPaths;
    Vault myVault;
    
    // Vault matrix is added.
    myVault.addColumnToVault({89, 46, 85, 22, 13, 31, 73, 79});
    myVault.addColumnToVault({70, 23, 52, 93, 78, 5, 38, 71});
    myVault.addColumnToVault({73, 99, 27, 68, 48, 63, 24, 13});
    myVault.addColumnToVault({83, 77, 5, 11, 19, 10, 49, 20});
    myVault.addColumnToVault({90, 10, 94, 56, 78, 32, 18, 34});
    myVault.addColumnToVault({22, 41, 91, 63, 11, 40, 6, 51});
    myVault.addColumnToVault({44, 1, 82, 49, 90, 14, 40, 93});
    myVault.addColumnToVault({92, 72, 62, 35, 94, 13, 74, 65});
     
    KnapsackArrayWith knap(8, 8);
    TreasurePath myTreasurePath(myVault.vaultPieces.size(), myVault.vaultPieces[0].size(), 0, myVault);
    KnapsackArrayWith newKnap = myTreasurePath.generateKnapsackArray(myVault, knap);
    
    // Finding the new max.
    SquareValue max = newKnap.knapsackArray[0][0][0];
    for(int findMax = 0; findMax < newKnap.knapsackArray.size(); findMax++){
        if(newKnap.knapsackArray[findMax][0][0].value > max.value){
            max = newKnap.knapsackArray[findMax][0][0];
        }
    }
    // I would like to note that I had to add one to the xCoordinate because of how I iterated my loop first.
    cout << "\nBilbo's starting position for the maximum path is: (" << (max.xCoordinate + 1) << ", " << max.yCoordinate << ").";
    
    vector<int> pieces =  max.getPieces();
    cout << "\nPath to get to " << max.value << ": {";
    for(int k = 0; k < pieces.size();k++){
        cout << pieces[k] << ", ";
    }
    cout << "\n\nThe max value is: " << max.value << "!";

    cout << "\n\nThe King has secreted the Arkenstone in Vault Seven, Row Seven, where there is one gem. Bilbo's path does not follow this, however, because he knows that he can maximize his profits in other ways, by taking a smarter path. Bilbo could go through 1, but he would not maximize his profits. Touching it would also likely get him killed (index out of bounds? not an issue but could be a funny way of being killed)";
    cout << "\n\n I may also have been mistaken about the phrasing of the problem. The arkenstone could also be at the end of the max path, which is vault 5 row 8";
    cout << "}\n";
    return 0;
}

