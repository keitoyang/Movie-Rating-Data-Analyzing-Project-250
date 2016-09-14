#include "movieBaseKY.h"

Movie::Movie (int index, string title, string year,vector<bool> genreRaw)
   :index(index)
   ,title(title)
   ,year(year)
   ,rating(0.0)
   ,count(0)
   ,sum(0.0)
   {
   // base the table: 
   //   Action:1 2 16 18
   //   Noir:6 10 11 13
   //   Light: 3 4 5 12
   //   Serious: 8 14
   //   Fantasy: 9 15
   //   History: 7 17
   // push_back string to genre vector
   if (genreRaw.at(0))
      genre.push_back("Unknown");
   if (genreRaw.at(1) || genreRaw.at(2) || genreRaw.at(16) || genreRaw.at(18))
      genre.push_back("Action");
   if (genreRaw.at(6) || genreRaw.at(10) || genreRaw.at(11) || genreRaw.at(13))
      genre.push_back("Noir");
   if (genreRaw.at(3) || genreRaw.at(4) || genreRaw.at(5) || genreRaw.at(12))
      genre.push_back("Light");
   if (genreRaw.at(8) || genreRaw.at(14))
      genre.push_back("Serious");
   if (genreRaw.at(15) || genreRaw.at(9))
      genre.push_back("Fantasy");
   if (genreRaw.at(17) || genreRaw.at(7))
      genre.push_back("History");
}

Movie::Movie ()
   :index(0)
   ,title("Unknown")
   ,year("01-Jan-1000")
   ,rating(0.0)
   ,count(0)
   ,sum(0.0)
{genre.push_back("Unknown");}

void Movie::newRating(double r)// the method only undata the average rating, dose save the new rating.
{
   sum+=r;
   count++;
   rating=sum/count;
}

vector<string> Movie::getGenre () const
{
   return genre;
}

double Movie::getRating () const
{
   return rating;
}

string Movie::getTitle() const
{
	return title;
}

int Movie::getIndex() const
{
	return index;
}

string Movie::toString () const
{
   ostringstream OUT;
   OUT << "Index: " << index << "\nTitle:  " << title << "\nYear: " << year << "\nGenre: ";
   for (size_t i=0; i<genre.size(); i++)
      OUT << genre.at(i) << ' '; 
   OUT << "\nRating(not biased): " << rating <<endl;
   return OUT.str();
}

Movie_base::Movie_base ()
{
   movieCollection = new vector<Movie>(0); 
   unknownAve = 0;
   actionAve = 0;
   noirAve = 0;
   lightAve = 0;
   seriousAve = 0;
   fantasyAve = 0;
   historyAve = 0;
}

void Movie_base::readMovieInfo (string fileName)
{
   // make the element 0 in movieCollection a dummy element for better indexing.
   Movie dummyMovie;
   movieCollection->push_back(dummyMovie);
   ifstream* INFILE = new ifstream (fileName.c_str(),ios_base::in);
   if (! INFILE->is_open()) 
      cerr<< "Unable to open file" << endl;
   while (!INFILE->eof())
   {
      int index;
      string title;
      string year;
	  vector<bool> genre(0);
	  char n;
	  string eol;
      (*INFILE)>>index;
	  if (INFILE->eof())
         break;
      (*INFILE)>>n;
	  (*INFILE)>>n;
      // we read the file and process the fields by appropriately deliminating with respect to the '|' character.
	  while (n !='|')
	  {
         title.push_back(n);
         (*INFILE)>>n;
	  }
	  (*INFILE)>>n;
	  while (n !='|')
	  {
         year.push_back(n);
         (*INFILE)>>n;
	  }
	  (*INFILE)>>n;
	  (*INFILE)>>n;
	  while (n != '|')
         (*INFILE)>>n;
	  (*INFILE)>>n;
	  for (int i=0;i<18;i++)
	  {
         genre.push_back(n=='1'?true:false);
		 (*INFILE)>>n;
         (*INFILE)>>n;  
	  }
	  genre.push_back(n=='1'?true:false);
	  // Add the movie to the movie collection (storing our Movie objects).
	  Movie curMovie (index,title,year,genre);
	  movieCollection->push_back(curMovie);
   }
}

void Movie_base::readMovieRat (string fileName)
{
   ifstream* INFILE = new ifstream (fileName.c_str(),ios_base::in);
   if (! INFILE->is_open()) 
      cerr<< "Unable to open file" << endl;
   while (!INFILE->eof())
   {
      int movieN;
	  double r;
	  int ignore;
	  (*INFILE)>>ignore;
	  (*INFILE)>>movieN;
	  (*INFILE)>>r;
	  (*INFILE)>>ignore;
          // calling newRating to updata the movie
	  newRating(movieN,r);
   }
}

void Movie_base::newRating(int index, double r)
{
   movieCollection->at(index).newRating(r);
}

void Movie_base::calAverage ()
{
	vector<double> sum(7);//sums of ratings for every genre 
	vector<int> count(7);//number of ratring for every genre
	sum.at(0)=0;
	sum.at(1)=0;
	sum.at(2)=0;
	sum.at(3)=0;
	sum.at(4)=0;
        sum.at(5)=0;
	sum.at(6)=0;
	count.at(0)=0;
	count.at(1)=0;
	count.at(2)=0;
	count.at(3)=0;
	count.at(4)=0;
        count.at(5)=0;
	count.at(6)=0;
	for (size_t i=1; i < movieCollection->size(); i++)
	{
		for (size_t j=0; j<movieCollection->at(i).getGenre().size(); j++)
		{
			  string g;
			  g = movieCollection->at(i).getGenre().at(j);
			  if ( g == "Unknown")
			  {
				  sum.at(0) +=  movieCollection->at(i).getRating();
				  count.at(0)++;
			  }
			  else if ( g == "Action")
			  {
				  sum.at(1) +=  movieCollection->at(i).getRating();
				  count.at(1)++;
			  }
			  else if ( g == "Noir")
			  {
				  sum.at(2) +=  movieCollection->at(i).getRating();
				  count.at(2)++;
			  }
			  else if ( g == "Light")
			  {
				  sum.at(3) +=  movieCollection->at(i).getRating();
				  count.at(3)++;
			  }
			  else if ( g == "Serious")
			  {
				  sum.at(4) +=  movieCollection->at(i).getRating();
				  count.at(4)++;
			  }
			  else if ( g == "Fantasy")
			  {
				  sum.at(5) +=  movieCollection->at(i).getRating();
				  count.at(5)++;
			  }
			  else if ( g == "History")
			  {
				  sum.at(6) +=  movieCollection->at(i).getRating();
				  count.at(6)++;
			  }
		}
	}
   // if count is not 0, calculate the average.
   if (count.at(0)!=0)
      unknownAve = sum.at(0)/count.at(0);
   if (count.at(1)!=0)
      actionAve = sum.at(1)/count.at(1);
   if (count.at(2)!=0)
      noirAve = sum.at(2)/count.at(2);
   if (count.at(3)!=0)
      lightAve = sum.at(3)/count.at(3);
   if (count.at(4)!=0)
      seriousAve = sum.at(4)/count.at(4);
   if (count.at(5)!=0)
      fantasyAve = sum.at(5)/count.at(5);
   if (count.at(6)!=0)
      historyAve = sum.at(6)/count.at(6);
}

vector<string> Movie_base::getGenre (int movieIndex) const
{
   return movieCollection->at(movieIndex).getGenre();
}

vector<double> Movie_base::getGenreAve () const
{
	vector <double> genreAve (7);
	genreAve.at(0) = unknownAve;
	genreAve.at(1) = actionAve;
	genreAve.at(2) = noirAve;
	genreAve.at(3) = lightAve;
	genreAve.at(4) = seriousAve;
	genreAve.at(5) = fantasyAve;
	genreAve.at(6) = historyAve;
	return genreAve;
}

// compare function for priority queue
class compareRating
{
public:
	bool operator()(Movie& lhs, Movie& rhs)
	{
		return (lhs.getRating() < rhs.getRating());
	}
};

vector<vector<Movie> > Movie_base::topMovies(size_t k)
{
	if (k >= movieCollection->size())
		cerr << "[Error]: Provided integer is greater than the movie collection size. Aborting." << endl;
	// top.at(0) holds top k action movie
	// top.at(1) holds top k noir movie
	// top.at(2) holds top k light movie
	// top.at(3) holds top k serious movie
	// top.at(4) holds top k fantasy movie
	// top.at(5) holds top k history movie
	vector<vector<Movie> > top = vector<vector<Movie> >(6);
	priority_queue <Movie, vector<Movie>, compareRating> topAction;
	priority_queue <Movie, vector<Movie>, compareRating> topNoir;
	priority_queue <Movie, vector<Movie>, compareRating> topLight;
	priority_queue <Movie, vector<Movie>, compareRating> topSerious;
	priority_queue <Movie, vector<Movie>, compareRating> topFantasy;
	priority_queue <Movie, vector<Movie>, compareRating> topHistory;

	for (size_t i = 1; i < movieCollection->size(); i++)
	{
		for (size_t j=0; j<movieCollection->at(i).getGenre().size(); j++)
	    {
		   string g;
                   // push movie in to their appropriate priority_queue
		   g = movieCollection->at(i).getGenre().at(j);
		   if ( g == "Action")
		      topAction.push(movieCollection->at(i));
		   else if ( g == "Noir")
		      topNoir.push(movieCollection->at(i));
		   else if ( g == "Light")
		      topLight.push(movieCollection->at(i));
		   else if ( g == "Serious")
		      topSerious.push(movieCollection->at(i));
		   else if ( g == "Fantasy")
		      topFantasy.push(movieCollection->at(i));
		   else if ( g == "History")
		      topHistory.push(movieCollection->at(i));
	   }
	}
	for (size_t i = 1; i <= k; i++)
	{
                // get movie from priority and put them into "top"
		top.at(0).push_back ( topAction.top() );
		topAction.pop();
		top.at(1).push_back ( topNoir.top() );
		topNoir.pop();
		top.at(2).push_back ( topLight.top() );
		topLight.pop();
		top.at(3).push_back ( topSerious.top() );
		topSerious.pop();
		top.at(4).push_back ( topFantasy.top() );
		topFantasy.pop();
		top.at(5).push_back ( topHistory.top() );
		topHistory.pop();
	}
	return top;
}


string Movie_base::toString () const 
{
   ostringstream OUT;
   for (size_t i=1;i<movieCollection->size();i++)
	   OUT << movieCollection->at(i).toString() << endl;
   OUT << endl << " Average of Unknown is: " << unknownAve << endl;
   OUT         << " Average of Action is : " << actionAve << endl;
   OUT         << " Average of Noir is   : " << noirAve << endl;
   OUT         << " Average of Light is  : " << lightAve << endl;
   OUT         << " Average of Serious is: " << seriousAve << endl;
   OUT         << " Average of Fantasy is: " << fantasyAve << endl;
   OUT         << " Average of History is: " << historyAve << endl;
   return OUT.str();
}
