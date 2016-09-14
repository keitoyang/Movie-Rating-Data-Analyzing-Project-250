#ifndef USERBASECP_H_
#define USERBASECP_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "movieBaseKY.h"

using namespace std;

/* User class, holding the user's id, a vector of vectors of type double to hold their rated movies, and fields
 to hold their average ratings for each of the 7 genres. */
class User 
{
private:
   int id;
   //2-Dimensional vector, to hold user ratings for all movies they've rated.
   // rating.at(0) holds the ratings for unknow.
   // rating.at(1) holds the ratings for action.
   // rating.at(2) holds the ratings for noir.
   // rating.at(3) holds the ratings for light.
   // rating.at(4) holds the ratings for serious.
   // rating.at(5) holds the ratings for fantasy.
   // rating.at(6) holds the ratings for history.
   vector<vector<double> > ratings;
   double ave_unknown;
   double ave_action;
   double ave_noir;
   double ave_light;
   double ave_serious;
   double ave_fantasy;
   double ave_history;
   vector<double> pug;//preference factor: pug[0]=unknow ..... pug[6]=history
public:
   /* Constructor that takes a user id and initializes all genre averages to 0. */
   explicit User (int id);

   /* Default constructor, initializing the user id to 0 and all genre averages to 0. */
   User ();

   /* Method to input new ratring to the user, put the rating in its appropriate place base on its genre.
      then re-calculate the ave of its genre*/
   void newRating(double r, vector<string> genre);

   /* Method to calculate pug for the user, given 943 user's average rating for genres */
   void calPug(vector<double> genreAve);

   /* Method to calculate a user's biased top k moive, given k and the top k movie of each genre */
   void biasedtopMovies (size_t k, vector<vector<Movie> >topMovies);

   /* toString function */
   string toString () const;
};

/* User base class to hold the collection of User objects. */
class User_base
{
private:
   vector<User>* userCollection;
public: 
   User_base ();

   /* Method to read in ratings from the file. We need movieBase as a parameter, because we want determine the genre of the movie */
   void readMovieRat (string fileName, const Movie_base &movieBase);

   /* Method to input new rating to a user, given the user id, movie gnere and a rating value.  */
   void newRating(int id, double r,vector<string> genre);

   /* Method to calculate pug for all user, given 943 user's average rating for genres */
   void calPugAll(vector<double> genreAve);

   /* Method to calculate a user's biased top k moive, given user id, k, and the top k movie of each genre */
   void biasedtopMovies (size_t id, size_t k, vector<vector<Movie> >topMovies);

   /* toString function */
   string toString () const;
};

#endif
