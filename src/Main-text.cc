#include "Queue.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

int main(int argc, char** argv) {
  
  bool RunStatus;  
  IRandVal *rvCall;
  IRandVal *rvLen;
    
  USERS* Users;
  SYSTEM* System;
  SERVERS *Servers;

  int MaxSimTimeVal;
  int SimTime;
  int MaxTime;
   
  int SimPr;
  SimParams *SimulationParameters;
   
   
  int NumSrvr;
  int NumUser;
  int QueLen;
  double Atot;
  double CLen;
  int Stts;
  int start_time;

  start_time = time(NULL);

  std::cout << "Start!\n";

  RunStatus=true;
  SimulationParameters= new SimParams();
        
  //Czas symulacji
  SimulationParameters->TimeOfSimulation = 500000;
        
  // Pewnie ilość serwerów
  SimulationParameters->NumberOfServers = 5;
        
  //Ilość userów
  SimulationParameters->NumberOfUsers = 200;
	
        
  // Długość kolejki
  SimulationParameters->LengthOfQueue = 20000000;
        
  //Natężenie ruchu
  SimulationParameters->DensityOfTraffic = 35;

  //Średni czas obsługi
  SimulationParameters->ModerateServiceTime = 90;

  //Czy statystyki
  SimulationParameters->GenerateStats = true;
        
        
        
  /* Jeszcze raz piszemy to samo dla kompatybilnosci wstecz */
  MaxTime = SimulationParameters->TimeOfSimulation;
  NumSrvr = SimulationParameters->NumberOfServers;
  NumUser = SimulationParameters->NumberOfUsers;
  QueLen  = SimulationParameters->LengthOfQueue;
  Atot = SimulationParameters->DensityOfTraffic;
  CLen = SimulationParameters->ModerateServiceTime;
  Stts = SimulationParameters->GenerateStats;
  ////////////////////


  rvLen  = new rvExp(CLen);

    
  //        switch(WaitL->currentIndex()){
  //            case 1:
  //                ipl=new IPpConst(0);
  //                break;
  //            case 0:
  //                ipl=new IPpConst(WaitLen->value());
  //                break;
  //            case 2:
  //                ipl=new IPpExp(WaitLen->value());
  //                break;
  //            default:
  //                throw;
  //        }        
  /* TODO: Dorobic wybor rozkladu */
  rvCall = new rvBin(Atot/CLen/NumUser);
  std::cout << "\nAtot " << Atot 
	    << "\nClen " << CLen 
	    << "\nNumUser " << NumUser 
	    << "\nMaxtime " << MaxTime;
  long double x = 1;
  x*=Atot;
  x/=CLen;
  x*= MaxTime;
  x/= NumUser;

    
    
  //IRandVal *rvLen  = new rvExp(CLen);
  /// IRandVal *rvLen  = new rvCnst (CLen);
        
  System = new SYSTEM(QueLen, NumSrvr, Stts);
  Users = new USERS(System, NumUser, rvCall, rvLen, Stts);
        
        
  /* Kompilator nie lubi niejawnej konwersji */
  int aa = (int)(Atot<NumSrvr? Atot+0.5: NumSrvr);
  /* Wstępne wypełnianie kolejki serwerów */
/*  for (int ne=0; ne<aa; ne++) {
    int LifeSpan = 0;
    while (!LifeSpan) LifeSpan = rvLen->Val();
    EVENT *E = new EVENT(NULL, LifeSpan);
    System->Servers->FreeSrv()->TakeEvent(E);
  }*/
  //////////////////////////////
  
  int lastMaxTime= MaxTime; 
    
    
  for( SimTime=1; SimTime<=MaxTime; SimTime++)
    {
      if (MaxTime != lastMaxTime) throw;    
    
      Users->GoOn();
      System->GoOn();
      
      /* Nie ma sensu za każdym razem gui updatować */
      if(SimTime%100==0 || SimTime==MaxTime)
	{
	  //SttsSmp* stServedEventsRef = (SttsSmp*)System->stServedEvents;
	  SttsTab *stCalLen = (SttsTab*)Users->stCalLen;

	  std::cout << std::endl << "T: " << SimTime ;
	  std::cout << std::endl << " GOS:" << 100*System->stGradeOfService->Avg()+0.5;
	  std::cout << std::endl << (100-100*System->stGradeOfService->Avg());	
	  
	  SttsSmp* GOS= (SttsSmp*)System->stGradeOfService;
	  std::cout << std::endl << (GOS->returnSum());
	
	  int timediff = time(NULL) - start_time;
	  std::cout << std::endl << (timediff);

	  // FIXME: Jeśli kolejka jest mała to wychodzi błąd natężenia ruchu
	  double  A = stCalLen->returnSum()/MaxTime;
	  std::cout << std::endl << (A);
	  std::cout << std::endl << (Atot - A);
	  std::cout << std::endl << (
				     System->reallyRejected
				     +System->Queue->waitedTooLong);

	  std::cout << std::endl << (GOS->Get(System->SERVED));
	 
	  std::cout << std::endl << (System->Queue->Len());

	  SimulationParameters->pb = 100*(1.0-System->stGradeOfService->Avg());
	  SimulationParameters->nb = 0;
	  SimulationParameters->qa = System->stServedEvents->Avg();
	  SimulationParameters->nz = System->stServedEvents->Avg();
	  SimulationParameters->pr =  100.0*SimTime/MaxTime;
	}
    
    }

  std::cout << "Symulacja zakończona\n";

  FILE *log = fopen("Log.txt", "at");
  fprintf(log, "%12i\t%6i\t%6i\t%6i\t%10.2f\t%10.2f\t%10.2f\t%10.2f\n",
	  MaxTime, NumSrvr, NumUser, QueLen,
	  Atot, CLen, 100*(1.0-System->stGradeOfService->Avg()),
	  System->stServedEvents->Avg()
	  );
  fclose(log);




        
  
  /////////////////////////////
  delete Users;
  delete System;
  delete SimulationParameters; 
       
  return 0;   
}









