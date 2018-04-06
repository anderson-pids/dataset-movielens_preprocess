#include "similarities/cosine.h"

cosine::cosine():similarity_base()
{
	cout << "Starting cosine.." << endl;
}

cosine::~cosine()
{
	delete mNorma;
	cout << "Finishing cosine.." << endl;
}

int cosine::Process()
{
	CalculateNorma();
	GenerateSimUserMatrix();
	
	return 0;
}

int cosine::CalculateNorma()
{
	int qtd_datapoints = mRatings->size();
	map<int, double>::iterator itLine;
	mNorma = new std::vector<double>(qtd_datapoints,0);

	for (int i = 0; i < qtd_datapoints; ++i)
	{
		itLine = mRatings->getLine(i)->begin();

		for (; itLine != mRatings->getLine(i)->end(); ++itLine)
			mNorma->at(i) = mNorma->at(i) + pow(itLine->second, 2);
		mNorma->at(i) = sqrt(mNorma->at(i));
	}

	return 0;
}

void cosine::calculateSim(mat* ratings, mat* sim, int i, int j)
{
	double sum, result;
	if(ratings->size(i) <= ratings->size(j))
		sum = setCik(i, j);
	else
		sum = setCik(j, i);

	if(sum != INT_MIN)
	{
		result = sum / (mNorma->at(i) * mNorma->at(j)) ;
		// result = log2(result);
		sim_mutex.lock();
		sim->set(i, j, result);
		sim->set(j, i, result);
		sim_mutex.unlock();
	}
}

int cosine::GenerateSimUserMatrix()
{
	cout << "Generating Similarity Sparse Matrix.." << endl;

	int qtd_datapoints = mRatings->size();
	int actual_dp = 0;
	cout << "Total of data points: " << qtd_datapoints << endl;
	int i,j;
	int qtd_th=0, num_threads=7000;
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
				t[k] = thread(&cosine::calculateSim, this, mRatings, mSim, i, j);
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

double cosine::setCik(int fIndex, int sIndex)
{
	double acum = 0;
	int qtd_common = 0;
	map<int, double>::iterator itLine = mRatings->getLine(fIndex)->begin();

	for (; itLine != mRatings->getLine(fIndex)->end(); ++itLine)
	{
		if(mRatings->get(sIndex, itLine->first) != 0)
		{
			qtd_common++;
			acum += mRatings->get(fIndex, itLine->first) * mRatings->get(sIndex, itLine->first);
		}
	}

	//TODO:: return correct value for each limit
	if(qtd_common > 0 && qtd_common < 5)
		return acum; //it needs some adjust to be regularized
	else if(qtd_common >= 5)
		return acum;

	return INT_MIN;
}