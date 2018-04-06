#ifndef NMSD_H
#define NMSD_H

#include <iostream>
#include <string>
#include <thread>
#include "similarity_base.h"
using namespace std;

// similarity function for negative mean square difference - nmsd

class nmsd: public similarity_base
{
public:
	nmsd();
	~nmsd();
	int Process();

private:
	int GenerateSimUserMatrix();
	double setCik(int fIndex, int sIndex);
	void calculateSim(mat* ratings, mat* sim, int i, int j);
};


#endif