#include "groupconfigfile.h"

#include <iostream>
#include <string>
#include <fstream>

GroupConfigFile::GroupConfigFile()
{
}

GroupConfigFile::~GroupConfigFile()
{
}

void GroupConfigFile::getConfigData(std::string &result, const std::string &defaultValue,
                                    const std::string &key, const std::string &groupName)
{
    if (groupName.empty())
    {
        std::cout << "getConfigData error : groupName is empty!\n" << std::endl;
        return;
    }

    if (key.empty())
    {
        std::cout << "getConfigData error : key is empty!\n" << std::endl;
        return;
    }

    if (m_mapGroupInfo.count(groupName) > 0)
    {
        if (m_mapGroupInfo[groupName].count(key) > 0)
        {
            result = m_mapGroupInfo[groupName][key];
            return;
        }
    }

    result = defaultValue;
    return;

}

void GroupConfigFile::setConfigData(const std::string &value, const std::string &key,
                                     const std::string &groupName)
{
    if (groupName.empty())
    {
        std::cout << "getConfigData error : groupName is empty!\n" << std::endl;
        return ;
    }

    if (key.empty())
    {
        std::cout << "getConfigData error : key is empty!\n" << std::endl;
        return ;
    }

    if (m_mapGroupInfo.count(groupName) > 0)
    {
        if (m_mapGroupInfo[groupName].count(key) > 0)
        {
            m_mapGroupInfo[groupName][key] = value;
            return ;
        }

        m_mapGroupInfo[groupName].insert(std::pair<std::string, std::string>(key, value));
        return ;
    }

    MapConfigInfo mapConfigInfo;

    mapConfigInfo.insert(std::pair<std::string, std::string>(key, value));
    m_mapGroupInfo.insert(std::pair<std::string, MapConfigInfo>(groupName, mapConfigInfo));

    writeConfigFile();

    return ;
}

bool GroupConfigFile::loadConfigFile()
{
    std::string fileName = getFileName();
    if (fileName == "")
    {
        std::cout << "Config file name null" << std::endl;
        return false;
    }

    std::ifstream inFile;
    inFile.open(fileName, std::ios_base::in);
    if (!inFile.is_open())
    {
        std::cout << "Error open config file \'" << fileName << "\'" << std::endl;
        return false;
    }

    std::string curGroupName = std::string("");

    std::string lineData;
    getline(inFile, lineData);
    while (!lineData.empty())
    {
        std::string groupName = std::string("");
        std::string key = std::string("");
        std::string value = std::string("");

        if (!parseData(lineData, key, value) && !parseGroup(lineData, groupName))
        {
            std::cout << "class GroupConfigFile, Function loadConfigFile parse data \' "
                      << lineData << " \' error" << std::endl;
//            return false;
        }

        if (groupName != "")
        {
            curGroupName = groupName;
            MapConfigInfo mapConfigInfo;
            m_mapGroupInfo.insert(std::pair<std::string, MapConfigInfo>(curGroupName, mapConfigInfo));

            goto GET_LINE_AGAIN;
        }

        if (key != "" && curGroupName != "")
        {
            m_mapGroupInfo[curGroupName].insert(std::pair<std::string, std::string>(key, value));
        }

GET_LINE_AGAIN:
        getline(inFile, lineData);
    }

    inFile.close();

    return true;
}

bool GroupConfigFile::writeConfigFile()
{
    std::string fileName = getFileName();
    if (fileName == "")
    {
        std::cout << "Config file name null" << std::endl;
        return false;
    }

    std::ofstream outFile;
    outFile.open(fileName, std::ios_base::out | std::ios_base::trunc);
    if (!outFile.is_open())
    {
        std::cout << "Error open config file \'" << fileName << "\'" << std::endl;
        return false;
    }

    MapGroupInfo::iterator mapGroupInfoIt = m_mapGroupInfo.begin();

    while (mapGroupInfoIt != m_mapGroupInfo.end())
    {
        outFile << "[" << (*mapGroupInfoIt).first << "]" << std::endl;

        MapConfigInfo::iterator mapConfigInfoIt = (*mapGroupInfoIt).second.begin();

        while (mapConfigInfoIt != (*mapGroupInfoIt).second.end())
        {
            outFile << (*mapConfigInfoIt).first << "=" << (*mapConfigInfoIt).second << std::endl;
            mapConfigInfoIt++;
        }

        mapGroupInfoIt++;
    }

    return true;
}

void GroupConfigFile::readConfigData()
{
    std::string result("");
#if GROUP_TEST
    getConfigData(result, defaultGroup1Key1, strGroup1Key1, strGroup1);
    m_configData.setGroup1Key1(result);
    getConfigData(result, defaultGroup1Key2, strGroup1Key2, strGroup1);
    m_configData.setGroup1Key2(result);
    getConfigData(result, defaultGroup1Key3, strGroup1Key3, strGroup1);
    m_configData.setGroup1Key3(result);
    getConfigData(result, defaultGroup2Key1, strGroup2Key1, strGroup2);
    m_configData.setGroup2Key1(result);
    getConfigData(result, defaultGroup2Key2, strGroup2Key2, strGroup2);
    m_configData.setGroup2Key2(result);
    getConfigData(result, defaultGroup3Key1, strGroup3Key1, strGroup3);
    m_configData.setGroup3Key1(result);
#endif
}

void GroupConfigFile::writeConfigData()
{
    m_mapGroupInfo.clear();
#if GROUP_TEST
    setConfigData(std::to_string( m_configData.getGroup1Key1() ), strGroup1Key1, strGroup1);
    setConfigData(m_configData.getGroup1Key2(), strGroup1Key2, strGroup1);
    setConfigData(std::to_string( m_configData.getGroup1Key3() ), strGroup1Key3, strGroup1);
    setConfigData(std::to_string( m_configData.getGroup2Key1() ), strGroup2Key1, strGroup2);
    setConfigData(std::to_string( m_configData.getGroup2Key2() ), strGroup2Key2, strGroup2);

    if (m_configData.getGroup3Key1())
    {
        setConfigData("1", strGroup3Key1, strGroup3);
    }else
    {
        setConfigData("0", strGroup3Key1, strGroup3);
    }
#endif

}

bool GroupConfigFile::parseData(std::string &lineData, std::string &key, std::string &value)
{
    if (lineData.empty())
    {
        std::cout << "class ConfigFile, function parseData() Data is null" << std::endl;
        return false;
    }

    size_t index = lineData.find("=");

    if (0 >= index)
    {
        std::cout << "class ConfigFile, function parseData() Data error" << std::endl;
        return false;
    }

    char *charKey = new char[index + 1];
    size_t size = lineData.copy(charKey, index, 0);
    if (size <= 0)
    {
        std::cout << "class ConfigFile, function parseData() Key error" << std::endl;
        return false;
    }
    charKey[index] = '\0';
    key.append(charKey);
    delete [] charKey;

    char *charValue = new char[lineData.size() - index - 1 + 1];
    size = lineData.copy(charValue, lineData.size() - index - 1, index + 1);
    if (size <= 0)
    {
        std::cout << "class ConfigFile, function parseData() Value error" << std::endl;
        return false;
    }
    charValue[lineData.size() - index - 1] = '\0';
    value.append(charValue);

    delete [] charValue;

    return true;
}

bool GroupConfigFile::parseGroup(std::string &lineData, std::string &groupName)
{
    if (lineData.empty())
    {
        std::cout << "class ConfigFile, function parseData() Data is null" << std::endl;
        return false;
    }

    size_t startIndex = lineData.find("[");
    size_t endIndex = lineData.find("]");

    if (startIndex == lineData.npos || endIndex == lineData.npos)
    {
        std::cout << "class GroupConfigFile, function parseGroup() Data error" << std::endl;
        return false;
    }

    char *charGroup = new char[endIndex - startIndex + 1];
    size_t size = lineData.copy(charGroup, endIndex - startIndex, startIndex + 1);
    if (size <= 0)
    {
        std::cout << "class ConfigFile, function parseData() Key error" << std::endl;
        return false;
    }
    charGroup[endIndex - startIndex] = '\0';
    groupName.append(charGroup);
    delete [] charGroup;

    return true;
}

void GroupConfigFile::dump()
{
    std::cout << "Config group : " << m_mapGroupInfo.size() << std::endl;

    MapGroupInfo::iterator mapGroupInfoIt = m_mapGroupInfo.begin();

    while (mapGroupInfoIt != m_mapGroupInfo.end())
    {
        std::cout << "[" << (*mapGroupInfoIt).first << "]" << std::endl;

        MapConfigInfo::iterator mapConfigInfoIt = (*mapGroupInfoIt).second.begin();

        while (mapConfigInfoIt != (*mapGroupInfoIt).second.end())
        {
            std::cout << (*mapConfigInfoIt).first << "=" << (*mapConfigInfoIt).second << std::endl;
            mapConfigInfoIt++;
        }

        mapGroupInfoIt++;
    }

    std::cout << "-----------------------------" << std::endl;
}

