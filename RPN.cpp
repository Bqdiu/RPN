#include <iostream>
#include <string.h>
using namespace std;

//struct
struct Node
{
    char data;
    Node *Next;
};

struct Stack
{
    Node *top;
};
//khai bao prototype
void showMenu();
Node *createStackNode(char d);
void createStack(Stack &s);
int IsEmty(Stack s);
int push(Stack &s, char d);
int pop(Stack &s, char &d); 
int top(Stack s, char &d);
void printStack(Stack s);
int isOperand(char c); // kiem tra toan hang
int pre(char c); // kiem tra toan tu
void RPN(char P[],Stack &stack); // ham doi sang hau to
float Result(Stack stack); // ket qua cua postfiz
// khai bao ham main
int main(){
    Stack s1;
    Stack s2;
    createStack(s1); 
    createStack(s2);
    char P1[] = "((8+3*2)/2+(9-3*2+5)*2)/3";
    char A,B,C,D;
    char P2[]="(A+B)*(C-(D+A))";
    int chon;
    do
    {
        showMenu();
        cout<<"\nNhap yeu cau:";
        cin>>chon;
        switch (chon)
        {
            case 1:
                cout<<"\n";
                puts(P1);
                cout<<"\nQ: ";
                RPN(P1,s1);
                cout<<"\nKet qua: "<<Result(s1);
                break;
            case 2:
                RPN(P2,s2);
                fflush(stdin);
                cout<<"\nNhap A:";
                cin>>A; 
                cout<<"Nhap B:";
                cin>>B;
                cout<<"Nhap C:";
                cin>>C;
                cout<<"Nhap D:";
                cin>>D;
                P2[1] = A;
                P2[3] = B;
                P2[7] = C;
                P2[10] = D;
                P2[12] = A;
                puts(P2);
                cout<<"\nQ: ";
                RPN(P2,s2);
                cout<<"\nKet qua: "<<Result(s2);
                break;
        }
    } while (chon!=0); 
}
// prototype
void showMenu(){
    cout<<"\n----------Chuyen bieu thuc trung to sang dang hau to----------";
    cout<<"\n1.P = ((8+3*2)/2+(9-3*2+5)*2)/3";
    cout<<"\n2.P = (A+B)*(C-(D+A))";
    cout<<"\n0.Thoat chuong trinh";
}
Node *createStackNode(char d){
    Node *p = new Node;
    if(p==NULL)
    {
        cout<<endl<<"Khong du bo nho de khoi tao";
        return NULL;
    }
    else
    {
        p->data = d;
        p->Next = NULL;
    }
    return p;
}
void createStack(Stack &s){
    s.top = NULL;
}
int IsEmty(Stack s){
    if(s.top==NULL)
        return 1; 
    return 0; 
}
int push(Stack &s, char d){
    Node *p = createStackNode(d);
    if(p==NULL)
        return 0;
    if(IsEmty(s)==1)
        s.top = p;
    else
    {
        p->Next = s.top;
        s.top = p;
    }
    return 1;
}
int pop(Stack &s, char &d){
    if(IsEmty(s)==1)
        return 0;
    Node *p = s.top;
    s.top = s.top->Next;
    d = p->data; 
    delete p;
    return 1;
}
int top(Stack s, char &d){
    if(IsEmty(s)==1)
        return NULL;
    d = s.top->data;
    return d;
}
void printStack(Stack s){
    while (IsEmty(s)!=1)
    {
        cout<<s.top->data<<" ";
        s.top = s.top->Next;
    }
}
int isOperand(char c){
    if((c >= '0' && c<= '9') || (c >= 'A' && c<= 'H'))
        return 1;
    return 0;
}
int pre(char c){
    switch (c)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return 0;
}
void RPN(char P[], Stack &stack){
    Stack postfix;
    createStack(stack);
    createStack(postfix);
    char temp;
    int len = strlen(P);
    for (int i = 0; i < len; i++)
    {
        if((P[i] == '(' || pre(P[i])))
        {
            if(pre(P[i]) == 1 && pre(stack.top->data) == 2) // neu P[i] la dau + - va postfix la * / thi pop postfix ra va push vao stack, push + - vao stack
            {
                pop(stack,temp);
                push(postfix,temp);
                push(stack,P[i]);
            }
            else
                push(stack,P[i]);
        }
        else if(isOperand(P[i]))
            push(postfix,P[i]);
        if(P[i] == ')') // neu gap ")" trong P[i] thi pop cac toan tu trong stack push sang postfix
        {
            while (stack.top->data != '(')
            {
                pop(stack,temp);
                push(postfix,temp);
            }
            pop(stack,temp); // xoa dau "("
        }        
    }
    while(postfix.top != NULL ) // push postfix lai vao stack de theo dung thu tu 
    {
        pop(postfix,temp);
        push(stack,temp);
    }
    printStack(stack);
}
float Result(Stack stack){
    Stack ketqua;
    createStack(ketqua);
    char temp;
    char val1;
    char val2;
    float result;
    while (stack.top != NULL)
    {
        if(isOperand(stack.top->data)) // toan hang
        {
            pop(stack,temp);
            push(ketqua,temp-'0'); //  chuyen ky tu sang so 
        }
        else // toan tu + - * /
        {
            pop(ketqua,val1);
            pop(ketqua,val2);
            switch (stack.top->data)
            {
                case '+': push(ketqua,val2+val1); break;
                case '-': push(ketqua,val2-val1); break;
                case '*': push(ketqua,val2*val1); break;
                case '/': push(ketqua,val2/val1); break;
            }
            pop(stack,temp); // xoa toan hang ra khoi stack
        }
    }
    pop(ketqua,temp);
    result = temp; 
    return result;
}