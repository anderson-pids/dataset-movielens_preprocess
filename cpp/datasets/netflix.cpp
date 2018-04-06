#include "datasets/netflix.h"

netflix::netflix(string path, string sim_function, int based):Dataset_Base(path, sim_function, based)
{
	cout << "Starting Netflix prize..(#tip: Netflix folder path)" << endl;
}

netflix::~netflix()
{
	cout << "Finishing netflix prize.." << endl;
}

int netflix::LoadRatings()
{
	cout << "Loading Ratings.." << endl;
	
	string lineId;
	int id;
	
	//statistics
	vector<int> *acumRatings = new vector<int>(5,0);
	int qtdRatings = 0;

	for(int i=0; i < mFiles.size(); ++i)
	{
		cout << "Reading: " << mFiles[i] << " --> (" << i + 1 <<  "/"<< mFiles.size() << ")" << endl;
		mFs.open(mFiles[i].c_str(), ios::in);

		if(!mFs.is_open())
		{
			cout << "[ERROR] Cannot open file: " << mFiles[i] << endl;
			exit(1);
		}

		getline(mFs,lineId);
		id = atoi(lineId.substr(0, lineId.size() - 1).c_str());
		LoadFile(id, acumRatings, &qtdRatings);
		mFs.close();
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
	long int totalMatrix = (long int)mRefBased->size() * mRefSecondary->size();
	long int totalGaps = totalMatrix - qtdRatings;

	cout << "Total matrix: " << totalMatrix << endl;
	cout << "Dataset sparsity: " << fixed << setprecision(2) << ((double)totalGaps/totalMatrix)*100 << "\%" << endl;

	delete acumRatings;

	return 0;
}

int netflix::LoadFile(int movieId,vector<int> *acumRatings,int *qtdRatings)
{

	string line;
	vector<string> relation;
	string userId, rating;
	int basedId, secondaryId;
	int indexDataPoint, indexsecDataPoint;
	unordered_map<int,int>::iterator itDataPoint;

	while(getline(mFs, line))
	{
		relation = Split(line, ',');

		userId = relation[0];
		rating = relation[1];

		if(!mBased)
		{
			basedId = atoi(userId.c_str());
			secondaryId = movieId;
		}
		else
		{
			basedId = movieId;
			secondaryId = atoi(userId.c_str());
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

		mRatings->set(indexDataPoint, indexsecDataPoint, stod(rating));
		
		//acumulate for statistics
		acumRatings->at(atoi(rating.c_str()) - 1) += 1;
		*qtdRatings += 1;		
	}

	return 0;
}