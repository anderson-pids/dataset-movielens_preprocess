#include "dataset_base.h"

Dataset_Base::Dataset_Base(string base_path, string simFunction, int based)
{
	mPath = base_path;
	mBased = based;
	srand(time(NULL));
	LoadSimTypes();
	Similarity_t type = GetSimType(simFunction);
	Initialize(type);	
}

Dataset_Base::~Dataset_Base()
{
	delete mRefBased;
	delete mRefSecondary;
	delete mRatings;
	delete mSim;
	delete mSimFunction;
	mFs.close();
}

void Dataset_Base::LoadSimTypes()
{
	mSimilarities["euclidean"] = EUCLIDEAN;
	mSimilarities["cosine"] = COSINE;
	mSimilarities["correlation"] = CORRELATION;
	mSimilarities["loglikelihood"] = LOGLIKELIHOOD;
	mSimilarities["nmsd"] = NMSD;
}

Similarity_t Dataset_Base::GetSimType(string sim_name)
{
	unordered_map<string,Similarity_t>::iterator it = mSimilarities.find(sim_name);

	if(it != mSimilarities.end())
		return it->second;
	else
	{
		cout << "[ERROR] Similarity function not found!" << endl;
		cout << "[INFO] Available similarity functions:" << endl;
		unordered_map<string, Similarity_t>::iterator itShow = mSimilarities.begin();

		for (; itShow != mSimilarities.end(); ++itShow)
		{
			cout << "[INFO] " << itShow->first << endl;
		}

		exit(1);
	}
}

void Dataset_Base::Initialize(Similarity_t simType)
{

	mRatings = new mat();
	mRefBased = new unordered_map<int,int>();
	mRefSecondary = new unordered_map<int,int>();
	string basePath = mPath;

	cout << "Initializing dataset from [" << basePath << "]" << endl;

	Folder f(mPath);

	// if dataset is one file open the file, otherwise load a vector of files
	if(!f.isFolder(mPath))
	{
		mFs.open(basePath.c_str(), ios::in);

		if(!mFs.is_open())
		{
			cout << "[ERROR] Cannot open file: " << basePath << endl;
			exit(1);
		}
	}
	else
		mFiles = f.GetFiles();


	switch(simType){
		case EUCLIDEAN:{
			cout << "Using Euclidean similarity function..." << endl;
			mSimFunction = new euclidean();
			break;
		}
		case COSINE:{
			cout << "Using Cosine similarity function..." << endl;
			mSimFunction = new cosine();
			break;
		}
		case CORRELATION:{
			cout << "Using Correlation similarity function..." << endl;
			mSimFunction = new correlation();
			break;			
		}
		case LOGLIKELIHOOD:{
			cout << "Using Log Likelihood similarity function..." << endl;
			mSimFunction = new loglikelihood();
			break;
		}
		case NMSD:{
			cout << "Using Average similarity function..." << endl;
			mSimFunction = new nmsd();
			break;
		}
	}

}

mat* Dataset_Base::GetMatrix()
{
	return mSim->clone();
}

mat* Dataset_Base::GetRatings()
{
	return mRatings->clone();
}

int Dataset_Base::Process()
{
	cout << "**********Information of dataset**********" << endl;
	LoadRatings();
	PrintReferences();
	cout << "**********End of dataset**********" << endl;

	//similarity function
	mSimFunction->SetMatrix(mRatings);
	mSimFunction->SetSecElementsSize(mRefSecondary->size());
	mSimFunction->Process();
	mSim = mSimFunction->GetMatrix();

	return 0;
}

void Dataset_Base::PrintReferences()
{
	fstream fs;
	/* Print based Ids */
	/* original_id preprocess_id */
	fs.open("referencesId_based.dat", ios::out);
	unordered_map<int,int>::iterator it = mRefBased->begin();

	for (;it != mRefBased->end(); ++it)
		fs << it->first << " " << it->second << endl;

	fs.close();

	/* Print secondary Ids */
	/* original_id preprocess_id */
	fs.open("referencesId_secondary.dat", ios::out);
	it = mRefSecondary->begin();

	for (;it != mRefSecondary->end(); ++it)
		fs << it->first << " " << it->second << endl;
	fs.close();
}
