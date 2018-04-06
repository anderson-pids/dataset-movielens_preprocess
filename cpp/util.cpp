#include "util.h"

string StrToLower(string str)
{
	for (unsigned i = 0; i < str.size(); i++)
	{
		char b=str[i];
		if ((b>='A')&&(b<='Z'))
			str[i]=b-'A'+'a';
	}

	return str;
}

void InitFile(string path)
{
	fstream fsin(path, ios::in);

	if(fsin.is_open())
		remove(path.c_str());

	fsin.close();
	fsin.open(path, ios::in | ios::out | ios::app);
	fsin.close();	
}

vector<string> &split(const std::string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> Split(const string &s,  char delim) {
    vector<string> elems;
    split(s, delim, elems);
    
    return elems;
}

// trim from begin
string &ltrim(string &s)
{
    s.erase(s.begin(), find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));
    
    return s;
}

// trim from end
string &rtrim(string &s)
{
    s.erase(find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(), s.end());
    
    return s;
}

// trim from both ends
string Trim(string &s)
{
    return ltrim(rtrim(s));
}