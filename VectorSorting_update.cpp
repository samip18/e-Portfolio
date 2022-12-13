//============================================================================
// Name        : VectorSorting.cpp
// Author      : Samip Pandey
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Vector Sorting Algorithms
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};


//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information using console (std::in)
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
vector<Bid> loadBids(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of bids.
    vector<Bid> bids;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // push this bid to the end
            bids.push_back(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
    return bids;
}

/**
 *
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<Bid>& bids, int begin, int end) {
	/*
	 */

	int low = begin;
	int high = end;
	string temp = "";
	int mid = 0;
	bool done = false;
	int pivot;

	// selecting middle element as pivot
	pivot = low + (high - low) / 2;

	while(!done) {
		// while vec[low] < pivot increment 1
		while(bids[low].title.compare(bids[pivot].title) < 0) {
			++low;
		}
		// while pivot < vec[high] decrement 1
		while(bids[pivot].title.compare(bids[high].title) < 0) {
			--high;
		}
		// if 1 or no elements is remaining all numbers are partitioned return high
		if(low >= high) {
			done = true;
		} else {
			// swap the values in high and low index vectors
			temp = bids[low].title;
			bids[low].title = bids[high].title;
			bids[high].title = temp;

			++low;
			--high;
		}
	}
	return high;
}


/**
 * Perform a quick sort on bid title
 * Average performance: O(n log(n))
 * Worst case performance O(n^2))
 *
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on
 */
void quickSort(vector<Bid>& bids, int begin, int end) {
	/*
	 */

	int j = 0;
	// if there is only one or no element its already sorted
	if(begin >= end) {
		return;
	}

	j = partition(bids, begin, end);

	// sorts recursively
	quickSort(bids, begin, j);
	quickSort(bids, j+1, end);
}


/**
 *
 * @param bid address of the vector<Bid>
 *            instance to be sorted
 */
void selectionSort(vector<Bid>& bids) {

	/*
	 *
	 */

	// variables declaration
	int i = 0;
	int j = 0;
	int minIndex = 0;
	string temp = "";				// holds the variable to be swapped

	// outer loop to traverse from first element to the second last element
	for(i = 0; i < bids.size()-1; ++i ) {
		minIndex = i;
		//
		for(j = i+1; j < bids.size(); j++) {
			if(bids[j].title.compare(bids[minIndex].title) < 0) {
				minIndex = j;
			}
		}
		// swapping the variable
		temp = bids[i].title;
		bids[i].title = bids[minIndex].title;
		bids[minIndex].title = temp;
	}

}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
    }

    // Define a vector to hold all the bids
    vector<Bid> bids;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Selection Sort All Bids" << endl;
        cout << "  4. Quick Sort All Bids" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            bids = loadBids(csvPath);

            cout << bids.size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 2:
            // Loop and display the bids read
            for (int i = 0; i < bids.size(); ++i) {
                displayBid(bids[i]);
            }
            cout << endl;

            break;

        case 3:
        	ticks = clock();
        	// FIXME (1b): Invoke the selection sort and report timing results
        	selectionSort(bids);
        	cout << "SELECTION SORTED: ";
        	for(int i = 0; i < bids.size(); ++i) {
        		cout << bids[i].title << endl;
        	}
            cout << bids.size() << endl;

            ticks = clock() - ticks;
            cout << ticks << endl;
            cout << ticks * (1.0/CLOCKS_PER_SEC) << " sec" << endl;

            break;
        // FIXME (2b): Invoke the quick sort and report timing results
        case 4:
        	ticks = clock();
            // FIXME (1b): Invoke the selection sort and report timing results
        	quickSort(bids, 0, bids.size()-1);
            cout << "QUICKSORT: ";
            for(int i = 0; i < bids.size(); ++i) {
            	cout << bids[i].title << endl;
            }
            cout << bids.size() << endl;

            ticks = clock() - ticks;
            cout << ticks << endl;
            cout << ticks * (1.0/CLOCKS_PER_SEC) << " sec" << endl;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
