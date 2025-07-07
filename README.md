# GeoProspector

GeoProspector 是一个以 C++ 为主、配合 Makefile 构建的地质勘探自动化与数据采集分析系统。项目集成了串口、摄像头、数据采集、可视化等多模块，适用于地质现场数据的高效采集、处理与展示，并支持与后端矿物识别框架进行网络通讯，实现自动化矿物识别与数据交互。

## 主要功能
- 串口（SerialPort）通信与设备数据采集（WzSerialPort.*）
- 摄像头图像采集与处理（camera.*、camerathread.*、imageuploader.*）
- 传感器（如 DHT11 温湿度）采集（dht11thread.*）
- 数据处理与多线程分析（dataprocess.*、dataprocessthread.*）
- 网络配置与远程通讯（netconfigwidget.*）
- 支持与后端矿物识别框架联网，实现自动化矿物识别与结果获取
- 数据可视化（visualizer.*）
- 跨平台 UI（基于 Qt .ui 文件：mainwindow.ui、visualizer.ui 等）
- Makefile 一键编译

## 目录结构
```
.
├── Makefile                     # 项目主构建文件
├── GeoProspector                # 可执行主程序
├── main.cpp                     # 主程序入口
├── mainwindow.*                 # 主界面及其实现
├── camera.* camerathread.*      # 摄像头数据采集与线程
├── dataprocess.* dataprocessthread.* # 数据处理及线程
├── dht11thread.*                # DHT11 传感器数据采集
├── WzSerialPort.*               # 串口通信实现
├── imageuploader.*              # 图像上传模块
├── netconfigwidget.*            # 网络配置与通讯
├── visualizer.*                 # 数据可视化模块
├── *.ui                         # Qt UI 界面文件
├── *.h *.cpp *.o                # 头文件、实现及目标文件
├── GeoProspector.pro            # Qt 工程文件
└── ...
```

## 编译与运行
### 依赖
- g++ / clang++ (支持 C++17)
- Qt 框架（建议 Qt5/Qt6）
- GNU Make

### 步骤
```bash
git clone https://github.com/gbn666/GeoProspector.git
cd GeoProspector
make
./GeoProspector
```
如需在 Qt Creator 中开发，可直接打开 `GeoProspector.pro`。

## 使用说明
- 启动后按界面提示进行设备连接和数据采集配置。
- 支持通过串口自动采集传感器、摄像头数据，同时进行实时处理与可视化。
- 可通过网络配置界面设置与后端矿物识别框架的通讯参数，完成图像或数据的自动上传与识别结果获取。
- 详细参数和模块说明请参考各 .cpp/.h 文件注释与 Qt 界面操作。

## 开发与贡献
欢迎提交 PR 与 Issue。  
如需扩展模块（如新类型传感器、通讯协议），请参考现有模块设计风格。

## 许可证
MIT License

---

> 由于 API 限制，以上文件结构仅展示部分内容，详情请访问 [项目源码目录](https://github.com/gbn666/GeoProspector/tree/master) 查看完整文件列表。
