#ifndef MOVIEBASEKY_H_
#define MOVIEBASEKY_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <functional>

using namespace std;

/*movie class, holding movie data: index, title, year, genre memberships, and a few other miscellaneous fields.*/
class Movie
{
private:
   int index;
   string title;
   string year;
   vector<string> genre;
   double rating; // average rating
   int count;     // total number of rating
   double sum;    // sum of rating
public:
   /* Constructor that takes in the index, title, year, and genres.*/
   Movie (int index, string title, string year,vector<bool> genreRaw);

   /* Default constructor that initializes class fields.*/ 
   Movie ();

   /* Method to input new ratring to the movie, then re-rcalculate the rating */
   void newRating(double r);

   /* Method to get genre */
   vector<string> getGenre () const;

   /* Method to get rating */
   double getRating () const;

   /* Method to get title */
   string getTitle() const;

   /* Method to get title */
   int getIndex() const;

   /* toString function */
   string toString () const;
};

// Movie base class to hold the entire series of movies.
class Movie_base
{
private:
   vector<Movie>* movieCollection;
   double unknownAve;
   double actionAve;
   double noirAve;  //they are the average rating for a movie genre
   double lightAve; 
   double seriousAve;
   double fantasyAve;
   double historyAve;
public:
   /*Default constructor that creates a new Movie_base class object.*/
   Movie_base ();

   /* Method to read file content and process its data. We process the index, title, year, and genre memberships
    for each movie -- organized in the file on a per-line basis.*/
   void readMovieInfo (string fileName);

   /* Method to retrieve movie ratings from a file. */
   void readMovieRat (string fileName);
   
   /* Method to input new rating to a movie, given the index of a movie and a rating value. */
   void newRating(int index, double r);

   /* Method to calculate the average for all genre */
   void calAverage ();

   /* Method to return the genre membership information for a movie, given the index of a movie. */
   vector<string> getGenre (int movieIndex) const;

   /* Method to return the genre average rating */
   vector<double> getGenreAve () const;

   ///* Method to return the top movies of every genre */
   // the reason we want top movies for every genre is it make user class easier to get their top movie,
   // detail of this strategy is explained in report question.
   vector<vector<Movie> > topMovies (size_t k);

   /* toString function */
   string toString () const;

};

#endif
