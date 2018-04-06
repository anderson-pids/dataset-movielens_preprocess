#include "similarities/nmsd.h"

nmsd::nmsd():similarity_base()
{
	cout << "Starting negative mean-square difference sim. function.." << endl;
}

nmsd::~nmsd()
{
	cout << "Finishing nmsd sim. function.." << endl;
}

int nmsd::Process()
{
	GenerateSimUserMatrix();
	return 0;
}

void nmsd::calculateSim(mat* ratings, mat* sim, int i, int j)
{
	double sum, result;
	if(ratings->size(i) <= ratings->size(j))
		sum = setCik(i, j);
	else
		sum = setCik(j, i);

	if(sum != INT_MIN)
	{
		result = sum;
		// result = log2(result);
		sim_mutex.lock();
		sim->set(i, j, result);
		sim->set(j, i, result);
		sim_mutex.unlock();
	}
}

int nmsd::GenerateSimUserMatrix()
{
	cout << "Generating Similarity Sparse Matrix.." << endl;
	
	int qtd_datapoints = mRatings->size();
	int actual_dp = 0;
	cout << "Total of data points: " << qtd_datapoints << endl;
	int i,j;
	int qtd_th=0, num_threads=7000; //using 50 threads to compute similarity
	thread t[num_threads];

	for(i = 0; i < qtd_datapoints; ++i)
	{
		cout << i + 1 << " ";
		if( (i+1) % 30 == 0)
			cout << endl;

		for (j = i + 1; j < qtd_datapoints; ++j)
		{
			for (int k=0; k < num_threads && j < qtd_datapoints; ++k, ++j){
				// calculateSim(mRatings, mSim, i, j);
				t[k] = thread(&nmsd::calculateSim, this, mRatings, mSim, i, j);
				qtd_th++;
			}

			for (int k=0; k < qtd_th; ++k)
				t[k].join();
			qtd_th = 0;
			j--;
		}
	}

	cout << endl;

	return 0;
}

double nmsd::setCik(int fIndex, int sIndex)
{
	double acum = 0;
	int qtd_common = 0;
	map<int, double>::iterator itLine = mRatings->getLine(fIndex)->begin();

	for (; itLine != mRatings->getLine(fIndex)->end(); ++itLine)
	{
		if(mRatings->get(sIndex, itLine->first) != 0)
		{
			qtd_common++;
			acum += pow(mRatings->get(fIndex, itLine->first) - mRatings->get(sIndex, itLine->first), 2);
		}
	}

	if(qtd_common > 0 && qtd_common < 5)
		return (-1)*( (double)(acum + 2*2*(5 - qtd_common))/5 );
	else if(qtd_common >= 5)
		return (-1)*(acum / qtd_common);

	return INT_MIN;
}