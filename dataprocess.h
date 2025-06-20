#ifndef DATAPROCESS_H
#define DATAPROCESS_H
#include "dataprocessthread.h"

//用来加载设备驱动，并打开/dev/*
//获取数据并显示在相应的qlabel或供计算使用
int DataProcess(int a);


//根据广谱气体的返回数据调用LED蜂鸣器进行警告
void WarnnigGas(int gas);


//根据超声波的数据设定距离警告
void WarningDistance(float distance);

//微弱光源确定

//

#endif // DATAPROCESS_H
