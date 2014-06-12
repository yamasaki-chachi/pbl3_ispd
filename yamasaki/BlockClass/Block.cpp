//
//  Block.cpp
//  Dijkstra
//
//  Created by yamasaki on 2014/06/09.
//  Copyright (c) 2014年 yamasaki. All rights reserved.
//

#include "Block.h"
#include "Dijkstra.h"

/*****************************************************************************
 ** Construtor
 *****************************************************************************/
Block::Block()
{
    block_x = IROBOT_D;     //メッシュ一個分の横の長さ
    block_y = IROBOT_D;     //メッシュ一個分の縦の長さ
    total_block_x = ceil(FIERD_X/block_x);  //横のメッシュ総数
    total_block_y = ceil(FIELD_Y/block_y);  //縦のメッシュ総数
    
    //ノード間移動コスト配列の初期設定
    std::vector<int> list_c;
    for(int i=0; i<total_block_x*total_block_y; i++)
    {
        for(int j=0; j<total_block_x*total_block_y; j++)
        {
            list_c.push_back(COST_MAX);
        }
        cost.push_back(list_c);
        list_c.clear();
    }
    
    //メッシュ配列の初期設定
    std::vector<DijkstraMesh> list_b;
    int count = 0;
    for(int i=0; i<total_block_y; i++)
    {
        for(int j=0; j<total_block_x; j++)
        {
            DijkstraMesh tmp;
            list_b.push_back(addFirstBlock(i, j, count, tmp));
            count++;
        }
        block.push_back(list_b);
        list_b.clear();
    }
    
    //ルート配列の初期設定
    for(int i=0; i<total_block_x*total_block_y; i++)
    {
        route.push_back(0);
    }
}

DijkstraMesh Block::addFirstBlock(int y, int x, int count, DijkstraMesh tmp)
{
    tmp.num = count;
    tmp.mark = UNKNOWN;
    tmp.center_x = x*block_x+block_x/2.0;
    tmp.center_y = y*block_y+block_y/2.0;
    
    return tmp;
}

void Block::addCost(int num, IRobotDirecton direction)
{
    current_mesh_num = num;
    current_create_direction = direction;
    
    for(int i=0; i<total_block_x*total_block_y; i++)
    {
        for(int j=0; j<total_block_x*total_block_y; j++)
        {
            if((i==j+1) || (j==i+1) || (i==j+total_block_x) || (j==i+total_block_x))
            {
                cost[i][j] = COST_BIG;
                if(((i%total_block_x)==total_block_x-1) && (j==i+1))
                {
                    cost[i][j] = COST_MAX;
                }
                if(((j%total_block_x)==total_block_x-1) && (i==j+1))
                {
                    cost[i][j] = COST_MAX;
                }
            }
        }
    }
    
    switch(current_create_direction){
        case UP:
            for(int i=current_mesh_num; (i%total_block_x)!=total_block_x-1; i++)
            {
                cost[i][i+1] = COST_LITTLE;
            }
            break;
        
        case DOWN:
            for(int i=current_mesh_num; (i%total_block_x)!=0; i--)
            {
                cost[i][i-1] = COST_LITTLE;
            }
            break;
            
        case RIGHT:
            for(int i=current_mesh_num; i>total_block_y-1; i-=total_block_y)
            {
                cost[i][i-total_block_x] = COST_LITTLE;
            }
            break;
            
        case LEFT:
            for(int i=current_mesh_num; i<total_block_x*total_block_y-total_block_x; i+=total_block_y)
            {
                cost[i][i+total_block_x] = COST_LITTLE;
            }
            break;
        
        default:
            break;
    }    
}

void Block::calcRoute(int x, int y, IRobotDirecton direction, int goal)
{
    int start;
    
    start = meshNumToCurrentPosition(x, y);
    addCost(start, direction);
    
    Dijkstra dijkstra(start, goal, total_block_x*total_block_y);
    dijkstra.setCost(cost);
    dijkstra.useDijkstra();
    route = dijkstra.getRoute();
    
    /*ここ，getRoute的なやつでControllerクラスに投げる仕様にする*/
    std::cout << "点" << std::endl;
	for(int i=0; i<total_block_x*total_block_y; i++)
    {
        std::cout << route[i] << std::endl;
    }
}

//後から実装する．とりあえず0を返す．
int Block::meshNumToCurrentPosition(float x, float y){
    
    return 3;
}

/*****************************************************************************
 ** TestMain

int main(){
    Block block;
    block.calcRoute(0, 0, UP, 0, 8);
    
    return 0;
}
 
******************************************************************************/

