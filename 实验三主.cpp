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
void CreatePriorityTable();//建立优先表 
void PrintPriorityTable();//打印优先表
void PrintStack(stack<string> analyseStack);//打印分析栈 
void PrintQueue(queue<string> concludeQ);//打印规约队列 
int getValue(int index);//从index位开始 获取表达式中下一个操作数 并且index移动到下一个单位的符号开始处 
string getValueS(int index);//从index位开始 获取表达式的下一个操作数 返回string 并且index移动到下一个单位的符号开始处 
bool isOpeartor(string str);//判断栈顶元素是不是操作符
bool isOpeartor(char c);//判断输入串要移入的元素是不是操作符 
bool OpeartorPriority();//算符优先分析
string ConcludeAnalyse(stack<string> analyseStack, char c);//规约分析 
double TransMode(queue<string> concludeQ);//翻译模式 
void ERROR();//程序出错 
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
		
		if(!isOpeartor(Q))           //如果是终结符 
		{
			concludeQ.push(Q);
			analyseStack.pop();
			
		}else{						//如果不是终结符 则Q 取下一个 
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
		算符优先分为两个阶段，
			1. 移进与规约
			2.当字符串移进完全以后，剩下的就是规约，这个时候只有规约 
	*/
	//第一阶段 此时当index!=st.size()-1时，就会一直移进，直到index指向了st.size()-1
	while(index!=st.size()-1)
	{
		string stacktop = analyseStack.top();      //取栈顶元素
		if(isOpeartor(stacktop))                   //当栈顶元素为运算符 
		{
			char s = stacktop[0];                
			if(!isOpeartor(st[index]))             //如果输入串要移入的是数字 
			{
				string data=getValueS(index);
				char c =  pt[c_d[s]][c_d['n']]   //从优先表中获取栈顶元素与移入元素的优先级
				cout<<"s"<<s<<"\tn\t";
				cout<<c<<endl;
				if(c == '<' || c=='=')			//如果是 < = 则把这个元素移进分析栈 
				{
					analyseStack.push(data);
				}else{
					ERROR();
				}
//				int data=getValue(index);
//				char c =  pt[c_d[s]][c_d['n']]   //从优先表中获取栈顶元素与移入元素的优先级
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
			}else{                                //如果不是数字 
				char i = st[index++];
				char c = pt[c_d[s]][c_d[i]];
				if(c == '<' || c == '=')        //如果是 < = 则把这个元素移进分析栈
				{
					analyseStack.push(""+i);
				}else if(c=='>'){              //如果是 > 则进行规约 
					
				}else{
					ERROR();                   // 如果是 （空格），那么输入串不匹配 
				}
			} 
		}else{                                //当栈顶元素不为运算符 是一个操作数 
			if(!isOpeartor(st[index]))             //如果输入串要移入的是数字  那么两个数字相邻 程序出错 
			{
				ERROR();
			}else{
				char i = st[index++];
				char c = pt[c_d['n']][c_d[i]];
				if(c == '<' || c == '=')        //如果是 < = 则把这个元素移进分析栈
				{
					analyseStack.push(""+i);
				}else if(c=='>'){              //如果是 > 则进行规约 
					
				}else{
					ERROR();                   // 如果是 （空格），那么输入串不匹配 
				}
			}
		} 
	} 
}
void ERROR()
{
	cout<<"输入出错！！";
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
void PrintPriorityTable()//打印优先表
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