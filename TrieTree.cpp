#include <iostream>
using namespace std;
/*
Trie树：字典序
分支节点  /  元素节点
trie，又称前缀树或字典树，是一种有序树，用于保存关联数组，其中的键通常是字符串。

 分支节点：用来找到元素结点，相当于路径，用来索引元素结点
 元素节点：键值对，键:一般是字符串 值:记录值指针
*/

//结构设计
#define LINKSIZE 27 //分支节点有27个指针，指向下一层的结点，每个指针对应一个值(a-z)
#define KEYSIZE 25 //元素结点的键是一个字符数组，最多25的字符

//T树节点可能是元素或者分支
typedef enum{ELEM=0,BRCH=1}NodeType;

//元素的键值对应的记录级指针
typedef struct {}Record;

//元素的键类型
typedef struct  
{
	char ch[KEYSIZE+1];
	int len;
}KeyType;

//元素类型
typedef struct  
{
	KeyType key;
	Record *recptr;
}ElemType;

struct TrieNode;

//分支类型
typedef struct  
{
	TrieNode *Link[LINKSIZE]; //指针数组，索引下一个节点 a/1 b/2 c/3
	//下标从1开始
}BrchType;

//T树的结点
struct TrieNode  
{
	NodeType utype;
	//共用体
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
	//查询
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