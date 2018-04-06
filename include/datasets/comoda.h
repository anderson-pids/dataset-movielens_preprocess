#ifndef COMODA_H
#define COMODA_H

#include <iostream>
#include <iomanip>
#include <string>
#include "dataset_base.h"
#include "util.h"

using namespace std;

class comoda: public Dataset_Base
{
public:
	comoda(string path, string sim_function, int based);
	~comoda();
protected:
	int LoadRatings();
};


#endif