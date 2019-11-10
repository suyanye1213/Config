#include "configfilefactory.h"

#include "simpleconfigfile.h"
#include "groupconfigfile.h"

ConfigFileFactory::ConfigFileFactory()
{
    m_configObject = nullptr;
}

ConfigFileFactory::~ConfigFileFactory()
{
    //
//    delete m_configObject;
}

AbstractConfigFile *ConfigFileFactory::getConfigObject(AbstractConfigFile::ConfigType configType)
{
    switch (configType)
    {
        case AbstractConfigFile::ConfigType::SIMPLE_CONFIG :
            m_configObject = dynamic_cast<AbstractConfigFile *>(SimpleConfigFile::getConfigFileObject());
        break;

        case AbstractConfigFile::ConfigType::GROUP_CONFIG :
            m_configObject = dynamic_cast<AbstractConfigFile *>(GroupConfigFile::getConfigFileObject());
        break;
    }

    return m_configObject;
}
