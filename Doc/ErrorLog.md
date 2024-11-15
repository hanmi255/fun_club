**1.在窗口未实现而使用导航指向**

解决方法：实现窗口内容



**2.CMake编译找不到路径**（更新VS后产生）

```
  C:/Program Files/Microsoft Visual Studio/2022/Preview/VC/Tools/MSVC/14.42.34321/bin/HostX64/x64/cl.exe is not a full path to an existing compiler tool. Tell CMake where to find the compiler by setting either the environment variable "CXX" or the CMake cache entry CMAKE_CXX_COMPILER to the full path to the compiler, or to the compiler name if it is in the PATH.
```

解决方法：将以下路径添加到Path环境变量

```
C:\Program Files\Microsoft Visual Studio\2022\Preview\VC\Tools\MSVC\14.42.34430\bin\Hostx64\x64
```



**3.QMediaPlayer 无法正常播放**
      解决方法：在CMakeLists中引入MultimediaWidgets

```c++
#include <QAudioOutput>

player->setAudioOutput(audiooutput);
        player->setSource(QUrl(url));
        player->play();
```

