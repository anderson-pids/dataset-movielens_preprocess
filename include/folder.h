#ifndef FOLDER_H
#define FOLDER_H

#include <iostream>
#include <vector>
#include <dirent.h>
#include <cstring>

using namespace std;

class Folder
{
public:
	Folder(const string path, const string extension="");
	~Folder();
	void SetExtension(const string extension);
	vector<string> GetFiles();
	bool isFolder(string path);
private:
	string path, extension;
	vector<string> files;
	vector<string> listFilesFilter(string path, string extension);
	bool isSignificantFile(const char *entry);
	bool hasSuffix(const string &str, const string &suffix);

};

#endif