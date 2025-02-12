# 使用 Ubuntu 作为基础镜像
FROM ubuntu:20.04

# 设置非交互模式
ENV DEBIAN_FRONTEND=noninteractive

# 更新包列表并安装必要的软件包
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    ninja-build \
    git \
    wget \
    unzip \
    libgtest-dev \
    curl \
    zip \
    ca-certificates \
    apt-transport-https \
    pkg-config \
    autoconf \
    automake \
    libtool \
    python3 \
    && rm -rf /var/lib/apt/lists/*

# 安装 CMake 3.31 版本
RUN wget https://github.com/Kitware/CMake/releases/download/v3.31.0/cmake-3.31.0-linux-x86_64.sh && \
    chmod +x cmake-3.31.0-linux-x86_64.sh && \
    ./cmake-3.31.0-linux-x86_64.sh --skip-license --prefix=/usr/local && \
    rm cmake-3.31.0-linux-x86_64.sh

# 安装 vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git /opt/vcpkg && \
    /opt/vcpkg/bootstrap-vcpkg.sh

# 将 vcpkg 添加到 PATH 并设置 VCPKG_ROOT 环境变量
ENV PATH="/opt/vcpkg:${PATH}"
ENV VCPKG_ROOT="/opt/vcpkg"

# 设置 GnuTLS 环境变量
ENV GIT_SSL_NO_VERIFY=1

# 设置工作目录
WORKDIR /usr/src/RW_UtiltyLibrary

# 复制项目源代码到容器中
COPY . /usr/src/RW_UtiltyLibrary

# 禁用 SSL 验证
RUN git config --global http.sslVerify false


# 安装依赖项并添加重试逻辑
#RUN for i in 1 2 3 4 5; do vcpkg install --triplet x64-linux --clean-after-build && break || sleep 10; done

# 构建项目，使用 CMakePresets.json 中的预设配置
RUN cmake --preset linux-x64-release && \
    cmake --build out/build/linux-x64-release