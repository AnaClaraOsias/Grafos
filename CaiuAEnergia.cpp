#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>


//problema de fluxo em grafos

// the maximum number of vertices
#define NN 1024

// adjacency matrix (fill this up)
int cap[NN][NN];

// flow network
int fnet[NN][NN];

// BFS
int q[NN], qf, qb, prev[NN];

int fordFulkerson( int n, int s, int t )
{
    // init the flow network
    memset( fnet, 0, sizeof( fnet ) );

    int flow = 0;

    while( true )
    {
        // find an augmenting path
        memset( prev, -1, sizeof( prev ) );
        qf = qb = 0;
        prev[q[qb++] = s] = -2;
        while( qb > qf && prev[t] == -1 )
            for( int u = q[qf++], v = 0; v < n; v++ )
                if( prev[v] == -1 && fnet[u][v] - fnet[v][u] < cap[u][v] )
                    prev[q[qb++] = v] = u;

        // see if we're done
        if( prev[t] == -1 ) break;

        // get the bottleneck capacity
        int bot = 0x7FFFFFFF;
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            bot = std::min(bot,cap[u][v] - fnet[u][v] + fnet[v][u]);

        // update the flow network
        for( int v = t, u = prev[v]; u >= 0; v = u, u = prev[v] )
            fnet[u][v] += bot;

        flow += bot;
    }

    return flow;
}

#define inf 987654321
int main(){

    int numR;
    while(std::cin>>numR){
      
        memset( cap, 0, sizeof( cap ) );
        std::vector<int> vertices(numR);
        for(int i=1;i<=numR;i++){
            int capa;
            std::cin>>capa;
            vertices[i] = capa;
        }

        for(int i=1;i<=numR;i++){
            cap[i+numR][i] = vertices[i];
        }

        int numArestas;
        std::cin >> numArestas;
        for(int i=0;i<numArestas;i++){
            int v1,v2,c;
            std::cin >>v1>>v2>>c;
            cap[v1][v2+numR] =c;
        } 
        
        int b,d;
        std::cin >>b >>d;
        for(int i=0;i<b;i++){
            int v3;
            std::cin >> v3;
            cap[0][v3+numR] = inf;
        }
        int numVertices = (numR*2)+2;
        for(int i=0;i<d;i++){
            int v4;
            std::cin>>v4;
            cap[v4][numVertices-1] = inf;
        }
    /*
        for(int i=0;i<numVertices;i++){
            for(int j=0;j<numVertices;j++){
                if(cap[i][j] == inf) std::cout << "inf" << " ";
                else std::cout<<cap[i][j] << " ";
            }
            std::cout <<std::endl;
        }
    */
        std::cout << fordFulkerson( numVertices, 0, numVertices-1) << std::endl;;     
    }
    return 0;
}
