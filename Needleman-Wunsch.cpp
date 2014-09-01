#include <cstdio>
#include <cstdlib>
#include <string>
#include <string.h>
#include <math.h>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <sstream>
#include <deque>
#include <math.h>
#include <ctime>
using namespace std;

/*Scoring Scheme */
const int MATCH = 1;  
const int MISMATCH = 0; 
const int GAP = 0; 

int ALIGNMENT_SCORE = 0; 
int SEQUENCE_AMOUNT = 0; 
int HIT = 0; 




struct Entry
{
	int value; //value given by maxEntry
	
	char direction; //checks to see if direction should go left during backtrace 'l' || 'u' || 'd'
	
	int x; //x coordinate
	int y; //y coordinate
	
	char x_char; //x character
	char y_char; //y character
};


vector < vector <Entry> > MATRIX;

map <pair <string, string>, vector< vector<Entry> > > MATRIX_HOLDER;



int Score(char x_char, char y_char)
{
	int retVal = 0; 
	if (x_char == y_char)
	{
		retVal = 1; 
	}
	return retVal; 

}

double calculatePercentage(int score, int size)
{
	double retVal = 0;
	retVal = (double)score/(double)size; 
	retVal = floor(retVal*100+0.5);
	return retVal;
}


bool correctInput(string str, string whichSeq)
{
	bool retVal = true; 
	if (whichSeq == "DNA")
	{
		//consists of ATCG
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] !=  'A' && str[i] !=  'T' && str[i] !=  'C' && str[i] !=  'G' )
			{
				retVal = false; 
			
			}
		}
	
	
		}
	
	else if (whichSeq =="RNA")
	{
	
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] != 'A' && str[i] !=  'U' && str[i] !=  'G' && str[i] !=  'C' )
			{
				retVal = false;
			
			}
		}
	}
	
	return retVal;
	
}

vector<string> sort (vector<string> input)
{
	int maxIndex = 0; 
	string maxStr = input[0];
	
	vector<string> retVal;
	int complete = input.size(); 
	while (retVal.size() != complete){
	
		maxStr = input[0]; 
		maxIndex = 0; 
		
		for (int i = 0; i <input.size(); i++)
		{
			if (maxStr.length() < input[i].length())
			{
				maxIndex = i; 
				maxStr = input[i]; 
			}
		}
		retVal.push_back(maxStr); 
		input[maxIndex] = "";
	}
	
	return retVal; 
	

}

char maxEntryDir( Entry curr, Entry diag, Entry up, Entry left, string phrase1, string phrase2)
{
	char retVal = 'u'; 

	int scoreDiag = 0; 
	int scoreUp = 0; 
	int scoreLeft = 0; 
	
	int maxValue = 0; //used for comparison between the three directions
	
	scoreDiag = diag.value + Score(phrase1[curr.x-1], phrase2[curr.y-1]);
	scoreUp  = up.value + GAP; 
	scoreLeft = left.value + GAP; 
	
	retVal = 'd'; 
	maxValue = scoreDiag; 
	
	if (scoreUp > maxValue)
	{	retVal = 'u';
		maxValue = scoreUp; 
	}
	
	if (scoreLeft > maxValue)
	{
		retVal = 'l';
		maxValue = scoreLeft;
	}
	
	return retVal; 
	
}

vector< vector <char> > Backtrace( vector< vector<Entry> > matrix, int x, int y, string phrase1, string phrase2)
{
	bool done = false; 
	
	Entry currEntry; 
	
	int xCoor = x-1; 
	int yCoor = y-1; 
	
	

	string phraseX = "";
	string phraseY = "";
	int counter = 0; 
	
	vector <vector <char> > phrases; 
	vector <char> phrase1Vec; 
	vector <char> phrase2Vec; 
	while (!done)
	{
		
		
		if (xCoor == 0 && yCoor == 0)
		{

			break;
		}

		
		if (phrase1[xCoor-1] == phrase2[yCoor-1])
		{
			phrase1Vec.push_back(phrase1[xCoor-1]);
			phrase2Vec.push_back(phrase2[yCoor-1]);
			ALIGNMENT_SCORE+=1; 

		}
		
		else if (phrase1[xCoor-1] != phrase2[yCoor-1])
		{
		
			if (matrix[yCoor][xCoor].direction == 'l')
			{
		
			phrase1Vec.push_back(phrase1[xCoor-1]);
			phrase2Vec.push_back('-');

			
			}
			
			else if (matrix[yCoor][xCoor].direction == 'd')
			{
			
			phrase1Vec.push_back(phrase1[xCoor-1]);
			phrase2Vec.push_back(phrase2[yCoor-1]);
				
			}

		}
		
		
		
		if (matrix[yCoor][xCoor].direction ==  'u')
		{
			//cout <<"Going Up"<<endl;
			yCoor-=1; 
		}
		else if (matrix[yCoor][xCoor].direction == 'l')
		{
			//cout <<"Going Left"<<endl;
			xCoor -=1; 
		}
		else if (matrix[yCoor][xCoor].direction == 'd')
		{
			//cout <<"Going Diagonal"<<endl;
			xCoor -=1;
			yCoor -=1; 
		}
		
	}
	
	phrases.push_back(phrase1Vec);
	phrases.push_back(phrase2Vec);
	
	return phrases;

}

int maxEntryVal( Entry curr, Entry diag, Entry up, Entry left, string phrase1, string phrase2)
{
	char retVal = 'u'; 

	int scoreDiag = 0; 
	int scoreUp = 0; 
	int scoreLeft = 0; 
	
	int maxValue = 0; //used for comparison between the three directions
	
	scoreDiag = diag.value + Score(phrase1[curr.x-1], phrase2[curr.y-1]);
	scoreUp  = up.value + GAP; 
	scoreLeft = left.value + GAP; 
	
	retVal = 'd'; 
	maxValue = scoreDiag; 
	
	if (scoreUp > maxValue)
	{	retVal = 'u';
		maxValue = scoreUp; 
	}
	
	if (scoreLeft > maxValue)
	{
		retVal = 'l';
		maxValue = scoreLeft;
	}
	
	return maxValue; 
	
}

string NW(string phrase1, string phrase2)
{
	vector<vector <Entry > > empty; 
	vector<vector <Entry> > matrix_temp; 
	
	MATRIX = empty; 
	matrix_temp = empty; 
	
	/*Fill the matrix*/
	int matrix_y = phrase2.size()+1;
	int matrix_x = phrase1.size()+1; 
	
	/*push back entry nodes into matrix until matrix is formed*/
	Entry temp; 
	temp.value = 0;
	vector <Entry> phrase1_vec;  
	for (int i = 0; i < matrix_x; i++)
	{
		phrase1_vec.push_back(temp); 
	}
	
	for (int i = 0; i < matrix_y; i++)
	{
		MATRIX.push_back(phrase1_vec);
		
	}
	
	/*Make sure the value at every entry at row zero and column zero is a 0*/
	/*Assign every entry in row zero the left direction (for backtrace)
	  Assign every entry in column zero to have the up direction (for backtrace)
	*/
	
	for (int i = 0; i < matrix_y; i++) //y axis
	{
		for (int j = 0; j <matrix_x; j++) //x axis
		{
			if (i == 0 || j == 0)
			{
				MATRIX[i][j].value = 0; 
				if (i ==0)
				{
					MATRIX[i][j].direction = 'l'; 
					
				}
				else if (j ==0)
				{
					MATRIX[i][j].direction = 'u';
				}
			}
			MATRIX[i][j].x = j; 
			MATRIX[i][j].y = i; 
		}
	}
	

	//Calculate the direction for every other entry
	for (int i = 1; i < matrix_y; i++)
	{
		for (int j = 1; j <matrix_x; j++)
		{
			
			MATRIX[i][j].direction = maxEntryDir(MATRIX[i][j], MATRIX[i-1][j-1], MATRIX[i-1][j], MATRIX[i][j-1], phrase1, phrase2);
			MATRIX[i][j].value = maxEntryVal(MATRIX[i][j], MATRIX[i-1][j-1], MATRIX[i-1][j], MATRIX[i][j-1], phrase1, phrase2);
		}
	}
	
	
	matrix_temp = MATRIX; 
	MATRIX_HOLDER[make_pair(phrase1,phrase2)] = matrix_temp; 
	//matrix_temp = empty; 
	
	
	
	vector< vector<char> > alignedPhrases;
	
	alignedPhrases = Backtrace(MATRIX, matrix_x, matrix_y, phrase1, phrase2);
	
	string newPhrase = ""; 
	for (int i = alignedPhrases[1].size()-1; i >=0; i--)
	{
		newPhrase+= alignedPhrases[1][i]; 
	}
	
	//cout<<newPhrase<< " is the new phrase"<<endl;
	return newPhrase;


}

void printMatrix(string seq1, string seq2)
{
	vector <vector <Entry> > temp; 
	int matrix_y = seq2.length()+1; 
	int matrix_x = seq1.length()+1; 
	temp = MATRIX_HOLDER[make_pair(seq1,seq2)]; 
	cout <<"---------------------------------------------------"<<endl;
	cout<< "Visual Matrix Representation " <<endl;
	cout<<"Sequence 1: "  << seq1<<endl;
	cout<<"Sequence 2: " <<seq2<<endl;
	cout <<"---------------------------------------------------"<<endl;
	cout<<endl;
	for (int i = 0; i <matrix_y; i++)
	{
		for (int j = 0; j <matrix_x; j++)
		{
			
			cout << temp[i][j].value << "\t";
			
			
		}
		cout<<"\n"; 
	}
	
	cout <<endl;
	
}

int main(int argc, char **argv)
{
	string phrase1;
	string phrase2; 
	
	string YesOrNo = "";
	
	cout <<"---------------------------------------------------"<<endl;
	cout << "Welcome to the Sequence Alignment Program"<<endl;
	cout <<"---------------------------------------------------"<<endl;

	string dna_or_rna = "";

	cout << "Would you like to enter DNA sequences or RNA sequences? (enter 'DNA' or 'RNA'): "; 
	cin >> dna_or_rna; 
	while(dna_or_rna!= "DNA" && dna_or_rna!= "RNA")
	{
		cout<<dna_or_rna<<" is not an option."<<endl;
		cout << "Please re-enter.\nWould you like to enter DNA sequences or RNA sequences? (enter 'DNA' or 'RNA'): "; 
		cin >> dna_or_rna; 
	}
	cout <<endl;
	
	cout << "How many sequences would you like to compare?  ";
	cin >>SEQUENCE_AMOUNT;
	
	string temp = ""; 
	vector<string> sequences; 
	for (int i = 0; i < SEQUENCE_AMOUNT; i++)
	{
		
		cout << "Please enter phrase #"<<i+1<< ":  ";
		cin>> temp; 
		while (!correctInput(temp, dna_or_rna))
		{
			if (dna_or_rna == "DNA")
			{
				cout<<"DNA consists of ATCG"<<endl;
				cout<<"Adenine (A) Thymine (T) Guanine (G) Cytosine (C)"<<endl;
			}
			else if (dna_or_rna == "RNA")
			{
				cout<<"RNA consists of AUGC"<<endl;
				cout<< "Adenine (A)  Uracil (U) Guanine (G) Cytosine (C)"<<endl;
			}
			cout << "Please re-enter phrase #"<<i+1<< ":  ";
			cin>> temp; 
		}
		sequences.push_back(temp); 
		temp = ""; 
		//cout<<endl;
	}
	
	/*Sort the sequences in order of length*/
	sequences = sort(sequences); 
	cout<<endl;
	
	clock_t begin = clock();



  
  	
	/*Display the sequence alignment*/
	cout<<"Sequence 1:\t"<<sequences[0]<<endl;
	for (int i = 1; i < sequences.size(); i++)
	{
		cout<<"Sequence "<< i+1<< ":\t" << NW(sequences[0], sequences[i])<<endl;
	}
	cout<<endl;
	clock_t end = clock();
	
	/*Display the score and percentage*/
	cout << "Alignment Score: "<< ALIGNMENT_SCORE <<" out of " << (sequences[0].length())*(sequences.size()-1)<<endl;
	cout << "Percentage : " << calculatePercentage(ALIGNMENT_SCORE, (sequences[0].length())*(sequences.size()-1))<<"%"<<endl;
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << "Time: "<< elapsed_secs<<endl;
	cout<<endl;
	
	char showMatrices = 'Y';
	string matrixPhrase = "";
	cout <<"Show Matrices? (Y/N): "; 
	cin >> showMatrices; 
	while (showMatrices == 'Y')
	{
		cout<<"Enter a sequence to view respective matrix:  ";
		cin >> matrixPhrase; 
		
		while (sequences[0] == matrixPhrase)
		{
			cout<<"Enter another sequence to view respective matrix:  ";
			cin >> matrixPhrase; 
		}
		
		printMatrix(sequences[0], matrixPhrase);
		cout<<"Would you like to view another matrix? (Y/N): ";
		cin >> showMatrices; 
	}
	cout <<"Bye Bye!"<<endl;
	
	
	
	
	return 0; 
}