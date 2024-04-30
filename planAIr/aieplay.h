//�򿪴��ڡ�����ͼƬ��ʵ��������������
//�����ҷ��ɻ����ҷ��ɻ����ƶ�
//�����ӵ��������ӵ����ͷ�
#include<opencv2/opencv.hpp>
//ʹ��һ��ͼ�ο�
#include<easyx.h>
//Windows�Դ���һ��������
#include<conio.h>
//ʱ�亯��
#include<time.h>
//�궨�嶨��ͼ�δ��ڴ�С����Ϊ֮�󲻻��ٸ�
#define BGWEIGHT 400 //���
#define BGHEIGHT 600 //�߶�
//�����Լ��ɻ��Ĵ�С��֮�󲻻��ٸ�
#define myAIRWEIGHT 45
#define myAIRHEIGHT 60
//����
#define enemyPlaneWEIGHT 25
#define enemyPlaneHEIGHT 25
// �ӵ�
#define BulletWEIGHT 8
#define BulletHEIGHT 8
//��������ͼ
#define MossmapW 45
#define MossmapH 60



//����ͼƬ����
IMAGE img[4];
//��������ͼ
IMAGE moss;
//�����ӵ�ͼƬ
IMAGE enemy_bullet;
//����л�����ͼ������в�ͬ�ͺŵĵ��ˣ����Ի��ɶ�ά���飩
IMAGE enemy_mask;

enum MyEnum //��ö�ٷ�����һЩԪ��
{
	//�����ӵ��������
	myBullet_NUM = 15,
	//�л��������
	ENEMY_NUM=10
};


//��ʼ����������ͼƬ֮�����ݶ����س���
void init() {
//��ͼƬ�����ؽ�ͼƬ����,����ͼƬ�Ŀ��Ҫ�ͻ滭�������ϣ�ע���ַ�����ʹ��
	//ע�⣡��ͼƬҪ����planAir��Ŀ�ļ����£���Ҫ�Ŵ���ʹ�����·����
	loadimage(&img[0],"./Images/background.png",BGWEIGHT,BGHEIGHT);	
	loadimage(&img[1], "./Images/beijingtu1.png", myAIRWEIGHT, myAIRHEIGHT);
	loadimage(&img[2], "./Images/enemy1.png", enemyPlaneWEIGHT, enemyPlaneHEIGHT);
	//�����ӵ�ͼƬ
	loadimage(&img[3], "./Images/bullet1.png", BulletWEIGHT, BulletHEIGHT);
	loadimage(&enemy_bullet, "./Images/bullet2.png", BulletWEIGHT, BulletHEIGHT);
	//��������ͼ
	loadimage(&moss, "./Images/yanmatu2.png", MossmapW, MossmapH);//�ҷ��ɻ�����ͼ
	loadimage(&enemy_mask, "./Images/yanmatue2.png", enemyPlaneWEIGHT, enemyPlaneHEIGHT);//�ҷ��ɻ�����ͼ
}
struct Plance//�ɻ��ṹ
{
	float x;
	float y;//�ɻ���̬����
	bool live; //�жϷɻ��ǲ��ǻ�����
	int width;
	int height;
	int hp;
	int type;//�ز�û�ҵ���û���ڶ��ֵл�
	
}player,bullet[myBullet_NUM],enemy[ENEMY_NUM];


void enemyHP(int i) //�����i�ݵл�
{
	enemy[i].hp = 3;
}


void gameInit()
{
	init();//ͼ����غ������ص���Ϸ���������У�����Ϸ����ʱ����ͼ��
	//��ʼ�������ɻ�
	player.x = BGWEIGHT/2;
	player.y = BGHEIGHT-70;
	player.live =true ;
	
	//��ÿһ���ӵ����г�ʼ��
	for (int i = 0; i < myBullet_NUM; i++) {
		bullet[i].x = 0;//�ӵ���λ���Ǹ��ŷɻ��ߵģ����ڸ����������κ����壬�ȼ򵥸���ֵ���С�
		bullet[i].y = 0;
		bullet[i].live = false;//�ӵ���δ���䣬���Ը�ֵfalse
	}

	//��ʼ���з��ɻ�
	for (int i = 0; i < ENEMY_NUM; i++) {
		enemy[i].live=false;//�л���û�����ȸ�ֵfalse
		//����Ҫ��������Ϊ�л��ǲ����ƶ���
		enemyHP(i);
	}

}


void gameDraw() {

	putimage(0, 0, &img[0]);//�ѱ���ͼ���ڻ�ͼ������
	//���Ƽ����ɻ�
	putimage(player.x, player.y, &moss, SRCAND);//��������ͼ����ԭͼ,��ͼ���͸�����ֲ���
	putimage(player.x, player.y, &img[1], SRCPAINT);//�Ѽ�������������,ͼ����ɫ��ת

	//�����ӵ�
	for (int i = 0; i < myBullet_NUM; i++)
	{
		if (bullet[i].live) {
			putimage(bullet[i].x, bullet[i].y, &img[3], SRCPAINT);
		}
	}
	//���Ƶл�
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
			bullet[i].live = true;//�����ӵ�ʱ���ӵ�ֵ��Ϊ��
			break;//����һ���ӵ�������if�����½���ѭ��
		}
	}
}


void BulletMove() {
	for (int i = 0; i < myBullet_NUM; i++) {
		if (bullet[i].live)
		{	
			bullet[i].y -= 0.5;
			//��������0�����ӵ����ڱ߽�û����ʧ��֪��Ϊʲô�����������
			if (bullet[i].y < 0.1) {
				bullet[i].live = false;//�ó����߽���ӵ���ʧ,���¸�ֵfalse���ӵ��ֿ��Է�����
			}
		}
	}
}

void createEnemy() {
	for (int i = 0; i < ENEMY_NUM; i++)
	{//�ж�һ�µл��Ƿ����
		if (!enemy[i].live)
		{//�����ڸ��л���ֵ�棬����л�
			enemy[i].live = true;
			enemy[i].x = rand() % (BGWEIGHT - 23);//X������������ﶼ����ν��ע��𳬹���ͼ��ͺ�
			enemy[i].y = 0;//y������Գ����滭��д0ʱ�ӻ滭�򶥲���ʼ����
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
			//�õл��ڴ����±��غ���ʧ��Ȼ�����²����л�
			if (enemy[i].y > BGHEIGHT) {
				enemy[i].live = false;
		}
		}
	}
}



//ʵ�ֽ�ɫ�ƶ�����ȡ������Ϣ����������
void playerMove(float speed)//����һ���ٶ�
{
#if 0 //�������루�ǻģʽ����Ԥ����)
	// ����Ĵ���ᱻ��Ϊע�ͣ����ᱻ����
	// ������һ����ʱ�ų��Ĵ����
	//�����������ֲ������˴�����������
#elif 1 //�Ԥ���� ����Ĵ���ᱻ���룬��Ϊ����Ϊ��
	//ʹ��Windows���̻�ȡ����,ʹ�÷���������GetAsyncKeyState
	//ע�⣡����getasynckeyskate�����м����ĸҪ�ô�д����дʱ����Сд���ܼ�⵽����Сд��һ��Ҳ��ⲻ����
	if (GetAsyncKeyState(VK_UP)||GetAsyncKeyState('W'))//VK_UP��һ���궨�壬��Windows����õģ���ʾ�ϼ��� 
	{
		//����ϱ߽��������÷ɻ���ɳ�ȥ���滭���ԭ��(0,0)�����Ͻǣ�
		if (player.y > 0) {
			player.y -= speed;//�����ƶ�
		}
		
	}
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S'))//VK_UP��һ���궨�壬��Windows����õģ���ʾ�ϼ��� 
	{
		if(player.y+60<BGHEIGHT){
		player.y += speed;//�����ƶ�
		}
	}
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A'))//VK_UP��һ���궨�壬��Windows����õģ���ʾ�ϼ��� 
	{
		if (player.x +20> 0) {
			player.x -= speed;//�����ƶ�
		}
	}
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D'))//VK_UP��һ���궨�壬��Windows����õģ���ʾ�ϼ��� 
	{	if(player.x+28<BGWEIGHT){
		player.x += speed;//�����ƶ�
	}
	}






#endif // 0
	static DWORD t1 = 0, t2 = 0;
	if (GetAsyncKeyState(VK_SPACE)) {
	//���¿ո���һ���ӵ�
		createBullet();
		t1 = t2;
}
	t2 = GetTickCount();
}

//����һ����ʱ��
bool Timer(int ms) {
	static DWORD t1, t2;//����������̬��������������ΪDWORD
	if (t2 - t1 > ms)//��t1��t2֮���ʱ����500����
	{
		t1 = t2;//��t1��t2���һ���ģ������´����ֵ��
		return true;
	}
	t2 = clock();//��ȡ��ǰʱ��ʱ�丳ֵ��t2
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
	gameInit();//�����ǵ��ú������������ú����ʹ��

	//��ʼһ����ͼ����
	initgraph(BGWEIGHT, BGHEIGHT);
	
	//˫�����ͼȥ����˸
	//BeginBatchDraw��ʼʱ��ͼ���뻺����
	BeginBatchDraw();
	while (1) {
		//����Щ��Ϣ����whileѭ��ʵ�ֲ���ˢ��
		gameDraw();
		FlushBatchDraw();//���û��flushˢ�º���ֻ����ֺ�ɫ���ڣ���Ϊͼ����end���Ż��ơ�
		playerMove(0.5);//���Ƽ����ɻ��ƶ������������ƶ��ٶȡ�
		BulletMove();
		if (Timer(500)) {
			createEnemy();
		}
		enemyMove(0.1);
		playPlance();
	}
	EndBatchDraw();//EndBatchDraw����ʱ��ͼ��ӻ������ŵ�����
//�ر��������	
	closegraph();

}
