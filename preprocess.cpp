#include <iostream>

#include "include/parser.h"
#include "include/mat.h"

using namespace std;

string dataset_name;
string dataset_path;
string sim_function;
int based=0;

void GetDatasetName(int argc, char *argv[]);
void PrintPair(string filename,mat *rating);
void PrintSimilarities(string filename, mat *sim, int start_at);

int main(int argc, char *argv[])
{
	GetDatasetName(argc, argv);
	
	Parser *p = new Parser(dataset_name, dataset_path, sim_function, based);
	p->Process();

	mat *sim = p->GetSimMatrix();
	mat *ratings = p->GetRatings();
	mat *ratingsTest = p->GetRatingsTest();

	PrintSimilarities("similarities.dat",sim, 1);
	PrintPair("ratingsTrain.dat",ratings);
	PrintPair("ratingsTest.dat",ratingsTest);

	delete p;	
	return 0;
}

void GetDatasetName(int argc, char *argv[])
{
	if(argc == 4)
	{
		dataset_name = argv[1];
		dataset_path = argv[2];
		sim_function = argv[3];
	}
	else if(argc == 5)
	{
		dataset_name = argv[1];
		dataset_path = argv[2];
		sim_function = argv[3];
		based = atoi(argv[4]);
	}
	else
	{
		cout << "[Error] Missing parameters!" << endl;
		cout << "[INFO] preprocess <DATASET_NAME> <DATASET_PATH> <SIM_FUNCTION> [BASED=0]" << endl;
		cout << "*BASED=0 -> User Based" << endl;
		cout << "*BASED=1 -> Item Based" << endl;
		exit(1);
	}
}

void PrintPair(string filename,mat *rating)
{
	fstream fs;
	fs.open(filename, ios::out);
	int qtd_datapoints = rating->size();
	map<int, double>::iterator itLine;

	for (int i = 0; i < qtd_datapoints; ++i)
	{
		itLine = rating->getLine(i)->begin();
		fs << i << endl;
		fs << itLine->first << " " << itLine->second;
		itLine++;
		for (; itLine != rating->getLine(i)->end(); ++itLine)
			fs << " " << itLine->first << " " << itLine->second;
		fs << endl;
	}

	fs.close();
}

void PrintSimilarities(string filename, mat *sim, int start_at)
{
	fstream fs;
	fs.open(filename, ios::out);
	int qtd_datapoints = sim->size();
	map<int, double>::iterator itLine;
	
	for (int i = 0; i < qtd_datapoints; ++i)
	{
		itLine = sim->getLine(i)->begin();
		for (; itLine != sim->getLine(i)->end(); ++itLine)
			fs << i + start_at << "  " << itLine->first + start_at << "  " << itLine->second << endl;
	}

	fs.close();
}