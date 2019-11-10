#include "configdata.h"

#if !(SIMPLE_TEST || GROUP_TEST)

ConfigData::ConfigData()
{
}

#endif


#if SIMPLE_TEST
ConfigData::ConfigData()
{
    m_key1 = std::stoi(defaultKey1, nullptr, 10);
    m_key2 = defaultKey2;
}

void ConfigData::setKey1(const std::string &key1)
{
    m_key1 = std::stoi(key1);
}

const int &ConfigData::getKey1()
{
    return m_key1;
}

void ConfigData::setKey2(const std::string &key2)
{
    m_key2 = key2;
}

const std::string &ConfigData::getKey2()
{
    return m_key2;
}

void ConfigData::setKey3(const std::string &key3)
{
    m_key3 = std::stod(key3);
}
const double &ConfigData::getKey3()
{
    return m_key3;
}
#endif

#if GROUP_TEST
ConfigData::ConfigData()
{
    m_group1Key1 = std::stoi(defaultGroup1Key1, nullptr, 10);
    m_group1Key2 = defaultGroup1Key2;
    m_group1Key3 = std::stod(defaultGroup1Key3, nullptr);
    m_group2Key1 = std::stof(defaultGroup2Key1, nullptr);
    m_group2Key2 = static_cast<short>( std::stoi(defaultGroup2Key2, nullptr, 10) );

    std::string temp = std::string(defaultGroup3Key1);
    m_group3Key1 = temp.compare("1") == 0 ? true : false;

}

void ConfigData::setGroup1Key1(const std::string &group1Key1)
{
    m_group1Key1 = std::stoi(group1Key1, nullptr, 10);
}
const int &ConfigData::getGroup1Key1()
{
    return m_group1Key1;
}

void ConfigData::setGroup1Key2(const std::string &group1Key2)
{
    m_group1Key2 = group1Key2;
}
const std::string &ConfigData::getGroup1Key2()
{
    return m_group1Key2;
}

void ConfigData::setGroup1Key3(const std::string &group1Key3)
{
    m_group1Key3 = std::stod(group1Key3, nullptr);
}
const double &ConfigData::getGroup1Key3()
{
    return m_group1Key3;
}

void ConfigData::setGroup2Key1(const std::string &group2Key1)
{
    m_group2Key1 = std::stof(group2Key1, nullptr);
}
const float &ConfigData::getGroup2Key1()
{
    return m_group2Key1;
}

void ConfigData::setGroup2Key2(const std::string &group2Key2)
{
    m_group2Key2 = static_cast<short>( std::stoi(group2Key2, nullptr, 10) );
}
const short &ConfigData::getGroup2Key2()
{
    return m_group2Key2;
}

void ConfigData::setGroup3Key1(const std::string &group3Key1)
{
    std::string temp = std::string(group3Key1);
    m_group3Key1 = temp.compare("1") == 0 ? true : false;
}
const bool &ConfigData::getGroup3Key1()
{
    return m_group3Key1;
}
#endif
