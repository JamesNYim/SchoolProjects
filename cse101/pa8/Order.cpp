//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 7
// Order.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[])
{
	ifstream in;
	ofstream out;
	string line;
	int lineCount = 1;
	if (argc != 3)
	{
		cerr << "Usage: " << argv[0] << "<input file> <output file>" << endl;
		return EXIT_FAILURE;
	}

	//Opening the input file
	in.open(argv[1]);
	if (!in.is_open())
	{
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return EXIT_FAILURE;
	}

	//Opening the output file
	out.open(argv[2]);
	if (!out.is_open())
	{
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return EXIT_FAILURE;
	}

	//Read each line 
	Dictionary d;
	while (getline(in, line))
	{
		d.setValue(line, lineCount);
		lineCount++;
	}
	out << d << endl << endl;;
	out << d.pre_string() << endl;
	
	//Closing Files
	in.close();
	out.close();
	return 0;
}



