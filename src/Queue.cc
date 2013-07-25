#include<iostream>
#include<math.h>
#include "Queue.h"
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include<queue>
using namespace std;
//Globalny obiekt
//SimParams SimulationParameters;





//---------------------------------------------------------------------------
///  EVENT
//---------------------------------------------------------------------------
EVENT::EVENT(USER *Owner, int tmServ, int tmWait) :
  tmWait(tmWait), tmServ(tmServ), Owner(Owner), Server(NULL), 
    isWait(0), isServ(0), isTaken(false)
{  
}

EVENT::~EVENT (void)
{
  
  if (Owner!=NULL)
    Owner->Free();
  if (Server!=NULL)
    Server->Free();
}

int EVENT::InQueue(void)
{
  if(this->Server){
    showParams();
    std::cout << "Message already in server!!!\n";
    throw;
  }

  isWait++;
  return isWait<=tmWait;
}

int EVENT::InServer(void)
{
  isServ++;
  return wasServed();
}

int EVENT::wasServed(void)
{
  return isServ>=tmServ;
}

void EVENT::showParams(void){
  bool server = Server? true:false;
  bool user = Owner? true:false;


  std::cout << std::endl
	    << "To wait:" << tmWait << std::endl
	    << "To served:" << tmServ << std::endl
	    << "Already waited: " << isWait << std::endl
	    << "Already served: "<< isServ << std::endl
	    << "Has Server: " << server << std::endl
	    << "Has Owner: " << user << std::endl
	    << "Was already taken: " << isTaken << std::endl;

}

//---------------------------------------------------------------------------
///  SERVER
//---------------------------------------------------------------------------

SERVER::SERVER(void)
{
  Event=NULL;
}


void SERVER::Free (void)
{
  Event = NULL;
}

bool SERVER::IsFree (void)
{
  return (Event==NULL);
}

void SERVER::TakeEvent (EVENT *E)
{
  Event=E;
  Event->isTaken=true;
  Event->Server = this;
  //  isTaken=true;
}

//---------------------------------------------------------------------------
///  SERVERS
//---------------------------------------------------------------------------

SERVERS::SERVERS (int Size, int Stts)
  : Size(Size)
{
  Servers = new SERVER [Size];
  ServersIterator = 0;
  stSrvUsg = Stts? new SttsTab: NULL;
  stSrvFly = Stts? new SttsLog("xySrvUsage-f.xy"): NULL;
}

SERVERS::~SERVERS (void)
{
  if (stSrvUsg) stSrvUsg->PdfToFile("xySrvUsage.xy");
  if (stSrvUsg) delete stSrvUsg;
  if (stSrvFly) delete stSrvFly;

  EVENT *Event;
  for (int i=0; i<Size; i++)
    if (!Servers[i].IsFree())
      {
	Event = Servers[i].Event;
	Event->Owner = NULL;
	Event->Server = NULL;
	if(Event){
	  delete Event;
	}else{
	  std::cout << "Dobule free in ~Servers\n";
	  throw;
	}
      }
}

/** Metoda znajduje pierwszy wolny serwer */
SERVER *SERVERS::FreeSrv (void)
{
  int i;
  SERVER *Server;

  
  Server = NULL;
  for (i=0; i<Size;i++)
    {
      if (Servers[i].IsFree())
	{
	  Server = &Servers[i];
	  break;
	}
    }
  return Server;
}

void SERVERS::Serve (void)
{
  int i, w;
  SERVER *Server;
  EVENT *Event;

  //liczba zajętych serwerów ()
  if (stSrvUsg || stSrvFly)
    {
      w = 0;
      for (i=0; i<Size;i++)
	w += !Servers[i].IsFree();
      if (stSrvFly) stSrvFly->Set(++ServersIterator, w);
      if (stSrvUsg) stSrvUsg->Inc(w);
    }

  //usuwanie obsłużonych zdarzeń
  for (i=0; i<Size;i++)
    {
      Server = &Servers[i];
      if (!Server->IsFree())
	{
	  Event = Server->Event;
	  if (Event->InServer())
	    {
	      if(Event)
		{
		  delete Event;
		}
	      else
		{
		  std::cout << "Double free in Servers::Gon\n";
		  throw;
		}
	    }
	}
    }
}

//---------------------------------------------------------------------------
///  USER
//---------------------------------------------------------------------------

USER::USER(IRandVal *rvCall, IRandVal *rvLen, IRandVal *rvWait)
  : Event(NULL), rvCall(rvCall), rvLen(rvLen), rvWait(rvWait)
{

}

EVENT *USER::Spawn (void)
{
  EVENT *newEvent = NULL;

  // Zapobiega generowaniu nowych zdarzeń podczas obsługi poprzedniego:
  if (Event!=NULL) return NULL;
  


  if (rvCall->Val())
    {
      
      int LifeSpan =0; 
      
      LifeSpan = rvLen->Val();	
      //Atot*NumSvr/TrLen/NumU
      if (LifeSpan)
	{
	 
	  ///FIXME Waiting
	  newEvent = new EVENT (this, LifeSpan,rvWait->Val());
	  Event = newEvent;
	}
    }
  return newEvent;
}
///User powinien móc posiadać więcej niż jedno zdarzenie.
void USER::Free (void)
{
  Event = NULL;
}

bool USER::IsFree (void)
{
  return Event==NULL;
}

//---------------------------------------------------------------------------
//  USERLIST
//---------------------------------------------------------------------------

USERS::USERS(SYSTEM *System, int Size,
	     IRandVal *rvCall,
	     IRandVal *rvLen,
	     IRandVal *rvWait,
	     int Stts)
  : System(System), Size(Size)
{
  //if (Stts)
  stCalLen = Stts? new SttsTab: NULL;
  stCalInt = Stts? new SttsTab: NULL;
  Users = new USER* [Size];
  for(int u=0;u<Size;u++)
    Users[u] = new USER (rvCall, rvLen, rvWait);
  cReq = cStp = 0;
}

USERS::~USERS(void)
{
  
  if (stCalLen) stCalLen->PdfToFile ("xyCallLen.xy");
  if (stCalLen) delete stCalLen;
  if (stCalInt) stCalInt->PdfToFile ("xyCallInt.xy");
  if (stCalInt) delete stCalInt;
  
  for(int u=0;u<Size;u++)
    delete Users[u];
  delete  []Users;
  
}

void USERS::GenTraffic(void)
{
  EVENT* Event;
  for(int u=0;u<Size;u++)
    {
      Event=NULL;
      Event = Users[u]->Spawn();
      if (Event)
	{
	  if (stCalLen) stCalLen->Inc(Event->tmServ);
	  System->TakeEvent(Event);	  
	  cReq++;
	}
    }

  
  if (stCalInt && ++cStp==60)
    {
      stCalInt->Inc(cReq);
      cReq = cStp = 0;
    }
}

//---------------------------------------------------------------------------
//  QUEUE
//---------------------------------------------------------------------------

QUEUE::QUEUE (int Size): Size(Size)
{
  waitedTooLong=0;

}

QUEUE::~QUEUE (void)
{
  EVENT *Event;

  while ( !q.empty() )
    {
      Event = q.back();
      q.pop_back();
      Event->Owner = NULL;
      if(Event){
	delete Event;
      }else{
	std::cout << "Double free in ~Queue\n";
	throw;
      }
    }
}

void QUEUE::AddEvent (EVENT *Event)
{
  if (q.size()==Size)
    {
      std::cout << "Should never happen\n";
      throw;  
    }
  

  q.push_front(Event);
  
}

// Return one event from Top
EVENT* QUEUE::GetEvent(){

  EVENT *Event=NULL;
  
  // Obviously if we have one
  if (q.size()==0){
    return NULL;
  }  

  Event= q.back();
  q.pop_back();  
  return Event;

}

int QUEUE::Empty(void)
{
  return q.size()==0;
}

bool QUEUE::isFull (void)
{
  return q.size()==Size;
}

int QUEUE::Len (void)
{
  return q.size();
}

void QUEUE::Wait()
{
  if(q.size()==0){return;}
  EVENT* Event = NULL;
  std::list<EVENT*>::iterator it;

  
  for ( it=q.begin() ; it != q.end(); it++ ) {
    
    Event = *it;
    if(! Event->InQueue()){
      it=q.erase(it);
      if(Event){
      delete Event;      
      //really rejected
      }else{
	std::cout << "Already dead\n";
	throw;
      }
    }
  }
  
  
}


//---------------------------------------------------------------------------
//  SYSTEM
//---------------------------------------------------------------------------

SYSTEM::SYSTEM (int queLen, int srvNum, int Stts)
{
  reallyRejected=0;
  QueueStatIterator = 0;
  Queue = new QUEUE (queLen);
  Servers = new SERVERS (srvNum, Stts);

  stGradeOfService = new SttsSmp;
  stServedEvents = new SttsSmp;
  if(Stts)
    {
      stQueueWaitingTime = new SttsTab;
      stQueueUsage = new SttsTab;
      // nawiasy mają znaczenie
      stQueueTimeUsage = new SttsLog ("xyQueLen-f.xy");
    }else
    {
      stQueueWaitingTime=stQueueTimeUsage=stQueueUsage=NULL;
      
    }
}

SYSTEM::~SYSTEM (void)
{
 
  if (stQueueWaitingTime)
    {
      stQueueWaitingTime->PdfToFile ("xyQueTime.xy");
      delete stQueueWaitingTime;
    }
  
  if (stQueueUsage)
    {
      stQueueUsage->PdfToFile("xyQueLen.xy");
      delete stQueueUsage;
    }

  if (stQueueTimeUsage) delete stQueueTimeUsage;

  delete stGradeOfService;
  delete stServedEvents;
  delete Servers;
  delete Queue;
}

void SYSTEM::TakeEvent (EVENT* Event)
{
  SERVER *Server;
  
  Server = Servers->FreeSrv();
  if (Server)
    {
      stGradeOfService->Inc(SERVED);
      stServedEvents->Inc(0);
      if (stQueueWaitingTime)
	stQueueWaitingTime->Inc(0);
      
      Server->TakeEvent(Event);
    }
  else
    {
      stGradeOfService->Inc(REJECTED_OR_QUEUED);
      if (!Queue->isFull())
	Queue->AddEvent(Event);
      else{
	reallyRejected++;
	if(Event){
	  delete Event;
	}else{
	  std::cout << "Double free when rejecting\n";
	  throw;
	}
      }
    }
}

void SYSTEM::Work (void)
{
  SERVER *Server;
  EVENT *Event;

  Queue->Wait();
  Servers->Serve();

  
  while ( !Queue->Empty() && (Server=Servers->FreeSrv()))
    {
      if( (Event = Queue->GetEvent()) ){
      stServedEvents->Inc(Event->isWait);
      if (stQueueWaitingTime)
	{
	  stQueueWaitingTime->Inc(Event->isWait);
	}
      
      Server->TakeEvent(Event);
      }
      //Server = Servers->FreeSrv();
    }

  if (stQueueUsage)    
    stQueueUsage->Inc(Queue->Len());
    
  if (stQueueTimeUsage)
    stQueueTimeUsage->Set(++QueueStatIterator, Queue->Len());
    
}





