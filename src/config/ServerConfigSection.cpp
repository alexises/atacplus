#include "ServerConfigSection.h"

ServerConfigSection::ServerConfigSection() : ConfigSection("server")
{
    this->setAttr("listen", "", true);
    this->setAttr("port", "49" , true);
    this->setAttr("logfile", "", false);
    this->setAttr("logformat", "%TimeStamp(format=\"%c\")% [%File%:%Line%] %Severity%: %Message%", false);
}
