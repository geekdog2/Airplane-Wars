//打开窗口、加载图片、实现链表、变量定义
//生成我方飞机、我方飞机的移动
//生成子弹，发射子弹，释放
#include<opencv2/opencv.hpp>
//使用一个图形库
#include<easyx.h>
//Windows自带的一个函数库
#include<conio.h>
//时间函数
#include<time.h>
//宏定义定义图形窗口大小，因为之后不会再改
#define BGWEIGHT 400 //宽度
#define BGHEIGHT 600 //高度
//定义自己飞机的大小，之后不会再改
#define myAIRWEIGHT 45
#define myAIRHEIGHT 60
//敌人
#define enemyPlaneWEIGHT 25
#define enemyPlaneHEIGHT 25
// 子弹
#define BulletWEIGHT 8
#define BulletHEIGHT 8
//定义掩码图
#define MossmapW 45
#define MossmapH 60



//建立图片数组
IMAGE img[4];
//保存掩码图
IMAGE moss;
//保存子弹图片
IMAGE enemy_bullet;
//保存敌机掩码图（如果有不同型号的敌人，可以换成二维数组）
IMAGE enemy_mask;

enum MyEnum //用枚举法定义一些元素
{
	//定义子弹最大数量
	myBullet_NUM = 15,
	//敌机最大数量
	ENEMY_NUM=10
};


//初始化函数，将图片之类内容都加载出来
void init() {
//把图片都加载进图片数组,背景图片的宽高要和绘画窗口贴合，注意字符集的使用
	//注意！！图片要放在planAir项目文件夹下，不要放错。（使用相对路径）
	loadimage(&img[0],"./Images/background.png",BGWEIGHT,BGHEIGHT);	
	loadimage(&img[1], "./Images/beijingtu1.png", myAIRWEIGHT, myAIRHEIGHT);
	loadimage(&img[2], "./Images/enemy1.png", enemyPlaneWEIGHT, enemyPlaneHEIGHT);
	//加载子弹图片
	loadimage(&img[3], "./Images/bullet1.png", BulletWEIGHT, BulletHEIGHT);
	loadimage(&enemy_bullet, "./Images/bullet2.png", BulletWEIGHT, BulletHEIGHT);
	//加载掩码图
	loadimage(&moss, "./Images/yanmatu2.png", MossmapW, MossmapH);//我方飞机掩码图
	loadimage(&enemy_mask, "./Images/yanmatue2.png", enemyPlaneWEIGHT, enemyPlaneHEIGHT);//我方飞机掩码图
}
struct Plance//飞机结构
{
	float x;
	float y;//飞机动态坐标
	bool live; //判断飞机是不是还活着
	int width;
	int height;
	int hp;
	int type;//素材没找到，没做第二种敌机
	
}player,bullet[myBullet_NUM],enemy[ENEMY_NUM];


void enemyHP(int i) //传入第i驾敌机
{
	enemy[i].hp = 3;
}


void gameInit()
{
	init();//图像加载函数加载到游戏启动函数中，在游戏启动时加载图像
	//初始化己方飞机
	player.x = BGWEIGHT/2;
	player.y = BGHEIGHT-70;
	player.live =true ;
	
	//将每一颗子弹进行初始化
	for (int i = 0; i < myBullet_NUM; i++) {
		bullet[i].x = 0;//子弹的位置是跟着飞机走的，现在给它坐标无任何意义，先简单赋个值就行。
		bullet[i].y = 0;
		bullet[i].live = false;//子弹还未发射，所以赋值false
	}

	//初始化敌方飞机
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].live=false;//敌机还没出现先赋值false
		//不需要传坐标因为敌机是不断移动的
		enemyHP(i);
	}

}


void gameDraw() {

	putimage(0, 0, &img[0]);//把背景图贴在绘图窗口内
	//绘制己方飞机
	putimage(player.x, player.y, &moss, SRCAND);//先贴掩码图再贴原图,将图像非透明部分擦除
	putimage(player.x, player.y, &img[1], SRCPAINT);//把己方飞行器贴上,图像颜色反转

	//绘制子弹
	for (int i = 0; i < myBullet_NUM; i++)
	{
		if (bullet[i].live) {
			putimage(bullet[i].x, bullet[i].y, &img[3], SRCPAINT);
		}
	}
	//绘制敌机
	for (int i = 0; i < ENEMY_NUM; i++) {

		putimage(enemy[i].x, enemy[i].y, &enemy_mask, SRCAND);
		putimage(enemy[i].x, enemy[i].y, &img[2], SRCPAINT);

	}


}

void createBullet() {
	for (int i = 0; i < myBullet_NUM; i++) {
		if (!bullet[i].live)
		{
			bullet[i].x = player.x+22;
			bullet[i].y = player.y;
			bullet[i].live = true;//发射子弹时把子弹值改为真
			break;//发射一颗子弹后跳出if，重新进入循环
		}
	}
}


void BulletMove() {
	for (int i = 0; i < myBullet_NUM; i++) {
		if (bullet[i].live)
		{	
			bullet[i].y -= 0.5;
			//本来设了0，但子弹卡在边界没有消失不知道为什么。（待解决）
			if (bullet[i].y < 0.1) {
				bullet[i].live = false;//让超出边界的子弹消失,重新赋值false后子弹又可以发射了
			}
		}
	}
}

void createEnemy() {
	for (int i = 0; i < ENEMY_NUM; i++)
	{//判断一下敌机是否存在
		if (!enemy[i].live)
		{//不存在给敌机赋值真，创造敌机
			enemy[i].live = true;
			enemy[i].x = rand() % (BGWEIGHT - 23);//X轴的坐标在哪里都无所谓，注意别超过绘图框就好
			enemy[i].y = 0;//y坐标可以超出绘画框，写0时从绘画框顶部开始产生
			enemyHP(i);
			break;
		}
	}
	
}

void enemyMove(float speed) {
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		if (enemy[i].live) {
			enemy[i].y+=speed;
			//让敌机在触碰下边沿后消失，然后重新产生敌机
			if (enemy[i].y > BGHEIGHT) {
				enemy[i].live = false;
		}
		}
	}
}



//实现角色移动，获取键盘信息，上下左右
void playerMove(float speed)//传入一个速度
{
#if 0 //条件编译（非活动模式进行预处理)
	// 这里的代码会被视为注释，不会被编译
	// 可以是一段临时排除的代码块
	//尽量少用这种操作，此处是用来测试
#elif 1 //活动预处理。 这里的代码会被编译，因为条件为真
	//使用Windows键盘获取输入,使用非阻塞函数GetAsyncKeyState
	//注意！！在getasynckeyskate函数中检测字母要用大写，大写时它大小写都能检测到。用小写它一个也检测不到。
	if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState('W'))//VK_UP是一个宏定义，是Windows定义好的，表示上键。 
	{
		//添加上边界条件，让飞机别飞出去（绘画框的原点(0,0)在左上角）
		if (player.y > 0) {
			player.y -= speed;//向上移动
		}
		
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))//VK_UP是一个宏定义，是Windows定义好的，表示上键。 
	{
		if(player.y+60<BGHEIGHT){
		player.y += speed;//向下移动
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))//VK_UP是一个宏定义，是Windows定义好的，表示上键。 
	{
		if (player.x +20> 0) {
			player.x -= speed;//向左移动
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))//VK_UP是一个宏定义，是Windows定义好的，表示上键。 
	{	if(player.x+28<BGWEIGHT){
		player.x += speed;//向右移动
	}
	}






#endif // 0
	static DWORD t1 = 0, t2 = 0;
	if (GetAsyncKeyState(VK_SPACE)) {
	//按下空格发射一个子弹
		createBullet();
		t1 = t2;
}
	t2 = GetTickCount();
}

//建立一个定时器
bool Timer(int ms) {
	static DWORD t1, t2;//定义两个静态变量，数据类型为DWORD
	if (t2 - t1 > ms)//让t1，t2之间的时间差超过500毫秒
	{
		t1 = t2;//将t1，t2变回一样的，方便下次求差值。
		return true;
	}
	t2 = clock();//获取当前时钟时间赋值给t2
	return false;
}



void playPlance() 
{
	for (int i = 0; i <= ENEMY_NUM; i++) {
		if (!enemy[i].live)
			continue;
		for (int k = 0; k < myBullet_NUM; k++)
		{
			if (!bullet[k].live)
				continue;
			if (bullet[k].x > enemy[i].x && bullet[k].x<enemy[i].x + enemyPlaneWEIGHT
				&& bullet[k].y>enemy[i].y && bullet[k].y < enemy[i].y + enemyPlaneHEIGHT) 
			{
				bullet[k].live = false;
				enemy[i].hp--;
			}
			if (enemy[i].hp <= 0) {
				enemy[i].live = false;
				
			}
		}
}
}



void start() 
{
	gameInit();//别忘记调用函数，函数调用后才能使用

	//开始一个绘图窗口
	initgraph(BGWEIGHT, BGHEIGHT);
	
	//双缓冲绘图去掉闪烁
	//BeginBatchDraw开始时，图像画入缓冲区
	BeginBatchDraw();
	while (1) {
		//将这些信息贴入while循环实现不断刷新
		gameDraw();
		FlushBatchDraw();//如果没有flush刷新函数只会出现黑色窗口，因为图像在end处才绘制。
		playerMove(0.5);//控制己方飞机移动，括号中是移动速度。
		BulletMove();
		if (Timer(500)) {
			createEnemy();
		}
		enemyMove(0.1);
		playPlance();
	}
	EndBatchDraw();//EndBatchDraw结束时，图像从缓冲区放到窗口
//关闭这个窗口	
	closegraph();

}
