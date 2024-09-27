#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

//read the coordinates of the live cells, then keep in an array to update.
//arr of arrays with the coodinates, [[x,y]]. Somehow check the other cells around?? idk
void nextGen(int rows, int cols, string *&grid) { //burrito shippuden
    string *nextGen = new string[rows];
    for (int row = 0; row < rows; row++) {
        string nextGenRow(cols, '.');
        for (int col = 0; col < cols; col++) {
            //iterate throught the neigbors of each 
            //int pos = (row*rows + col);
            char currCell = grid[row][col];
            //cout<<"row "<<row<<" col " << col<<" currCell "<<currCell<<endl; <- for debugging
            int liveNeighbors = 0;
            for (int x = -1; x < 2; x++) {
                for (int y = -1; y < 2; y++) {
                    int newRow = row + x;
                    int newCol = col + y;
                    if (newRow == row && newCol == col) continue;
                    if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols) {
                        char neighPos = grid[newRow][newCol];//= (newRow*rows + newCol);
                        if (neighPos == 'O') liveNeighbors++;
                    }
                }
            }
            if ((currCell == 'O' && (liveNeighbors == 2 || liveNeighbors == 3)) ||
                (currCell == '.' && liveNeighbors == 3)) {
                nextGenRow.at(col) = 'O';
            }
            //cout<<"live Neighbors "<<liveNeighbors<<endl; <- for debugging
        }
        nextGen[row] = nextGenRow;
    }
    delete[] grid;
    grid = nextGen;
}

void printGrid(string grid, int rows, int cols) {
    string pipeChar(cols, '|');
    cout<<pipeChar<<endl;
    for (int i = 0; i < rows; i++) {
        int startVal = i*cols;
        cout << grid.substr(startVal,cols) << endl;// test if it works
    }
    cout<<pipeChar<<endl;
}

void readInput() {
    //read the grid first
    int len = 4;
    string *grid = new string[len];
    string line;
    int rows = 0;
    int cols;
    while (getline(cin>>ws, line) && line != "x") {
        // grid += line;
        // rows++;
        cols = line.length();
        string tempLine;
        for (int i = 0; i < cols; i++) {
            if (line[i] != ' ') {
                tempLine += line[i];
            }
        }
        grid[rows++] = tempLine;//line;
        cols = tempLine.length();
        if (rows == len) {
            int newLen = len*2;
            string *newGrid = new string[newLen];
            for (int i = 0; i < len; i++) {
                newGrid[i] = grid[i];
            }
            len = newLen;
            delete[] grid;
            grid = newGrid;
        }
    }
    //Read the commands next
    while(true) {
        char c;
        cin >> c;
        if (cin.eof()) break;
        switch(c) {
            case 's':
                nextGen(rows, cols, grid);
                break;
            case 'p':
                //printGrid(grid, rows, cols);
                string pipeChar(cols, '|');
                cout<<pipeChar<<endl;
                for (int i = 0; i < rows; i++) {
                    cout << grid[i] << endl;// test if it works
                }
                cout<<pipeChar<<endl;
                break;
        }
    }
    delete[] grid;
}

int main() {
    readInput();
    return 0;
}