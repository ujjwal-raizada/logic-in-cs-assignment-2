#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<chrono> // header for time calculation
#include "Proof.h"
using namespace std;
using namespace std::chrono;

int main() {

	cin>>n;
	cin.ignore();
    // Dummy Object in vector to start indexing from 1
    ProofLine dummy_obj;
    pf.push_back(dummy_obj);

    int Truth[n+1];
    Truth[0] = 0;


    double time_taken = 0.0;

	for(int i = 1; i <= n; i++) {
		string s;
		string temp = "";
	 	getline(cin, s);
		//cin >> s;
	    for(int i = 0; i < s.length(); i++)
	    	if(s[i] != ' ')
	    		temp += s[i];

	  ProofLine pf_obj;           // creating ProofLine Object
		pf_obj.splitProofLine(temp);

  	pf.push_back(pf_obj);       // Adding Object to vector


    auto start = high_resolution_clock::now();

 		if(pf_obj.verify())         // Verify() will check this proof line for errors.
      	Truth[i] = 1;
  	else
  	  Truth[i] = 0;

    auto end = high_resolution_clock::now();

    time_taken += (double)(duration_cast<microseconds>(end - start)).count();
	}

  for(int i = 1; i < n+1; i++){
    if(Truth[i] == 0){
      cout << "Error!!! \nFailed at line: " << i;
      cout << "\nTime consumed: " << time_taken << " micro-seconds\n";

      return 0;
    }
  }
  cout << "Following proof is Correct !!!";

  
  cout << "\nTime consumed: " << time_taken << " micro-seconds\n";


  return 0;
}