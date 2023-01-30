// $Id: main.cpp,v 1.13 2021-02-01 18:58:18-08 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <regex>
#include <string>
#include <unistd.h>
#include <fstream>
using namespace std;

#include "avl.h"
#include "util.h"
#include "debug.h"

using str_str_map = AVLTree<string,string>;
using str_str_pair = str_str_map::value_type;

void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            debugflags::setflags (optarg);
            break;
         default:
            complain() << "-" << char (optopt) << ": invalid option"
                       << endl;
            break;
      }
   }
}

int main (int argc, char** argv) {
 /* 
   sys_info::execname (argv[0]);
   scan_options (argc, argv);

   str_str_map test;
//   cout << test << endl;
   for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
      str_str_pair pair (*argp, to_string<int> (argp - argv));
      cout << "Before insert: " << pair << endl;
      test.insert (pair);
   }

   cout << test.empty() << endl;
   for (str_str_map::iterator itor = test.begin();
        itor != test.end(); ++itor) {
      cout << "During iteration: " << *itor << endl;
   }

   str_str_map::iterator itor = test.begin();
   test.erase (itor);

*/
    sys_info::execname (argv[0]);
    scan_options (argc, argv);

	str_str_map tree;
	str_str_pair keyValue;

	//Reading through the line variables
	smatch regexResult;
	ifstream infile;
	int lineNo = 0;
	string fileName;
	string currentLine;

	//Regex Expressions
	regex commentRegex {R"(^\s*(#.*)?$)"};
	regex keyValueRegex {R"(^\s*(.*?)\s*=\s*(.*?)\s*$)"};
	regex keyRegex {R"(^\s*(.*)\s*?$)"};
	regex keyEqualsValueRegex {R"(^\s*(.*)\s*=\s*$)"};
	regex equalsRegex {R"(^\s*[=]\s*$)"};
	regex equalsValueRegex {R"(^\s*[=]\s*(.*?)\s*$)"};


	//If there are file inputs
	if (argc > 1)
	{
		for (int inNo = 1; inNo < argc; inNo++)
		{
			
			//Opening the file
			infile.open(argv[inNo]);
			if (!infile.is_open())
			{
				throw "File failed to open";
			}
			fileName = argv[inNo];
		}
		//Checking the input cases
		while (std::getline(infile, currentLine))
		{
			++lineNo;

			//Comment
			if (regex_search(currentLine, regexResult, commentRegex))
			{
				continue;
			}

			//Key
			if (regex_search(currentLine, regexResult, keyRegex))
			{
				string key = regexResult[1];
				//If the key isnt in our tree
				if (tree.find(key) == tree.end())
				{
					cout << fileName << key << ": key not found" << endl;
				}

				//If it is we print
				else
				{
					cout << fileName << *(tree.find(key)) << endl;
				}
			}

			//key = value
			if (regex_search(currentLine, regexResult, keyValueRegex))
			{
				string key = regexResult[1];
				string value = regexResult[2];
				tree.insert({key, value});
				cout << fileName << regexResult[1] << " = " << regexResult[2] << endl;
			}

			//Equals
			if (regex_search(currentLine, regexResult, equalsRegex))
			{
				for (auto iter = tree.begin(); iter != tree.end(); ++iter)
				{
					cout << fileName << *iter << endl;
				}
			}

			//Equals Value
			if (regex_search(currentLine, regexResult, equalsValueRegex))
			{
				for (auto iter = tree.begin(); iter != tree.end(); ++iter)
				{
					if (iter->second == regexResult[2])
					{
						cout << fileName << *iter << endl;
					}
				}
			}
		}
	}
	//Read from cin
	else
	{
		while (std::getline(cin, currentLine))
		{
			++lineNo;

			//Comment
			if (regex_search(currentLine, regexResult, commentRegex))
			{
				continue;
			}

			//Key
			if (regex_search(currentLine, regexResult, keyRegex))
			{
				string key = regexResult[1];
				//If the key isnt in our tree
				if (tree.find(key) == tree.end())
				{
					cout << fileName << key << ": key not found" << endl;
				}

				//If it is we print
				else
				{
					cout << fileName << *(tree.find(key)) << endl;
				}
			}

			//key = value
			if (regex_search(currentLine, regexResult, keyValueRegex))
			{
				string key = regexResult[1];
				string value = regexResult[2];
				tree.insert({key, value});
				cout << fileName << regexResult[1] << " = " << regexResult[2] << endl;
			}

			//Equals
			if (regex_search(currentLine, regexResult, equalsRegex))
			{
				for (auto iter = tree.begin(); iter != tree.end(); ++iter)
				{
					cout << fileName << *iter << endl;
				}
			}

			//Equals Value
			if (regex_search(currentLine, regexResult, equalsValueRegex))
			{
				for (auto iter = tree.begin(); iter != tree.end(); ++iter)
				{
					if (iter->second == regexResult[2])
					{
						cout << fileName << *iter << endl;
					}
				}
			}
		}
	}
/*
	for (; optind < argc; ++optind)
	{
		string line;
		ifstream inFile;
		inFile.open(argv[optind]);
		AVLTree<string, string> T;


		while (getline(inFile, line))
		{
			//If the line is a comment
			regex regexComment {R"(^\s*(#.*)?$)"};
			if (regex_match(line, regexComment) || line.empty())
			{
				//we dont care about this line this is a comment
				//continue;
			}

			regex regex2 {R"([=\s])"};
			if (not regex_match(line, regex2))
			//If we are just printing the line
			{
				if (tree.find(line) != nullptr)
				{
					
					cout << *(tree.find(line)) << endl;
				}
				else
				{
					cout << "key not found" << endl;
				}

			}

			//key = value
			regex regex3 {R"(/[a-zA-Z0-9]+[\s]+=[\s]+[a-zA-Z0-9]/)"};
			if (regex_match(line, regex3))
			{
				//Getting the key n value
				size_t equalsPos = line.find("=");
				string key = line.substr(0, equalsPos);
				string value = line.substr(equalsPos + 1);
				
				//inserting in tree
				tree.insert({key, value});

				//printing
				cout << key << " = " << value << endl;
			}

			//printing the whole thing
			regex regex4 {R"(=)"};
			if (regex_match(line, regex4))
			{
				for (auto iter = tree.begin(); iter != tree.end(); ++iter)
				{
					cout << *iter << endl;
				}
			}

			//Printing out everything with the same value
			regex regex5 {R"(=.*)"};
			if (regex_match(line, regex5))
			{
				size_t equalsPos = line.find("=");
				string value = line.substr(equalsPos + 1);
				for (auto iter = tree.begin(); iter != tree.end(); ++iter)
				{
					if (iter->second == value)
					{
						cout << *iter << endl;
					}
				}
			}
		}
	}
	*/
    cout << "EXIT_SUCCESS" << endl;
    return EXIT_SUCCESS;
}




