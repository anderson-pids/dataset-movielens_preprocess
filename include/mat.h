#ifndef MAT_H
#define MAT_H

#include <iostream>
// #include <unordered_map>
#include <map>
#include <vector>

using namespace std;

class mat
{
public:
	mat(int line);
	mat();
	~mat();
	
	void debug();
	mat* clone();
	mat* clone(double def_value);

	inline double get(int line, int column)
	{
		map<int,double>::iterator itColumn = mData->at(line)->find(column);

		if (itColumn != mData->at(line)->end())
			return itColumn->second;
		else
			return 0;
	}

	inline void set(int line, int column, double value)
	{
		map<int, double> *col = mData->at(line);

		map<int,double>::iterator itColumn = mData->at(line)->find(column);
		if(itColumn != mData->at(line)->end())
			itColumn->second = value;
		else
			mData->at(line)->insert(make_pair(column, value));
	}

	void addLine();
	int size();
	int size(int line);
	map<int, double>* getLine(int i);

private:
	vector<map<int, double>*> *mData;
	int mLine;
	int mColumn;
};
#endif