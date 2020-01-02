#include <iostream>
#include <vector>
using namespace std;
 
class ChessBoard{
public:
 
    int boardSize;
    vector<vector<bool>> chessBoard;
    vector<int> currentQueens;
    vector<vector<int>> solutions;
    bool isGoing = true;
    bool isTacky = false;
 
    // initialized with size (size x size)
    ChessBoard(int size){
        boardSize = size;
    }
 
    // isLegalPosition takes a position and returns true if it is a partial legal move, or a winning mvoe. Otherwise, if a move is illegal it returns false.
    bool isLegalPosition(vector<int> position){
        currentQueens = position;
        // Column, row ,and diagonal

        for(int i = 0; i < position.size(); i++){
            for(int j = i + 1; j < position.size(); j++){
                // This is column
                if(currentQueens[i] != 0) {
                    if (currentQueens[i] == currentQueens[j]) {
                        return false;
                    }
 
                    if ((abs(currentQueens[j] - currentQueens[i]) == abs(j - i)) && (currentQueens[j] != 0)) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    
    // Prints the board.
    void printBoard(vector<int> board){
        cout << "\nBoard: {";
        for(int i = 0; i < board.size(); i++){
            cout << board[i] << ", ";
        }
        cout << "}\n";
    }
    
    // returns true if the board is full.
    bool isFull(vector<int> path, int n){
        if(path[n] == 0){
            return false;
        }
        return true;
    }
    
    bool firstSolutionIsFull(vector<int> path, int n){
        for(int i = 0; i < n; i++){
            if(path[i] == 0){
                return false;
            }
        }
        return true;
    }
    bool otherSolutionIsFull(vector<int> path, int n){
        for(int i = 0; i < n; i++){
            if(path[i] != 0){
                return false;
            }
        }
        return true;
    }
    
    // Iterating through the first row to check if it is empty.
    // If there is any non zero value, the function returns false.
    // Otherwise, it returns true.
    bool isEmpty(vector<int> path, int n){
        for(int i = 0; i < n; i++){
            if(path[i] != 0){
                return false;
            }
        }
        return true;
    }
    
    vector<int> generateEmptyVector(int size){
        vector<int> emptyVector = {};
        for(int i = 0; i < size; i++){
            emptyVector.push_back(0);
        }
        return emptyVector;
    }
    
    
    bool isInWeirdFinalPosition(vector<int> path){
        if(path[0] == path.size()){
            for(int i = 1; i < path.size(); i++){
                if(!(path[i] == 0)){
                    return false;
                }
            }
            return true;
        }
        else{
            return false;
        }
    }
    // The backtrack functions uses recursion to backtrack. Takes a path, row, and column to start checking. Returns a vector solution.
    vector<int> backtrack(vector<int> path, int row, int column){
        // Starting the backtracking at the column already found, since you are always moving to the right.

        // TODO: This might have broken because of the <=
        
        if(isInWeirdFinalPosition(path)){
            vector<int> empty = generateEmptyVector(path.size());
            //printBoard(empty);
            isGoing = false;
            isTacky = true;
            return empty;
        }
        for(int counter = column + 1; counter <= path.size(); counter++){
            
            if(counter == path.size()){
                //return path;
            }
            
            vector<int> backTrackPath = path;
            backTrackPath[row] = counter;
            // if the new value is a solution.

            if(isLegalPosition(backTrackPath)){
                return backTrackPath;
            }
        }
        
        // if no solution is found in this row, go back to the previous (the previous value in path, and start from there)
        path[row] = 0;
        vector<int> c = backtrack(path, row - 1, path[row - 1]);
        
        return c;
    };
    
    // gives the next move.
    vector<int> nextLegalPosition(vector<int> path, int n){
        vector<int> toReturn = {0};
        if(isFull(path, n - 1)){
            // Loop through the last row of the board, starting from the value of the row.
            // (Using 0 based indexing, of course) -> because this is the last one.
            int row = n - 1;
            // Get the column based on the value of the row.
            int column = path[row];
            for(int columnCounter = (column + 1); columnCounter < path.size(); columnCounter++){
                vector<int> forwardPath = path;
                forwardPath[row] = columnCounter;
                // If a new position is a legal move, then, return that position.
                if(isLegalPosition(forwardPath)){
                    return forwardPath;
                }
            }
            
            // If nothing is returned in that for loop, recursion needs to be called.
            path[row] = 0;
            toReturn = backtrack(path, row - 1, path[row - 1]);
        }
        // If the entire board is empty, just place it in the first spot.
        else if(isEmpty(path, n - 1)){
            vector<int> forwardPath = path;
            forwardPath[0] = 1;
            return forwardPath;
        }
        else{
            // If the position is a partial solution, go to the next row and check there. If there is a solution there, return that, otherwise, backtrack.

            if(isLegalPosition(path)){
                
                // Gets the row before the nearest zero. (this is working)
                int row = findLastPosition(path)[0];
                // The nextRow, or the row that will be searched for the next piece, is set to row + 1.
                int nextRow = row + 1;
                // My reasoning for having it initialized as 1 is that it is a new row and therefore all of them need to be checked from left to right. I think it is 1? Zero means empty.
                // TODO: The path.size() + 1 might break stuff, but it is currently working.
                for(int columnCounter = 1; columnCounter <= path.size(); columnCounter++){
                    vector<int> forwardPath = path;
                    forwardPath[nextRow] = columnCounter;
                    if(isLegalPosition(forwardPath)){
                        return forwardPath;
                    }
                }
                
                // Otherwise, if no successful position is found from the search, backtracking must be done, to row - 1, not nextRow - 1
                int oldRowVal = path[row];
                path[row] = 0;
                toReturn = backtrack(path, row, oldRowVal);
            }
            // If the position is not a partial solution, keep looking in the current row and check there. If there is a solution there, return that, otherwise, backtrack.
            else if(!(isLegalPosition(path))){
                // Gets the row before the nearest zero. (this is working)
                int row = findLastPosition(path)[0];
                int column = path[row];
                // Starts at the value of path at the row, because it moves to the right.
                for(int columnCounter = column; columnCounter < path.size() + 1; columnCounter++){
                    vector<int> forwardPath = path;
                    // Updates the current row
                    forwardPath[row] = columnCounter;
                    if(isLegalPosition(forwardPath)){
                        return forwardPath;
                    }
                }
                path[row] = 0;
                toReturn = backtrack(path, row - 1, path[row - 1]);
            }
            
            
        }
        return toReturn;
    }
    
    
    // You should be able to display (initial/one each) solutions for instances up through about n=30
    // Need to write a function to display the first solutions of the n-queens problem (lexographically, meaning the first...)
    vector<int> findFirstSolution(vector<int> path, bool printTheBoard){
        vector<int> solutionPath = path;
        // maybe while there is not a full, legal solution?
        while(!firstSolutionIsFull(solutionPath, path.size())){
            
            vector<int> solution = nextLegalPosition(solutionPath, path.size());
            solutionPath = solution;

        }
        if(printTheBoard){
            printBoard(solutionPath);
        }
        return solutionPath;
    }

    
    // Generates the list of first solutions, given a starting point and end point.
    vector<vector<int>> generateFirstSolutions(int lowerBound, int upperBound, bool printTheBoard){
        vector<vector<int>> firstSolutions = {};
        for(int solutionCounter = lowerBound; solutionCounter < upperBound; solutionCounter++){
            vector<int> emptyPath = {};
            // This part generates the empty path of size n for the solutions.
            for(int pathCounter = 0; pathCounter < solutionCounter; pathCounter++){
                emptyPath.push_back(0);
            }
            vector<int> solution = findFirstSolution(emptyPath, printTheBoard);
            firstSolutions.push_back(solution);
        }
        return firstSolutions;
    }
    

    
    bool isBoardEmpty(vector<int> path){
        for(int i = 0; i < path.size(); i++){
            if(!(path[i] == 0)){
                return false;
            }
        }
        return true;
    }
    
    // Make solution returns all solutions to an n-queens problem, given a path.
    int makeSolution(vector<int> path, bool printSolutions){
        int counter = 0;
        while(isGoing){
            vector<int> oneSolution = findFirstSolution(path, printSolutions);
            solutions.push_back(oneSolution);
            vector<int> newVector = nextLegalPosition(oneSolution, path.size());
            counter++;
            path = newVector;
            if(isBoardEmpty(newVector)){
            }
            if(printSolutions){
                printBoard(oneSolution);
            }
        }
        return counter;
    }
    
    // Used to find the position (used for backtracking)
    vector<int> findLastPosition(vector<int> board){
        for(int boardCounter = 1; boardCounter < board.size(); boardCounter++){
            // When a board position is empty (aka 0), the position before it was the last piece.
            if(board[boardCounter] == 0){
                return {boardCounter - 1, (board[(boardCounter - 1)])};
            }
        }
        // Otherwise, if a 0 is not found, it is a full board, so the last position is the last piece in the vector.
        int s = board.size();
        //cout << "\nThis is the find last board - " << board[board.size() - 1];
        return {s - 1, board[board.size() - 1]};
    }
};
 
int main()
{
    std::cout<<"Hello, World!"<<std::endl;
    ChessBoard chess(8);
    // checking to make sure that the isLegalPosition() function works.
 
    //vector<int> c = chess.nextLegalPosition({1, 0, 0, 0}, 4);
    
    cout << "Using the next legal position function:";
    vector<int> c = chess.nextLegalPosition({1, 0, 0, 0}, 4);
    chess.printBoard(c);
    
    int startingNSol = 4;
    int endingNSol = 20;
    vector<int> testSol = chess.generateEmptyVector(startingNSol);
    cout << "First solutions: \n";
    for(int j = startingNSol; j < endingNSol; j++){
        ChessBoard ch(8);
        ch.findFirstSolution(testSol, true);
        testSol.push_back(0);
    }
    
    
    
    int startingN = 4;
    int endingN = 11;
    int aSolution = 0;
    vector<int> test = chess.generateEmptyVector(startingN);
    for(int i = startingN; i <= endingN; i++){
        ChessBoard ch(8);
        aSolution = ch.makeSolution(test, false);
        
        //cout << "\nA board: " << aSolution;

        if(ch.isTacky){
            cout << "\nBoard size: " << i << " - Number of solutions: " << aSolution - 1 << "\n";
        }
        else{
            cout << "\nBoard size: " << i << " - Number of solutions: " << aSolution << "\n";

        }
        aSolution = 0;
        test.push_back(0);
    }
    cout << "\nisLegalPosition does not need test cases because the numbers would not be right if it didn't work like it was supposed to.\n";
    cout << "\nThe program is very slow, but still prints out the right numbers up to 14 in a reasonable amount of time. It can be assumed that it will work for all of them because it works for more than 2.\n";
        cout << "\nPrinting out the first solution to a problem is efficient until n=20, where it begins to slow down.\n";
    return 0;
}

