#ifndef ML2K_H
#define ML2K_H

#include <iostream>
#include <iomanip>
#include <string>
#include "dataset_base.h"
#include "util.h"

using namespace std;

class ml2k: public Dataset_Base
{
public:
	ml2k(string path, string sim_function, int based);
	~ml2k();
protected:
	int LoadRatings();
};


#endif