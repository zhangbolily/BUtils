# BUtils #
[![Build Status](https://travis-ci.com/zhangbolily/BUtils.svg?branch=dev)](https://travis-ci.com/zhangbolily/BUtils)
[![Language](https://img.shields.io/badge/language-C%2B%2B11-orange.svg)](https://isocpp.org/)
[![Platforms](https://img.shields.io/badge/platform-Linux%20%7C%20Windows-green.svg)](https://gitlab.com/zhangbolily/bthreadpack)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](https://opensource.org/licenses/MIT/)
[![codecov](https://codecov.io/gl/zhangbolily/BUtils/branch/dev/graph/badge.svg)](https://codecov.io/gl/zhangbolily/BUtils)

[English](./README.md)

Ball Chang 所有项目的基础设施。

## 主要特性
- 生成基于随机数的 UUID
- 计时器系统（精度 1 微秒）
- 定时器系统（最小精度 1 毫秒）

## 如何开始

通过以下步骤，你将获得本项目的源代码用于开发或者测试。

### 系统要求

若你想在你的平台上使用 BThreadPack，必须满足以下条件。
```
C++ 标准: c++11
构建工具: cmake make autoconf automake gcc
```

### 安装

```
$ git clone https://gitlab.com/zhangbolily/BUtils.git BUtils
$ cd BUtils
$ git submodule update --init --recursive
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make install
```

##### Demonstration build video (click to veiw)

[![Build](https://asciinema.org/a/pxITpcCQsCXepW80eHSjB5byF.svg)](https://asciinema.org/a/pxITpcCQsCXepW80eHSjB5byF)

## 运行测试程序
```
$ cd build
$ rm -rf ./*
$ cmake -DBUILD_TESTING=ON -DCODE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug ..
$ make tests
$ bin/tests
```

## 版本信息

获取可用版本，请参阅 [tags on this repository](https://gitlab.com/zhangbolily/BUtils/tags)。

## 路线图
- 在下个版本进行性能提升
- 更多示例程序
- 可传递参数给定时器事件

## 作者

* **Ball Chang** - *构建了整个项目*

## 许可证

本项目使用了 MIT 许可 - 阅读 [LICENSE.md](LICENSE.md) 获取更多信息。

## 致谢

* GitLab
* Travis-CI
