
#include <iostream>
using namespace std;


string longestPalindrome ( const string& str ) {
	int longest = 0, start = 0, end = 0;
	int len = str.length ( );
	bool** table = new bool* [len];
	for ( int i = 0; i < len; i++ ) {
		table[i] = new bool[len];
	}
	for ( int dist = 0; dist < len; dist++ ) {
		for ( int i = 0, j = dist; j < len; j++, i++ ) {
			if ( dist == 0 ) {
				table[i][j] = true;
			}
			else if ( dist == 1 ) {
				table[i][j] = (str[i] == str[j]);
			}
			else {
				// since i+1 --> j-1 is a smaller distance, it must have been covered before
				table[i][j] = (str[i] == str[j] && table[i + 1][j - 1]);
			}
			if ( j - i + 1 > longest && table[i][j] ) {
				start = i;
				end = j;
				longest = j - i + 1;
			}
		}
	}
	return str.substr ( start, longest );
}


int main ( )
{
	string result = longestPalindrome ( "caba" );
	cout << result;
}