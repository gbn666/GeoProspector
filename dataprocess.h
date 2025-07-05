#ifndef DATAPROCESS_H
#define DATAPROCESS_H


#include <fcntl.h>     // open(), O_RDWR 等宏
#include <unistd.h>    // read(), close() 等

// 定义 ProcessMode 枚举
enum ProcessMode {
    BroadGas,
    Ultrasonic,
    LightLevel,
    TempHumidity,
    LEDBuzzer
};
//用来加载设备驱动，并打开/dev/*
//获取数据并显示在相应的qlabel或供计算使用
int DataProcess(ProcessMode mode);



//根据广谱气体的返回数据调用LED蜂鸣器进行警告
void WarningGas(int gas);


//根据超声波的数据设定距离警告
void WarningDistance(float distance);

//微弱光源确定

//

#endif // DATAPROCESS_H
