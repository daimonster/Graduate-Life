/*重载运算符：作为成员函数还是非成员函数
对于很多运算符来说，可以选择使用成员函数或非成员函数来实现运算符重载。一般来说，非成员函数应该是友元函数，这样它才能直接访问类的私有数据。例如，Time类的加法运算符在Time类声明中的原型如下：
Time operator+(const Time & t)const
这个类也可以使用下面的原型：
frind Time operator+(const Time & t1,const Time & t2);
加法运算符需要两个操作数。对于成员函数版本来说，一个操作数通过this指针隐式地传递，另一个操作数作为函数参数显示地传递：对于友元版本来说，两个操作数都作为参数来传递。
这两个原型都与表达式T2+T3匹配，其中T2和T3都是Time类型对象。也就是说，编译器将下面的语句
T1=T2+T3
转换为下面两个的任何一个
T1=T2.operator+(T3);//成员函数类型
T1=operator(T2,T3);//非成员函数
记住，在定义运算符时，必须选择其中的一个格式，而不能同时选择这两种格式。因为这两种格式都与同一个表达式匹配，同时定义这两种格式将被视为二义性错误，导致编译错误
那么哪种格式最好呢？对于某些运算符来说，成员函数是唯一合法的选择。在其他情况下，这两种格式没有太大的区别

一个矢量类
下面介绍另一种使用了运算符重载和友元的类设计

