# csgiao-stm32-fw

真人CS平台的stm32主控板代码

整个项目的开源文档在立创开源平台，网址：待补充

目录结构参考了稚晖君的项目，基于stm32CubeMx+Clion+Hal库

你可以使用Clion或Stm32CubeIDE打开这个项目，无法使用keil

程序入口会从Core/Src/main.c 跳转到 UserApp/Main.c


Bsp文件夹存储和硬件驱动有关信息，包括：
- interface_use：手机app进行usb通信的接口协议
- pwm：pwm接口函数
- retarget_usb：usb printf重定向相关代码


Ctrl文件夹存储一些顶层，包括：
- MultiTimer：软件定时器框架代码
- multi_button：按键驱动框架代码
- menu：各种按键和软件定时器的回调函数
- player：最顶层的关于枪械系统的状态机和顶层逻辑，数据记录。