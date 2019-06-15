#include <iostream>
#include <string.h>
#include <map>
#include <stack>
#include <cstdlib>
#include <string>
#include <sstream>
#include <queue>
using namespace std;

stack<string> analyseStack;
string st;
map<char,int> c_d;
int index = 0;
char pt[9][9]={
	{' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{' ','>','>','<','<','<','>','<','>'},
	{' ','>','>','<','<','<','>','<','>'},
	{' ','>','>','>','>','<','>','<','>'},
	{' ','>','>','>','>','<','>','<','>'},
	{' ','<','<','<','<','<','=','<',' '},
	{' ','>','>','>','>',' ','>',' ','>'},
	{' ','>','>','>','>',' ','>',' ','>'},
	{' ','<','<','<','<','<',' ','<','='}
	}; 
void CreatePriorityTable();//�������ȱ� 
void PrintPriorityTable();//��ӡ���ȱ�
void PrintStack(stack<string> analyseStack);//��ӡ����ջ 
void PrintQueue(queue<string> concludeQ);//��ӡ��Լ���� 
int getValue(int index);//��indexλ��ʼ ��ȡ���ʽ����һ�������� ����index�ƶ�����һ����λ�ķ��ſ�ʼ�� 
string getValueS(int index);//��indexλ��ʼ ��ȡ���ʽ����һ�������� ����string ����index�ƶ�����һ����λ�ķ��ſ�ʼ�� 
bool isOpeartor(string str);//�ж�ջ��Ԫ���ǲ��ǲ�����
bool isOpeartor(char c);//�ж����봮Ҫ�����Ԫ���ǲ��ǲ����� 
bool OpeartorPriority();//������ȷ���
string ConcludeAnalyse(stack<string> analyseStack, char c);//��Լ���� 
double TransMode(queue<string> concludeQ);//����ģʽ 
void ERROR();//������� 
int main() {
	cin>>st;
	CreatePriorityTable();
	PrintPriorityTable();
	analyseStack.push("#");
	
	return 0;
}
string ConcludeAnalyse(stack<string> analyseStack, char c)
{
	queue<string> concludeQ;
	string Q = analyseStack.top();
	analyseStack.pop();
	concludeQ.push(Q);
	Q = analyseStack.top();
	do{
		
		if(!isOpeartor(Q))           //������ս�� 
		{
			concludeQ.push(Q);
			analyseStack.pop();
			
		}else{						//��������ս�� ��Q ȡ��һ�� 
			concludeQ.push(Q);
			analyseStack.pop();
			concludeQ.push(analyseStack.top()); 
			analyseStack.pop();
		}
		Q = analyseStack.top();
	}while(pt[c_d[Q[0]]][c_d[c]] != '<')
	
	
}
double TransMode(queue<string> concludeQ)
{
	if(concludeQ.size()==3)
	{
		double res = 0;
		string op2 = concludeQ.front();
		concludeQ.pop();
		string op = concludeQ.front();
		concludeQ.pop();
		string op1 = concludeQ.front();
		concludeQ.pop();
		
		if(op2==")")
		{
			return double(atoi(op.c_str()));
		}else{
			if(op == "+"){
				return double(atoi(op1.c_str())) + double(atoi(op2.c_str()));
			}else if(op == "-"){
				return double(atoi(op1.c_str())) + double(atoi(op2.c_str()));
			}else if(op == "*"){
				return double(atoi(op1.c_str())) * double(atoi(op2.c_str()));
			}else{
				return double(atoi(op1.c_str())) / double(atoi(op2.c_str()));
			}
		}
	}
} 
bool OpeartorPriority()
{
	/*
		������ȷ�Ϊ�����׶Σ�
			1. �ƽ����Լ
			2.���ַ����ƽ���ȫ�Ժ�ʣ�µľ��ǹ�Լ�����ʱ��ֻ�й�Լ 
	*/
	//��һ�׶� ��ʱ��index!=st.size()-1ʱ���ͻ�һֱ�ƽ���ֱ��indexָ����st.size()-1
	while(index!=st.size()-1)
	{
		string stacktop = analyseStack.top();      //ȡջ��Ԫ��
		if(isOpeartor(stacktop))                   //��ջ��Ԫ��Ϊ����� 
		{
			char s = stacktop[0];                
			if(!isOpeartor(st[index]))             //������봮Ҫ����������� 
			{
				string data=getValueS(index);
				char c =  pt[c_d[s]][c_d['n']]   //�����ȱ��л�ȡջ��Ԫ��������Ԫ�ص����ȼ�
				cout<<"s"<<s<<"\tn\t";
				cout<<c<<endl;
				if(c == '<' || c=='=')			//����� < = ������Ԫ���ƽ�����ջ 
				{
					analyseStack.push(data);
				}else{
					ERROR();
				}
//				int data=getValue(index);
//				char c =  pt[c_d[s]][c_d['n']]   //�����ȱ��л�ȡջ��Ԫ��������Ԫ�ص����ȼ�
//				cout<<"s"<<s<<"\tn\t";
//				cout<<c<<endl;
//				if(c=='<' || c=='=')
//				{
//					string res;
//    				stringstream ss;
//    				ss << data;
//    				ss >> res;
//					analyseStack.push(res);
//				}
			}else{                                //����������� 
				char i = st[index++];
				char c = pt[c_d[s]][c_d[i]];
				if(c == '<' || c == '=')        //����� < = ������Ԫ���ƽ�����ջ
				{
					analyseStack.push(""+i);
				}else if(c=='>'){              //����� > ����й�Լ 
					
				}else{
					ERROR();                   // ����� ���ո񣩣���ô���봮��ƥ�� 
				}
			} 
		}else{                                //��ջ��Ԫ�ز�Ϊ����� ��һ�������� 
			if(!isOpeartor(st[index]))             //������봮Ҫ�����������  ��ô������������ ������� 
			{
				ERROR();
			}else{
				char i = st[index++];
				char c = pt[c_d['n']][c_d[i]];
				if(c == '<' || c == '=')        //����� < = ������Ԫ���ƽ�����ջ
				{
					analyseStack.push(""+i);
				}else if(c=='>'){              //����� > ����й�Լ 
					
				}else{
					ERROR();                   // ����� ���ո񣩣���ô���봮��ƥ�� 
				}
			}
		} 
	} 
}
void ERROR()
{
	cout<<"���������";
	exit(-1); 
} 
bool isOpeartor(string str)
{
	if(str=="+"||str=="-"||str=="*"||str=="/"||str=="("||str==")"||str=="#")
	{	
		return true;
	}else{
		return false;
	}
}
bool isOpeartor(char c)
{
	if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'||c=='#')
	{
		return true;
	}else{
		return false;
	}
}
int getValue(int index)
{
	string str=st.substr(index,st.size()-index);
	int result;
	result = atoi(str.c_str());
	while(st[index] >= 48 && st[index] <= 57)
	{
		index++;
	}
	return result;
} 
string getValueS(int index)
{
	string res="";
	while(st[index] >= 48 && st[index] <= 57)
	{
		index++;
		res+=st[index];
	}
	return res;
}
void CreatePriorityTable()
{
	c_d['+'] = 1;
	c_d['-'] = 2;
	c_d['*'] = 3;
	c_d['/'] = 4;
	c_d['('] = 5;
	c_d[')'] = 6;
	c_d['n'] = 7;
	c_d['#'] = 8;
} 
void PrintPriorityTable()//��ӡ���ȱ�
{
	cout<<"\t+\t-\t*\t/\t(\t)\tn\t#"<<endl;
	for(int i =1;i<9;i++)
	{
		cout<<"\t";
		for(int j = 1; j < 9;j++)
		{
			cout<<pt[i][j]<<"\t";
		}cout<<endl;
	}
} 
void PrintStack(stack<string> analyseStack)
{
	while(!analyseStack.empty())
	{
		cout<<analyseStack.top()<<"\t";
		analyseStack.pop();	
	} 
	cout<<endl;
} 
void PrintQueue(queue<string> concludeQ)
{
	while(!concludeQ.empty()){
		cout<<concludeQ.front()<<"\t";
		concludeQ.pop();
	} cout<<endl;
} 