## 数据库连接池

### 运行demo
1. 修改config.json配置文件，json文件中各名称含义如下：<br>
    "ip": 数据库ip地址<br>
    "port": 数据库端口<br>
    "userName": 用户名<br>
    "passwd": 用户密码<br>
    "dbName": 数据库名称<br>
    "minConnSize": 最小连接个数<br>
    "maxConnSize": 最大连接个数<br>
    "maxIdleTime": 连接最大空闲时长<br>
    "maxWaitTime": 获取连接最大等待时长<br><br>
2. 建表语句：
    ```
    CREATE TABLE `person` (
    `id` int NOT NULL,
    `age` int DEFAULT NULL,
    `sex` varchar(255) DEFAULT NULL,
    `name` varchar(255) DEFAULT NULL,
    PRIMARY KEY (`id`)
    )
    ```
3. 附加开发库：<br>
    libmysqlclient-dev_8.0.37<br>
    json库 <https://github.com/open-source-parsers/jsoncpp>