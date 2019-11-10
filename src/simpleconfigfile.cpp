#include "simpleconfigfile.h"

#include <iostream>
#include <string>
#include <fstream>

SimpleConfigFile::SimpleConfigFile()
{
}
SimpleConfigFile::~SimpleConfigFile()
{
}

void SimpleConfigFile::getConfigData(std::string &result, const std::string &defaultValue,
                                     const std::string &key, const std::string &groupName)
{
    std::string temp = groupName;

    if (key.empty())
    {
        std::cout << "getConfigData error : key is empty!\n" << std::endl;
        return;
    }

    if (m_mapConfigInfo.count(key) > 0)
    {
        result = m_mapConfigInfo[key];
        return;
    }

    result = defaultValue;
    return;

}

void SimpleConfigFile::setConfigData(const std::string &value, const std::string &key,
                                     const std::string &groupName)
{
    std::string temp = groupName;

    if (key.empty())
    {
        std::cout << "getConfigData error : key is empty!\n" << std::endl;
        return;
    }

    if (m_mapConfigInfo.count(key) > 0)
    {
        m_mapConfigInfo[key] = value;
        return ;
    }

    m_mapConfigInfo.insert(std::pair<std::string, std::string>(key, value));

    writeConfigFile();

    return ;
}

bool SimpleConfigFile::loadConfigFile()
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

    std::string lineData;
    getline(inFile, lineData);

    while (!lineData.empty())
    {
        std::string key;
        std::string value;

        if (!parseData(lineData, key, value))
        {
            std::cout << "class ConfigFile, Function loadConfigFile parse data \' "
                      << lineData << " \' error" << std::endl;
//            return false;
        }

        m_mapConfigInfo.insert(std::pair<std::string, std::string>(key, value));

        getline(inFile, lineData);
    }

    inFile.close();

    return true;
}

bool SimpleConfigFile::writeConfigFile()
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

    std::map<std::string, std::string>::iterator it = m_mapConfigInfo.begin();
    while (it != m_mapConfigInfo.end())
    {
        outFile << (*it).first << "=" << (*it).second << std::endl;
        it++;
    }

    return true;
}

void SimpleConfigFile::readConfigData()
{
    std::string result("");

#if SIMPLE_TEST
    getConfigData(result, defaultKey1, strKey1);
    m_configData.setKey1(result);
    getConfigData(result, defaultKey2, strKey2);
    m_configData.setKey2(result);
    getConfigData(result, defaultKey3, strKey3);
    m_configData.setKey3(result);
#endif

}

void SimpleConfigFile::writeConfigData()
{
    m_mapConfigInfo.clear();

#if SIMPLE_TEST
    setConfigData(std::to_string( m_configData.getKey1() ), strKey1);
    setConfigData(m_configData.getKey2(), strKey2);
    setConfigData(std::to_string( m_configData.getKey3() ) , strKey3);
#endif

}

bool SimpleConfigFile::parseData(std::string &lineData, std::string &key, std::string &value)
{
    if (lineData.empty())
    {
        std::cout << "class ConfigFile, function parseData() Data is null" << std::endl;
        return false;
    }

    size_t index = lineData.find("=");

    if (lineData.npos == index)
    {
        std::cout << "class SimpleConfigFile, function parseData() Data error" << std::endl;
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

void SimpleConfigFile::dump()
{
    std::cout << "Config map data : " << m_mapConfigInfo.size() << std::endl;

    std::map<std::string, std::string>::iterator it = m_mapConfigInfo.begin();

    while (it != m_mapConfigInfo.end())
    {
        std::cout << (*it).first << "=" << (*it).second << std::endl;
        it++;
    }

    std::cout << "-----------------------------" << std::endl;
}
