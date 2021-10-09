# 学习YAML的使用

## 目录

- [目录](##目录)
- [编译信息](##编译信息)
- [YAML在Windows上使用(编译)](##YAML在Windows上使用(编译))
- [YAML在Linux上使用（编译）](##YAML在Linux上使用（编译）)
- [C++读写YAML文件](##C++读写YAML文件)

## 编译信息

作者：xzf

创建时间：2021/10/09

更新时间：2021/10/09

## 说明

本文主要说明，简单学习 YAML 的用法。

验证通过的环境：

- Linux: `Linux xzf-linux 5.11.0-37-generic #41~20.04.2-Ubuntu SMP Fri Sep 24 09:06:38 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux`
- Window: `Microsoft Windows [版本 10.0.19042.1165]`
- [yaml-cpp 版本](https://github.com/jbeder/yaml-cpp)
- cmake 版本：3.20.5

## YAML在Windows上使用(编译)

事前准备:

- 安装 [cmake](https://cmake.org/) 
- 下载[yaml-cpp源码](https://github.com/jbeder/yaml-cpp)

编译：

1. 打开cmake

   ![](https://github.com/chemoontheshy/learnYAML/blob/master/img/yaml_1.png)

2. 选择路径：

   - Where is the source code：
   - Where to build the binaries：
   - 其中 **build** 为自己新建的文件夹，生成的中间产物都在这个文件。

   ![](img\yaml_2.png)

3. 点击 **“Configure”** 会弹出选择的vs版本和系统。

   ![](img\yaml_5.png)

4. 完成上一步后会出现配置文件。如果要生成动态库需要在下图的框选的地方打勾✔，默认只生成静态库。

   ![](img\yaml_6.png)

5. 选择好后，再次点击 **“Configure”**。

6. 点击 **“Generate”** ，会有生成的工程文件。

7. 进入刚刚选择的 **build** 文件夹，点击 `YAML_CPP.sln`。

8. 右键ALL_BUILD，点击生成，Debug和release版本都点击。

9. 在 **“输出”** 的窗口查看可以知道生成的静态库或者动态库的位置。

   ![](img\yaml_9.png)

10. 头文件可以在源文件下面的 **“include”**文件里复制。



## YAML在Linux上使用（编译）

这个比较简单跟着官方步骤走就好。

```sh
git clonehttps://github.com/jbeder/yaml-cpp.git
# ...
mkdir build
cd build
# (如果需要生成动态库需要增加 -DYAML_BUILD_SHARED_LIBS=ON)
# camke -DYAML_BUILD_SHARED_LIBS=ON ..
camke ..
```

需要注意的是生成动态库的时候，执行程序的时候，需要的是带版本的so。



## C++读写YAML文件

配置文件 `config.yaml`:

```yaml
name: taka
sex: male
age: 18
delete: delete
```

`main.cpp`：

```cpp
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
	//read
	YAML::Node config = YAML::LoadFile("config.yaml");
	cout << "name: " << config["name"].as<string>() << endl;
	cout << "sex: " << config["sex"].as<string>() << endl;
	cout << "age: " << config["age"].as<int>() << endl;
	cout << "delete: " << config["delete"].as<string>() << endl;

	std::ofstream fout("config.yaml");

	//add
	config["add"] = "add";

	//change
	config["age"] = 25;

	//delete
	config.remove("delete");

	//write
	fout << config << endl;
	fout.close();
	return 0;
}
```

