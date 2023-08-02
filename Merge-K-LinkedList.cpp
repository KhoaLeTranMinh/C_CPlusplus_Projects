// TestingStuff.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<queue>
#include<math.h>
#include <map>
#include<unordered_map>
#include<vector>
using namespace std;




struct ListNode {
	int val;
	ListNode* next;
	ListNode ( ) : val ( 0 ), next ( nullptr ) {}
	ListNode ( int x ) : val ( x ), next ( nullptr ) {}
	ListNode ( int x, ListNode* next ) : val ( x ), next ( next ) {}

};

void merge ( int value, int times, ListNode* pushed ) {
	ListNode* tracking = pushed;
	while ( tracking->next != NULL ) {
		tracking = tracking->next;
	}
	for ( int i = 0; i < times; i++ ) {
		ListNode* another = new ListNode ( value );
		tracking->next = another;
		tracking = another;
	}


}

void listTrim ( vector<ListNode*>& lists ) {
	while ( !lists.empty ( ) ) {
		ListNode* listExtra = NULL;
		for ( int i = 0; i < lists.size ( ); i++ ) {
			if ( lists[i] == NULL ) {
				lists.erase ( lists.begin ( ) + i );
			}
		}
		// If we can't find any elements with NULL value;
		if ( find ( lists.begin ( ), lists.end ( ), listExtra ) == lists.end ( ) ) {
			break;
		}
	}
}

ListNode* mergeKLists ( vector<ListNode*>& lists ) {
	/*while ( find ( lists.begin ( ), lists.end ( ), NULL ) != lists.end ( ) ) {
		vector<ListNode*> ::iterator it = find ( lists.begin ( ), lists.end ( ), NULL );
		lists.erase ( it );
	}*/

	listTrim ( lists );
	if ( lists.empty ( ) ) {
		return NULL;
	}
	ListNode* result = new ListNode ( );
	while ( !lists.empty ( ) )
	{
		vector<int> entry;
		for ( int i = 0; i < lists.size ( ); i++ ) {
			entry.push_back ( lists[i]->val );
		}
		int smallestElement = *min_element(entry.begin ( ), entry.end ( ) );
		map<int, int> tracking;
		for ( int i = 0; i < lists.size ( ); i++ ) {


			if ( tracking.find ( lists[i]->val ) != tracking.end ( ) ) {
				tracking[lists[i]->val]++;
			}
			else {
				tracking.insert ( pair<int, int> ( lists[i]->val, 1 ) );

			}
			if ( lists[i]->val == smallestElement ) {
				ListNode* deleted = lists[i];
				lists[i] = (lists[i]->next) ? lists[i]->next : NULL;
				delete deleted;
			}

		}
		listTrim ( lists );

		int times = tracking[smallestElement];
		merge ( smallestElement, times, result );

	}
	ListNode* lastDel = result;
	result = result->next;
	delete lastDel;
	return result;
}

int main ( ) {
	ListNode* list1 = NULL;
	ListNode* list2 = new ListNode ( -1, new ListNode ( 5 ) );
	ListNode* list3 = new ListNode ( 1, new ListNode ( 4, new ListNode ( 6 ) ) );
	ListNode* list4 = new ListNode ( 4, new ListNode ( 5, new ListNode ( 6 ) ) );
	vector<ListNode*> checking{ list1,list2,list3,list4 };
	ListNode* result = mergeKLists ( checking );
	ListNode* print = result;
	while ( print != NULL ) {
		cout << print->val << " ";
		print = print->next;
	}
	return 0;
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