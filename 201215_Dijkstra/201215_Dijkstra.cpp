// 201215_Dijkstra.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//               [3]------3------[5]      
//                |              / \      
//                |             /   \     
//                4            3     4    
//                |           /       \   
//                |          /         \  
// [1]-----2-----[2]---1---[4]         [8]
//   \                       \         /  
//    \                       \       /   
//     3                       2     4    
//      \                       \   /     
//       \                       \ /      
//       [6]----------6----------[7]   
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define NODE_COUNT  8
#define I           1000 //INT_MAX

vector<int> root[NODE_COUNT][NODE_COUNT];

void Dijkstra(int a) 
{
    int edgeCost[NODE_COUNT][NODE_COUNT] = {
    {0, 2, I, I, I, 3, I, 1},
    {2, 0, 4, 1, I, I, I, I},
    {I, 4, 0, I, 3, I, I, I},
    {I, 1, I, 0, 3, I, 2, I},
    {I, I, 3, 3, 0, I, I, 4},
    {3, I, I, I, I, 0, 6, I},
    {I, I, I, 2, I, 6, 0, 4},
    {1, I, I, I, 4, I, 4, 0},
    };

    int min;
    int minIndex;
    bool visited[NODE_COUNT];
    memset(visited, 0, sizeof(bool) * NODE_COUNT);

    for (int i = 0; i < NODE_COUNT; i++)
    {
        min = I;
        minIndex = -1;
        for (int j = 0; j < NODE_COUNT; j++)
        {
            if (min > edgeCost[a][j] && visited[j] == false)
            {
                minIndex = j;
                min = edgeCost[a][j];

            }
        }
        visited[minIndex] = true;
        for (int j = 0; j < NODE_COUNT; j++)
        {
            if (edgeCost[a][j] > edgeCost[minIndex][j] + min)
            {
                edgeCost[a][j] = edgeCost[minIndex][j] + min;
                for (int k = 0; k < NODE_COUNT; k++)
                {
                    vector<int>::iterator it;

                    root[a][j].clear();
                    for (it = root[a][minIndex].begin(); it != root[a][minIndex].end(); it++)
                    {
                        root[a][j].push_back(*it);
                    }
                }
                root[a][j].push_back(minIndex);
            }
        }
    }

    for (int i = 0; i < NODE_COUNT; i++)
    {
        printf("%d번에서 %d번으로 가는 최소 루트 : [ %d ]", a + 1, i + 1, a + 1);
        
        if (a <= i)
        {
            if (root[a][i].size() != 0)
                printf("--%d-->", edgeCost[a][*root[a][i].begin()]);
            else
                printf("--%d-->", edgeCost[a][i]);

            vector<int>::iterator it;
            for (it = root[a][i].begin(); it != root[a][i].end(); it++)
            {
                printf("[ %d ]", (*it) + 1);
                if(it + 1 != root[a][i].end())
                    printf("--%d-->", edgeCost[*it][*(it + 1)]);
            }
            if (root[a][i].size() != 0)
                printf("--%d-->", edgeCost[*(root[a][i].end() - 1)][i]);

        }
        else
        {
            if(root[i][a].size() != 0)
                printf("--%d-->", edgeCost[a][*root[i][a].rbegin()]);
            else
                printf("--%d-->", edgeCost[a][i]);

            vector<int>::reverse_iterator it;
            for (it = root[i][a].rbegin(); it != root[i][a].rend(); it++)
            {
                printf("[ %d ]", (*it) + 1);
                if (it + 1 != root[i][a].rend())
                    printf("--%d-->", edgeCost[*it][*(it + 1)]);
            }
            if (root[a][i].size() != 0)
                printf("--%d-->", edgeCost[*(root[i][a].rend() - 1)][i]);
        }

        printf("[ %d ] \n비용 : %d\n", i + 1, edgeCost[a][i]);
    }
    printf("\n");
}

int main()
{
    for (int i = 0; i < NODE_COUNT; i++)
    {
        Dijkstra(i);
    }
    std::cout << "Hello World!\n";
}

