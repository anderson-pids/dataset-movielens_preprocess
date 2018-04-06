#ifndef CORRELATION_H
#define CORRELATION_H

#include <iostream>
#include <string>
#include <cmath>
#include <thread>
#include <vector>
#include "similarity_base.h"
using namespace std;

class correlation: public similarity_base
{
public:
	correlation();
	~correlation();
	int Process();
protected:
	vector<double> *mNorma;
	vector<double> *mMean;

private:
	int GenerateSimUserMatrix();
	int CalculateNorma();
	int CalculateMean();
	double setCik(int fIndex, int sIndex);
	double setCik2(int fIndex, int sIndex);

	void calculateSim(mat* ratings, mat* sim, int i, int j);
};


#endif