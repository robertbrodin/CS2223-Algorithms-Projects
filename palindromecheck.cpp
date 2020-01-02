//
//  palindromecheck
//
//  Created by Robert Brodin on 11/11/19.
//  Algorithms - Professor Engling, B Term 2019
//

#include <iostream>
#include <vector>
using namespace std;

// checkPalindrome takes a string and returns true if the string is a palindrome, the function returns false if the string is not a palindrome.
// checkPalindrome ignores case and punctuation.
bool checkPalindrome(string stringToCheck){
    
    string reversedString = "";
    string stringToCheckWithAlpha = "";
    // Iterates through the list backwards, and appends in an order that is reverse (relative to the original order).
    for(int i = stringToCheck.length();i>=0;i--){
        // If the string is a letter in the alphabet and not anything else, concatenate it to the reverse string.
        if(isalpha(stringToCheck[i])){
            // If it is, make it lowercase and add it to the list.
            //cout << stringToCheck[i] << "\n";
            char tempChar = tolower(stringToCheck[i]);
            string tempString(1, tempChar);
            reversedString.append(tempString);
        }
    }
    // Iterates through the list forwards.
    for(int j = 0; j < stringToCheck.length(); j++){
        // If the string is a letter in the alphabet and not anything else, concatenate it to the reverse string.
        if(isalpha(stringToCheck[j])){
            // If it is, make it lowercase and add it to the list.
            //cout << stringToCheck[j] << "\n";
            char tempChar = tolower(stringToCheck[j]);
            string tempString(1, tempChar);
            stringToCheckWithAlpha.append(tempString);
        }
    }
    // If the reverse string with only letters and the normal string with only letters are the same, display that they are the same and return true.
    if(stringToCheckWithAlpha == reversedString){
        cout << stringToCheck << " - this is a palindrome!\n";
        return true;
    }
    // If the reverse string with only letters and the normal string with only letters are different, display that they are different and return false.
    else{
        cout << stringToCheck << " - this is not a palindrome!\n";
        return false;
    }
    // My algorithm will be to go through each list, find all letters, make them one combined string, and check if that is equal to the initial string (the reversed one).
};

int main(int argc, const char * argv[]) {
    
    // Running checkPalindrome on several test cases. This should be sufficient.
    checkPalindrome("Never odd or even");
    checkPalindrome("Never  ......      odd or even!!!!!!!!!!!!");
    checkPalindrome("CS 2223");
    checkPalindrome("CS 2223 SC");

    //std::cout << "Hello, World!\n";
    
    return 0;
}
