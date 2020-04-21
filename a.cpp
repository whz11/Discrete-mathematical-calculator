#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>
#include <map>
using namespace std;
char sr[100];//输入表达式
char back[100];//后缀表达式
string word;//字母存放
map<char,int> M;//字母与01的映射
int n;
int one[50][50];//不定长数组，存放主析取范式对应字母变量的01情况，也就是表达式真值为1
int zero[50][50];//不定长数组，存放主析取范式对应字母变量的01情况，也就是表达式真值为0
int oneCount=0;
int zeroCount=0;
int out(char a)
{
    if(a=='!') return 9;
    if(a=='&') return 7;
    if(a=='|') return 5;
    if(a=='>') return 3;
    if(a=='=') return 1;
    return 0;

}
int in(char a)
{
    if(a=='!') return 10;
    if(a=='&') return 8;
    if(a=='|') return 6;
    if(a=='>') return 4;
    if(a=='=') return 2;
    return 0;
}
 
void change()
{
    int j=0;
    stack<char> s;
    char y;
    s.push('#');
      int i = 0;
    while(sr[i]!='#')
    {
        if(isalpha(sr[i]))
        {
            back[j++]=sr[i];
            if(word.find(sr[i])==-1)
            {
                word.push_back(sr[i]);
            }
        }
    else if(sr[i]=='(')
        {
            
            s.push(sr[i]);
        }
        else if(sr[i]==')')
        {
            for(y=s.top(),s.pop();y!='(';y=s.top(),s.pop())
            {
                back[j++]=y;
            }
           s.pop();
      
        }
        else
        {
            while(!s.empty()&&s.top()!='('&&(out(sr[i])<=in(s.top())))
            {
                back[j++]=s.top();
                s.pop();
            }
            s.push(sr[i]);
        }
        i++;
    }
    while(!s.empty())
    {
        y=s.top();
        s.pop();
        if(y!='#')
        {
            back[j++]=y;
        }
    }
    back[j]='#';
}
int calculate()
{
    stack<int> s;
    char ch;
    int j=0;
    int t1,t2;
    while(1)
    {
        ch=back[j];
        if(ch=='#') break;
        if(ch==0) break;
        j++;
        if((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z'))
        {
            s.push(M[ch]);
        }
        else
        {
            if(ch=='!')
            {
                t1=s.top();
                s.pop();
                s.push(!t1);
            }
            else if(ch=='&')
            {
                t1=s.top();
                s.pop();
                t2=s.top();
                s.pop();
                if(t1==1&&t2==1)
                {
                    s.push(1);
                }
                else
                {
                    s.push(0);
                }
            }
            else if(ch=='|')
            {
                t1=s.top();
                s.pop();
                t2=s.top();
                s.pop();
                if(t1==0&&t2==0)
                {
                    s.push(0);
                }
                else
                {
                    s.push(1);
                }
            }
            else if(ch=='>')
            {
                t1=s.top();
                s.pop();
                t2=s.top();
                s.pop();
                if(t1==0&&t2==1)
                {
                    s.push(0);
                }
                else
                {
                    s.push(1);
                }
            }
            else if(ch=='=')
            {
                t1=s.top();
                s.pop();
                t2=s.top();
                s.pop();
                if((t1==1&&t2==1)||(t1==0&&t2==0))
                {
                    s.push(1);
                }
                else
                {
                    s.push(0);
                }
            }
    }
  }
    int ans=s.top();
    return ans;
}
void dfs(int step)
{
    if(step==n)
    {
        for(int i=0;i<n;i++)
        {
            if(M[word[i]])
            {
                printf("1 ");
            }
            else
            {
                printf("0 ");
            }
        }
    printf("%d\n",calculate());
        if(calculate()){
            for(int i=0;i<n;i++){
                one[oneCount][i]=M[word[i]];
            }
            oneCount++;
        }else{
            for (int i=0; i<n; i++) {
                zero[zeroCount][i]=M[word[i]];
            }
            zeroCount++;
        }
        return;
    }
    M[word[step]]=1;
    dfs(step+1);
    M[word[step]]=0;
    dfs(step+1);
}
void disjunctive(){ //主析取
    printf("主析取范式:\n");
    while(oneCount--){
        printf("(");
        for(int j=0;j<n;j++){
            if(j!=0) printf("∧");
            if(one[oneCount][j]==1){
                printf("%c",word[j]);
            }else{
                printf("!%c",word[j]);
            }
        }
        printf(")");
        if(oneCount!=0)printf("v");
    }
    printf("\n");
}
void conjunction(){//主合取
    printf("主合取范式:\n");
    while(zeroCount--){
        printf("(");
        for(int j=0;j<n;j++){
            if(j!=0) printf("v");
            if(zero[zeroCount][j]==1){
                printf("%c",word[j]);
            }else{
                printf("!%c",word[j]);
            }
        }
        printf(")");
        if(zeroCount!=0)printf("∧");
    }
    printf("\n");
}

int main(){
    
    printf("或运算为 |  , 与运算为 &   ,单条件为 >  ,双条件为 = ,非运算为 !\n");
    printf("请输入命题个数，如p&q即输入2:\n");
    cin>>n;
    do{
        printf("请输入表达式,以#结尾\n");
        cin>>sr;
    }while (sr[strlen(sr)-1]!='#');
    change();
    for(int i=0;i<n;i++){
        printf("%c ",word[i]);
    }
    printf("result\n");
    dfs(0);
    disjunctive();
    conjunction();
     return 0;
}
