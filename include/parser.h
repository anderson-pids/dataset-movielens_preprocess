#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <unordered_map>
#include "types.h"
#include "mat.h"
#include "dataset_base.h"
#include "datasets/ml10m100k.h"
#include "datasets/ml2k.h"
#include "datasets/ml100k.h"
#include "datasets/comoda.h"
#include "datasets/netflix.h"

using namespace std;

class Parser
{
public:
	Parser(string dataset_name, string dataset_path, string sim_function, int based);
	~Parser();
	void Process();
	mat* GetSimMatrix();
	mat* GetRatings();
private:
	
	int mBased;
	string mDataSetPath, mSimFunction;
	Dataset_Base *mDatasetBase;
	mat *mSimMatrix, *mRatings, *mRatingsTest;
	unordered_map<string,Dataset_t> mDatasets;
	Dataset_t mDatasetType;

	// Methods
	void LoadDataSetTypes();
	void GetDataSetType(string dataset_name);
};

#endif