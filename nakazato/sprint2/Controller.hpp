#include"Map.hpp"
#include"Create.h"
#include <fstream>


enum SearchFlag
{
	WALL,
	OBSTACLE,
	DOCK
};

class Controller
{
public:
	Controller()
	{
		this->map.push_back_CreatePointList(this->create.getCurrentCoordinate());

		this->create.Straight_Run = false;
		this->create.Right_Run    = false;
		this->create.Left_Run     = false;

		this->search_flag = WALL;
		this->finished = false;
	}


void checkState();


// 最大絶対値を360にしてCreateから角度を取得
int getAngleFromCreate()
{
	return getAngle() % 360;
}


// Createの座標を記録
void recordCreateCoordinate( Coordinate coord )
{
	this->map.push_back_CreatePointList( coord );	// world座標に記録
}

void recordObstacleCoordinate( Coordinate coord )
{
	this->map.push_back_ObstaclePointList( coord );
}

void output_CreateList()
{
	std::vector<Coordinate> create_list;
	create_list = this->map.getCreatePointList();

	std::ofstream ofs("./output/create_list");
	for(int i=0;i<this->map.getCreateListSize();i++)
	{
		ofs << i << "\t" << create_list[i].x << "\t" << create_list[i].y << std::endl;
	}
	ofs.close();
}

void output_ObstacleList()
{
	std::vector<Coordinate> obstacle_list;
	obstacle_list = this->map.getObstaclePointList();

	std::ofstream ofs("./output/obstacle_list");
	for(int i=0;i<this->map.getObstacleListSize();i++)
	{
		ofs << i << "\t" << obstacle_list[i].x << "\t" << obstacle_list[i].y << std::endl;
	}
	ofs.close();

	std::ofstream ofs_a("./output/angle_list");
	for(int i=0;i<this->angle.size();i++)
	{
		ofs_a << i << "\t" << this->angle[i ]<< std::endl;
	}
	ofs_a.close();

}

// 宣言
	Map map;	// Createの蓄えた軌跡情報（ブロックと座標系）
	Create create;
	enum SearchFlag search_flag;
	bool finished;
	std::vector<int> angle;
private:

};

#include "Controller.cpp"
