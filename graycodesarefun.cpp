//
//  main.cpp
//  graycodesarefun
//
//  Created by Robert Brodin on 11/18/19.
//  Copyright © 2019 Robert Brodin. All rights reserved.
//
#include <iostream>
#include <vector>
using namespace std;

/*
BRGC(int n)
Generate the binary reflected Gray code of order n
Input: A positive integer n
Output: A vector of all strings of given length of the gray code.
if n = 1 make list L containing bit strings 0 and 1 in this order (only two long)
otherwise:
    - Generate vector L1 of bit strings by calling BRGC(n − 1)
    - Copy vector L1 to list L2 in reverse order
    - add 0 in front of each bit string in vector L1
    - add 1 in front of each bit string in vector L2
    - append L2 to L1 to get vector L
Lastly, return L
*/
vector<string> BRGC(int n){
    // if n = 1, return a bit string.
    vector<string> L;
    if(n == 1){
        L.push_back("0");
        L.push_back("1");
    }
    else{
        // Creates L1 and L2, L2 will be reversed,
        vector<string> L2 = BRGC(n - 1);
        vector<string> L1 = L2;
        // Reverse L2
        reverse(L2.begin(), L2.end());
        
        vector<string> L3 = L1;
        vector<string> L4 = L2;
        // Adding the zeroes to L1 (in front of every number)
        for(int x = 0;x<L1.size();x++){
            L3[x] = "0" + L3[x];        }
        // Adding the ones to L2 (in front of every number)
        for(int l = 0;l<L2.size();l++){
            L4[l] = "1" + L4[l];        }

        // Finally, append L4 to L3 to get the list of bit strings.
        L3.insert(L3.end(), L4.begin(), L4.end());
        // Sets L equal to L3 (L is the return variable)
        L = L3;
    }
    return L;
}

// BRGCSpecific() takes a list of bit strings (should be from function BRGC()) and returns a vector which contains the changes from the previous bit string to the current bit string in a vector.
// This function is interesting because of how Binary reflected gray code works. Only one bit is changed for each increase in index, with each value either being changed to zero or one.
// The format of the return values are: {{"leave or join", "person"}}
vector<vector<int>> BRGCSpecific(vector<string> BRGCVector){
    vector<vector<int>> vectorToReturn = {};
    // Starting off at one because the program looks at the previous index. Do not want an ArrayIndexOfOutBound error.
    for(int i = 1; i < BRGCVector.size() ; i++){
        // The size of the vector is unknown, to compensate for this another loop is used to iterate through each number in the bitstring.
        for(int x = 0; x < BRGCVector[i - 1].size(); x++){
            // If the previous bitstring's current index and the current bitstring's current index are not equal, it means that a change has occured.
            if(!(BRGCVector[i - 1][x] == BRGCVector[i][x])){
                // If the value of the old one is equal to 1, it means that the value of the new one must equal 0.
                if(BRGCVector[i - 1][x] == '1'){
                    // Add the changed number and the index to a new vector and append that vector to a list of all changes.
                    vector<int> vectorToAdd = {0, x};
                    vectorToReturn.push_back(vectorToAdd);
                }
                // If the value of the old one is equal to 0, it means that the value of the new one must equal 1.
                else if (BRGCVector[i - 1][x] == '0'){
                    // Add the changed number and the index to a new vector and append that vector to a list of all changes.
                    vector<int> vectorToAdd = {1, x};
                    vectorToReturn.push_back(vectorToAdd);
                }
            }
        }
    }
    // Lastly, return vectorToReturn.
    return vectorToReturn;
}

int main(int argc, const char * argv[]) {
    
    // n decides the length of each bit string. For the sake of Part B n is equal to four.
    int n = 4;
    
    // testBRGC is used to store BRGC(n), which in this case will store the vector of gray codes of length 4.
    vector<string> testBRGC = BRGC(n);
    // specificBRGC is used to store BRGCSpecific(), which will store the vector containing vectors which contain the movements from graycode to graycdoe.
    vector<vector<int>> specificBRGC = BRGCSpecific(testBRGC);
    // Loop used to display all of the gray code.
    cout << "Part A - Binary reflected graycode of length " << n << ":\n";
    for(int r=0;r<testBRGC.size();r++){
        cout << testBRGC[r];
        cout << "\n";
    }
    
    // kidsInPicture is used to store the names of the children in Part B.
    vector<string> kidsInPicture = {"Dylan", "Chris", "Bob", "Alice"};
    // orderOfKids is initialized as empty and will be used to store the order of movement in the process of taking a photograph.
    vector<string> orderOfKids = {};
    cout << "\nPart B - Gray code changes (from last position to current): \n";
    // Iterate through each movement in specificBRGC
    for(int t=0;t<specificBRGC.size();t++){
        cout << specificBRGC[t][0] << ", " << specificBRGC[t][1] << "\n";
        // Append the name which aligns with the index of the movement.
        // This is achieved by aligning the order of the children with a specific index and calling each child by a number.
        orderOfKids.push_back(kidsInPicture[specificBRGC[t][1]]);
    }
    
    // Printing out all of the kids:
    cout << "\nOrder in photo: ";
    // orderOfKids contains the order of children. The loop simply displays each child in order.
    for(int q = 0;q < orderOfKids.size();q++){
        cout << orderOfKids[q] << ", ";
    }
    std::cout << "\n What is special about the order in the photo is that it follows the ABACABADABACABA pattern, which oftens appears when using trees and repeating tasks. The first letters of each name correspond with ABACABADABACABA. If the names in kidsInPicture were changed, the pattern would still be the same but the acronym would be different.\n";
    return 0;
}
