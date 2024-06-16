#include <iostream>
#include "mysql/mysqlConn.h"
#include "connectionPool.h"
#include <chrono>
#include <thread>
using namespace std;


void op1(int begin, int end)
{
    for (int i = begin; i <= end; ++i)
    {
        MysqlConn conn;
        conn.connect("127.0.0.1", "root", "123456", "testdb", 3306);
        string sql = "";
        sql += "insert into person values (" + to_string(i) + ", 11, 'man', 'fws');";
        conn.update(sql);
    }
}

void op2(ConnectionPool* pool, int begin, int end)
{
    for (int i = begin; i <= end; ++i)
    {
        shared_ptr<MysqlConn> ptr = pool->getConnection();
        string sql = "";
        sql += "insert into person values (" + to_string(i) + ", 11, 'man', 'fws');";
        ptr.get()->update(sql);
    }
}

void test1()
{
    ConnectionPool* pool = ConnectionPool::getConnectionPool();
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
#if 0
    op1(1, 200); //30892
#else
    op2(pool, 1, 200); //27427
#endif
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto len = end - begin;
    cout << len.count() / 1000000;
}

void test2()
{
    ConnectionPool* pool = ConnectionPool::getConnectionPool();
    MysqlConn conn;
    conn.connect("127.0.0.1", "root", "123456", "testdb", 3306);
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

#if 0 //10318
    thread t1(op1, 1, 50);
    thread t2(op1, 51, 100);
    thread t3(op1, 101, 150);
    thread t4(op1, 151, 200);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
#else
    thread t1(op2, pool, 1, 50);
    thread t2(op2, pool, 51, 100);
    thread t3(op2, pool, 101, 150);
    thread t4(op2, pool, 151, 200);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
#endif

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    auto len = end - begin;
    cout << len.count() / 1000000;
}

int main()
{
    // test1();
    test2();
    return 0;
}