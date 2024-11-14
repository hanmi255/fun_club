**1.在窗口未实现而使用导航指向**

![4afc04512bcbdd4442147abe0a10fab9](C:\Users\asus\Documents\Tencent Files\1935495445\nt_qq\nt_data\Pic\2024-10\Ori\4afc04512bcbdd4442147abe0a10fab9.png)

解决方法：实现窗口内容



**2.CMake编译找不到路径**（更新VS后产生）

```
  C:/Program Files/Microsoft Visual Studio/2022/Preview/VC/Tools/MSVC/14.42.34321/bin/HostX64/x64/cl.exe is not a full path to an existing compiler tool. Tell CMake where to find the compiler by setting either the environment variable "CXX" or the CMake cache entry CMAKE_CXX_COMPILER to the full path to the compiler, or to the compiler name if it is in the PATH.
```

解决方法：将以下路径添加到Path环境变量

```
C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Tools\MSVC\14.42.34430\bin\Hostx64\x64
```



3.**INVALID_CLIENT: Invalid redirect URI**[使用Spotify的API时]

解决方法：将**Redirect URIs**改为如下形式。port可更改

```
http://localhost:8000
```



