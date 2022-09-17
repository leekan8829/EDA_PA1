#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "assert.h" 
#include <map>
#include <set>

using namespace std;

class Graph{
public:
    map<string, set<string>> adjList_;
    //map<dest, set<src>> adjList_;
    Graph(){}

    Graph(vector<string> src,vector<set<string>> dest){
        for(int i=0;i<src.size();i++){
            adjList_.insert( make_pair(src[i],dest[i]) );
        }
    }

    void insert_edge(string src,string dest){
        adjList_[dest].insert(src);
    }

    void print_graph(vector<string> dest){
        for(int i=0;i<dest.size();i++){
            cout << "dest: " << dest[i]<< ", src={ ";
            for(auto &s:adjList_[dest[i]]){
                cout << s << " ";
            }
            cout <<"}"<< endl;
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


void out_boolean(Graph graph,vector<vector<string>> boolean_function,map<string,int> hash_index){
    //map<dest, set<src>> adjList_;
    map<string,string>

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


    int first_name = 0;
    for(int i=0;i<blif_everyline_data.size();i++){
        if(blif_everyline_data[i].find(".names")!=-1){
            if(first_name==0){
                first_name = i;//紀錄第一個name的位置 
            }
            name_vec.push_back(blif_everyline_data[i]);
        }        
    }

    //cout << "first name " << first_name <<endl;
    //處理input output字串
    split_str(input_,input_vec);
    pop_front(input_vec);
    split_str(output_,output_vec);
    pop_front(output_vec);


    // ----------test area---------
    // test_Graph(vector<string> src,vector<set<string>> dest)

    Graph new_graph;
    vector<string> dest_vec; //放dest以便print
    for(auto &v:name_vec){
        vector<string> name_test; //暫時放src
        split_str(v,name_test);
        pop_front(name_test);
        string dest;
        dest = name_test.back();
        name_test.pop_back();
        for(auto &src:name_test){
            new_graph.insert_edge(src,dest);
        }
        dest_vec.push_back(dest);
    }

    new_graph.print_graph(dest_vec);

    //map<dest,vector<boolean function>> boolean_function;
    //store boolean function
    vector<vector<string>> boolean_function;
    vector<string> every_dest_boolean;
    for(int i=first_name+1;i<blif_everyline_data.size();i++){
        if(blif_everyline_data[i].find(".names")!=-1 || blif_everyline_data[i].find(".end")!=-1){
            boolean_function.push_back(every_dest_boolean);
            every_dest_boolean.clear();
            continue; //跳到name下一行
        }
        else{
            every_dest_boolean.push_back(blif_everyline_data[i]);
        }
    }
    
    //create a hash table for dest and boolean fuction
    map<string,int> hash_index;
    for(int i=0;i<dest_vec.size();i++){
        hash_index.insert(make_pair(dest_vec[i],i));
    }
    // for(auto &i:hash_index){
    //     cout << i.first << ":" << i.second << endl;
    // }



    // for(auto &dest_:boolean_function){
    //     for(auto &s_:dest_){
    //         cout << s_ <<endl;
    //     }
    //     cout<<"___________next______________"<<endl;
    // }

    for(auto &i:boolean_function[hash_index["q"]]){
        cout << i << endl;
    }
    return 0;
}