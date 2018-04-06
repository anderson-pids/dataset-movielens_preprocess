#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>

using namespace std;

string StrToLower(string str);
void InitFile(string path);
vector<string> Split(const string &s,  char delim);
string Trim(string &s);

#endif