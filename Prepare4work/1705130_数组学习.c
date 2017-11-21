/*数组可以说是最简单的一种数据结构，它占据一块连续的内存并按照顺序存储数据。创建数组时，我们需要首先指定数组容量的大小，然后根据大小分配内存。即使我们只在数组中存储一个数据，也需要为所有的数据分配内存。因此数据的空间效率不是很好，经常有空闲的区域没有得到充分的应用。
    由于数组中的内存是连续的，于是可以根据下标O(1)时间读写任何元素，因此它的时间效率是很高的。我们可以根据数组时间效率高的有点，用数组来实现简单的哈希表：把数组的下标设为哈希表的键值，而把数组中的每一个数字设为哈希表的值(Value)，这样每一个下标及数组中该下标对应的数字就组成了一个键值-值的配对，有了这样的哈希表，我们就可以在O(1)实现查找，从而可以高效地解决很多问题。面试题35“第一个值出现一次的字母”就是很好的例子。
    为解决数组空间效率不高的问题，人们由设计实现了多种动态数组，比如C++的STL中的vector。但数据的数目超过数组的容量时，我们重新分配一块更大的空间(STL的vector每次扩充容量时，新的容量都是前一次的两倍)，把之前的数据复制到新的数组中，再把之前的内存释放，这样就能减少内存的浪费。但我们也注意到每一次扩充数组容量时都有大量的额外操作，这对时间性能有负面的影响，因此数用动态数组时要尽量减少改变数组容量大小的次数。
    在C/C++中，数组和指针是相互关联又有区别的两个概念。当我们声明一个数组时，其数组的名字也是一个指针，该指针指向数组的第一个元素。我们可以用一个指针来访问数据。但值得注意的是，C/C++没有记录数组的代销哦啊，因此用指针访问数组中的元素时，程序员要确保没有超出数组的边界。下面通过一个例子来了解数组和指针的区别。运行下面的代码，请问输出是什么？*/
#include<stdio.h>
int Getsize(int data[])
{
    return sizeof(data);
}
int main(int argc,char * argv[])
{
    int data1[]={1,2,3,4,5};
    int size1=sizeof(data1);
    int *data2=data1;
    int size2=sizeof(data2);
    int size3=Getsize(data1);
    printf("%d,%d,%d",size1,size2,size3);
    return 0;
}//64为系统的指针大小是8个字节，任何系统的指针大小都是8个字节
