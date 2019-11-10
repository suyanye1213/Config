#include <iostream>

using namespace std;

#include "configfilefactory.h"
#include "configdata.h"

int main()
{
    cout << "Hello World!" << endl;

    ConfigFileFactory configFileFactory;
    AbstractConfigFile *abstractConfigFile = nullptr;

    abstractConfigFile = configFileFactory.getConfigObject(AbstractConfigFile::ConfigType::SIMPLE_CONFIG);

    if (abstractConfigFile == nullptr)
    {
        cout << "abstractConfigFile == nullptr \n" << endl;
        return 0;
    }

    abstractConfigFile->setFileName("/home/suyanye/project/config.ini");
    abstractConfigFile->initConfigFileObject();
    abstractConfigFile->dump();

    return 0;
}
