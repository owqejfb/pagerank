
#include <iostream>
#include <string>
#include<map>
#include <vector>
#include <iomanip>
using namespace std;

class AdjacencyList {

    //adjaceny list implementation
    map< string, vector<string>> board;
    
    //keeps track of the index corresponding to the map
    map<string, int> indexTracker;
    
    //keeps track the outDegree of each url
    map<string, int> outDegreeCounter;


public:
        
    void PageRank(int n);
    int getOutDegree(string from);
    void intializeIndexTracker();
    void addEdge(string from, string to);

};

void AdjacencyList::addEdge(string from, string to) {

    //insert our submission into the lsit
    board[to].push_back(from);
    if (board[from].size() == 0) {
      
      //this blank if statement is meant to put the "from" url into the board map in the case it never has a url going to it
      //this blank statement is absolutely essential *do not remove*
    }
  
    outDegreeCounter[from]++;
    if (outDegreeCounter[to] == 0) {
       
       //this blank if statement is meant to put the "to" url into the outDegree map 
       //in the case it never goes to another url, only receives
       
       //basically this intializes any URLS to 0 without every changing any non zeros outdegree urls
       
       //this blank statement is absolutely essential *do not remove*
    }
}


int AdjacencyList::getOutDegree(string url) {

    //gets out degree of url
    return outDegreeCounter[url];
}

void AdjacencyList::intializeIndexTracker() {

    //attaches an index to every url in order
    //meant to be able to do multiplcations within in the list because
    //our map is ordered, but the vectors (urls a site goes to) are not in order

    int index = 0;
    for (auto it = outDegreeCounter.begin(); it != outDegreeCounter.end(); it++) {
        
        this->indexTracker[it->first] = index;
        index++;
    }
}

void AdjacencyList::PageRank(int n) {
    
    //vector that will hold the matrix values/answers
    vector<float> answer;
    
    //intialize the vector
    for (unsigned int i = 0; i < outDegreeCounter.size(); i++) {
        
        answer.push_back( ((1.0f / ((float)outDegreeCounter.size()))));
    }

    intializeIndexTracker();
    
    for (int k = 0; k < n - 1; k++) {
        //create temp vector hold result of a specific iteration
        vector<float> tempAnswer;       
        
        for (auto it = board.begin(); it != board.end(); it++) {
            //sum of the row to put into tempAnswer vector
            float rowSum = 0;

            //we do not enter this loop if it->second.size() is 0 (meaning that the 
            unsigned int j;
            for (j = 0 ; j < it->second.size(); j++) {

                //get val to add to rowSum
                //val is (1/outDegree of url)
                float val = (1.0f / ( (float) (getOutDegree(board[it->first].at(j)))));
                
                //indexTracker finds the appropiate index to use from answer vector
                //index tracker adds an index to every url depending on lexical order
                rowSum = rowSum + (val * answer.at(indexTracker[board[it->first].at(j)]));
                
            }
            //push the answer for the row into tempAnswer
            tempAnswer.push_back(rowSum); 
        }
        //replace old answer with new answer
        answer = tempAnswer;
    }

    //print answer

    int index = 0;
    for (auto it = board.begin(); it != board.end(); it++) {
        cout << it->first << " ";
        cout << fixed;
        cout << setprecision(2) <<answer.at(index) << endl;
        index++;
    }
}

int main()
{

    int no_of_lines, power_iterations;
    string from, to;
    cin >> no_of_lines;
    cin >> power_iterations;
    AdjacencyList graph;
    
    //add edges to graph
    for (int i = 0; i < no_of_lines; i++)
    {
        cin >> from;
        cin >> to;
        graph.addEdge(from, to);
    }
    
    //determine pageRank
    if (no_of_lines > 0) {

        graph.PageRank(power_iterations);
    }

    return 0;
}





