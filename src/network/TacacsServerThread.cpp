#include "TacacsServerThread.h"

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
   return;
}
