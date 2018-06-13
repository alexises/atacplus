#include "ServerConfigSection.h"

ServerConfigSection::ServerConfigSection() : ConfigSection("server")
{
    this->setAttr("listen", "", true);
    this->setAttr("port", "49" , true);
}
