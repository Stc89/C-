# C++ 同名覆盖和多态

多态是一个比较有意思的话题

# #同名覆盖

在基类中定义了一个非[虚拟函数](http://www.so.com/s?q=虚拟函数&ie=utf-8&src=internal_wenda_recommend_textn)，然后在[派生类](http://www.so.com/s?q=派生类&ie=utf-8&src=internal_wenda_recommend_textn)中又定义了一个同名同[参数](http://www.so.com/s?q=参数&ie=utf-8&src=internal_wenda_recommend_textn)同返回类型的[函数](http://www.so.com/s?q=函数&ie=utf-8&src=internal_wenda_recommend_textn)，这就是覆盖了。在派生类对象上直接调用这个函数名，只会调用派生类中的那个。

# #测试程序

```
#include<iostream>

using namespace std;

/**
 * 基类
 */
class Mammal{
public:

  void Speak() const {
  cout << "Mammal" <<endl;
};
};

/**
 * Dog类
 */
class Dog:public Mammal{
public:

  void Speak() const {
    cout << "Dog" << endl;
  };
};


int main(){
  Dog dog;
  dog.Speak();
}
```

# #程序输出

```
Dog

--------------------------------
Process exited after 3.931 seconds with return value 0
请按任意键继续. . .
```



# #函数重载
在基类中定义了一个非虚拟函数，然后在派生类中定义一个同名，但是具有不同的参数表的函数，这就是重载。在派生类对象上调用这几个函数时，用不同的参数会调用到不同的函数，有可能会直接调用到基类中的那个。

# #测试程序

```
#include<iostream>

using namespace std;

/**
 * 基类
 */
class Mammal{
public:

  void Speak() const {
  cout << "Mammal" <<endl;
};
};

/**
 * Dog类
 */
class Dog:public Mammal{
public:

  void Speak(int i) const {
    cout << "Dog i:" << i << endl;
  };
};


int main(){
  Dog dog;
  dog.Speak(12);
}
```



# # 程序输出

```
Dog i:12

--------------------------------
Process exited after 3.884 seconds with return value 0
请按任意键继续. . .
```



# #多态
在基类中定义了一个虚拟函数，然后在派生类中又定义一个同名，同参数表的函数，这就是多态。多态是这3种情况中唯一采用动态绑定技术的一种情况。也就是说，通过一个基类指针来操作对象，如果对象是基类对象，就会调用基类中的那个函数，如果对象实际是派生类对象，就会调用派声雷中的那个函数，调用哪个函数并不由函数的参数表决定，而是由函数的实际类型决定。

# #测试程序

```
#include<iostream>
using namespace std;
class CFather
{
public:
	CFather()
	{
		cout << "CFather()" << endl;
	}
	
    void AA()
    {
        cout << "CFather :: AA()" << endl;
    }
};
class CSon1 : public CFather
{
public:
	CSon1()
	{
		cout << "CSon1()" << endl;
	}
    void AA()
    {
        cout << "CSon1 :: AA()" << endl;
    }
};

class CSon2 : public CFather
{
public:
	CSon2()
	{
		cout << "CSon2()" << endl;
	}
    void AA()
    {
        cout << "CSon2 :: AA()" << endl;
    }
};

int main()
{
	class CFather *pf;
	
	class CSon1 mCs1;
	class CSon2 mCs2;

	pf = &mCs1;
	pf->AA(); 

	pf = &mCs2;
	pf->AA(); 

    system("pause");
    return 0;
}
```

# # 程序输出

```
CFather()
CSon1()
CFather()
CSon2()
CFather :: AA()
CFather :: AA()
请按任意键继续. . .
```

构造函数被调用比较容易理解。

**基类的指针同时是可以被派生类赋值的**，这就是`pf = &mCs1;` 和 `pf = &mCs2;`  没有问题的原因。

子类对象可以直接赋值给父类对象
子类对象可以直接初始化父类对象
父类指针可以指向子类对象
父类引用可以直接引用子类对象

**但是上面的代码有个问题**

我怎么才能调用到派生类里面的`AA()` 函数呢?

当然，我可以修改调用方式，声明一个派生类的对象，然后再用派生类的对象去调用派生类里面的函数。

不过这样就显得不多态了，多态要求我在基类里面调用一次，所有派生类都能被调用到。

**所有就出现了虚函数**

# #测试程序

```
#include<iostream>
using namespace std;
class CFather
{
public:
	CFather()
	{
		cout << "CFather()" << endl;
	}
	
    virtual void AA()
    {
        cout << "CFather :: AA()" << endl;
    }
};
class CSon1 : public CFather
{
public:
	CSon1()
	{
		cout << "CSon1()" << endl;
	}
    void AA()
    {
        cout << "CSon1 :: AA()" << endl;
    }
};

class CSon2 : public CFather
{
public:
	CSon2()
	{
		cout << "CSon2()" << endl;
	}
    void AA()
    {
        cout << "CSon2 :: AA()" << endl;
    }
};

int main()
{
	class CFather *pf;
	
	class CSon1 mCs1;
	class CSon2 mCs2;

	pf = &mCs1;
	pf->AA(); 

	pf = &mCs2;
	pf->AA(); 

    system("pause");
    return 0;
}
```

 # #程序输出

```
CFather()
CSon1()
CFather()
CSon2()
CSon1 :: AA()
CSon2 :: AA()
请按任意键继续. . .
```

我只是在基类种把 `void AA()` 修改成了 `virtual void AA()` 。

情况就发生了巨大的变化，也就是这个变化，显得我们作为一个 **懒**码农的需求。

