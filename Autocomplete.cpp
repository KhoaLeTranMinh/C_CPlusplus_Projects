// Autocomplete.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<map>
#include<string>
#include<vector>

using namespace std;


struct Node {
	bool isWord;
	map<char, Node*> children;
	Node ( ) :
		isWord ( false ), children ( {} ) {}

	Node ( bool isWord, map<char, Node*> children ) :
		isWord ( isWord ), children ( children ) {}
};


class Solution {
private:
	Node* trie;
public:
	Solution ( ) {
		this->trie = new Node ( );
	}

	void build ( vector<string> words ) {
		for ( int i = 0; i < words.size ( ); i++ ) {
			Node* current = this->trie;
			for ( int j = 0; j < words[i].size ( ); j++ ) {
				if ( current->children.find ( words[i][j] ) == current->children.end ( ) ) {
					current->children[words[i][j]] = new Node ( );
				}
				current = current->children[words[i][j]];
			}
			current->isWord = true;
		}

	}

	vector<string> autocomplete ( const string& prefix ) {
		Node* current = this->trie;
		vector<string> result;
		for ( int i = 0; i < prefix.size ( ); i++ ) {
			if ( current->children.find ( prefix[i] ) == current->children.end ( ) ) {
				return {};
			}
			else {
				current = current->children[prefix[i]];
			}
		}
		return findWordsFromNode ( current, prefix, result );
	}

	vector<string> findWordsFromNode ( Node* curr, string prefix, vector<string>& result ) {
		if ( curr->isWord ) {
			result.push_back ( prefix );
		}

		for ( const auto& pair : curr->children ) {
			result = findWordsFromNode ( pair.second, prefix + pair.first, result );
		}

		return result;
	}


};


int main ( )
{
	Solution s;
	s.build ( { "dog","eat","cat", "doge", "door", "dark", "dodge", "dork" } );
	vector<string> result = s.autocomplete ( "do" );
	for ( string s : result ) {
		cout << s << " ";
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file