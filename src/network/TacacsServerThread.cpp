#include "TacacsServerThread.h"
#include "TacacsPacketContext.h"
#include "BufferExaustionException.h"
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
   TacacsPacketContext ctx(TacacsConnectionType::Server);
   this->sock->setBuffer(ctx.getRbuff(), ctx.getWbuff());
   int reqRbytes = 12;
   int reqWbytes = 0;
   while(1) 
   {
       LOG_MSG(debug) << "process new meessage";
       this->sock->processBytes(reqRbytes, reqWbytes);
       try 
       {
           TacacsPacketWithHeader* packet = ctx.decode();
       }
       catch (BufferExaustionException& e)
       {
            LOG_MSG(info) << "need "<< e.getSize() << " more byte for decoding";
            reqRbytes += e.getSize();
       }
   }
   return;
}
