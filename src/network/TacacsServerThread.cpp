#include "TacacsServerThread.h"
#include "log.h"

TacacsServerThread::TacacsServerThread(BufferedTcpSocket* sock)
{
   this->sock = sock;
}

TacacsServerThread::~TacacsServerThread()
{
   delete this->sock;
}

void TacacsServerThread::operator()()
{
   LOG_MSG(debug) << "start new session ";
   while(1) {}
   return;
}
