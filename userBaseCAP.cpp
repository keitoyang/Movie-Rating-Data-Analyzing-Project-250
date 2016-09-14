#include "userBaseCAP.h"

User::User (int id)
   :id(id)
   ,ratings(vector<vector<double> >(7))
   ,ave_unknown(0)
   ,ave_action(0)
   ,ave_noir(0)
   ,ave_light(0)
   ,ave_serious(0)
   ,ave_fantasy(0)
   ,ave_history(0)
   ,pug(vector<double>(7))
{}

User:: User ()
   :id(0)
   ,ratings(vector<vector<double> >(7))
   ,ave_unknown(0)
   ,ave_action(0)
   ,ave_noir(0)
   ,ave_light(0)
   ,ave_serious(0)
   ,ave_fantasy(0)
   ,ave_history(0)
   ,pug(vector<double>(7))
{}

void User::newRating(double r, vector<string> genre)
{
   // a movie can be multiple genre, put them in multiple position.
   for (size_t i=0; i<genre.size(); i++)
   {
      string g;	  
      g = genre.at(i);
      // base on movie genre, put them in different vector
	  if ( g == "Unknown")
	  {
		  ratings.at(0).push_back(r);
		  double sum=0;
		  for (size_t i=0; i<ratings.at(0).size(); i++)
			  sum += ratings.at(0).at(i);
		  ave_unknown = sum/ratings.at(0).size();
	  }
	  else if ( g == "Action")
	  {
		  ratings.at(1).push_back(r);
		  double sum=0;
		  for (size_t i=0; i<ratings.at(1).size(); i++)
			  sum += ratings.at(1).at(i);
		  ave_action = sum/ratings.at(1).size();
	  }
	  else if ( g == "Noir")
	  {
		  ratings.at(2).push_back(r);
		  double sum=0;
		  for (size_t i=0; i<ratings.at(2).size(); i++)
			  sum += ratings.at(2).at(i);
		  ave_noir = sum/ratings.at(2).size();
	  }
	  else if ( g == "Light")
	  {
		  ratings.at(3).push_back(r);
		  double sum=0;
		  for (size_t i=0; i<ratings.at(3).size(); i++)
			  sum += ratings.at(3).at(i);
		  ave_light = sum/ratings.at(3).size();
	  }
	  else if ( g == "Serious")
	  {
		  ratings.at(4).push_back(r);
		  double sum=0;
		  for (size_t i=0; i<ratings.at(4).size(); i++)
			  sum += ratings.at(4).at(i);
		  ave_serious = sum/ratings.at(4).size();
	  }
	  else if ( g == "Fantasy")
	  {
		  ratings.at(5).push_back(r);
		  double sum=0;
		  for (size_t i=0; i<ratings.at(5).size(); i++)
			  sum += ratings.at(5).at(i);
		  ave_fantasy = sum/ratings.at(5).size();
	  }
	  else if ( g == "History")
	  {
		  ratings.at(6).push_back(r);
		  double sum=0;
		  for (size_t i=0; i<ratings.at(6).size(); i++)
			  sum += ratings.at(6).at(i);
		  ave_history = sum/ratings.at(6).size();
	  }
   }
}

void User::calPug(vector<double> genreAve)
{
        // if a user never review a genre of movie, set preference factor to 1,
        // otherwise set to user's average/all user's average
	if (ave_unknown!=0)
	   pug.at(0) = ave_unknown/genreAve.at(0);
	else pug.at(0) = 1;
	if (ave_action!=0)
	   pug.at(1) = ave_action/genreAve.at(1);
	else pug.at(1) = 1;
	if (ave_noir!=0)
	   pug.at(2) = ave_noir/genreAve.at(2);
	else pug.at(2) = 1;
	if (ave_light!=0)
	   pug.at(3) = ave_light/genreAve.at(3);
	else pug.at(3) = 1;
	if (ave_serious!=0)
	   pug.at(4) = ave_serious/genreAve.at(4);
	else pug.at(4) = 1;
	if (ave_fantasy!=0)
	   pug.at(5) = ave_fantasy/genreAve.at(5);
	else pug.at(5) = 1;
	if (ave_history!=0)
	   pug.at(6) = ave_history/genreAve.at(6);
	else pug.at(6) = 1;
}

void User::biasedtopMovies (size_t k, vector<vector<Movie> >topMovies)
{
	vector<Movie> top(0);// vector that hold top K movie
	double topAction,topNoir,topLight,topSerious,topFantasy,topHistory;
         cout << "\nUser " << id << " Preference factor:\n"
		 << " Action: " << pug.at(1) << "\n Noir  : " << pug.at(2) << "\n Light : " << pug.at(3) << "\n Serious: " << pug.at(4) << "\n Fantasy: " << pug.at(5) << "\n History: " << pug.at(6) 
         <<"\n\nTop " << k << " Moive for User " << id << ":" << endl;
	for (size_t i=1; i<=k; i++)
	{
                // get the real rating for all genre's top movie, the top movie for user must form one of those six movie
		topAction = topMovies.at(0).at(0).getRating() * pug.at(1);
		topNoir   = topMovies.at(1).at(0).getRating() * pug.at(2);
		topLight  = topMovies.at(2).at(0).getRating() * pug.at(3);
		topSerious= topMovies.at(3).at(0).getRating() * pug.at(4);
		topFantasy= topMovies.at(4).at(0).getRating() * pug.at(5);
		topHistory= topMovies.at(5).at(0).getRating() * pug.at(6);
                
                // if this genre's top is highest among 6, put it into the vector that hold top k movie
		if (topAction>topNoir && topAction>topLight && topAction>topSerious 
                   && topAction>topFantasy && topAction>topHistory)
		{
			bool repeat=false;
			for (size_t j=0; j<top.size(); j++)
			{
				if (topMovies.at(0).at(0).getIndex() == top.at(j).getIndex())
				{
                                        // if the movie is repeated, do not push in.
					repeat = true;
					k++;
				}
			}
			if (!repeat)
				top.push_back (topMovies.at(0).at(0));
			topMovies.at(0).erase(topMovies.at(0).begin());
                        // erase the top element of this genre, so its second top is now the top.
		}
		else if (topNoir>topLight && topNoir>topSerious && topNoir>topFantasy && topNoir>topHistory)
		{
			bool repeat=false;
			for (size_t j=0; j<top.size(); j++)
			{
				if (topMovies.at(1).at(0).getIndex() == top.at(j).getIndex())
				{
					repeat = true;
					k++;
				}
			}
			if (!repeat)
				top.push_back (topMovies.at(1).at(0));
			topMovies.at(1).erase(topMovies.at(1).begin());
		}
		else if (topLight>topSerious && topLight>topFantasy && topLight>topHistory)
		{
			bool repeat=false;
			for (size_t j=0; j<top.size(); j++)
			{
				if (topMovies.at(2).at(0).getIndex() == top.at(j).getIndex())
				{
					repeat = true;
					k++;
				}
			}
			if (!repeat)
				top.push_back (topMovies.at(2).at(0));
			topMovies.at(2).erase(topMovies.at(2).begin());
		}
		else if (topSerious>topFantasy && topSerious>topHistory)
		{
			bool repeat=false;
			for (size_t j=0; j<top.size(); j++)
			{
				if (topMovies.at(3).at(0).getIndex() == top.at(j).getIndex())
				{
					repeat = true;
					k++;
				}
			}
			if (!repeat)
				top.push_back (topMovies.at(3).at(0));
			topMovies.at(3).erase(topMovies.at(3).begin());
		}
		else if (topFantasy>topHistory)
		{
			bool repeat=false;
			for (size_t j=0; j<top.size(); j++)
			{
				if (topMovies.at(4).at(0).getIndex() == top.at(j).getIndex())
				{
					repeat = true;
					k++;
				}
			}
			if (!repeat)
				top.push_back (topMovies.at(4).at(0));
			topMovies.at(4).erase(topMovies.at(4).begin());
		}
		else 
		{
			bool repeat=false;
			for (size_t j=0; j<top.size(); j++)
			{
				if (topMovies.at(5).at(0).getIndex() == top.at(j).getIndex())
				{
					repeat = true;
					k++;
				}
			}
			if (!repeat)
				top.push_back (topMovies.at(5).at(0));
			topMovies.at(5).erase(topMovies.at(5).begin());
		}
	}
	for (size_t o=0; o<top.size(); o++)
       cout << endl << "#" << o+1 << ":" << endl << top.at(o).toString() << endl;
}

string User::toString () const
{
    ostringstream OUT;
    OUT << "Index: " << id << "\nRating:  \n";
	for (size_t i=0; i<ratings.size(); i++)
	{
        if (i==0)
			OUT << " Average rating of Unknown: " << ave_unknown << "Preference:" << pug.at(0) << " Ratings: ";
        if (i==1)
			OUT << " Average rating of Action : " << ave_action << "Preference:" << pug.at(1) << " Ratings: ";
        if (i==2)
			OUT << " Average rating of Noir   : " << ave_noir << "Preference:" << pug.at(2) << " Ratings: ";
        if (i==3)
			OUT << " Average rating of Light  : " << ave_light << "Preference:" << pug.at(3) << " Ratings: ";
        if (i==4)
			OUT << " Average rating of Serious: " << ave_serious << "Preference:" << pug.at(4) << " Ratings: ";
        if (i==5)
			OUT << " Average rating of Fantasy: " << ave_fantasy << "Preference:" << pug.at(5) << " Ratings: ";
        if (i==6)
			OUT << " Average rating of History: " << ave_history << "Preference:" << pug.at(6) << " Ratings: ";
	    for (size_t j=0; j<ratings.at(i).size(); j++)
        OUT << ratings.at(i).at(j) << ' '; 
        OUT << endl;
	}
	OUT << endl;
    return OUT.str();
}

User_base::User_base ()
{
    // We have 943 users total, with 0 being a dummy user. Thus, we set the size to 944.
    userCollection = new vector<User>(944); 
    for (size_t i=1; i<userCollection->size(); i++)
    {
        // set id for all user.
        // unlike movie_base, we have to set the id for all user first, because the u.data is not sorted by user id
        User curUser (i);
        userCollection->at(i)=(curUser);
	}
}

void User_base::readMovieRat (string fileName, const Movie_base &movieBase)
{
    ifstream* INFILE = new ifstream (fileName.c_str(),ios_base::in);
    if (! INFILE->is_open()) 
        cerr<< "Unable to open file" << endl;
    while (!INFILE->eof())
    {
        int movieN;
        int userID;
		double r;
		int ignore;
		(*INFILE)>>userID;
		(*INFILE)>>movieN;
		(*INFILE)>>r;
		(*INFILE)>>ignore;
		newRating(userID,r,movieBase.getGenre(movieN));// transilate the movie index to movie genre.
	}
}

void User_base::newRating(int id, double r,vector<string> genre)
{
   userCollection->at(id).newRating(r,genre);
}

void User_base::calPugAll(vector<double> genreAve)
{
        // after we have the average rating for each genre, we can use it method to calculate pug for all users
	for (size_t i=1; i<userCollection->size(); i++)
		userCollection->at(i).calPug(genreAve);
}

void User_base::biasedtopMovies (size_t id, size_t k, vector<vector<Movie> >topMovies)
{
   userCollection->at(id).biasedtopMovies(k,topMovies);
}

string User_base::toString () const 
{
    ostringstream OUT;
    //for (size_t i=1;i<userCollection->size();i++)
	   // OUT << userCollection->at(i).toString() << endl;
	    for (size_t i=1;i<4;i++)
	    OUT << userCollection->at(i).toString() << endl;
	return OUT.str();
}
