#include<bits/stdc++.h>
#include "Expression.h"
using namespace std;


int main() {


    Expression exp;
    string infix = "";
    string temp;
    cout << "Input infix expression: ";
    getline(cin, temp);
    int count = 0;
    for(int i = 0; i < temp.length(); i++){
    	if(temp[i] == ' ')
    		count++;
    }
    if(count == temp.length()){
    	cout << "Not valid Input\n";
    	return 0;
    }

    // Removing Spaces from input
    for(int i = 0; i<temp.length(); i++){
    	if(temp[i] == ' ')
    		continue;
    	infix += temp[i];
    }

    // Starting time calculation after taking input
    auto main_start = high_resolution_clock::now(); 
    
    // setting infix string from input
    exp.setInfix(infix);

    auto postfix_start = high_resolution_clock::now();
    exp.postFix();
    auto postfix_stop = high_resolution_clock::now();


    auto parse_tree_start = high_resolution_clock::now();
    exp.createParseTree();
    auto parse_tree_stop = high_resolution_clock::now();


    auto inorder_start = high_resolution_clock::now();
	exp.printInOrder();
	auto inorder_stop = high_resolution_clock::now();


	auto verifyWellFormed_start = high_resolution_clock::now();
	exp.verifyWellFormed();
	auto verifyWellFormed_stop = high_resolution_clock::now();


	auto main_stop = high_resolution_clock::now();


    cout << "\n\n";
    // Displaying time of each function
	cout << "time used by main " << (duration_cast<microseconds>(main_stop - main_start)).count() << " microsec" << endl;
	cout << "time used by postfix " << (duration_cast<microseconds>(postfix_stop - postfix_start)).count() << " microsec" << endl;
	cout << "time used by inorder " << (duration_cast<microseconds>(inorder_stop - inorder_start)).count() << " microsec" << endl;
	cout << "time used by verifyWellFormed " << (duration_cast<microseconds>(verifyWellFormed_stop - verifyWellFormed_start)).count() << " microsec" << endl;
	

    return 0;
}