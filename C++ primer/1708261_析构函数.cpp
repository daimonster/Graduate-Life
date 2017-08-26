/*析构函数
用构造函数创建对象后，程序负责跟踪该对象，直到其过期为止。对象过期时，程序将自动调用一个特殊的成员函数：析构函数/析构函数完成清理工作。
例如，如果构造函数使用new来分配内存，则析构函数将使用delete来释放内存。Stock的构造函数没有使用new，因此析构函数实际上没有要完成的任务。在这种情况要，只需要让编译器生成一个什么都不做的隐私析构函数即可
和构造函数一样析构函数的名称也很特殊：在类名前加上~.因此，Stock类的析构函数为~Stock().另外，和构造函数一样，异构函数也可以没有返回值和声明类型。与构造函数不同的是，析构函数没有参数，因此Stock的原型必须是这样的：
~Stock()
可以将它编写为不执行任何操作的函数
Stock::~Stock(){}
什么
