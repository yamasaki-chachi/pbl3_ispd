#include "main.hpp"



/*超音波センサの値を取得するプログラム*/

unsigned long int counter=0;

int main()
{
	// Createのスタート準備
	startOI("/dev/ttyUSB0");
// 宣言
//初期化処理	
	// ブロック（座標系）の作成
	// Createが向いている方向xを登録
	Controller controller;
	// 超音波ON
//壁探索ループ
	
	
	while(controller.getWallSearchFlag())	
	{
		std::cout << getBumpsAndWheelDrops() << std::endl;
		controller.checkState();	// バンパーに当たったら回避モードに移行
	}
	// Create発進
	// 走行距離を、誤差を考慮して計算
	// if(距離>Createの大きさ/2)
	//		Createの回転量を計算（誤差考慮）
	// 		走行距離を座標に登録
	// 		その座標に該当するブロックのマークを"none"にする
	//		超音波センサで得た距離から位置を計算
	//		その位置を座標に登録
	// 		その座標に該当するブロックのマークを"障害物"にする
	//		距離を0にする
	// if(バンパーセンサ)
	//		衝突位置と前回プロット位置からの距離を計算、座標にプロット
	//		該当ブロックのマークを"障害物"にする
	//		20cm下がる
	//		90度半時計回転（誤差考慮）
	// 		Createの方向を登録
	// 		距離を0にする
	// 		
	// X1 /4 < X2で壁探索終了
	//		壁を補間し、補間した部分のブロックのマークを"障害物"にする
	//		障害物探索ループへ
	//
//障害物探索ループ
	// 超音波OFF
	// 一番右上の未探索領域に向かう
	// 到達後、下向きになる
	// 距離を0にする
	// 発進
	// if（）


	stopOI();

	return 0;
}
