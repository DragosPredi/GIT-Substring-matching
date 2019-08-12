#include "Trie.h"

ofstream modified("modified.out");
ofstream added ("added.out");
ofstream deleted("deleted");

Trie *Trie::getNode(void) 
{ 
	Trie *pNode = new Trie; 

	pNode->timestamp = 0; 
	pNode->visited = false;

	for (int i = 0; i < ALPHABET_SIZE; i++) 
		pNode->children[i] = NULL; 

	return pNode; 
} 
int Trie::getIndex(char V)
{
	int index;

	if(V >= 'a' && V <= 'z')
		index = V - 'a';
	else if(V == '\\')
		index = 26;
	else if(V == '_')
		index = 27;
	else if(V == '.')
		index = 28; 
	else if(V == ':')
		index = 29;

	return index;
}
void Trie::insert(Trie *root, string key, int timestamp) 
{ 
	Trie *pCrawl = root; 

	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = getIndex(static_cast<char>(key[i]));
		if (!pCrawl->children[index]) 
			pCrawl->children[index] = getNode(); 

		pCrawl = pCrawl->children[index]; 
	} 

	pCrawl->timestamp = timestamp; 
}

int Trie::search(Trie *root, string key, int timestamp) 
{ 
	Trie *pCrawl = root; 
	
	for (int i = 0; i < key.length(); i++) 
	{ 
		int index = getIndex(static_cast<char>(key[i]));

		if (!pCrawl->children[index]) 
			return ADDED; 

		pCrawl = pCrawl->children[index];
	} 
	bool visited = (pCrawl->visited) ? 1 : 0;
	if(pCrawl->timestamp)
		pCrawl->visited = true;

	if(pCrawl != NULL && pCrawl->timestamp && !visited && pCrawl->timestamp != timestamp)
		return MODIFIED;
	if(pCrawl != NULL && pCrawl->timestamp && !visited && pCrawl->timestamp == timestamp)
		return DELETED;

} 
bool Trie::isEmpty(Trie *root) 
{ 
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        if (root->children[i]) 
            return false; 
    return true; 
} 
Trie *Trie::remove(Trie *root, string key, int depth) 
{ 
    if (!root) 
        return NULL; 

    if (depth == key.size()) 
    { 

        if (root->timestamp) 
            root->timestamp = false; 

        if (isEmpty(root)) 
        { 
            delete (root); 
            root = NULL; 
        } 
  
        return root; 
    } 
  
    int index = getIndex(static_cast<char>(key[depth])); 
    root->children[index] =  
          remove(root->children[index], key, depth + 1); 
  
    if (isEmpty(root) && root->timestamp == false) 
    { 
        delete (root); 
        root = NULL; 
    } 
  
    return root; 
} 
void Trie::createTrie(Trie *root, vector<string> &v, vector<int> &timestamp)
{
	for(int i = 0; i < v.size() ; i++)
	{
		string toLower = v[i];
		transform(toLower.begin(), toLower.end(), toLower.begin(), ::tolower);
		root->insert(root, toLower, timestamp[i]);
	}
}

void Trie::searchTrie(Trie *root, vector<string> &strings, vector<int> &timestamp, bool round)
{
	for(int i = 0 ; i < strings.size() ; i++)
	{
		string toLower = strings[i];
		transform(toLower.begin(), toLower.end(), toLower.begin(), ::tolower);

		int a = root->search(root, toLower, timestamp[i]);
		if(a == Trie::MODIFIED)
			modified << strings[i] << "\n";
		if(a == Trie::DELETED && round == true)
			deleted << strings[i] << "\n";
		if(a == Trie::ADDED)
			added << strings[i] << "\n";
	}
}

void Trie::deleteTrie(Trie *root, const vector<string> previous)
{
	for(int i = 0; i < previous.size(); i++)
	{
		string toLower = previous[i];
		transform(toLower.begin(), toLower.end(), toLower.begin(), ::tolower);
		root->remove(root, toLower);
	}
}