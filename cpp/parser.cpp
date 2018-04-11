#include "parser.h"

Parser::Parser(string dataset_name, string dataset_path, string sim_function, int based)
{
	cout << "Init parser.." << endl;
	this->LoadDataSetTypes();
	this->GetDataSetType(dataset_name);
	mDataSetPath = dataset_path;
	mSimFunction = sim_function;
	mBased = based;

	string type_based = (based)?"Item based":"User based";
	cout << "Parsing dataset in " << type_based << " model" << endl; 
}

Parser::~Parser()
{
	delete mSimMatrix;
	delete mRatings;
	delete mRatingsTest;
	// delete mDatasetBase; -- deleted after Process method
	cout << "Finishing parser.." << endl;
}

void Parser::LoadDataSetTypes()
{
	mDatasets["comoda"] = COMODA;
	mDatasets["ml2k"] = ML2K;
	mDatasets["ml100k"] = ML100K;
	mDatasets["ml10m100k"] = ML10M100K;
	mDatasets["ml1m"] = ML1M;
	mDatasets["toy"] = TOY;
	mDatasets["netflix"] = NETFLIXPRIZE;
}

void Parser::GetDataSetType(string dataset_name)
{
	unordered_map<string,Dataset_t>::iterator it = mDatasets.find(dataset_name);

	if(it != mDatasets.end())
		mDatasetType = it->second;
	else
	{
		cout << "[ERROR] Dataset not found!" << endl;
		cout << "[INFO] Available datasets:" << endl;
		unordered_map<string, Dataset_t>::iterator itShow = mDatasets.begin();

		for (; itShow != mDatasets.end(); ++itShow)
		{
			cout << "[INFO] " << itShow->first << endl;
		}

		exit(1);
	}
}

void Parser::Process()
{
	switch(mDatasetType)
	{
		case ML10M100K:
		case ML1M:
			{
				cout << "Movie Lens 10M100K | 1M processing.." << endl;
				mDatasetBase = new ml10m100k(mDataSetPath,mSimFunction,mBased);
				break;
			}
		case NETFLIXPRIZE:
			{
				cout << "Netflix prize processing.." << endl;
				mDatasetBase = new netflix(mDataSetPath, mSimFunction, mBased);
				break;
			}
		case ML2K:
			{
				cout << "Movie Lens 2K processing.." << endl;
				mDatasetBase = new ml2k(mDataSetPath, mSimFunction, mBased);
				break;
			}
		case TOY:
			{
				cout << "Toy processing.." << endl;
				mDatasetBase = new ml2k(mDataSetPath, mSimFunction, mBased);
				break;
			}
		case ML100K:
			{
				cout << "Movie Lens 100K processing.." << endl;
				mDatasetBase = new ml100k(mDataSetPath, mSimFunction, mBased);				
				break;
			}
		case COMODA:
			{
				cout << "CoMoDa processing.." << endl;
				mDatasetBase = new comoda(mDataSetPath, mSimFunction, mBased);				
				break;
			}
		default:
			cout << "...No dataset selected" << endl;
			break;
	}

	mDatasetBase->Process();
	mSimMatrix = mDatasetBase->GetMatrix();
	mRatings = mDatasetBase->GetRatings();

	delete mDatasetBase;
}

mat* Parser::GetSimMatrix()
{
	return mSimMatrix;
}

mat* Parser::GetRatings()
{
	return mRatings;
}