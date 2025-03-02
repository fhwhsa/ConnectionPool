/**
 * 数据库API封装
 */

#ifndef _MYSQLCONN_H_
#define _MYSQLCONN_H_

#include <mysql/mysql.h>
#include <string>
#include <unordered_map>

class MysqlConn
{
public:
    /**
     * 描述：初始化数据库连接
     */
    MysqlConn();

    /**
     * 描述：释放数据库连接
     */
    ~MysqlConn();

    /**
     * 描述：连接数据库
     * 返回值：执行成功返回true
     */
    bool connect(std::string host, std::string user, std::string passwd, std::string dbname, unsigned int port = 0);

    /**
     * 描述：更新数据库
     * 返回值：执行成功返回true
     */
    bool update(std::string sql);

    /**
     * 描述：查询数据库
     * 返回值：执行成功返回true
     */
    bool query(std::string sql);

    /**
     * 取出结果集下一条结果
     * 返回值：结果集有下一条结果返回true
     */
    bool next();

    /**
     * 描述：检查结果集是否为空
     * 返回值：结果集不为空返回true
     */
    bool hasRes();

    /**
     * 描述：获取列数
     * 返回值：列数
     */
    unsigned int getColNum();

    /**
     * 获取结果中的字段值
     * 参数：
     *      （1）index 根据下标取值
     *      （2）item 根据字段名取值
     * 异常：下标越界或没有字段名抛出异常
     * 返回值：对应字段值
     */
    std::string value(int index);
    std::string value(std::string item);

    /**
     * 描述：开启事务
     * 返回值：执行成功返回true
     */
    bool start_transaction();

    /**
     * 描述：提交事务
     * 返回值：执行成功返回true
     */
    bool commit();

    /**
     * 描述：事务回滚
     * 返回值：执行成功返回true
     */
    bool rollback();


private:
    MYSQL *mysqlconn = nullptr;

    MYSQL_RES *mysqlres = nullptr;                      /*结果集*/
    MYSQL_FIELD *mysqlfield = nullptr;                  /*结果集列的字段定义*/
    unsigned int num = 0;                               /*结果集列数*/
    unsigned long *len = nullptr;                       /*当前行各值长度*/
    MYSQL_ROW mysqlrow = nullptr;                       /*当前行*/
    std::unordered_map<std::string, int> stoindex;      /*字段值对应下标*/
    void initQuery();                                   /*进行查询操作前初始化数据*/
};

#endif