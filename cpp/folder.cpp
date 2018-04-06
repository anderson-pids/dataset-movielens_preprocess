#include "folder.h"

Folder::Folder(const string path, const string extension)
{
	this->path = path;
	this->extension = extension;
}

Folder::~Folder()
{

}

void Folder::SetExtension(const string extension)
{
	this->extension = extension;
}

vector<string> Folder::GetFiles()
{
	listFilesFilter(path, extension);

	return files;
}

vector<string> Folder::listFilesFilter(string path, string extension)
{
	/* cout << "****Listing all files with extension****" << endl; */
	DIR *pDIR;
	struct dirent *entry;
	
	if( pDIR = opendir(path.c_str()))
	{
		while(entry = readdir(pDIR))
		{
			string name(entry->d_name);

			if(isSignificantFile(entry->d_name) && hasSuffix(name, extension))
			{
				string new_path = path + "/" + name;

				if(isFolder(new_path))
					listFilesFilter(new_path, extension);
				else
					files.push_back(new_path);
			}
		}
		closedir(pDIR);
	}
	else
	{
		cout << "[ERROR] Cannot open file: " << path << endl;		
		exit(1);
	}

	return files;
}

bool Folder::isSignificantFile(const char *entry)
{
	return strcmp(entry, ".") != 0 && strcmp(entry, "..") != 0;
}

bool Folder::hasSuffix(const string &str, const string &suffix)
{
	return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

bool Folder::isFolder(string path)
{
	DIR *pDIR;

	if( pDIR = opendir(path.c_str()))
	{
		closedir(pDIR);
		return true;
	}
	else
	{
		return false;
	}
}