/*
 * CS106B Section Handout Test Harness: Section 1
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Originally codified by Trip Master
 * and Nick Bowman for CS106B Spring 2020.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "string.h"
#include "vector.h"
#include "SimpleTest.h"

using namespace std;

/*
 * PigLatin (Code Write)
 * ---------------------
 * Write TWO functions that convert a string INPUT into its
 * pig-Latin form. To convert a word into pig-Latin, follow these
 * steps:
 * 1. Split INPUT into 2 parts, the string of letters BEFORE the
 *    first vowel, and the string of letters AFTER (and including) the
 *    first vowel.
 * 2. Append the before-string to the after-string.
 * 3. Append "ay" to this resulting string.
 *
 * You may assume your input is a single, valid word with no trickery.
 *
 * Both functions below should have the same functionality, but pigLatinReturn()
 * expects a new string in return that is the pig-Latin form of INPUT, and
 * pigLatinReference() expects the parameter INPUT to be modified by the function call.
 */

 const string vowels = "AaEeIiOoUuYy";

 bool isVowel (char ch){
     return vowels.find(ch)!=string::npos;
 }

string pigLatinReturn(string input){
    int strIndex = 0;
    for (int i = 0; i < input.length(); i++){
        if(isVowel(input[i])){
            strIndex = i;
            break;
        }
    }

    string One = input.substr(0, strIndex);
    string Two = input.substr(strIndex);
    return Two + One + "ay";
}

void pigLatinReference(string &input){
    int strIndex = 0;
    for (int i = 0; i < input.length(); i++){
        if(isVowel(input[i])){
            strIndex = i;
            break;
        }
    }

    string One = input.substr(0, strIndex);
    string Two = input.substr(strIndex);
    input =  Two + One + "ay";
}


/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("test case from handout"){
    string name = "julie";
    string str1 = pigLatinReturn(name);
    EXPECT_EQUAL(str1, "uliejay");

    pigLatinReference(name);
    EXPECT_EQUAL(name, "uliejay");
}

PROVIDED_TEST("Test a few more names from the handout"){
    Vector<string> names = { // Declarations like this will make you the talk of the town!
        "nick",
        "kylie",
        "trip"
    };
    Vector<string> pigLatinNames = {
        "icknay",
        "yliekay",
        "iptray"
    };
    for (int i = 0; i < names.size(); i++){
        EXPECT_EQUAL(pigLatinNames[i], pigLatinReturn(names[i]));
        /* Not good form to modify the contents of a container you loop thru, so make a copy! */
        string nameCpy = names[i];
        pigLatinReference(nameCpy);
        EXPECT_EQUAL(pigLatinNames[i], nameCpy);
    }
}
