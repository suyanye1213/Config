#ifndef ABSTRACTCONFIGFILE_H
#define ABSTRACTCONFIGFILE_H

#include <string>
#include "configdata.h"

class AbstractConfigFile
{
public:

    AbstractConfigFile();
    virtual ~AbstractConfigFile();

    enum ConfigType
    {
        SIMPLE_CONFIG = 0,
        GROUP_CONFIG,
    };

//    static AbstractConfigFile getConfigFileObject()
//    {
//        AbstractConfigFile abstractConfigFile;
//        return abstractConfigFile;
//    }

    /* #brief   设置配置文件的路径及文件名
     * #note    None
     * #param   fileName :  传入   配置文件的路径及文件名
     * #retval  None
     */
    void setFileName(const std::string &fileName);

    /* #brief   获取配置文件的路径及文件名
     * #note    None
     * #param   None
     * #retval  返回配置文件的路径及文件名
     */
    const std::string &getFileName();

    /* #brief   初始化ConfigFile实例
     * #note    在初始化前需要先调用setFileName函数
     * #param   None
     * #retval  初始化成功返回true，否则返回false
     */
    bool initConfigFileObject();

    /* #brief   获取配置信息
     * #note    纯虚函数
     * #param   result :        获取的配置信息
     *          defaultValue :  设置默认的配置信息，用于配置信息中没有该字段时
     *          key :           字段值
     *          groupName :     组名，只有在分组模式中使用
     * #retval  None
     */
    virtual void getConfigData(std::string &result, const std::string &defaultValue,
                               const std::string &key, const std::string &groupName) = 0;

    /* #brief   设置配置信息
     * #note    纯虚函数
     * #param   value :     配置信息
     *          key :       字段
     *          groupName : 组名，只有在分组模式中使用
     * #retval  None
     */
    virtual void setConfigData(const std::string &value, const std::string &key,
                               const std::string &groupName) = 0;

    /* #brief   将配置信息打印出来
     * #note    纯虚函数
     * #param   None
     * #retval  None
     */
    virtual void dump() = 0;

private:
     /* #brief   从配置文件中加载配置信息
     * #note    纯虚函数
     * #param   None
     * #retval  加载成功返回true，失败返回false
     */
    virtual bool loadConfigFile() = 0;
    /* #brief   将配置信息写入配置文件
     * #note    纯虚函数
     * #param   None
     * #retval  写入成功返回true，失败返回false
     */
    virtual bool writeConfigFile() = 0;

    /* #brief   读出配置信息
     * #note    纯虚函数
     * #param   None
     * #retval  None
     */
    virtual void readConfigData() = 0;
    /* #brief   写入配置信息
     * #note    纯虚函数
     * #param   None
     * #retval  None
     */
    virtual void writeConfigData() = 0;

    /* #brief   将从配置文件中加载出来的一行数据进行解析
     * #note    纯虚函数
     * #param   lineData :      从配置文件中读取的一行信息
     *          key :           解析出来的字段名
     *          value :         解析出来的配置信息
     * #retval  解析成功，返回true, 否则false
     */
    virtual bool parseData(std::string &lineData, std::string &key, std::string &value) = 0;

    /* #brief   将从配置文件中加载出来的一行分组信息解析
     * #note    纯虚函数，只有在分组配置信息中使用
     * #param   lineData :      从配置文件中读取的一行分组信息
     *          groupName :     解析出来的组名
     * #retval  解析成功，返回true, 否则false
     */
    virtual bool parseGroup(std::string &lineData, std::string &groupName)
    {
        std::string temp = lineData;
        temp = groupName;
        return false;
    }


private:
    std::string m_fileName;     //保留配置文件的路径及文件名
    ConfigData m_configData;    //保存配置文件，用于系统使用
};

#endif // ABSTRACTCONFIGFILE_H
