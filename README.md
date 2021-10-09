# C++语法基础补充

目录

- 目录
- 编译信息
- 基本文件结构
- 最简单的编译
- 同时编译多个文件
- 编译静态
- 编译动态
- 引用静态库
- 引用动态库
- 混合
- 标准化
- 其他

## 编译信息

作者：xzf

创建时间：2021/10/08

更新时间：2021/10/08

## 说明

本文主要说明，基于 [cmake-example](https://github.com/ttroy50/cmake-examples) 的简单学习 cmake 的用法。在Linux系统上使用cmake编译c++，

环境：`Linux xzf-linux 5.11.0-37-generic #41~20.04.2-Ubuntu SMP Fri Sep 24 09:06:38 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux`



## 基本文件结构

- project (项目名称)
  - lib（库生成的路径）
  - bin (二进制可执行文件的路径)
  - build (执行文件，中间产物，makefile)
  - include (.h)(本文为了兼容，不采用分开，只会在引用第三方库的时候使用)
  - src (h.,*.cpp 文件)
  - 3rd (其他文件或者引用库)
  - CMakeLists.txt (cmake的配置文件)
- 执行编译命令
  - cd build
  - camke ..
  - make



## 最简单的编译

### 1. 结构

```sh
.
├── bin
├── build
├── CMakeLists.txt
└── src
    └── main.cpp

```



### 2. CMakeLists.txt

```cmake
#Set the munimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

#set the project name
project (hello_cmake)

SET(SOURCES src/main.cpp)

#Add an executalbe
add_executable(hello_cmake ${SOURCES})

#Output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
```



### 3. src

**main.cpp**

```cpp
#include <iostream>
  
int main()
{
        std::cout<< "Hello Cmake!"<<std::endl;
        return 0;
}

```



## 多文件的编译

### 1. 结构

```sh
.
├── bin
├── build
├── CMakeLists.txt
└── src
    ├── Hello.cpp
    ├── Hello.h
    └── main.cpp

```



### 2. CMakeLists.txt

```cmake
# Set the munimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(hello_headers)

# Output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin )

# Add .cpp
SET(SOURCES
        src/Hello.cpp
        src/main.cpp)

#Add an executalble
add_executable(hello_headers ${SOURCES})

#include .h
target_include_directories(hello_headers
                PRIVATE
                       ${PROJECT_SOURCE_DIR}/src
)


```



### 3. main.cpp

**Hello.h**

```cpp
#ifndef __HELLO_H__
#define __HELLO_H__

class Hello
{
public:
	void print();

};

#endif
```

**Hello.cpp**

```cpp
#include <iostream>
  
#include "Hello.h"

void Hello::print()
{
        std::cout<<"hello Headers!"<<std::endl;
}

```

**main.cpp**

```cpp
#include <iostream>
  
int main()
{
        std::cout<< "Hello Cmake!"<<std::endl;
        return 0;
}

```



## 编译静态库

### 1. 结构

```sh
.
├── bin
├── build
├── CMakeLists.txt
└── src
    ├── Hello.cpp
    ├── Hello.h
    └── main.cpp

```



### 2. CMakeLists.txt

```cmake
# Set the munimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(hello)

# Output path
# Shared
# SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/hello/lib )
# static
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/hello/lib )

# Add library
add_library(hello STATIC
        src/Hello.cpp
)

#include .h
target_include_directories(hello
        PUBLIC
                ${PROJECT_SOURCE_DIR}/include
)

#Copy include to the output path
file(COPY ${PROJECT_SOURCE_DIR}/include DESTINATION  ${PROJECT_SOURCE_DIR}/hello/)

```



## 编译动态库

基本和静态库编译一样，只是CMakeLists.txt的不同

### 1. 结构

```sh
.
├── bin
├── build
├── CMakeLists.txt
└── src
    ├── Hello.cpp
    ├── Hello.h
    └── main.cpp
```



### 2. CMakeLists.txt

```cmake
# Set the munimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(hello)

# Output path
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/hello/lib )

# Add library
add_library(hello SHARED
        src/Hello.cpp
)

#include .h
target_include_directories(hello
        PUBLIC
                ${PROJECT_SOURCE_DIR}/include
)

#Copy include to the output path
file(COPY ${PROJECT_SOURCE_DIR}/include DESTINATION  ${PROJECT_SOURCE_DIR}/hello/)

```





## 调用静态库

### 1. 结构

```sh
.
├── 3rd
│   ├── include
│   │   └── Hello.h
│   └── lib
│       └── libhello.a
├── bin
├── build
├── CMakeLists.txt
└── src
    └── main.cpp

```



### 2. CMakeLists.txt

`特别注意：引入头文件和库要在生成exe之前`

```cmake
# Set the munimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(hello_static)

# Output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET(3RD ${PROJECT_SOURCE_DIR}/3rd)

# link include
INCLUDE_DIRECTORIES(${3RD}/include)

# link lib
LINK_DIRECTORIES(${3RD}/lib)


# Add an executable with the above sources
add_executable(hello_static
        src/main.cpp
)

target_link_libraries(hello_static hello)

```



## 调用静态库

`调用动态基本和静态库是一样的`



## 混合编译

### 1. 结构

```sh
.
├── 3rd
│   ├── include
│   │   └── Hello.h
│   └── lib
│       └── libhello.so
├── bin
├── build
├── CMakeLists.txt
└── src
    ├── cmix.cpp
    ├── cmix.h
    └── main.cpp

```



### 2. CMakeLists.txt

`特别注意：引入头文件和库要在生成exe之前`

```cmake
# Set the munimum version of CMake that can be used
cmake_minimum_required(VERSION 3.5)

# Set the project name
project(hello_cmix)

# Output path
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

SET(3RD ${PROJECT_SOURCE_DIR}/3rd)

# link include
INCLUDE_DIRECTORIES(${3RD}/include)

# link lib
LINK_DIRECTORIES(${3RD}/lib)


# Add an executable with the above sources
add_executable(hello_cmix
        src/main.cpp
        src/cmix.cpp
)

#include .h
target_include_directories(hello_cmix
        PRIVATE
                ${PROJECT_SOURCE_DIR}/src
)

#link the shared
target_link_libraries(hello_cmix hello)


```



## 标准化

待写



## 其他

待写
