#include <bits/stdc++.h>
using namespace std;

/*
sudoku[i][j] contains 0 then it is blank
otherwise a value is already entered
*/

// Valid will check whether any two same numbers are in same row and column
bool validConfig(int n, int sudoku[100][100]) {
	for(int x=0;x<n;x++) {
		for(int y=0;y<n;y++) {
			int val = sudoku[x][y];
			if(val==0) continue;
			//Check if val is present in that row
			for(int j=0;j<n;j++) 
				if(sudoku[x][j]==val && j!=y){
					//cout<<"Value present in row:"<<i<<","<<j<<":"<<sudoku[
					return false;
				}
			
			//Check if val is present in that column
			for(int i=0;i<n;i++) if(sudoku[i][y]==val && i!=x) return false;
		}
	}
    
	//Check each 3x3 square, and find if any value is repeated.
	for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			//For each square calculate the starting and ending positions
			int dig[10];
			for(int x=1;x<=9;x++) dig[x]=0;
			
			for(int x=3*i; x<=(3*i)+2; x++) {
				for(int y=3*j; y<=(3*j)+2; y++) {
					int tmp = sudoku[x][y];
					if(tmp==0) continue;
					if(dig[tmp]!=0) return false;
					dig[tmp]++;
				}
			}	
		}
	}
	
	return true;
}

bool flag=0;
void printSol(int n, int sudoku[100][100]) {
	cout<<"possible outcome\n";
	for(int x=0;x<n;x++) {
		for(int y=0;y<n;y++) {
			cout<<sudoku[x][y]<<" ";
		}
		cout<<"\n";
	}
	flag=1;
}

void solveSudoku(int i, int j, int n, int sudoku[100][100]) {
	if(flag) return;
	if(!validConfig(n, sudoku)) {
		//cout<<"Invalid config\n";
		return;
	}
	
	//cout<<"_____\n";
	//printSol(n, sudoku);
	
	//Check if the current i,j contains blank
	if(sudoku[i][j]==0) {
		//Put every possible value and go to next value in the row
		for(int x=1;x<=9;x++) {
			sudoku[i][j]=x;
			//cout<<"Putting:"<<x<<" at "<<i<<","<<j<<"\n";;
			//Go to next column if possible
			if(j+1<n) solveSudoku(i, j+1, n, sudoku);
			//Otherwise go to the next row, and 0th column
			else if(i+1<n) solveSudoku(i+1, 0, n, sudoku);
			else if(validConfig(n, sudoku)) printSol(n, sudoku);
			sudoku[i][j]=0;
		}
	}
	else {
			//Go to next column if possible
			if(j+1<n) solveSudoku(i, j+1, n, sudoku);
			//Otherwise go to the next row, and 0th column
			else if(i+1<n) solveSudoku(i+1, 0, n, sudoku);
			else if(validConfig(n, sudoku)) printSol(n, sudoku);
	}
}

int main() {
	int n;
	cin>>n;
	
	int sudoku[100][100];
	for(int x=0;x<n;x++) {
		for(int y=0;y<n;y++) {
			cin>>sudoku[x][y];
		}
	}
	//cout<<validConfig(n, sudoku);
	solveSudoku(0, 0, n, sudoku);
	
return 0;
}
