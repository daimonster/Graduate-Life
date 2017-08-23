/*还需要创建类描述的第二部分：为那些由类声明中的原型表示的成员函数提供代码。成员函数定义与常规函数定义非常相似，它们由函数头和函数题，也可以由返回类型和参数。但它们还有两个特殊的特征：
定义成员函数时，使用作用域解析运算符(::)来这出函数所属的类
类方法可以访问类的private组件
首先，成员的函数头使用作用域运算符解析(::)来指出函数所属的类。例如，update()成员函数的函数头如下：
void Stock::update(double price)
这种表示法意味着我们定义的update()函数是Stock类的成员。这不仅将update()标识为成员函数，还意味着我们可以将另一个类的成员函数也命名为update().例如，Buffonon()类的update()函数的函数头如下：
void Buffoon::update()
因此，作用域解析运算符确定了方法定义对应的类的身份。我们说，标识符update()具有类作用域(class scope).Stock类的其他成员函数不必使用作用域解析运算符，就可以使用update()方法，这是因为它们属于同一个类，因此update()是可见的。然而，在类声明和方法定义之外使用update()时，需要采取特殊的措施。
类方法的完整名称包括类名。我们说Stock::update()是函数的限定名;而简单的update()是全名的缩写(非限定名)，它只能在类作用域中使用
方法的第二个特点是，方法可以访问类的私有成员。例如show()方法可以使用这样的代码：
std::cout<<"Company: "<<company
		<<" Shares: "<<shares<<endl;
		<<" Shares Price: $"<<share_val
		<<" Total Worth: $"<<total_val<<endl;
其中，company、shares等都是Stock类的私有数据成员*/
#include<iostream>
#include "1708171_stock.h"
void Stock::acquire(const std::string &co,long n,double pr){
	company=co;
	if(n<0){
		std::<<"Number of shares can't be negative;"
			<<compant<<" shares set to 0.\n";
		shares=0;
		}
		else
			shares=n;
		shares_val=pr;
		set_tot();
} 
void Stock::buy(long num,double price){
	if(num<0)
	{
		std::cout<<"Number of shares purchased can't be negative."
			<<"Transaction is aborted.\n";
	}
	else{
		shares+=num;
		share_val=price;
		set_tot();
	}
}
void Stock::sell(long num,double price){
	using std::cout;
	if(num<0)
	{
		std::cout<<"Number of shares sold can't be negative."
			<<"Transaction is aborted.\n";
	}
	else if(num>shares){
		cout<<"You can't sell more than you have!"
			<<"Transaction is aborted.\n";
	}
	else{
		shares-=num;
		share_val=price;
		set_tot();
	}
}
void Stock::update(double price){
	share_val=price;
	set_tot();
}
void Stock::show(){
	std::cout<<"Company: "<<company
			<<" Shares "<<shares<<'\n'
			<<" share Price: $"<<<<share_val;
			<<" Total Worth: $"<<<<total_val<<'\n';
}
/*
1成员函数说明
acquire()函数管理对某个公司股票的首次购买，而buy()和sell()管理增减或减少持有的股票。方法buy()和sell
