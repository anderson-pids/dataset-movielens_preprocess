#include "mat.h"

mat::mat()
{
	mLine = 0;
	mData = new vector<map<int, double> *>();
}

mat::mat(int line)
{
	mLine = line;
	mData = new vector<map<int, double> *>(line);

	for(int i = 0; i < line; ++i)
		mData->at(i) = new map<int, double>();
}

mat::~mat()
{
	vector<map<int, double>* >::iterator it = mData->begin();
	for (int i = 0; i < mData->size(); ++i)
	{
		map<int, double>* column = mData->at(i);
		delete column;
	}

	delete mData;
}

void mat::debug()
{
	vector<map<int, double>* >::iterator itLine = mData->begin();

	for(int i =0 ;i < mData->size(); ++i)
	{
		cout << i << endl;

		map<int, double>*column = mData->at(i);
		map<int, double>::iterator itColumn = column->begin();

		for(;itColumn != column->end(); ++itColumn)
		{
			cout << "\t" << itColumn->first << " -> " << itColumn->second << endl;
		}
	}
}

mat* mat::clone(double def_value)
{
	mat *newMat = new mat(mLine);

	for(int i = 0; i < mData->size(); ++i)
	{
		map<int, double>*column = mData->at(i);
		map<int, double>::iterator itColumn = column->begin();

		for(;itColumn != column->end(); ++itColumn)
		{
			newMat->set(i, itColumn->first, def_value);
		}
	}

	return newMat;
}

mat* mat::clone()
{
	mat *newMat = new mat(mLine);

	for(int i = 0; i < mData->size(); ++i)
	{
		map<int, double>*column = mData->at(i);
		map<int, double>::iterator itColumn = column->begin();

		for(;itColumn != column->end(); ++itColumn)
		{
			newMat->set(i, itColumn->first, itColumn->second);
		}
	}

	return newMat;
}

void mat::addLine()
{
	map<int, double> *newLine = new map<int, double>();
	mData->push_back(newLine);
	mLine++;
}

int mat::size()
{
	return mLine;
}

int mat::size(int line)
{
	return mData->at(line)->size();
}

map<int, double>* mat::getLine(int line)
{
	return mData->at(line);	
}
