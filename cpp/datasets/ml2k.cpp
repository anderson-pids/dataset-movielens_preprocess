#include "datasets/ml2k.h"

ml2k::ml2k(string path, string sim_function, int based):Dataset_Base(path, sim_function, based)
{
}

ml2k::~ml2k()
{
}

int ml2k::LoadRatings()
{
	cout << "Loading Ratings.." << endl;

	string line;
	vector<string> relation;
	int userId, movieId;
	double rating;
	int basedId, secondaryId;
	int indexDataPoint, indexsecDataPoint;
	int auxRating;
	unordered_map<int,int>::iterator itDataPoint;

	//statistics
	vector<int> *acumRatings = new vector<int>(5,0);
	int qtdRatings = 0;

	cout << "Reading first line header..." << endl;
	getline(mFs, line);

	cout << "Reading ratings..." << endl;

	while(getline(mFs, line))
	{
		relation = Split(line, '\t');

		userId = atoi(relation[0].c_str());
		movieId = atoi(relation[1].c_str());
		rating = stod(relation[2].c_str());

		if(!mBased)
		{
			basedId = userId;
			secondaryId = movieId;
		}
		else
		{
			basedId = movieId;
			secondaryId = userId;
		}
		
		// Add based data Point
		itDataPoint = mRefBased->find(basedId);
		if(itDataPoint == mRefBased->end())
		{
			indexDataPoint = mRefBased->size();
			mRefBased->insert(make_pair(basedId, indexDataPoint));
			mRatings->addLine();
		}
		else indexDataPoint = itDataPoint->second;

		// Add secondary data point
		itDataPoint = mRefSecondary->find(secondaryId);
		if(itDataPoint == mRefSecondary->end())
		{
			indexsecDataPoint = mRefSecondary->size();
			mRefSecondary->insert(make_pair(secondaryId, indexsecDataPoint));
		}
		else indexsecDataPoint = itDataPoint->second;

		mRatings->set(indexDataPoint, indexsecDataPoint, round(rating));

		//TODO:: resolve case for float ratings - ex: 3.5 => it's gonna be rounded, for now
		//acumulate for statistics
		auxRating = round(rating);
		acumRatings->at(auxRating-1) += 1;
		qtdRatings++;
	}

	cout << "Finished reading of dataset..." << endl;
	cout << "*** Statistics Information ***" << endl;

	if(!mBased)
	{
		cout << "Users: " << mRefBased->size() << endl;
		cout << "Movies: " << mRefSecondary->size() << endl;
	}
	else
	{
		cout << "Movies: " << mRefBased->size() << endl;
		cout << "Users: " << mRefSecondary->size() << endl;
	}

	cout << "Number of Ratings: " << qtdRatings << endl;
	// show % per type of rating
	for(int i=0; i < acumRatings->size(); ++i)
		cout << "\t[" << i + 1 << "] => " << acumRatings->at(i) << " (" << fixed << setprecision(2) << ((double)acumRatings->at(i)/qtdRatings)*100 << "\%)" << endl;

	// show dataset sparsity
	int totalMatrix = mRefBased->size() * mRefSecondary->size();
	int totalGaps = totalMatrix - qtdRatings;
	cout << "Dataset sparsity: " << fixed << setprecision(2) << ((double)totalGaps/totalMatrix)*100 << "\%" << endl;

	delete acumRatings;

	return 0;
}