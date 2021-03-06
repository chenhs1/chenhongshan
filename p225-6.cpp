﻿// p225-6.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
/*切割木棍问题	为下列问题设计一个动态规划算法。
已知小木棍的销售价格pi和长度i相关，i=1,2,……，n，如何把长度为n的木棍切割为若干根长度为整数的小木棍，使得所能获得的总销售价格最大？
该算法的时间效率和空间效率各是多少？


解：令长度为n的木棍能获得的最大价格为price(n)=MAX(price(i)+price(n-i))。
长度为n的价格有两种，第一种：原始长度为n时的价格，第二种：加n分割为个小块 再加起来的价格。

假设i和pi的关系如下
i（长度）	1	2	3	4	5	6	7	8	9	10
pi（价格）	1	7	8	9	10	17	17	20	23	24

先从最短的长度 1开始找相对应长度可得到的最大价值，因为长度1无法再分，所以maxprice[1] 就为原始长度价格 price[1]。
然后长度2的可得到的最大价值maxprice[2]就为maxprice[1] +maxprice[1] 和 price[2]之中最大的那个。
长度3可得到的最大价值maxprice[3]就为 maxprice[1]+maxprice[2] 、maxprice[2]+maxprice[1]和price[3]中最大的那个。
（为什么没有maxprice[1]+maxprice[1]+maxprice[1]？因为1+1=2，长度为2的最大价格maxprice[2]已知，所以不需要再把2分为1+1了。
而1+2=3、2+1=3时的长度3的maxprice[3]的价格是未知的，也就是每个长度只需要分为两部分就可以。）
因为比当前长度小的所有整数长度的对应的最大价格都是已知的，
所以长度为n时只需要找到maxprice[1]+maxprice[n-1]、maxprice[2]+maxprice[n-2]、…、maxprice[i]+maxprice[n-i]、…、maxprice[n-1]+maxprice[1]、price[n]中最大的值，
再赋值给maxprice[n]。
*/

#include <iostream>
using namespace std; //自底向上，两个循环，不用递归；   
int main()
{
	int n = 10;
	int price[11] = { 0, 1, 7, 8, 9, 10, 17, 17, 20, 23, 24 };

	int *r = new int[n + 1];

	for (int i = 0; i <= n; ++i)
		r[i] = 0;  //初始化  

	for (int i = 1; i <= n; ++i)//规模长度为i    
	{
		int q = INT_MIN;
		for (int j = 1; j <= i; ++j)//计算规模为i的最大收益    
		{
			if (q < (price[j] + r[i - j]))//因为i>i-j，所以当计算r[i]时，r[i-j]已经解决，可以直接用    
				q = (price[j] + r[i - j]);  //迭代q；  
		}
		r[i] = q;  //找出i这个位置的最优解；  
	}
	cout << r[n]; //最后是n这个位置，就是n米长的木头的最大价值。  

	delete r;
	return 0;
}


/*此算法的时间效率是O(n^2)，空间效率是O（N）*/