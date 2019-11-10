#ifndef SIMPLECONFIGFILE_H
#define SIMPLECONFIGFILE_H

#include <map>

#include "abstractconfigfile.h"
#include "configdata.h"


class SimpleConfigFile : public AbstractConfigFile
{
public:
    SimpleConfigFile();
    ~SimpleConfigFile();

    static SimpleConfigFile *getConfigFileObject()
    {
        static SimpleConfigFile simpleConfigFile;
        return &simpleConfigFile;
    }

    /* #brief   获取配置信息
     * #note    继承自AbstractConfigFile类
     * #param   result :        获取的配置信息
     *          defaultValue :  设置默认的配置信息，用于配置信息中没有该字段时
     *          key :           字段值
     *          groupName :     组名，只有在分组模式中使用
     * #retval  None
     */
    void getConfigData(std::string &result, const std::string &defaultValue,
                       const std::string &key, const std::string &groupName = "");

    /* #brief   设置配置信息
     * #note    继承自AbstractConfigFile类
     * #param   value :     配置信息
     *          key :       字段
     *          groupName : 组名，只有在分组模式中使用
     * #retval  None
     */
    void setConfigData(const std::string &value, const std::string &key,
                       const std::string &groupName = "");

    /* #brief   将配置信息打印出来
     * #note    继承自AbstractConfigFile类
     * #param   None
     * #retval  None
     */
    void dump();

private:
    /* #brief   从配置文件中加载配置信息
     * #note    继承自AbstractConfigFile类
     * #param   None
     * #retval  加载成功返回true，失败返回false
     */
    bool loadConfigFile();
    /* #brief   将配置信息写入配置文件
     * #note    继承自AbstractConfigFile类
     * #param   None
     * #retval  写入成功返回true，失败返回false
     */
    bool writeConfigFile();

    /* #brief   读出配置信息
     * #note    继承自AbstractConfigFile类
     * #param   None
     * #retval  None
     */
    void readConfigData();
    /* #brief   写入配置信息
     * #note    继承自AbstractConfigFile类
     * #param   None
     * #retval  None
     */
    void writeConfigData();

    /* #brief   将从配置文件中加载出来的一行数据进行解析
     * #note    继承自AbstractConfigFile类
     * #param   lineData :      从配置文件中读取的一行信息
     *          key :           字段
     *          value :         配置信息
     * #retval  解析成功，返回true, 否则false
     */
    bool parseData(std::string &lineData, std::string &key, std::string &value);



private:
    std::map<std::string, std::string> m_mapConfigInfo;         //存放配置信息键值对
    ConfigData m_configData;                                    //存放配置信息
};

#endif // SIMPLECONFIGFILE_H
