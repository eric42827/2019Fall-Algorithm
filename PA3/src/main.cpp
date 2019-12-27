#include<iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;

int ind(int i,int j,int num){return i*num+j;}//num for total num (this is n*n mat)
/*
-100<=w<=100
*/

struct CycleBreaker
{
    char graphType;
    int n = 0;  //numOfVertices
    int m = 0;  //numOfEdges
    vector<uint16_t> edges; //denote which vertex connect
    //vector<uint16_t> weights;   //denote weight of vertices
    ofstream ofs;

    CycleBreaker(const char *inputFile){ //constructor
        ifstream ifs(inputFile);
        if(!ifs)
            return;
        ifs >> graphType;
        ifs >> n;
        ifs >> m;
        
        edges.assign(n*n,UINT16_MAX);
        //weights.assign(n*n,0);
        for(int i = 0; i < m; i++){
            uint16_t a = 0,b = 0,w = 0;
            ifs >> a >> b >> w;
            edges[ind(a,b,n)] = w;
            //weights[a] = w;
            if(graphType != 'd'){
                edges[ind(b,a,n)] = w;
            }
        }
    }

    void output(const char *outputFile){//outputfile
        ofs.open(outputFile);
        ofs << graphType << endl;
        ofs << n << endl;
        ofs << m << endl;
        
        for(int i = 0;i < n;i++){
            for(int j = 0;j < n;j++){
                if(edges[ind(i,j,n)]<=100&&edges[ind(i,j,n)]>=-100)
                    ofs << i << " " << j << " " << edges[ind(i,j,n)] << endl;
            }
        }
         

        ofs.flush();
        ofs.close();
    }
    
};


int main(int argc, char *argv[]){
    CycleBreaker breaker(argv[1]);
    breaker.output(argv[2]);
    return 0;
}