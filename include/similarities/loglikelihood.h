#ifndef LOGLIKELIHOOD_H
#define LOGLIKELIHOOD_H

#include <iostream>
#include <string>
#include "similarity_base.h"
using namespace std;

class loglikelihood: public similarity_base
{
public:
	loglikelihood();
	~loglikelihood();
	int Process();
protected:
	// Graph *mCounter;

private:
	int AccumulateRatings();
	int GenerateSimUserMatrix();
};


#endif