/*小牛牛是牛牛王国的将军,为了训练出精锐的部队,他会对新兵进行训练。部队进入了n个新兵,每个新兵有一个战斗力值和潜力值,当两个新兵进行决斗时,总是战斗力值高的获胜。获胜的新兵的战斗力值就会变成对手的潜力值 + 自己的战斗力值 - 对手的战斗力值。败者将会被淘汰。若两者战斗力值一样,则会同归于尽,双双被淘汰(除了考察的那个新兵之外，其他新兵之间不会发生战斗) 。小牛牛想知道通过互相决斗之后新兵中战斗力值+潜力值最高的一个可能达到多少,你能帮助小牛牛将军求出来吗?
输入描述:

输入包括n+1行,第一行包括一个整数n(1 ≤ n ≤ 10^5);
接下来的n行,每行两个整数x和y(1 ≤ x,y ≤ 10^9)



输出描述:

输出一个整数,表示新兵中战斗力值+潜力值最高的一个能达到多少。

示例1
输入

2
1 2
2 1

输出

4

*/
#include<iostream>
#include<map>
#include<algorithm>
using namespace std;
struct solider{
    int x;
    int y;
};
int main(){
    int n;
    long long Cursum=0,AvailableCE=0,Maxsum=0;
    cin>>n;
    solider a[n];
    for(int i=0;i<n;i++){
        cin>>a[i].x>>a[i].y;
        if(a[i].x<a[i].y){ 
            AvailableCE+=a[i].y-a[i].x;
            Cursum=2*a[i].x;
            if(Cursum>Maxsum)Maxsum=Cursum;}
        else{
            Cursum=a[i].x+a[i].y;
            if(Cursum>Maxsum)Maxsum=Cursum;}
    }
     cout<<Maxsum+AvailableCE<<endl;
     return 0;
}
