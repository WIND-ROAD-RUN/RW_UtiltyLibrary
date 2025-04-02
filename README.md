# RW_UtiltyLibrary

## 项目简介

RW_UtiltyLibrary 是一个从旧有的剔废系统重构而来的项目，旨在提供一套通用的库和工具函数，支持工业剔废系统的开发和部署。项目使用 CMake 进行构建，并计划通过 vcpkg 管理依赖，后期将容器化部署。

## 目录结构

- ./cmake 构建项目使用的CMake功能函数
- ./example 项目的使用案例（后期将会补充，目前只是添加了文件夹)
- ./RW  通用库目录
- ./ RWScanner   工业剔废系统的组件目录
- ./ThirdLibrary 第三方库目录


## 构建项目

本项目使用 CMake 进行构建，以下是构建步骤：

1. 安装必要的工具和依赖：
   - CMake 3.27 或更高版本
   - Ninja
   - vcpkg（用于管理第三方库）

2. 克隆项目到本地：
 ```
 git clone https://github.com/WIND-ROAD-RUN/RW_UtiltyLibrary.git
 ```
3. 目前使用Visual Studio 2022 打开项目将会对项目自动进行配置


其他构建方式待补充