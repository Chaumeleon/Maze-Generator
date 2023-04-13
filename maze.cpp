/* CS210 Project 4: Maze Generator
 * Authors: Brycen Bissell and Brandon Chau
 */

#include <iostream>
#include <stack>
#include <set>
#include <random>
#include <ctime>

using namespace std;

static mt19937 mt(time(nullptr));

void horizontalWalls(vector<vector<string> > &maze) {
    for (int k = 0; k <maze[0].size() + 2; k++) {
        cout << 'X' << " ";
    }
    cout << endl;
}

void printMaze(vector<vector<string> > &maze) {
    horizontalWalls(maze);
    for (int i = 0; i < maze[0].size(); i++) {
        for (int j = 0; j < maze[0].size(); j++) {
            if (j == 0 || j == maze[0].size()) {
                cout << 'X' << " ";
            }
            cout << maze[i][j] << " ";
        }
        cout << 'X' <<endl;
    }
    horizontalWalls(maze);
}

bool unVisited(set<pair<int,int> > &visited, pair<int,int> &currentPosition, vector<vector<string> > &maze, deque<pair<int, int>> &nextRoom) {
    vector<pair<int, int> > temp;
    if (currentPosition.second - 2 >= 0 && !visited.count(make_pair(currentPosition.first, currentPosition.second - 2))) {
        temp.push_back(make_pair(currentPosition.first, currentPosition.second - 2));
    }
    //move left
    if (currentPosition.second + 2 <= maze.size() && !visited.count(make_pair(currentPosition.first, currentPosition.second + 2))) {
        temp.push_back(make_pair(currentPosition.first, currentPosition.second + 2));
    }
    //move right
    if (currentPosition.first + 2 <= maze.size() && !visited.count(make_pair(currentPosition.first + 2, currentPosition.second))) {
        temp.push_back(make_pair(currentPosition.first + 2, currentPosition.second));
    }
    //move down
    if (currentPosition.first - 2 >= 0 && !visited.count(make_pair(currentPosition.first - 2, currentPosition.second))) {
        temp.push_back(make_pair(currentPosition.first - 2, currentPosition.second));
    }
    //move up
    if (temp.empty()) {
        return false;
    }
    int i = mt() % temp.size();
    nextRoom.push_back(temp[i]);
    return true;
    //inserts random positions into set
}

void breakWall(pair<int,int> &cur, pair<int,int> &next, vector<vector<string> > &maze){
    maze[next.first][next.second] = ".";
    //checking if rows are the same
    if (cur.first == next.first) {
        if (cur.second < next.second) {
            maze[cur.first][next.second - 1] = ".";
        } else {
            maze[cur.first][next.second + 1] = ".";
        }
    }
    //checking if columns are the same
    if (cur.second == next.second) {
        if (cur.first < next.first) {
            maze[cur.first + 1][next.second] = ".";
        } else {
            maze[cur.first - 1][next.second] = ".";
        }
    }
}

void makeMaze(vector<vector<string> > &maze) {
    set<pair<int, int> > visited;
    //marking all the rooms in the graph as unvisited
    deque<pair<int, int> > previousRoom;

    maze.back()[0] = ".";

    pair<int, int> currentPosition;

    pair<int, int> markedNeighbor;

    previousRoom.push_back(make_pair(maze.back().size() - 1, 0));
    //starting position

    while(!previousRoom.empty()) {

        currentPosition = previousRoom.back();
        //while stack is not empty, load unvisited neighbors into stack

        if (unVisited(visited, currentPosition, maze, previousRoom)) {
            markedNeighbor = previousRoom.back();
            breakWall(currentPosition, markedNeighbor, maze);
        } else {
            previousRoom.pop_back();
        }
        visited.insert(currentPosition);
    }
}

int main(int argc, char *argv[]) {

    if (argc > 1) {
        int roomSize = stoi(argv[1]);
        int input = 2 * roomSize - 1;

        vector<string> v (input, "X");
        vector<vector<string> > maze (input , v);
        makeMaze(maze);
        printMaze(maze);
    }
    return 0;
}
