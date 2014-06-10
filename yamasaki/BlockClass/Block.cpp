//
//  Block.cpp
//  Dijkstra
//
//  Created by yamasaki on 2014/06/09.
//  Copyright (c) 2014年 yamasaki. All rights reserved.
//

#include "Block.h"

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
    for(int i=0; i<total_block_y; i++)
    {
        for(int j=0; j<total_block_x; j++)
        {
            list_c.push_back(COST_BIG);
        }
        cost.push_back(list_c);
        list_c.clear();
    }
    
    //メッシュ配列の初期設定
    std::vector<Mesh> list_b;
    int count = 0;
    for(int i=0; i<total_block_y; i++)
    {
        for(int j=0; j<total_block_x; j++)
        {
            Mesh tmp;
            list_b.push_back(pushBackBlock(i, j, count, tmp));
            count++;
        }
        block.push_back(list_b);
        list_b.clear();
    }
}

Mesh Block::pushBackBlock(int y, int x, int count, Mesh tmp)
{
    tmp.num = count;
    tmp.mark = UNSEARCH;
    tmp.center_x = x*block_x+block_x/2.0;
    tmp.center_y = y*block_y+block_y/2.0;
    
    return tmp;
}

void Block::addCost(int num, IRobotDirecton direction)
{
    current_mesh_num = num;
    current_create_direction = direction;
    
    /*行が変わるところはCOST_MAXを入れないといけない*/
    /*実装予定*/
    
    switch(current_create_direction){
        case UP:
            for(int i=current_mesh_num; (i%total_block_x)==total_block_x-1; i++)
            {
                cost[i][i+1] = COST_LITTLE;
                cost[i+1][i] = COST_LITTLE;
            }
            break;
        
        case DOWN:
            for(int i=current_mesh_num; (i%total_block_x)==total_block_x; i--)
            {
                cost[i][i-1] = COST_LITTLE;
                cost[i-1][i] = COST_LITTLE;
            }
            break;
            
        case RIGHT:
            for(int i=current_mesh_num; i>total_block_y-1; i-=total_block_y)
            {
                cost[i][i-total_block_x] = COST_LITTLE;
                cost[i-total_block_x][i] = COST_LITTLE;
            }
            break;
            
        case LEFT:
            for(int i=current_mesh_num; i<total_block_y*total_block_x-total_block_x; i+=total_block_y)
            {
                cost[i][i+total_block_x] = COST_LITTLE;
                cost[i+total_block_x][i] = COST_LITTLE;
            }
            break;
        
        default:
            break;
    }
    
}

void Block::calcRoute()
{
/*テスト用*/
    
    std::cout << "メッシュ番号    マーカー    (x, y)" << std::endl;
    for(int i=0; i<total_block_y; i++)
    {
        for(int j=0; j<total_block_x; j++){
            std::cout << block[i][j].num << ", " << block[i][j].mark << ", (" << block[i][j].center_x << ", " << block[i][j].center_y << ")" << std::endl;
        }
    }
    
    for(int i=0; i<total_block_y; i++)
    {
        for(int j=0; j<total_block_x; j++)
        {
            std::cout << cost[i][j] << "  ";
        }
        std::cout << std::endl;
    }

}

//後から実装する．とりあえず0を返す．
int Block::meshNumToCurrentPosition(float x, float y){
    
    return 0;
}

int main(){
    Block block;
    block.addCost(block.meshNumToCurrentPosition(0, 0), UP);
    block.calcRoute();
    
    return 0;
}
