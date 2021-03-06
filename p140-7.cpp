﻿// p140-7.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//a.对于一个包含100万随机数的数组排列，快速排序比插入排序快多少倍？
/*
插入排序（时间复杂度介于N和N2之间，空间复杂度1），将数组分为有序和无序两个部分，默认数组左变第一个元素是有序的，依次遍历数组第二个元素到最后，与数组左变有序序列比较。如果小于左变有序序列则交换位置。
快速排序（时间复杂度NlogN，空间复杂度lgN）），与归并排序一样，都是利用分治的排序算法。将数组分成两个子数组，将两部分独立排序，递归发生在处理数组之前。不需要额外的内存空间存储一个临时数组。
*/

#include <iostream>
#include<time.h>
#include <sys/timeb.h>
using namespace std;
//效率测试
#define NUMBER 1000000
long long getSystemTime()
{
	struct timeb t;
	ftime(&t);
	return 1000 * t.time + t.millitm;
}

//-----------------快速排序 ---------------------
void quickSort(int *a, int left, int right)
{
	if (left > right) return;
	int i = left;
	int j = right;
	int tem = a[left];
	while (i != j)
	{
		while (a[j] > tem && i < j)
			j--;
		while (a[i] <= tem && i < j)
			i++;
		if (i < j)
		{
			int t = a[j];
			a[j] = a[i];
			a[i] = t;
		}
	}

	a[left] = a[i];
	a[i] = tem;

	quickSort(a, left, i - 1);
	quickSort(a, i + 1, right);
	return;
}

//--------------------插入排序---------------------
void insertSort(int *a, int len)
{
	int index;
	int tem;
	// 遍历无序序列
	for (int i = 1; i < len; i++)
	{
		index = i;  //存储当前基准数位置
		tem = a[i];
		// 遍历有序序列
		for (int j = i; j > 0; j--)
		{

			if (tem < a[j - 1])  //找到比基准数大的位置，则将有序序列后移，并记录有序序列位置
			{
				a[j] = a[j - 1];
				index = j - 1;
			}
			else
			{
				break;
			}
		}
		a[index] = tem; //将基准数填入
	}
}

int main()
{
	long long timeStart, timeEnd, timeUse;
	srand((unsigned)time(NULL));

	int(*array)[NUMBER] = new int[7][NUMBER];
	int *arrayHeap = new int[NUMBER + 1];


	for (int i = 0; i < NUMBER; ++i)
	{
		//生成一个小于len的随机数
		int number = rand() % NUMBER;
		for (int j = 0; j < 7; ++j)
		{
			array[j][i] = number;
		}
		arrayHeap[i + 1] = number;
	}

	timeStart = getSystemTime();
	quickSort(array[1], 0, NUMBER - 1);
	timeEnd = getSystemTime();
	timeUse = timeEnd - timeStart;
	cout << "quickSort  耗时:" << timeUse << "ms" << endl;;

	timeStart = getSystemTime();
	insertSort(array[4], NUMBER);
	timeEnd = getSystemTime();
	timeUse = timeEnd - timeStart;
	cout << "insertSort     耗时:" << timeUse << "ms" << endl;;


	delete[]array;
	delete arrayHeap;

}

/*总结：
b.对于n>1的n元素数组，不存在插入排序比快速排序更快的情形。
但是对于小数组，快速排序比插入排序慢。因此在设计排序的时候可以考虑通过判断长度来切换排序算法。
*/

