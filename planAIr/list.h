//记录飞机、子弹相关数据
//添加一个申请结点的头文件
#include<stdlib.h>
//用于检测结点是否申请失败
#include<assert.h>

//创建单链表,先创建链表结点的结构体
typedef struct NODE
{
	int x;//x坐标
	int y;//y坐标
	int speed;//移速
	struct NODE* next;//指针，用来指向下一个结点

}Node;

//链表结构的结点
typedef struct LinkList
{
	struct NODE* head;//头指针
	struct NODE* end;//尾指针
		
}LL;

//创建链表结点函数
Node* Node_init(int x, int y, int speed) {
	//利用malloc函数，此函数属于stdlib库，用于分配内存空间
	//给Node*分配一个Node大小的内存空间，注意动态分配内存时不会初始化
	Node* temp = (Node*)malloc(sizeof(Node));
	//判断指针是否创建成功
	assert(temp);
	//把形参都传进来
	temp->x = x;
	temp->y = y;
	temp->speed = speed;
	//动态分配内存时，要把没赋值的指针指空，避免出现野指针
	//空指针是不能访问的，因为它内存编号是0,0~255都是系统占用的
	temp->next = NULL;
	return temp;

}

//单链表结点插入函数 尾插法
void LinkList_insert(LL *list,int x,int y,int speed) {
	if (list == NULL) {
		return;
	}
	if (list->head == NULL) {
		//
		list->head = list->end = Node_init(x, y, speed);
		list->end = list->end->next;//更新尾指针
	}
	else
	{
		list->end->next = Node_init(x, y, speed);
	}
}