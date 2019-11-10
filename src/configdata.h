/**
 ** 版权说明：
 **     该程序是由苏彦业在2019年10月19日编写，并于2019年10月19日修改；
 **     该程序并不保证没有任何BUG，使用中出现的任何问题，本人不承担责任；
 **     该程序在git上共享，欢迎大家一起修改并优化
 **
 ** 使用说明：
 **     在使用前需要在头文件第23行添加配置文件字段名，在头文件第26行添加配置文件字段默认值，
 ** 并添加配置信息的set、get方法。
 **/

#ifndef CONFIGDATA_H
#define CONFIGDATA_H

/*
 * ConfigData类用来存放配置信息
 */

#include <string>

#define SIMPLE_TEST 1
#define GROUP_TEST 0

#if !(SIMPLE_TEST || GROUP_TEST)

class ConfigData
{
public:

    ConfigData();
};

#endif

#if SIMPLE_TEST

//配置信息字段名
#define strKey1         "key1"
#define strKey2         "key2"
#define strKey3         "key3"

//配置信息默认值
#define defaultKey1       "1"
#define defaultKey2       "hello world!"
#define defaultKey3       "1.234"

class ConfigData
{
public:

    ConfigData();

    void setKey1(const std::string &key1);
    const int &getKey1();

    void setKey2(const std::string &key2);
    const std::string &getKey2();

    void setKey3(const std::string &key3);
    const double &getKey3();

private:
    int m_key1;
    std::string m_key2;
    double m_key3;
};

#endif


#if GROUP_TEST

//配置组名
#define strGroup1               "group1"
#define strGroup2               "group2"
#define strGroup3               "group3"

//配置信息字段名
#define strGroup1Key1           "group1key1"
#define strGroup1Key2           "group1key2"
#define strGroup1Key3           "group1key3"
#define strGroup2Key1           "group2key1"
#define strGroup2Key2           "group2key2"
#define strGroup3Key1           "group3key1"

//配置信息默认值
#define defaultGroup1Key1       "1"
#define defaultGroup1Key2       "hello world!"
#define defaultGroup1Key3       "1.234"
#define defaultGroup2Key1       "0.123"
#define defaultGroup2Key2       "100"
#define defaultGroup3Key1       "0"

class ConfigData
{
public:

    ConfigData();

    void setGroup1Key1(const std::string &group1Key1);
    const int &getGroup1Key1();

    void setGroup1Key2(const std::string &group1Key2);
    const std::string &getGroup1Key2();

    void setGroup1Key3(const std::string &group1Key3);
    const double &getGroup1Key3();

    void setGroup2Key1(const std::string &group2Key1);
    const float &getGroup2Key1();

    void setGroup2Key2(const std::string &group2Key2);
    const short &getGroup2Key2();

    void setGroup3Key1(const std::string &group3Key1);
    const bool &getGroup3Key1();

private:
    int m_group1Key1;
    std::string m_group1Key2;
    double m_group1Key3;
    float m_group2Key1;
    short m_group2Key2;
    bool m_group3Key1;

};

#endif

#endif // CONFIGDATA_H
