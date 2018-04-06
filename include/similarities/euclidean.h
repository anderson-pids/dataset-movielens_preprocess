#ifndef EUCLIDEAN_H
#define EUCLIDEAN_H

#include <iostream>
#include <thread>
#include <string>
#include <cmath>
#include "similarity_base.h"
using namespace std;

class euclidean: public similarity_base
{
public:
	euclidean();
	~euclidean();
	int Process();

private:
	int GenerateSimUserMatrix();
	double setCik(int fIndex, int sIndex);
	double setCik2(int fIndex, int sIndex);
	void calculateSim(mat* ratings, mat* sim, int i, int j);
};


#endif