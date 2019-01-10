//============================================================================
// Name        : StableMatching.cpp
// Author      : Otakar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Deque.h"

#include <iostream>
using std::cout;
using std::endl;

#include <stdexcept>
using std::runtime_error;

// ============================================================================
int main() {

	int currProposer = -1;
	int currWoman = -1;
	int currHusband = -1;
	int n = 6;					// number of men and women each

	try{
			// 1) Create and load queue with free men
		    Deque dm;
		    for (int i = n; i > 0; i--){
		    	dm.insert_front(i-1);
		    }

		    cout << "\nPrinting men queue: ";
		    dm.printDeque();

		    // 2) Create and load array of deques with mens preferences
		    // TODO: Load prefs from .txt file and enqueue them
		    Deque mPrefs[n];
		    mPrefs[0].insert_front(4); mPrefs[0].insert_front(1); mPrefs[0].insert_front(2);
		    mPrefs[0].insert_front(0); mPrefs[0].insert_front(5); mPrefs[0].insert_front(3);

		    mPrefs[1].insert_front(5); mPrefs[1].insert_front(2); mPrefs[1].insert_front(0);
		    mPrefs[1].insert_front(1); mPrefs[1].insert_front(4); mPrefs[1].insert_front(3);

		    mPrefs[2].insert_front(4); mPrefs[2].insert_front(2); mPrefs[2].insert_front(3);
		    mPrefs[2].insert_front(0); mPrefs[2].insert_front(5); mPrefs[2].insert_front(1);

		    mPrefs[3].insert_front(2); mPrefs[3].insert_front(5); mPrefs[3].insert_front(1);
		    mPrefs[3].insert_front(4); mPrefs[3].insert_front(3); mPrefs[3].insert_front(0);

		    mPrefs[4].insert_front(4); mPrefs[4].insert_front(5); mPrefs[4].insert_front(1);
		    mPrefs[4].insert_front(3); mPrefs[4].insert_front(0); mPrefs[4].insert_front(2);

		    mPrefs[5].insert_front(4); mPrefs[5].insert_front(3); mPrefs[5].insert_front(5);
		    mPrefs[5].insert_front(0); mPrefs[5].insert_front(2); mPrefs[5].insert_front(1);

			//cout << "\nPrinting m Prefs (deque):";					// DEBUG
		    //cout << "\nm0: "; mPrefs[0].printDeque();
		    //cout << "\nm1: "; mPrefs[1].printDeque();
		    //cout << "\nm2: "; mPrefs[2].printDeque();
		    //cout << "\nm3: "; mPrefs[3].printDeque();
		    //cout << "\nm4: "; mPrefs[4].printDeque();
		    //cout << "\nm5: "; mPrefs[5].printDeque();

		    // 3) Create arrays with womens preferences
		    int wPrefs [6][6] = {  							// TODO: later, load prefs
		    		{5, 1, 2, 0, 4, 3},						//       from .txt file
					{0, 2, 3, 5, 4, 1},
					{5, 2, 3, 1, 4, 0},
					{5, 1, 2, 4, 0, 3},
					{4, 2, 3, 0, 1, 5},
					{4, 3, 1, 5, 0, 2}		};
		    /*
		    cout << "\n\nwPrefs:";							// PRINT wPrefs - DEBUG
		    for (int i = 0; i < n; i++) {
		    	cout << "\nw" << i << ": ";
		    	for (int j = 0; j < n; j++ ){
		    		//iwPrefs[ wPrefs[i] ][ wPrefs[j] ] = j;
		    		cout << wPrefs[i][j] << ", ";
		    	}
		    }
		    */

		    int iwPrefs [n][n];						// Inverse of wPrefs, OPTIMIZATION for
		    for (int i = 0; i < n; i++) {			// faster comparison of men`s ranking
		    	for (int j = 0; j < n; j++ ){		// on w`s pref list
		    		iwPrefs[i][ wPrefs[i][j] ] = j;
		    	}
		    }

		    cout << "\n\niwPrefs (2d array), position=man id, value=position in the list";					// PRINT iwPrefs - DEBUG
		    for (int i = 0; i < n; i++) {
		    	cout << "\nw" << i << ": ";
		    	for (int j = 0; j < n; j++ ){
		    		cout << iwPrefs[i][j] << ", ";		// i = row (woman)
		    	}
		    }

		    // 4) Init arrays to represent the matchings
		    //
		    int wife [n], husband[n];
		    for (int i = 0; i < n; i++ ){
		    	wife[i] = -1; husband[i] = -1;
		    }

		    while ( !dm.empty() ){

			    currProposer = dm.peek_front();
			    cout << "\n\nCurrent proposer: m" << currProposer;

			    cout << "\nm" << currProposer << " pref list: "; mPrefs[currProposer].printDeque();

			    // check current highest woman on his list
			    currWoman = mPrefs[currProposer].remove_front();

			    cout << "\nw" << currWoman << " pref list (inv): ";
		    	for (int j = 0; j < n; j++ ){
		    		cout << "m" << j << ":" << iwPrefs[currWoman][j];

		    		switch (iwPrefs[currWoman][j]){
		    			case 1: cout << "st"; break;
		    			case 2: cout << "nd"; break;
		    			case 3: cout << "rd"; break;
		    			default: cout << "th"; break;
		    		}

		    		if (j < n-1)
		    			cout << ", ";
		    	}

			    // PROPOSE to her
			    // check if woman has some husband
			    if ( husband[currWoman] == -1 ){					// If single
			    	cout << "\nw" << currWoman << " is single, MATCH successful";
			    	dm.remove_front();
			    	husband[currWoman] = currProposer;
			    	wife[currProposer] = currWoman;
			    }
			    else{												// IF not single
			    	cout << "\nw" << currWoman << " is NOT single";
			    	currHusband = husband[currWoman];

			    	// compare positions in the woman`s rating list
			    	if ( iwPrefs[currWoman][currHusband] > iwPrefs[currWoman][currProposer]  ){

			    		cout << "\nw" << currWoman << " prefers m" << currProposer << " over her husband m" << currHusband;
			    		// A) return husband back to queue of free men
			    		dm.remove_front();
			    		dm.insert_front(currHusband);
			    		cout << ". m" << currHusband << " is FREE again.";

			    		// B) Create new match
				    	husband[currWoman] = currProposer;
				    	wife[currProposer] = currWoman;
			    	}
			    	else{
			    		cout << "\nw" << currWoman << " prefers her curr husband m" << currHusband << " over the proposer m" << currProposer;
			    	}
			    }
		    }
		    cout << "\n\nGale-Shapley stable matching set: ";
		    for (int i = 0; i < n; i++){
		    	cout << "m" << i << " - w" << wife[i];
		    	if (i < n-1)
		    		cout << ", ";
		    }

	}catch(std::runtime_error& oor){
		cout << oor.what();
	}

	return 0;
}

