#include<iostream>
#include<vector>
#include<iostream>
#include <string>
#include <stack>

int n;
using namespace std;

/*! function to convert string to integer */
int toInt(string s) {
	int t = 0, p = 1;

	for(int i = s.size()-1; i >= 0; i--) {
		t += p*(s[i] - '0');
		p *= 10;
	}
	return t;
}


/*! Object of this class define a single line of proof.
    It contains details about sequent, operation (^i, ^e, Vi etc)
    and the refrence line numbers. */
class ProofLine {
  protected:
  	string operation;            /*!< String to store operation performed. */
  	int line_no_2, line_no_1;    /*!< integers to store line number referred for the operation  */

    bool andElimination1();      /*!< Function to verify AND Elimination 1*/
    bool andElimination2();      /*!< Function to verify AND Elimination 2*/
    bool implElimination();      /*!< Function to verify Implication Elimination */
    bool orIntro1();             /*!< Function to verify OR Introduction 1 */
    bool orIntro2();             /*!< Function to verify OR Introduction 2 */
    bool MT();                   /*!< Function to verify Modus Tollens */
    bool andIntro();             /*!< Function to verify AND Introduction */

  public:
    string exp;                  /*1< String to store expression in this ProofLine */

    /*! Zero Parameter Constructor for ProofLine Class. */
    ProofLine() {
  		line_no_1 = 0;
  		line_no_2 = 0;
      exp = "";
      operation = "";
  	}

    /* Function to print values of Data Members after splitting given proof line. */
  	void printProofLine() {
  		cout << exp << " " << operation << " " << line_no_1 << " " << line_no_2<<endl;
  	}

    /* Function to split given proof line into different data members. */
  	void splitProofLine(string proof_line) {

      string s1 = "", s2 = ""; 
  		int i;
      int len = proof_line.size();                          // Extracting expression from proofline
      for (i = 0; proof_line[i] != '/' and i < len; i++)
        exp += proof_line[i];
      
      i++;
      for ( ; proof_line[i] != '/' and i < len; i++)        // Extracting operation from proofline
        operation += proof_line[i];

      i++;
      for ( ; proof_line[i] != '/' and i < len; i++)        // Extracting line number from proofline
        s1 += proof_line[i];

      i++;
      for ( ; i < len; i++)
        s2 += proof_line[i];


  		line_no_1 = toInt(s1);         // converting line number 1 from string to integer.
  		line_no_2 = toInt(s2);         // converting line number 2 from string to integer.
  	}

    /* Abstraction of different verification functions in one function. */
  	bool verify() {
      if(line_no_1 >= n or line_no_2 >= n)
        return false;

      if(operation == "^i")
        return andIntro();

  	  if(operation == "^e1")
        return andElimination1();

      if(operation == "^e2")
        return andElimination2();

      if(operation == "P")
        return true;

      if(operation == "Vi1")
        return orIntro1();

      if(operation == "Vi2")
        return orIntro2();

      if(operation == ">e")
        return implElimination();

      if(operation == "MT")
        return MT();

      return false;
  	}
};

std::vector < ProofLine > pf;

bool ProofLine::andElimination1(){ 
  int flag = 0;
  string temp = "";
  string temp_exp = pf[line_no_1].exp;

  for(int i = 1; i<temp_exp.length(); i++)
  {
    if(temp_exp[i] == '(')
      flag += 1;
    if(temp_exp[i] == ')')
      flag -= 1;
    if(temp_exp[i] == '^' and flag == 0)
      break;
    else
      temp += temp_exp[i];
  }

  if(temp == exp)             // comparing both strings
    return true;
  else
    return false;
}

bool ProofLine::andElimination2(){
  int flag = 0;
  string temp = "";
  string temp_exp = pf[line_no_1].exp;

  // Breaking the the given statement into two parts.
  for(int i = 1; i<temp_exp.length(); i++)
  {
    if(temp_exp[i] == '(')
      flag += 1;
    if(temp_exp[i] == ')')
      flag -= 1;
    if(temp_exp[i] == '^' and flag == 0){
      for(int j = i+1; j<temp_exp.length()-1; j++)
        temp += temp_exp[j];
      break;
    }          
  }

  if(temp == exp)             // comparing both strings
    return true;
  else
    return false;
}

bool ProofLine::implElimination(){
  string temp1 = "";
  string temp2 = "";
  string temp_exp1 = pf[line_no_1].exp;
  string temp_exp2 = pf[line_no_2].exp;
  int flag = 0;

  // Breaking the the given statement into two parts.
  for(int i = 1; i<temp_exp1.length()-1; i++){
    if(temp_exp1[i] == '(')
      flag += 1;
    if(temp_exp1[i] == ')')
      flag -= 1;
    if(temp_exp1[i] == '>' and flag == 0)
      break;
    else
      temp1 += temp_exp1[i];
  }

  flag = 0;
  for(int i = 1; i<temp_exp1.length(); i++){
    if(temp_exp1[i] == '(')
      flag += 1;
    if(temp_exp1[i] == ')')
      flag -= 1;
    if(temp_exp1[i] == '>' and flag == 0){
      for(int j = i+1; j<temp_exp1.length()-1; j++)
        temp2 += temp_exp1[j];
      break;
    }
  }

  if(temp1 == temp_exp2 and temp2 == exp)
    return true;
  else
    return false;
}

bool ProofLine::orIntro1(){
  string temp = "";
  string temp_exp = pf[line_no_1].exp;

  // Breaking the the given statement into two parts.
  int flag = 0;
  for(int i = 1; i<exp.length()-1; i++){
    if(exp[i] == '(')
      flag += 1;
    if(exp[i] == ')')
      flag -= 1;
    if(flag == 0 and exp[i] == 'V')
      break;
    else
      temp += exp[i];
  }
  if(temp == temp_exp)
    return true;
  else
    return false;
}

bool ProofLine::orIntro2(){
  string temp = "";
  string temp_exp = pf[line_no_1].exp;

  // Breaking the the given statement into two parts.
  int flag = 0;
  for(int i = 1; i<exp.length()-1; i++){
    if(exp[i] == '(')
      flag += 1;
    if(exp[i] == ')')
      flag -= 1;
    if(flag == 0 and exp[i] == 'V'){
      for(int j = i+1; j<exp.length()-1; j++)
        temp += exp[j];
      break;
    }
  }
  if(temp == temp_exp)
    return true;
  else
    return false;
}

bool ProofLine::MT(){
  string p = "";
  string q = "";
  string exp2 = pf[line_no_2].exp;
  string exp1 = pf[line_no_1].exp;
  int flag = 0;

  // Breaking the the given statement into two parts.
  for(int i = 1; i<exp1.length()-1; i++){
    if(exp1[i] == '(')
      flag += 1;
    if(exp1[i] == ')')
      flag -= 1;
    if(exp1[i] == '>' and flag == 0)
      break;
    else
      p += exp1[i];
  }

  flag = 0;
  for(int i = 1; i < exp1.length()-1; i++){
    if(exp1[i] == '(')
      flag += 1;
    if(exp1[i] == ')')
      flag -= 1;
    if(exp1[i] == '>' and flag == 0){
      for(int j = i+1; j < exp1.length()-1; j++)
        q += exp1[j];
      break;
    }
  }

  // Building negation of statements
  p = "(~" + p + ")";                                                                                                                                                                                                                                                                                          
  q = "(~" + q + ")";

  if(p == exp and q == exp2)
    return true;
  else
    return false;
}

bool ProofLine::andIntro(){
  string p = pf[line_no_1].exp;
  string q = pf[line_no_2].exp;
  string temp = "(" + p + "^" + q + ")";
  if(temp == exp)
    return true;
  else
    return false;
}
