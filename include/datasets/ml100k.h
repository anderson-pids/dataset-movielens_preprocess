#ifndef ML100K_H
#define ML100K_H

#include <iostream>
#include <iomanip>
#include <string>
#include "dataset_base.h"
#include "util.h"

using namespace std;

class ml100k: public Dataset_Base
{
public:
	ml100k(string path, string sim_function, int based);
	~ml100k();
protected:
	int LoadRatings();
};
#endif