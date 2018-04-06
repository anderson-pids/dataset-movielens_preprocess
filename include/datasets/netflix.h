#ifndef NETFLIX_H
#define NETFLIX_H

#include <iostream>
#include <iomanip>
#include <string>
#include "dataset_base.h"
#include "util.h"
#include "mat.h"

using namespace std;

class netflix: public Dataset_Base
{
public:
	netflix(string path, string sim_function, int based);
	~netflix();
protected:
	int LoadRatings();
	int LoadFile(int movieId, vector<int> *acumRatings,int *qtdRatings);
};


#endif