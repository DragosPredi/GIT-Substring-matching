// C++ implementation of search and insert cat
// operations on Trie 
#include <bits/stdc++.h> 
using namespace std; 
#include "Trie.h"



vector<string> createGitIgnore()
{
	vector<string> ignore;
	string stringToRead;

	ifstream gitignore;
	gitignore.open("gitignore.in");

	while(gitignore >> stringToRead){
		transform(stringToRead.begin(), stringToRead.end(), stringToRead.begin(), ::tolower);
		ignore.push_back(stringToRead);
	}
	gitignore.close();
	
	return ignore;
}
vector<regex> createRegex()
{
	vector<regex> regexPatterns;
	string stringToRead;

	ifstream gitignore;
	gitignore.open("gitignore_regex.in");

	while(gitignore >> stringToRead){
		transform(stringToRead.begin(), stringToRead.end(), stringToRead.begin(), ::tolower);
		regexPatterns.push_back(static_cast<regex>(stringToRead));
	}

	gitignore.close();

	return regexPatterns;
}

void createVersionWGit(const vector<string> ignore, string fileName, vector<string> &v, vector<int> &timestamp)
{
	ifstream inFile;
	inFile.open(fileName);

	string stringToRead;
	int timestampToRead;

	while(inFile >> stringToRead >> timestampToRead)
	{
		string toLower = stringToRead;
		transform(toLower.begin(), toLower.end(), toLower.begin(), ::tolower);
		bool isFound = false;
		for(int i = 0 ; i < ignore.size() ; i++)
			if(toLower.find(ignore[i]) != string::npos)
				isFound = true;
			
		if(isFound == false)
		{
			v.push_back(stringToRead);
			timestamp.push_back(timestampToRead);
		}
	}
	inFile.close();
}

void createVersionWRegex(const vector<regex> ignore, string fileName, vector<string> &v, vector<int> &timestamp)
{
	ifstream inFile;
	inFile.open(fileName);

	string stringToRead;
	int timestampToRead;
	while(inFile >> stringToRead >> timestampToRead)
	{
		string toLower = stringToRead;
		transform(toLower.begin(), toLower.end(), toLower.begin(), ::tolower);
		bool isFound = false;
		for(int i = 0 ; i < ignore.size() ; i++)
			if(regex_match(toLower, ignore[i]) == true)
				isFound = true;

		if(isFound == false)
		{
			v.push_back(stringToRead);
			timestamp.push_back(timestampToRead);
		}
	}
	inFile.close();
}

void createVersionNoGit(string fileName, vector<string> &v, vector<int> &timestamp)
{
	ifstream inFile;
	inFile.open(fileName);

	string stringToRead;
	int timestampToRead;

	while(inFile >> stringToRead >> timestampToRead)
	{
		v.push_back(stringToRead);
		timestamp.push_back(timestampToRead);
	}

	inFile.close();

}



int main() 
{ 
	int task;
	cout << "Ce task doriti rezolvat?" << "\n";
	cout << "Apasati 1-->task1 || 2-->task2 || 3-->task3" << "\n";
	cin >> task;

	/*
		Pentru fiecare task modul de rezolvare este similar
		creez vectorii previous si current si ignore daca este cazul
		creez trie
		parcurg trie de 2 ori
		dealoc memoria
	*/
	if(task == 1)
	{
		vector<string> previous, current;
		vector<int> timestampPrevious, timestampCurrent;

		createVersionNoGit("previous.in", previous, timestampPrevious);
		createVersionNoGit("current.in", current, timestampCurrent);

		Trie *root = root->getNode();

		root->createTrie(root, previous, timestampPrevious);

		root->searchTrie(root, current, timestampCurrent, false);
		root->searchTrie(root, previous, timestampPrevious, true);
	}
	if(task == 2)
	{
		vector<string> previous, current;
		vector<int> timestampPrevious, timestampCurrent;
		vector<string> ignore = createGitIgnore();

		createVersionWGit(ignore, "previous.in", previous, timestampPrevious);
		createVersionWGit(ignore, "current.in", current, timestampCurrent);

		Trie *root = root->getNode();

		root->createTrie(root, previous, timestampPrevious);

		root->searchTrie(root, current, timestampCurrent, false);
		root->searchTrie(root, previous, timestampPrevious, true);

		root->deleteTrie(root, previous);
	}
	if(task == 3)
	{
		vector<string> previous, current;
		vector<int> timestampPrevious, timestampCurrent;
		vector<regex> ignore = createRegex();

		createVersionWRegex(ignore, "previous.in", previous, timestampPrevious);
		createVersionWRegex(ignore, "current.in", current, timestampCurrent);
		
		Trie *root = root->getNode();

		root->createTrie(root, previous, timestampPrevious);

		root->searchTrie(root, current, timestampCurrent, false);
		root->searchTrie(root, previous, timestampPrevious, true);

		root->deleteTrie(root, previous);
	}
	
	return 0; 
} 
