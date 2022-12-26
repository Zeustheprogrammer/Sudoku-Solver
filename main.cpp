#include <iostream>
#include<iomanip>
#include <string>
#include <math.h>
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <Windows.h>
using namespace std;

class Sudoku{
    vector <vector <char> > board;
    int PUZZLE_SIZE = 9;
    char EMPTY_VALUE = '.';
public:
    void scan(){
        char temp;
        int choice;
        cout<<"HOW WOULD YOU LIKE TO ENTER THE PUZZZLE:"<<endl;
        cout<<"1. WHOLE PUZZLE"<<endl<<"2. ROW WISE"<<endl<<"3. EACH ELEMENT"<<endl;
        cout<<"'''NOTE: EMPTY ELEMENT IS DENOTED BY .'''"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
                cout<<"Enter the puzzle: "<<endl;
                for(int i=0; i<9; i++){
                vector<char> v1;
                for(int j=0; j<9; j++){
                    cin>>temp;
                    v1.push_back(temp);
                  }
                board.push_back(v1);
                }
          break;
        
        case 2:
              for(int i=0; i<9; i++){
                vector<char> v1;
                cout<<"Enter the "<<i+1<<" row"<<endl;
                for(int j=0; j<9; j++){
                    cin>>temp;
                    v1.push_back(temp);
                  }
                board.push_back(v1);
              }
          break;

          case 3:
              for(int i=0; i<9; i++){
                vector<char> v1;
                for(int j=0; j<9; j++){
                    cout<<"Enter the "<<((i+1)*10)+(j-9)<<" element"<<endl;
                    cin>>temp;
                    v1.push_back(temp);
                  }
                board.push_back(v1);
          break;
        }

      }
    }

    bool isValid(int row, int col, char c) {
      for (int i = 0; i < 9; i++) {
        if (board[i][col] == c)
          return false;
    
        if (board[row][i] == c)
          return false;
    
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
          return false;
      }
      return true;
    }

    bool solveSudoku(bool v = false) {
      for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
          if (board[i][j] == '.') {
            for (char c = '1'; c <= '9'; c++) {
              if (isValid(i, j, c)) {
                board[i][j] = c;
                if (v)
                    {
                        sleep(100);
                        printPuzzle();
                    }

                if (solveSudoku(v))
                  return true;
                else
                  board[i][j] = '.';
                  if (v)
                    {
                        sleep(100);
                        printPuzzle();
                    }
              }
            }

            return false;
          }
        }
      }
      return true;
    }
    void setCursorPosition(int x, int y)
    {
        static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        cout.flush();
        COORD coord = {(SHORT)x, (SHORT)y};
        SetConsoleCursorPosition(hOut, coord);
    }
    
    void sleep(int miliseconds)
    {
         this_thread::sleep_for(chrono::milliseconds(miliseconds));
    }
    
    void printPuzzle(bool clear= true)
    {   if(clear){
         setCursorPosition(0, 0);
        }
        string text, separator, padding;
        
        for (int i = 0; i < 9; i++)
        {
            text = "|";
            separator = " -";
            padding = "|";
            for (int j = 0; j < 9; j++)
            {
                string value;
                if(board[i][j]==EMPTY_VALUE)
                  value = " ";
                else
                  value = board[i][j]; 
                text += "  " + value + "  |";
                separator += "------";
                padding += "     |";
                if (j % 3 == 2 && j != 9 - 1)
                {
                    text += "|";
                    padding += "|";
                }
            }
            if (i != 0 && i % 3 == 0)
            {
                replace(separator.begin(), separator.end(), '-', '=');
            }
            cout << separator << endl;
            cout << padding << endl;
            cout << text << endl;
            cout << padding << endl;
        }
        cout << separator << endl;
    }
    
	void print(){
	    for(int i=0; i<9; i++){
	        if(i==3 || i==6)
	            cout<<"------+------+------"<<endl;
	        for(int j=0; j<9; j++){
	            if(j==3 || j==6)
	                cout<<"|";
	            cout<<board[i][j]<<" ";
	        }
	        cout<<endl;
	    }
	}
};
int main() {
	Sudoku obj;
  char choice;
  do {
  system("cls");
  obj.scan();
  obj.printPuzzle(true);
  char solve;
  cout<<"Do you want to run algorithn to solve the puzzle. (y/n): ";
  cin>>solve;
  if(solve=='N'|| solve =='n'){
    cout.flush();
    return 0;
  }
  obj.solveSudoku(true);
  cout.flush();
  cout<<"Do you want to continue. (y/n): ";
  cin>>choice;
  }
  while(choice=='y' || choice == 'Y');

    return 0;
}
