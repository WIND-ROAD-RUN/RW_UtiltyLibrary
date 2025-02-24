# 使用官方的 MySQL 镜像作为基础镜像
FROM mysql:latest

# 设置环境变量
ENV MYSQL_ROOT_PASSWORD=my-secret-pw
ENV MYSQL_DATABASE=mydatabase
ENV MYSQL_USER=myuser
ENV MYSQL_PASSWORD=mypassword

# 复制初始化 SQL 脚本
COPY init.sql /docker-entrypoint-initdb.d/

# 暴露 MySQL 端口
EXPOSE 3306