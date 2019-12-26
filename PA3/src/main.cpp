#include<iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

int ind(int i,int j,int num){return i*num+j;}

struct CycleBreaker
{
    char graphType;
    int n = 0;  //numOfVertices
    int m = 0;  //numOfEdges
    vector<uint16_t> edges; //denote which vertex connect
    vector<uint16_t> weights;   //denote weight of vertices

    CycleBreaker(const char *inputFile){
        ifstream ifs(inputFile);
        if(!ifs)
            return;
        ifs >> graphType;
        ifs >> n;
        ifs >> m;
        uint16_t a = 0,b = 0,w = 0;
        edges.assign(n,0);
        for(; m > 0; m--){
            ifs >> a >> b;
            edges[a] = b;
            weights[a] = w;
            if(graphType != 'd'){
                edges[b] = a;
                weights[b] = w;
            }
        }


    }
    
};


int main(int argc, char *argv[]){
    CycleBreaker breaker(argv[1]);
    return 0;
}