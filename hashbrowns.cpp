//
//  main.cpp
//  HashBrowns
//
//  Created by Robert Brodin on 11/30/19.
//  Homework 6, Algorithms, B Term, 2019, Professor Engling.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// specialIsAlpha is the normal isalpha() function with an apostrophe added as a "special character", where the function returns true.
bool specialIsAlpha(char character){
    if(character == '\''){
        return true;
    }
    else{
        return isalpha(character);
    }
}

class HashTable{
  
public:
    
    // hashTable is used to store the words.
    string hashTable[1000];
    // hashTableNumbers`is used to store the haskkeys
    int hashTableNumbers[1000];
    // uniqueNumbers is used to store all hashkeys and see which of them are repeats. The name does not do the variable justice.
    vector<int> uniqueNumbers = {};
    
    /*
     int C = 123;
     int M = 1000;
     */

    // generateHashKeys takes an integer C (a somewhat arbitrary number), integer M (the size of the array), and a vector containing integers vectorOfStrings, which contains all words to be assigned hash values.
    vector<int> generateHashKeys(int C, int M, vector<string> vectorOfStrings){
        vector<int> hashValues = {};
        
        // For each word, create a unique hash value.
        for(int x = 0; x < vectorOfStrings.size(); x++){
            
            // Calculation for generating the unique hash value every time.
            int h = 0;
            int s = vectorOfStrings[x].length();
            for(int y = 0; y < s; y++){
                int ci = vectorOfStrings[x][y];
                h = ((h * C) + ci) % M;
            }

            // Once that hash key is generated, push it to the vector.
            hashValues.push_back(h);
        }
        // Finally, return the vector containing all of the hash values.
        return hashValues;
    }
    
    // findNextValidIndex takes an integer startingIndex (the number which the search starts at), and returns a number of the next index in the "circular array".
    int findNextValidIndex(int startingIndex){
        // If the starting index is 999, meaning it is at the end of the array, the next position in the "circular array" is zero.
        if(startingIndex >= 999){
            return 0;
        }
        // Otherwise, just add one to the starting index.
        else{
            return (startingIndex + 1);
        }
    }
    
    // calculateDifference takes an integer start (the first number), and an integer end (the last number), and returns the difference between them, in reference to the "circular array"
    int calculateDifference(int start, int end){
        if(start > end){
            return end + (1000 - start);
        }
        else if (start < end){
            return end - start;
        }
        else{
            return 0;
        }
    }
    
    // createHashTable takes hash keys (hashKeys), and words to assign the hash values to, and returns void.
    // The function prints out the results of the hash table.
    void createHashTable(vector<int> hashKeys, vector<string> hashValues){
        // Used to check if a word is already in the hashtable.
        vector<string> usedWords = {};
        
        // for each hashKey, create a new value in the array.
        for(int hashKeyCounter = 0; hashKeyCounter < hashKeys.size(); hashKeyCounter++){
            // If the hashTable at the index of the hashKey (at position hashKeyCounter in hashKeys) is not equal to anything ("", because it is a string), update the hashTable with that hashValue
            if(find(usedWords.begin(), usedWords.end(), hashValues[hashKeyCounter]) != usedWords.end()){
                
            }
            else{
                // If a value in the hashTable is empty, then add the word to it.
                if(!isalpha(hashTable[hashKeys[hashKeyCounter]][0])){
                    hashTable[hashKeys[hashKeyCounter]] = hashValues[hashKeyCounter];
                    hashTableNumbers[hashKeys[hashKeyCounter]] = hashKeys[hashKeyCounter];
                    usedWords.push_back(hashValues[hashKeyCounter]);
                    uniqueNumbers.push_back(hashKeys[hashKeyCounter]);
                }
                // If the desired value in the hashTable is taken, keep looking (a while loop is utilized for this), until it is empty.
                else{
                    bool validIndexFound = false;
                    // currentIndex is to keep track of the index, One is added every time if the hashtable is not empty at the desired spot.
                    int currentIndex = hashKeys[hashKeyCounter];
                    while(!validIndexFound){
                        currentIndex = findNextValidIndex(currentIndex);
                        // If a value in the hashTable is empty, then add the word to it.
                        if(!isalpha(hashTable[currentIndex][0])){
                            hashTable[currentIndex] = hashValues[hashKeyCounter];
                            hashTableNumbers[currentIndex] = hashKeys[hashKeyCounter];
                            usedWords.push_back(hashValues[hashKeyCounter]);
                            uniqueNumbers.push_back(hashKeys[hashKeyCounter]);
                            validIndexFound = true;
                         }
                    }
                }
            }
        }
        

        // All of the following variables are totem-variables used to keep track of the largest distances (filled and empty), and their respective positions. I don't really feel like going into depth with what they do because it's relatively obvious.
        float nonEmptyCounter = 0;
        int currentEmptyStreak = 0;
        int largestEmptyStreak = 0;
        int currentFilledStreak = 0;
        int largestFilledStreak = 0;
        int largestDistance = 0;
        int startPositionLongest = 0;
        int endPositionLongest = 0;
        int tempStart;
        int tempEmptyStart;
        int startPositionEmpty;
        int endPositionEmpty;
        bool startingAgain = true;
        bool startingAgainEmpty = true;
        string largestWordDistance = "";
        
        // For each value in the hash table, print out the address, the word, the hash value of the word, and the difference between the actual address and the hash value.
        for(int x = 0; x <= 999; x++){
            if(!(hashTable[x] == "")){
                cout << "\n" << "Hash Address: " << x << " - Hashed Word: " << hashTable[x] << " - Hash Value of Word: " << hashTableNumbers[x] << " - Difference between actual address and hash value: " << calculateDifference(hashTableNumbers[x], x) << "\n";
                nonEmptyCounter++;
                // Checking largest streak of empty numbers.
                if(currentEmptyStreak > largestEmptyStreak){
                    largestEmptyStreak = currentEmptyStreak;
                    endPositionEmpty = x;
                    startPositionEmpty = tempEmptyStart;
                }
                // Checking the difference between numbers.
                if(calculateDifference(hashTableNumbers[x], x) > largestDistance){
                    largestDistance = calculateDifference(hashTableNumbers[x], x);
                    largestWordDistance = hashTable[x];
                }
                // startingAgain is used only because of the circular array.
                if(startingAgain){
                    tempStart = x;
                    startingAgain = false;
                }
                currentEmptyStreak = 0;
                startingAgainEmpty = true;
                currentFilledStreak++;
                // if x is at the end, need to check the first few again.
                if(x == 999){
                    int whileLoopCounter = 0;
                    bool keepGoing = true;
                    while(keepGoing){
                        if(!(hashTable[whileLoopCounter] == "")){
                            currentFilledStreak++;
                            whileLoopCounter++;
                        }
                        else{
                            if(currentFilledStreak > largestFilledStreak){
                                largestFilledStreak = currentFilledStreak;
                                startPositionLongest = tempStart;
                                endPositionLongest = whileLoopCounter;
                                keepGoing = false;
                            }
                            keepGoing = false;

                        }
                    }
                }
            }
            // If it isn't empty, change the other counting values.
            else{
                if(currentEmptyStreak > largestEmptyStreak){
                    largestEmptyStreak = currentEmptyStreak;
                }
                // Filled counter here. -> If it's larger when there is an empty spot.
                if(currentFilledStreak > largestFilledStreak){
                    largestFilledStreak = currentFilledStreak;
                    startPositionLongest = tempStart;
                    endPositionLongest = x;
                }
                // TODO: need to make this inclusive.
                if(startingAgainEmpty){
                    tempEmptyStart = x;
                    startingAgainEmpty = false;
                }
                currentEmptyStreak++;
                currentFilledStreak = 0;
                startingAgain = true;
            }
        }
        
        int highestCount = 0;
        int highestHashKey = 0;
        vector<string> usedWords2 = {};
        for(int y = 0; y < uniqueNumbers.size(); y++){
            int hashCount = count(uniqueNumbers.begin(), uniqueNumbers.end(), uniqueNumbers[y]);
                if(hashCount > highestCount){
                    highestCount = hashCount;
                    highestHashKey = uniqueNumbers[y];
                }
        }
    
        cout << "\n";
        float loadFactor = nonEmptyCounter / double(1000);
        cout << "The number of non-empty addresses is: " << nonEmptyCounter << ", meaning that the load factor is ";
        cout << fixed;
        cout << setprecision(4);
        cout << loadFactor << "\n";

        cout << "The largest empty streak is: " << largestEmptyStreak << " - from " << startPositionEmpty << " to " << endPositionEmpty << "\n";
        cout << "The largest filled streak is: " << largestFilledStreak << " - from " << startPositionLongest << " to " << endPositionLongest << "\n";
        cout << "The hash key that appears most often is: " << highestHashKey << ", which appears " << highestCount << " times\n";
        cout << "The word with the largest distance away from its original hash address is: " << largestWordDistance << ", with a distance of " << largestDistance << "\n";


    }
    
};

int main() {
    
    
    // The file raven.txt is opened and the words are read.
    ifstream inputFile;
    string words;
        
    inputFile.open("raven.txt"); // The name of the file you set up.
    vector<string> wordsToHash = {};
        
        while(inputFile >> words)
        {
            string toAppend = "";
            // For each character in the word, if there is a character that is not in the alphabet or is an apostrophe ignore everything after it.
            // For every alpha character or ', add it to the list of characters to push to the wordsToHash vector.
            for(int i = 0; i < words.length(); i++){
                char t = words[i];
                if(!specialIsAlpha(t)){
                    break;
                }
                else{
                    toAppend = toAppend + t;
                }
            }
            wordsToHash.push_back(toAppend);
        }
            

    // Initialize a hashtable and generate a list of hashkeys for each word in wordsToHash.
    HashTable myHashTable;
    vector<int> hashKeys = myHashTable.generateHashKeys(123, 1000, wordsToHash);

    // Creates a hash table with the hashkeys and the wordsToHash.
    myHashTable.createHashTable(hashKeys, wordsToHash);
    
    inputFile.close();

}
