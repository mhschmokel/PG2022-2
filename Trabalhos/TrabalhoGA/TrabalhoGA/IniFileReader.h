#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class IniFileReader
{
	public:
		IniFileReader();
		void init(string filePath);
		string getValueByKey(string key);

	private:
		vector <string> fileContent;
};

