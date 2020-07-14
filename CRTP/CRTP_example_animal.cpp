#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Father{
 public:
    int num;
    void father_print()const {
        static_cast<const T*>(this) ->print();
    }

};

class son: public Father<son>{
 public:
    son(int i =0){num = i;}

    void print()const {
        cout<<"this is the son print()"<<num<<endl;
    }

    void not_virtual_print(){cout <<"not virtual function"<<num <<endl;}

};//静态模板，奇异递归模板


template<typename T>
class Base{
public:
    void base_show()const {
        static_cast<const T*>(this) ->show(); //将基类中的this指针转化为T*类型
    }
    Base<T> operator+(){
        static_cast<T*>(this)->operator+();
    }
};

class Derived : public Base<Derived>{
public:
    Derived (int hoo):val(hoo){};
    void show()const {
        cout<<"say hello in the Derived class"<<endl;
        cout<<"the val is"<<this ->val<<endl;
    }
    Derived operator+(){
        ++(this->val);
        return *this;
    }
private:
    int val;
};//在派生类中重构了"+"这个运算符

//为了 保留多态性和减少虚函数表查找开销
// 我们使用模板类继承一非模板类的基类,如下例子

class Animal{
 public:
    virtual void say()const =0;//纯虚函数
    virtual ~Animal(){}
};

template<typename T>
class Animal_CRTP:public Animal{
 public:
    void say() const override {
        static_cast<const T*>(this) ->say();
    }
};

class Cat:public Animal_CRTP<Cat>{
 public:
    void say()const{
        cout<< "Meow I'm a cat meow"<<endl;
    }

};

class Dog:public Animal_CRTP<Dog>{
 public:
    void say()const{
        cout<< "Wang, I'm a Dog Wang"<<endl;
    }
};
template <typename T>
void Action(Animal_CRTP<T> &animal){
    animal.say();
}
int main(){
    son* e = new son(10);
    son p;
    e->print();
    Father<son> *q =&p;
    q->father_print();
    Derived dev(122);
    Base<Derived> *base =&dev;
    base->base_show();
    +(*base);
    base->base_show();
    Derived d(66);
    d.show();
    d.base_show();
    Cat cat;
    Dog dog;
    Action(dog);
    Action(cat);
}


