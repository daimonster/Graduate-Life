# 某餐馆有n张桌子，每张桌子有一个参数：a 可容纳的最大人数； 有m批客人，每批客人有两个参数:b人数，c预计消费金额。 在不允许拼桌的情况下，请实现一个算法选择其中一部分客人，使得总预计消费金额最大
# 输入描述:

# 输入包括m+2行。 第一行两个整数n(1 <= n <= 50000),m(1 <= m <= 50000) 第二行为n个参数a,即每个桌子可容纳的最大人数,以空格分隔,范围均在32位int范围内。 接下来m行，每行两个参数b,c。分别表示第i批客人的人数和预计消费金额,以空格分隔,范围均在32位int范围内。

# n,m
# a * n
# b * m,c * m

# 输出描述:

# 输出一个整数,表示最大的总预计消费金额


# 输入例子1:

# 3 5 
# 2 4 2 
# 1 3 
# 3 5 
# 3 7 
# 5 9 
# 1 10


# 输出例子1:

# 20
import bisect
 
n,m = map(int,input().split())
a = sorted(list(map(int,input().split())))
M = []
for i in range(m):
    M.append(list(map(int,input().split())))
 
Mc = sorted(M,key = lambda x : x[1],reverse = True)
sum = 0
for l in Mc:
    index = bisect.bisect_left(a,l[0])
    if index < len(a):
        sum += l[1]
        del a[index]
 
print(sum)

