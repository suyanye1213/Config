#ifndef CONFIGFILEFACTORY_H
#define CONFIGFILEFACTORY_H

#include "abstractconfigfile.h"

class ConfigFileFactory
{
public:
    ConfigFileFactory();
    ~ConfigFileFactory();

    AbstractConfigFile *getConfigObject(AbstractConfigFile::ConfigType configType);

private:
    AbstractConfigFile *m_configObject;
};

#endif // CONFIGFILEFACTORY_H
