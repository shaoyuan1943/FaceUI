# FaceUI
Direct2D界面库

---
2016.02.21 12:50  
有其他事情需要处理，FaceUI暂停开发两周。

2016.03.04 21:35  
1. 修改了控件的注册方式，这样FaceUI自带的控件可以通过宏方便的控制。  
2. 将match.hpp移除FaceUI的头文件，match由FaceUI内部使用，不公开给使用者，避免使用者设置match的目录。

2016.03.14 15:16  
1. FaceUI恢复正常开发进度

2016.03.16 18:17  
1. 将WndsMgr修改为UIMgr。  
2. 移除了OnFinalMessage函数，传统Window实体只实现OnWndCreated和OnWndDestory函数，其他的消息处理留给上一层的WindowImpl实现体。

2016.03.20 02:24  
1. 更改了工程目录，添加window目录。   
2. 修改了WindowImpl的实现，将WindowImpl定义为window控件和window窗口的集合体，提供对外可重写的接口。

2016.03.20 03:13  
1. 修改了UIMgr类，剔除了多余的东西。  
2. 对WindowImpl类稍作整理。

2016.03.21 00:05  
1. 修改函数命名。  
2. 将OnWndCreated和OnWndDestory事件放回WindowImpl类中。

2016.04.18 9:10  
1. 家里最近在搞装修，时间全忙在装修的事情上了，FaceUI暂停开发，待装修完毕后会恢复开发进度。  

2016.07.07 23:54  
1. FaceUI恢复更新
