#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<list>

#ifndef _QUEUE_H
#define _QUEUE_H

/**
 *  RANDOM VALS
 */

class IRandVal {
 public:
  virtual int Val (void) = 0;
  virtual ~IRandVal (void) {}
  static const int MY_RANDMAX= 2147483648; //2 ** 31
};

class rvBin : public IRandVal {
 private:
  long int rnd;
  long int ipp;
  int isTrue(void);
 public:
  rvBin (double pp);
  virtual int Val (void);
  virtual ~rvBin (void) {}

};

/** Algorytm Box-Mullera
 * http://en.wikipedia.org/wiki/Normal_distribution */
class rvNormal : public IRandVal {
 private:
  double avg;
  double variance;
 public:
  rvNormal(double avg, double variance);  
  virtual int Val (void);
  virtual ~rvNormal (void) {}

};

/** Algorytm Knutha
 http://en.wikipedia.org/wiki/Poisson_distribution */
class rvPoisson : public IRandVal {
 private:
  double avg;
 public:
  rvPoisson(double avg);
  virtual int Val (void);
  virtual ~rvPoisson (void) {}

};

class rvBinominal : public IRandVal {
 private:
  unsigned long n;
  double p;
 public:
  rvBinominal(unsigned long n, double p);
  virtual int Val (void);
  virtual ~rvBinominal (void) {}

};

class rvErlang : public IRandVal {
 private:
  int A;
    double B, a1, sq, scale, scale2;    
 public:
    rvErlang(int order, double loc);
  virtual int Val (void);
  virtual ~rvErlang (void) {}

};

class rvCnst : public IRandVal {
 private:
  double avg;
 public:
  rvCnst (double avg);
  virtual int Val (void);
  virtual ~rvCnst (void) {}
};

/** Kwantylow funkcji
 * http://en.wikipedia.org/wiki/Exponential_distribution */
class rvExp : public IRandVal {
 private:
  double avg;
 public:
  rvExp (double avg);  
  virtual int Val (void);
  virtual ~rvExp (void) {}
};



/**
 *  STTSMAP
 *
 * Interfejs dla statystyk
 */
class IStts {
 public:
  virtual ~IStts (void) {};
  virtual void Set (int key, int val) = 0;
  virtual void Inc (int key) = 0;
  virtual int Get (int key) = 0;
  virtual double Avg (void) = 0;
  virtual double nzAvg (void) = 0;
  virtual void ValToFile (const char *nm) = 0;
  virtual void PdfToFile (const char *nm) = 0;
  //virtual int returnSum(void) = 0;
};



/**
 *  STTSTAB
 */
class SttsTab : public IStts {
 private:
  int *Tab;
  int Size;
  char *pth;
 public:
  SttsTab (void);
  ~SttsTab (void);
  void Clr (void);
  void Set (int key, int val);
  void Inc (int key);
  int Get (int key);
  int Fm (void);
  int To (void);
  double returnSum(void);
  double Avg (void);
  double nzAvg (void);
  void ValToFile (const char *nm);
  void PdfToFile (const char *nm);
  int returnSize(void);
};


/**
 *  SttsLog
 */

class SttsLog : public IStts {
 private:
  double sum, avg, nzs, nza;
  int mxStp, crStp;
  FILE *f;
 public:
  SttsLog (char *pth, int mxStp=50000);
  ~SttsLog (void);
  void Set (int key, int val);
  void Inc (int key);
  int Get (int key);
  int Fm (void);
  int To (void);
  double Avg (void);
  double nzAvg (void);
  void ValToFile (const char *nm);
  void PdfToFile (const char *nm);
  //int returnSize();
};

/**
 *  EVENT
 */

class USER;
class SERVER;
class SYSTEM;
class QUEUE;
//class IStts;
class IRandVal;

class EVENT {

  
  friend class QUEUE;
  friend class SYSTEM;
  friend class USERS;

  
  
 public:
  bool isTaken;
  
  static const int NO_WAITING=-1;

  /// tmWait=-1 => noe
  EVENT(USER *Owner, int tmServ=90, int tmWait=-1);
  ~EVENT(void);
  USER *Owner;
  SERVER *Server;
  //EVENT *Next;
  int InQueue(void);
  int InServer(void);

 private:
  int tmWait, tmServ;  // parametry
  int isWait, isServ;  // stan chwilowy
  int wasServed(void);
  void showParams(void);
};


/**
 *  SERVER
 */

class SERVER {
 friend class USERS;
 friend class SERVERS;
 private:
  EVENT *Event; 
 public:
  SERVER (void);
  void Free (void);
  bool IsFree (void);
  void TakeEvent (EVENT *E);
 
};

class SERVERS{
 private:
  SERVER *Servers;
  int Size;
  int ServersIterator;
 public:
  IStts *stSrvUsg;
  IStts *stSrvFly;
  SERVERS (int Size, int Stts);
  ~SERVERS (void);
  SERVER *FreeSrv (void);
  void Serve (void);
};

/**
 *  STTSTAB
 */

class SttsSmp : public IStts {
 private:
  double sum, avg, nzs, nza;
 public:
  SttsSmp (void);
  ~SttsSmp (void);
  void Clr (void);
  void Set (int key, int val);
  void Inc (int key);
  int Get (int key);
  int Fm (void);
  int To (void);
  double Avg (void);
  double nzAvg (void);
  void ValToFile (const char *nm);
  void PdfToFile (const char *nm);
  int returnSum(void);
};




/**
 *  USER
 */

class USER {
 private:
  SYSTEM *System;
  EVENT *Event;
  IRandVal *rvCall;
  IRandVal *rvLen;
  IRandVal *rvWait;
 public:
  USER (IRandVal *rvCall,
	IRandVal *rvLen, IRandVal *rvWait);
  EVENT *Spawn (void);
  void Free (void);
  bool IsFree (void);
};

/**
 * Users
 */
class USERS {
 private:
  USER **Users;
  int Size;
  int cReq, cStp;
  SYSTEM *System;
 public:
  IStts *stCalLen;
  IStts *stCalInt;
  USERS(SYSTEM *System, int Size, 
	IRandVal *rvCall, 
	IRandVal *rvLen,
	IRandVal* rvWait,
	int Stts);

  ~USERS(void);
  void GenTraffic (void);
};

/**
 *  QUEUE
 * Kolejka opakowywuje standardowa kolekcje
 * <list> z bilioteki stl
 */
class QUEUE {
 private:
  std::list<EVENT*> q;
  int Size;
 public:
  QUEUE(int Size);
  ~QUEUE(void);
  int Empty(void);
  bool isFull (void);
  int Len (void);
  int waitedTooLong;

  EVENT* GetEvent(void);
  void AddEvent(EVENT* Event);
  void Wait (void);
};

/**
 *  SYSTEM
 */

class SYSTEM {
 public:
  static const int SERVED=1;
  static const int REJECTED_OR_QUEUED=0;
  QUEUE *Queue;
  SERVERS *Servers;
  int reallyRejected;

  
  int QueueStatIterator;
    
  /// new SttsSmp;   
  IStts *stGradeOfService;

  /** new SttsSmp;
   * Zdarzenia przekazane serwerom */
  IStts *stServedEvents;

  /** Czas czekania w kolejce
   * 0 -> przyjecie do kolejki
   * inna liczba -> to czas czekania */
  IStts *stQueueWaitingTime;
  IStts *stQueueUsage;
  IStts *stQueueTimeUsage;

  SYSTEM (int queLen, int srvNum, int Stts);
  ~SYSTEM (void);
  void Init (int A);
  void Work (void);
  void TakeEvent (EVENT* Event);
};


/**
 *  SimParams
 */
class SimParams {
 public:
  
  int TimeOfSimulation, NumberOfServers, NumberOfUsers, LengthOfQueue;
  double DensityOfTraffic, ModerateServiceTime;
  double pr, pb, qa, nz;
  int nb;
  int GenerateStats;
};



#endif
