////
////  main.cpp
////  15-puzzle-algorithm
////
//// Rohan Bhalla 11/5/22
////
//
//#include <iostream>
//#include <vector>
//#include <string>
//#include <fstream>
//using namespace std;
//
//struct Node{
//    int hValue = 0;     //  value of calculated heuristic
//    vector <vector<int>> stateArray;    //  current state of puzzle
//    Node* upNode = nullptr;
//    Node* downNode = nullptr;
//    Node* leftNode = nullptr;
//    Node* rightNode = nullptr;
//};
//
////  global variables
//float weight = 0.0;
//vector<vector<int>> goalBoard {
//    {0, 0, 0, 0},
//    {0, 0, 0, 0},
//    {0, 0, 0, 0},
//    {0, 0, 0, 0}
//};
//string actionsString = "";
//vector<Node*> uniqueStates;
//int depth = 0;
//
//
//    // function protoypes:
//
////  open file stream
//void openFile(ifstream& ifs, string fileName);
//
////  read from file and fill in information (mirna)
//void readFile(ifstream& ifs, vector<vector<int>>& initialBoard);
//
////  write required information to new file  (rohan)
//void writeToFile();
//
////  generates new array for next node
//vector<vector<int>> generateNextState(vector<vector<int>> currBoard, string direction);
////  helper function for checking legal states
//
////  f(n) calculator
//int bestEstimateCost(int hValue, int currDepth);
//
////  h(n) heuristic calculator
//int heursiticFunc(vector<vector<int>> currBoard);
//
//pair<int,int> findCellOfValue(vector<vector<int>> board, int targetVal);
//
////  comparing two tiles (returns true if same, false otherwise)
//bool compareBoards(vector<vector<int>> boardA, vector<vector<int>> boardB);
//
////  check if generated node is unqiue
//bool isStateUnique(Node* currState);
//
////  generate all possible non-repeated states from inital state
//void generateTree(Node* initialState);
//
////  generate solution path for generated tree
//void searchTree(Node* headNode);
//
////  print board to screen
//void printBoard(vector<vector<int>> board);
//
//
//
//int main(int argc, const char * argv[]) {
//    cout << "AI PROJECT 1\n";
//    ifstream ifs;
//    vector<vector<int>> initialBoard{
//        {0, 0, 0, 0},
//        {0, 0, 0, 0},
//        {0, 0, 0, 0},
//        {0, 0, 0, 0}
//    };
//    openFile(ifs, "Input1.txt");
//    readFile(ifs, initialBoard);
//    cout << "Initial board:\n";
//    printBoard(initialBoard);
//    Node* headNode = new Node();
//    headNode->stateArray = initialBoard;
//    uniqueStates.push_back(headNode);
//    cout << "\nGoal board:\n";
//    printBoard(goalBoard);
//    generateTree(headNode);
//    searchTree(headNode);
//    cout << actionsString << endl;
//    return 0;
//}
//
//
//void openFile(ifstream& ifs, string fileName) {
//    ifs.open(fileName);
//    if(!ifs){
//        cout << "File cannot be opened." << endl;
//        exit(1);
//    }
//}
//
//
//void readFile(ifstream& ifs, vector<vector<int>>& initialBoard) {
//    int readInt;
//    
//    ifs >> weight;
//    cout << "W: " << weight << "\n\n";
//    
//    for(int i = 0; i < 4; i++) {
//        for(int j = 0; j < 4; j++){
//            ifs >> readInt;
//            initialBoard[i][j] = readInt;
//        }
//    }
//    
//    for(int i = 0; i < 4; i++) {
//        for(int j = 0; j < 4; j++){
//            ifs >> readInt;
//            goalBoard[i][j] = readInt;
//        }
//    }
//    
//}
//
//
//int bestEstimateCost(int hValue, int currDepth) {
//    return (currDepth + (weight*hValue));
//}
//
//
//pair<int,int> findCellOfValue(vector<vector<int>> board, int targetVal) {
//    int xPos = -1;
//    int yPos = -1;
//    for(int i=0; i < board.size(); ++i)
//    {
//        for(int j=0; j < board[i].size(); ++j)
//        {
//            if(board[i][j] == targetVal)
//            {
//                yPos = i;
//                xPos = j;
//                break;
//            }
//        }
//    }
//    return  make_pair(yPos, xPos);
//}
//
//
//int heursiticFunc(vector<vector<int>> currBoard) {
//    int answer = 0;
//    for(int i=0; i < currBoard.size(); ++i)
//    {
//        for(int j=0; j < currBoard[i].size(); ++j)
//        {
//            //Find where the number in current cell is kept in the Target board
//            pair<int,int> coordOfTarget = findCellOfValue(goalBoard, currBoard[i][j]);
//            //Take absolute difference of x and y positions and add max to answer
//            answer += max(abs(coordOfTarget.first-i),abs(coordOfTarget.second-j));
//        }
//    }
//    return answer;
//}
//
//
//bool compareBoards(vector<vector<int>> boardA, vector<vector<int>> boardB) {
//    bool areSame = true;
//    for(size_t i = 0; i <boardA.size(); ++i)
//    {
//        for(size_t j=0; j < boardA[i].size(); ++j)
//        {
//            if(boardA[i][j] != boardB[i][j])
//            {
//                areSame = false;
//                break;
//            }
//        }
//    }
//    return areSame;
//}
//
//
//bool isStateUnique(Node* currState) {
//    bool flag = true;
//    for(size_t i=0; i < uniqueStates.size(); ++i)
//    {
//        if(compareBoards(uniqueStates[i]->stateArray, currState->stateArray))
//        {
//            //If the two boards are the same then it is not unique
//            flag = false;
//            break;
//        }
//    }
//    return flag;
//}
//
//
//void printBoard(vector<vector<int>> board) {
//    for(size_t i=0; i < board.size(); ++i)
//    {
//        for(size_t j=0; j < board[i].size(); ++j)
//        {
//            cout << board[i][j] << " ";
//        }
//        cout << endl;
//    }
//}
//
//vector<vector<int>> generateNextState(vector<vector<int>> currBoard, string direction)
//{
//    vector<vector<int>> updatedBoard = currBoard;
//    //Find where 0 is kept in the current board
//    pair<int,int> zeroPos = findCellOfValue(currBoard, 0);
//    if(direction == "up")
//    {
//        //Check to see we can go up
//        if(zeroPos.first != 0)
//        {
//            updatedBoard[zeroPos.first][zeroPos.second] = updatedBoard[zeroPos.first-1][zeroPos.second];
//            updatedBoard[zeroPos.first-1][zeroPos.second] = 0;
//        }
//    }
//    else if(direction == "down")
//    {
//        //Check to see we can go down
//        if(zeroPos.first != 3)
//        {
//            //swap zero with its x+1 position cell value
//            updatedBoard[zeroPos.first][zeroPos.second] = updatedBoard[zeroPos.first+1][zeroPos.second];
//            updatedBoard[zeroPos.first+1][zeroPos.second] = 0;
//            
//        }
//        
//    }
//    else if(direction == "right")
//    {
//        //Check to see we can go right
//        if(zeroPos.second != 3)
//        {
//            //swap zero with its y+1 position cell value
//            updatedBoard[zeroPos.first][zeroPos.second] = updatedBoard[zeroPos.first][zeroPos.second+1];
//            updatedBoard[zeroPos.first][zeroPos.second+1] = 0;
//            
//        }
//    }
//    else if(direction == "left")
//    {
//        //Check to see we can go left
//        if(zeroPos.second != 0)
//        {
//            //swap zero with its y+1 position cell value
//            updatedBoard[zeroPos.first][zeroPos.second] = updatedBoard[zeroPos.first][zeroPos.second-1];
//            updatedBoard[zeroPos.first][zeroPos.second-1] = 0;
//        }
//    }
//    return updatedBoard;
//}
//
//void generateTree(Node* initialState) {
//        //Base case
//    if(initialState == nullptr) {
//        return;
//    }
//    //Recursive case
//    vector<vector<int>> tempVec;
//    
//    initialState->hValue = heursiticFunc(initialState->stateArray);          //Fill in h-value
//    tempVec = generateNextState(initialState->stateArray, "up");
//    //  Up child (does action give a new looking board)
//    if(isStateUnique(initialState)) {
//        //Check to see if action is legal (changes the board)
//        if(!compareBoards(tempVec, initialState->stateArray)) {
//            Node* newNode = new Node();
//            initialState->upNode = newNode;
//            initialState->upNode->stateArray = tempVec;
//            uniqueStates.push_back(initialState->upNode);
//        }
//    }
//    generateTree(initialState->upNode);
//    
//    //  Down child
//    tempVec = generateNextState(initialState->stateArray, "down");
//    if(isStateUnique(initialState)) {
//        if(!compareBoards(tempVec, initialState->stateArray)) {
//            Node* newNode = new Node();
//            initialState->downNode = newNode;
//            initialState->downNode->stateArray = tempVec;
//            uniqueStates.push_back(initialState->downNode);
//        }
//    }
//    generateTree(initialState->downNode);
//    
//    //  Left node
//    tempVec = generateNextState(initialState->stateArray, "left");
//    if(isStateUnique(initialState)) {
//        if(!compareBoards(tempVec, initialState->stateArray)) {
//            Node* newNode = new Node();
//            initialState->leftNode = newNode;
//            initialState->leftNode->stateArray = tempVec;
//            uniqueStates.push_back(initialState->leftNode);
//        }
//    }
//    generateTree(initialState->leftNode);
//    
//    //  Right node
//    tempVec = generateNextState(initialState->stateArray, "right");
//    if(isStateUnique(initialState)) {
//        if(!compareBoards(tempVec, initialState->stateArray)) {
//            Node* newNode = new Node();
//            initialState->rightNode = newNode;
//            initialState->rightNode->stateArray = tempVec;
//            uniqueStates.push_back(initialState->rightNode);
//        }
//    }
//    generateTree(initialState->rightNode);
//    
//    depth++;
//}
//
//void searchTree(Node* headNode)
//{
//    Node* currNode = headNode;
//    int currDepth = 0;
//    //loop while current node isnt null or if goal node is found
//    
//    //HAVE TO TAKE MIN OF F VALUE AND NOT H VALUES!!!!!!!!!!!
////    while(!compareBoards(currNode->stateArray, goalBoard))
//    while(currNode != nullptr)
//    {
//        int upVal = INT_MAX;
//        int downVal = INT_MAX;
//        int rightVal = INT_MAX;
//        int leftVal = INT_MAX;
//        //If goal has been reached then we can exit
//        if(compareBoards(currNode->stateArray, goalBoard))
//        {
//            break;
//        }
//        else
//        {
//            if(currNode->upNode != nullptr)
//            {
//                upVal = currNode->upNode->hValue + currDepth;
//            }
//            if(currNode->downNode != nullptr)
//            {
//                downVal = currNode->downNode->hValue + currDepth;
//            }
//            if(currNode->rightNode != nullptr)
//            {
//                rightVal = currNode->rightNode->hValue + currDepth;
//            }
//            if(currNode->leftNode != nullptr)
//            {
//                leftVal = currNode->leftNode->hValue + currDepth;
//            }
//            
//            //Take minimum and update current to be that node
//            if(min(upVal, min(downVal, min(rightVal,leftVal))) == upVal)
//            {
//                currNode = currNode->upNode;
//                actionsString += "U ";
//            }
//            else if(min(upVal, min(downVal, min(rightVal,leftVal))) == downVal)
//            {
//                currNode = currNode->downNode;
//                actionsString += "D ";
//            }
//            else if(min(upVal, min(downVal, min(rightVal,leftVal))) == rightVal)
//            {
//                currNode = currNode->rightNode;
//                actionsString += "R ";
//            }
//            else
//            {
//                currNode = currNode->leftNode;
//                actionsString += "L ";
//            }
//            //need function that returns which path is minimum
//            //reset the hvalue variables for next loop iteration
//            //Increment the depth for next iteration/level
//            currDepth++;
//        }
//        
//    }
//}
