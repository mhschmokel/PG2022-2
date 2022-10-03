#include "IniFileReader.h"

IniFileReader::IniFileReader()
{
}

void IniFileReader::init(string filePath)
{
	string text;
	ifstream MyReadFile(filePath);

	while (getline(MyReadFile, text)) 
	{	
		fileContent.push_back(text);
	}

	MyReadFile.close();
}

string IniFileReader::getValueByKey(string key)
{
	for (int i = 0; i < fileContent.size(); i++)
	{
		if (fileContent[i].substr(0, key.size()) == key) 
		{
			return fileContent[i].substr(key.size() + 1);
		}
	}
	return string();
}
