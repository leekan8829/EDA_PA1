#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "assert.h" 
#include <map>
#include <set>

/*
graph OK
read file OK

parse file
將各點（a b c）用index去mapping

建graph 

*/

using namespace std;

struct Edge{
    int src, dest, weight;
};

typedef pair<int,int> Pair;

class Graph{
public:
    vector <vector<Pair>> adjList;
    /*
            1   2   3   4   5   6
    src 1 (d,w)(0,2) 
        2
        3
        4
        5
        6
    */

    /*
        adjList 
    */
    Graph(vector<Edge> const &edges,int n){
        adjList.resize(n);
        for(auto &edge: edges){
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back(make_pair(dest,weight));

        }
    }
};
void printGraph(Graph const &graph,int n){
    for(int i = 0 ; i < n;i++){
        cout << i << "-->";
        for(Pair v: graph.adjList[i]){
            cout << "(" << i <<", " << v.first<<", "<<v.second << ") ";
        }
        cout << endl;
    }
}


class test_Graph{
public:
    map<string, set<string>> adjList_;
    test_Graph(){}

    test_Graph(vector<string> src,vector<set<string>> dest){
        for(int i=0;i<src.size();i++){
            adjList_.insert( make_pair(src[i],dest[i]) );
        }
    }

    void insert_edge(string src,string dest){
        adjList_[src].insert(dest);
    }

    void print_graph(vector<string> src){
        for(int i=0;i<src.size();i++){
            for(auto &s:adjList_[src[i]]){
                cout << "src:" << src[i] << ", dest="<< s << endl;
            }
        }
    }


};


void split_str(string s,vector<string> &s_vect){
    while (1){
        s_vect.push_back(s.substr(0, s.find(" ")));
        s = s.substr(s.find(" ")+1,s.length());
        if (s.find(" ") == -1){
            s_vect.push_back(s);
            break;
        }
    }
}

template<typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.erase(vec.begin());
}

int main(int argc, char *argv[])
{

    string line;
    string Filename = argv[1];
    vector<string> blif_everyline_data;
    ifstream myFile;
    myFile.open(Filename);
    //myFile.open("xor.blif");

    string model_;
    string input_;
    string output_;
    vector<string> input_vec;
    vector<string> output_vec;
    vector<string> name_vec; //存放每一行name

    while(getline(myFile, line)){
        blif_everyline_data.push_back(line);
    }
    
    myFile.close();

    model_ = blif_everyline_data[0];
    input_ = blif_everyline_data[1];
    output_ = blif_everyline_data[2];


    for(int i=0;i<blif_everyline_data.size();i++){
        string name;
        if(blif_everyline_data[i].find(".names")!=-1){
            name_vec.push_back(blif_everyline_data[i]);
        }        
    }

    //-----------test name_vec-------
    // for(auto s:name_vec){
    //     cout<<s<<endl;
    // }

    
    //處理input output字串
    split_str(input_,input_vec);
    pop_front(input_vec);
    split_str(output_,output_vec);
    pop_front(output_vec);



    // ----------test area---------
    // test_Graph(vector<string> src,vector<set<string>> dest)

    vector<string> name_test; //開一個test vector 來存放一行name的element

    split_str(name_vec[0],name_test);
    pop_front(name_test);

    string x__;
    x__ = name_test.back();

    name_test.pop_back();
    

    test_Graph new_graph;

    for(auto &src:name_test){
        new_graph.insert_edge(src,x__);
    }
    new_graph.print_graph(name_test);

    return 0;
}