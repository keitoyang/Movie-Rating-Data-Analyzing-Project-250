//CSE250 Project #2, Kun Yang, Christopher Pei
//A program that read u.item and u.data, then output the top k movie for user x
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "movieBaseKY.h"
#include "userBaseCAP.h"

using namespace std;


int main()
{
   Movie_base movieBase;
   movieBase.readMovieInfo ("u.item");
   movieBase.readMovieRat  ("u.data");
   movieBase.calAverage();
   User_base userBase;
   userBase.readMovieRat  ("u.data",movieBase);
   userBase.calPugAll(movieBase.getGenreAve());

   int k, id;
   cout << "Enter two int, first one for User ID, second for number of top movies\n(for example: '10 30' means show top 30 movie for user #10): ";
   cin >> id;
   cin >> k;
   userBase.biasedtopMovies (id,k,movieBase.topMovies(k));

   //cout << movieBase.toString() <<endl;
   //cout << userBase.toString() <<endl;
   return 0;
}
