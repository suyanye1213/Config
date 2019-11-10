#include "abstractconfigfile.h"

#include <iostream>

using namespace std;

AbstractConfigFile::AbstractConfigFile()
{
}
AbstractConfigFile::~AbstractConfigFile()
{
}

void AbstractConfigFile::setFileName(const std::string &fileName)
{
    m_fileName = fileName;

    return;
}

const std::string &AbstractConfigFile::getFileName()
{
    return m_fileName;
}

bool AbstractConfigFile::initConfigFileObject()
{
    if (!loadConfigFile())
    {
        std::cout << "loadConfigFile \'" << m_fileName << "\' error" << std::endl;
        return false;
    }
    
    readConfigData();
    writeConfigData();

    if (!writeConfigFile())
    {
        std::cout << "writeConfigFile \'" << m_fileName << "\' error" << std::endl;
        return false;
    }

    return true;
}
