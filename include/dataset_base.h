#ifndef DATASET_BASE_H
#define DATASET_BASE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <ctime>
#include <cstdio>
#include <cstdlib>

#include "mat.h"
#include "folder.h"
#include "similarity_base.h"
#include "similarities/nmsd.h"
#include "similarities/cosine.h"
#include "similarities/correlation.h"
#include "similarities/euclidean.h"
#include "similarities/loglikelihood.h"

using namespace std;

class Dataset_Base //interface for dataset's
{
public:
	Dataset_Base(string base_path, string simFunction, int based);
	virtual ~Dataset_Base(); //let destructor enable for children classes
	int Process(); //pure virtual function for processing dataset
	mat* GetMatrix();
	mat* GetRatings();
	unordered_map<int,int>* GetReference();
protected:
	string mPath;
	fstream mFs;
	vector<string> mFiles;
	int mBased;
	similarity_base *mSimFunction;
	unordered_map<string,Similarity_t> mSimilarities;
	
	/**** must be updated in children classes ****/
	mat *mRatings, *mSim;
	unordered_map<int,int> *mRefBased, *mRefSecondary; // Relation between original ids with preprocess ids - based
	
	void Initialize(Similarity_t simType);
	void LoadSimTypes();
	Similarity_t GetSimType(string sim_name);
	virtual int LoadRatings() = 0;
	void PrintReferences();
};

#endif