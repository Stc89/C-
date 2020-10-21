# #C++实现最简单的栈

# #源码

```
#include <iostream>
using namespace std;

class IntStack{
	enum {ssize = 100};
	int stack[ssize];
	int top;
	public:
		/*构造函数，初始化top变量的值*/
		IntStack():top(0){}
		void push(int i){
			stack[top++] = i;
			//cout << "top: "<< top << endl;
		}
		int pop(){
			return stack[--top];
		}
};

int main(){
	IntStack is;
	for(int i = 0; i< 20; i++){
		cout << i*i << endl; 
		is.push(i*i);
	}
	cout << "--------------------------" << endl;
	for(int j = 0; j< 20; j++)
		cout << is.pop() << endl;
}
```

