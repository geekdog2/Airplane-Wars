//��¼�ɻ����ӵ��������
//���һ���������ͷ�ļ�
#include<stdlib.h>
//���ڼ�����Ƿ�����ʧ��
#include<assert.h>

//����������,�ȴ���������Ľṹ��
typedef struct NODE
{
	int x;//x����
	int y;//y����
	int speed;//����
	struct NODE* next;//ָ�룬����ָ����һ�����

}Node;

//����ṹ�Ľ��
typedef struct LinkList
{
	struct NODE* head;//ͷָ��
	struct NODE* end;//βָ��
		
}LL;

//���������㺯��
Node* Node_init(int x, int y, int speed) {
	//����malloc�������˺�������stdlib�⣬���ڷ����ڴ�ռ�
	//��Node*����һ��Node��С���ڴ�ռ䣬ע�⶯̬�����ڴ�ʱ�����ʼ��
	Node* temp = (Node*)malloc(sizeof(Node));
	//�ж�ָ���Ƿ񴴽��ɹ�
	assert(temp);
	//���βζ�������
	temp->x = x;
	temp->y = y;
	temp->speed = speed;
	//��̬�����ڴ�ʱ��Ҫ��û��ֵ��ָ��ָ�գ��������Ұָ��
	//��ָ���ǲ��ܷ��ʵģ���Ϊ���ڴ�����0,0~255����ϵͳռ�õ�
	temp->next = NULL;
	return temp;

}

//����������뺯�� β�巨
void LinkList_insert(LL *list,int x,int y,int speed) {
	if (list == NULL) {
		return;
	}
	if (list->head == NULL) {
		//
		list->head = list->end = Node_init(x, y, speed);
		list->end = list->end->next;//����βָ��
	}
	else
	{
		list->end->next = Node_init(x, y, speed);
	}
}