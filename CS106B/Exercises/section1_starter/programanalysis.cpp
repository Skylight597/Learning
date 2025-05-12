#include "SimpleTest.h"
#include "vector.h"
#include "strlib.h"

using namespace std;

/*
   @param input: input string whose last names will be filtered
   @param suffix: the substring which we will filter last names by
   Functionality: this function filters the input string and returns last names
        that end with 'suffix'
*/
Vector<string> filter(string input, string suffix)
{
    Vector<string> filteredNames;
    Vector<string> names = stringSplit(input, ',');

    for (string name: names) {
        // convert to lowercase so we can easily compare the strings
        if (endsWith(toLowerCase(name), toLowerCase(suffix))) {
            filteredNames.add(name);
        }
    }
    return filteredNames;
}

STUDENT_TEST("Filter names") {
    Vector<string> results = filter("Zelenski,Szumlanski,Rodriguez Cardenas", "Ski");
    EXPECT_EQUAL(results, {"Zelenski","Szumlanski"});

    results = filter("AmbaTi,Szumlanski,Tadimeti", "TI");
    Vector<string> expected = {"AmbaTi", "Tadimeti"};
    EXPECT(results == expected);

    results = filter("Zelenski,Szumlanski,Rodriguez Cardenas", "nas");
    EXPECT_EQUAL(results, {"Rodriguez Cardenas"});

    results = filter("Szumlanski,Rodriguez Cardenas", "AaS");
    EXPECT_EQUAL(results, {});

    // what other tests could you add?
}