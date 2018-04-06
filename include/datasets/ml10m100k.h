#ifndef ML10M100K_H
#define ML10M100K_H

#include <iostream>
#include <iomanip>
#include <string>
#include "dataset_base.h"
#include "util.h"

using namespace std;

class ml10m100k: public Dataset_Base
{
public:
	ml10m100k(string path, string sim_function, int based);
	~ml10m100k();
private:
	int LoadRatings();
};
#endif