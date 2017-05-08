#include <iostream>
using namespace std;
/*
Trie�����ֵ���
��֧�ڵ�  /  Ԫ�ؽڵ�
trie���ֳ�ǰ׺�����ֵ�������һ�������������ڱ���������飬���еļ�ͨ�����ַ�����

 ��֧�ڵ㣺�����ҵ�Ԫ�ؽ�㣬�൱��·������������Ԫ�ؽ��
 Ԫ�ؽڵ㣺��ֵ�ԣ���:һ�����ַ��� ֵ:��¼ֵָ��
*/

//�ṹ���
#define LINKSIZE 27 //��֧�ڵ���27��ָ�룬ָ����һ��Ľ�㣬ÿ��ָ���Ӧһ��ֵ(a-z)
#define KEYSIZE 25 //Ԫ�ؽ��ļ���һ���ַ����飬���25���ַ�

//T���ڵ������Ԫ�ػ��߷�֧
typedef enum{ELEM=0,BRCH=1}NodeType;

//Ԫ�صļ�ֵ��Ӧ�ļ�¼��ָ��
typedef struct {}Record;

//Ԫ�صļ�����
typedef struct  
{
	char ch[KEYSIZE+1];
	int len;
}KeyType;

//Ԫ������
typedef struct  
{
	KeyType key;
	Record *recptr;
}ElemType;

struct TrieNode;

//��֧����
typedef struct  
{
	TrieNode *Link[LINKSIZE]; //ָ�����飬������һ���ڵ� a/1 b/2 c/3
	//�±��1��ʼ
}BrchType;

//T���Ľ��
struct TrieNode  
{
	NodeType utype;
	//������
	union
	{
		ElemType elem;
		BrchType brch;
	};
};

class TrieTree
{
private:
	TrieNode *root;
	int num;
	static TrieNode *BuyNode()
	{
		TrieNode *p = (TrieNode *)malloc(sizeof(TrieNode));
		if (p == NULL)
			exit(1);
		memset(p,0,sizeof(TrieNode));
		return p;
	}
	static TrieNode *BuyElem(const ElemType &kx)
	{
		TrieNode *p = BuyNode();
		p->utype = ELEM;
		p->elem = kx;
		return p;
	}
	static int FindIndex(KeyType kx,int pos)
	{
		int index = 0;
		if (pos < kx.len)
		{
			index = kx.ch[pos]-'a'+1;
		}
		return index;
	}

	static TrieNode *BuyBrch(TrieNode *pelem,int pos)
	{
		TrieNode *p = BuyNode();
		p->utype = BRCH;
		int index = FindIndex(pelem->elem.key,pos);
		p->brch.Link[index] = pelem;
		return p;
	}
	static void insert(TrieNode *&ptr,const ElemType &elem,int pos)
	{
		if (ptr == NULL)
		{
			ptr = BuyElem(elem);
		}
		else if (ptr->utype == ELEM)
		{
			ptr = BuyBrch(ptr,pos);
			int index = FindIndex(elem.key,pos);
			insert(ptr->brch.Link[index],elem,pos+1);
		}
		else if (ptr->utype == BRCH)
		{
			int index = FindIndex(elem.key,pos);
			insert(ptr->brch.Link[index],elem,pos+1);
		}
	}
public:
	TrieTree():root(NULL),num(0){}
	~TrieTree(){}
	void Insert(const ElemType &x)
	{
		int pos = 0;
		insert(root,x,pos);
		++num;
	}
	//��ѯ
TrieNode *FindValue(const KeyType &kx)
	{
		int pos = 0;
		TrieNode *ptr = root;
		while(ptr != NULL && ptr->utype != ELEM)
		{
			int index = FindIndex(kx,pos++);
			ptr = ptr->brch.Link[index];
		}
		if (ptr != NULL && strcmp(kx.ch,ptr->elem.key.ch) != 0)
		{
			ptr = NULL;
		}
		return ptr;
	}
int get_num()
{
	return num;
}
};
void main()
{
	TrieTree myt;
	ElemType ar[]={"data",4,NULL,"eye",3,NULL,"date",4,NULL,
		"elema",5,NULL,"elemb",5,NULL,"elems",5,NULL,
		"elem",4,NULL};
	int n = sizeof(ar)/sizeof(ar[0]);
	for(int i = 0;i<n;++i)
	{
		myt.Insert(ar[i]);
	}
	cout<<myt.get_num();
	KeyType kx;
	cout<<"please input arr and the len"<<endl;
	while(cin>>kx.ch>>kx.len, kx.len != 0)
	{
		TrieNode *p = myt.FindValue(kx);
		if(p != NULL)
		{
			cout<<p<<" "<<p->elem.key.ch<<endl;
		}else
		{
			cout<<"not"<<endl;
		}
	}
}