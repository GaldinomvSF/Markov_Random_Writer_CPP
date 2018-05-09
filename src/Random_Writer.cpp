/* File: Random_Writer.cpp
 * ------------------------------------------------
 * This program generates Text based on Markov Model
 * This is my solution for the Stanford CS106B assignments number 2
 */

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "console.h"
#include "map.h"
#include "vector.h"

using namespace std;
const int SOLUTION_SIZE = 2000;   // 2000 characters will be shown in the solution

string readfile(string filename){

    string fullbook;
    ifstream myfile(filename);
    char ch;

    if (myfile.fail()){
        cout << "Filename is incorrect:";
        return fullbook;
    }

    while(myfile.get(ch))
        fullbook = fullbook + ch;

    myfile.close();
    return fullbook;
}

void ramdon_writing(string fullbook, int order){

    int count;

    Map<string,Vector<char>> char_map;

    /****Map for SubStrings of N-order and a Vector with the char that follows them****/
    for (count = 0 ; count < fullbook.length() ; count ++){

        string pattern = fullbook.substr(count,order);
        char following = fullbook[count+order];

        if (char_map.containsKey(pattern)){
            char_map[pattern].add(following);
        }
        else{
            Vector<char> follows;
            follows.add(following);
            char_map.put(pattern,follows);
        }

    }

    /* Finds the most popular N-order string in the book to start the writing*/
    int most_used = 0;
    string most_popular;

    for (string aux : char_map){
        if ( most_used <= char_map[aux].size()){
            most_used = char_map[aux].size();
            most_popular = aux;
        }
    }

    /***** Creates a 2000 character writing using Markov's model ******/
    srand (time(NULL));

    string solution = most_popular;
    int rsize = 0 ;

    /* Solutions for 2000 characters ***/
    for (int i=0; i < SOLUTION_SIZE ;i++){

        string seed = solution.substr(i,order);

        if (char_map.containsKey(seed)){

            int vecsize = char_map[seed].size() - 1 ;

            //Randomly chooses wich vector to return, respecting its limits
            if (vecsize == 0 )        rsize = 0;
            else if (vecsize == 1)    rsize = rand() % 2 ;
            else                      rsize = rand() % vecsize ;

            char follower = char_map[seed].get(rsize);
            solution = solution + follower;
        }
        else
            break;
    }
    cout << "The following is a random writing based on a order-" << order << " Markov Model:" << endl << endl<< solution;
}

int main() {

    string filename;
    int order_Markov;

    cout << "Type the book's name: " ;
    cin >> filename;

    cout << "Type Markov's order: " ;
    cin >> order_Markov;

    if (order_Markov >= 1)
        ramdon_writing(readfile(filename), order_Markov);
    else
        cout << "Values for Markov's order should be Equal or Greater than 1";

    return 0;
}
