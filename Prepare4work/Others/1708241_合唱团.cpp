/*题目描述
有 n 个学生站成一排，每个学生有一个能力值，牛牛想从这 n 个学生中按照顺序选取 k 名学生，要求相邻两个学生的位置编号的差不超过 d，使得这 k 个学生的能力值的乘积最大，你能返回最大的乘积吗？
输入描述:

每个输入包含 1 个测试用例。每个测试数据的第一行包含一个整数 n (1 <= n <= 50)，表示学生的个数，接下来的一行，包含 n 个整数，按顺序表示每个学生的能力值 ai（-50 <= ai <= 50）。接下来的一行包含两个整数，k 和 d (1 <= k <= 10, 1 <= d <= 50)。

输出描述:

输出一行表示最大的乘积。*/
/*
 * 因为有正有负，负负得正，所以要维护两个dp数组，一个存储最大，一个存储最小。
 * 定义fm[k][i]表示当选中了k个学生，并且以第i个学生为结尾，所产生的最大乘积
 * fn[k][i]表示选中了k个学生，并且以第i个学生为结尾，所产生的最小乘积
 * 那么fm[k+1][i+1] = max(fm[k][i] * stu[i+1],fn[k][i] * stu[i+1]),
 * 即当选中了k个学生之后，再选择i+1学生，所产生的最大的最大乘积；
 * 然而，并不能保证上一次选择的就是第i个学生，所以要遍历子数组fm[k],
 * 令j从i到1，并且j与i+1之间最小间隔D,遍历fm[k][j],以及fn[k][j];
 * 同理fn[k+1][i+1] = min(fn[k][i] * stu[i+1],fm[k][i] * stu[i+1])。
 * 最后，遍历一遍fm[K][i]求得最大值（i从1~N）
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
int main(){
	int n,k,d;
	cin>>n;
	vector<int> stu(n + 1,0);
	for(int i = 1;i <= n;i++){
		cin>>stu[i];}
	cin>>k>>d;
	vector<vector<int> >dpmax(11,vector<int>(51,0));
	vector<vector<int> >dpmin(11,vector<int>(51,0));
	int maxnum = INT_MIN;
	for(int i = 1;i <= n;i++){
        dpmax[1][i] = dpmin[1][i] = stu[i];
		for(int j = 2;j <= k;j++){
			for(int l = i-1;l > 0 && i - l <= d;l--){
				dpmax[j][i] = max(dpmax[j][i],max(dpmax[j-1][l] * stu[i],dpmin[j-1][l] * stu[i]));
				dpmin[j][i] = min(dpmin[j][i],min(dpmax[j-1][l] * stu[i],dpmin[j-1][l] * stu[i]));
			}
		}
		maxnum = max(maxnum,dpmax[k][i]);
	}
	cout << maxnum << endl;
	return 0;
}
	
