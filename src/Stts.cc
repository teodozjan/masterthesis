#include "Queue.h"


//---------------------------------------------------------------------------
///  STTSSMP
//---------------------------------------------------------------------------

SttsSmp::SttsSmp (void)
{
  sum = avg = nzs = nza = 0.0;
}
SttsSmp::~SttsSmp (void)
{
}


void SttsSmp::Set (int key, int val)
{  
  sum += val;
  avg += key * val;
  if (key)
    {
      nzs += val;
      nza += key * val;
    }
}
void SttsSmp::Inc (int key)
{
  sum++;
  avg += key;
  if (key)
    {
      nzs++;
      nza += key;
    }
}
int SttsSmp::Get (int key)
{

  switch (key)
    {
    case 0:      
      return(sum - nzs);
      break;
    case 1:
      return nzs;
      break;
    default:
      return 0; 
    }

}
int SttsSmp::Fm (void)
{
  return 0;
}
int SttsSmp::To (void)
{
  return 0;
}
double SttsSmp::Avg (void)
{
  return sum!=0? avg/sum:0;
}
double SttsSmp::nzAvg (void)
{
  return nzs!=0? nza/nzs:0;
}

int SttsSmp::returnSum(void)
{
  return sum;
}

void SttsSmp::ValToFile (const char *nm)
{
  std::cout << "Doing nothing with string "<< *nm << std::endl;
}
void SttsSmp::PdfToFile (const char *nm)
{
  std::cout << "Doing nothing with string " << *nm << std::endl;
}

//---------------------------------------------------------------------------
///  STTSTAB
//---------------------------------------------------------------------------

SttsTab::SttsTab (void)
{
  Size = 1000;
  Tab = new int[Size];
  memset (Tab, 0, Size*sizeof(int));
};
SttsTab::~SttsTab (void)
{
  delete []Tab;
}
void SttsTab::Clr (void)
{
  delete []Tab;
  Size = 1000;
  Tab = new int[Size];
  memset (Tab, 0, Size*sizeof(int));
};
void SttsTab::Set (int key, int val)
{
  if (key>=Size)
    {
      int *Tmp = new int [2*Size];
      memcpy (Tmp, Tab, Size*sizeof(int));
      memset (Tmp+Size, 0, Size*sizeof(int));
      delete []Tab;
      Tab = Tmp;
    }
  Tab[key] = val;
}
void SttsTab::Inc (int key)
{
  if (key>=Size)
    {
      int *Tmp = new int [2*Size];
      memcpy (Tmp, Tab, Size*sizeof(int));
      memset (Tmp+Size, 0, Size*sizeof(int));
      delete []Tab;
      Tab = Tmp;
      Size*=2;
    }
  Tab[key] ++;
}
int SttsTab::Get (int key)
{
  return key<Size? Tab[key]: 0;
}
int SttsTab::Fm (void)
{
  return 0;
}
int SttsTab::To (void)
{
  int k;
  for (k=Size-1; k>=0; k--)
    if (Tab[k])
      return k;
  return 0;
}
double SttsTab::Avg (void)
{
  double s=0.0, a=0.0;
  int k, *val = Tab;
  for (k=0; k<Size; k++)
    {
      s += *val;
      a += k * *val;
      val++;
    }
  a = s==0? 0: a/s;
  return a;
}

double SttsTab::returnSum (void)
{
  double a=0.0;
  int k;
  int *val = Tab;
  for (k=0; k<Size; k++)
    {

      a += k * *val;
      val++;
    }
  
  return a;
}

double SttsTab::nzAvg (void)
{
  double s=0.0, a=0.0;
  // bez wartoci 0:
  int k, *val = Tab+1;
  for (k=1; k<Size; k++)
    {
      s += *val;
      a += k * *val;
      val++;
    }
  a = s==0? 0: a/s;
  return a;
}
void SttsTab::ValToFile (const char *nm)
{
  std::cout << "This string should not be ignored: " << nm << std::endl;

  FILE *f;
  int k, fm, to;
  f = fopen(nm, "wt");
  fm = Fm();
  to = To();
  for (k=fm; k<=to; k++)
    fprintf(f, "%6i\t%10i\n", k, Tab[k]);

  fclose(f);
}
void SttsTab::PdfToFile (const char *nm)
{
  FILE *f;
  int k, fm, to, *val;
  double s;
  f = fopen(nm, "wt");
  fm = Fm();
  to = To();
  val = Tab;
  for (k=0; k<Size; k++)
    s += *val++;
  for (k=fm; k<=to; k++)
    fprintf(f, "%6i\t%12f\n", k, Tab[k]/s);
      
  fclose(f);
}

int SttsTab::returnSize(void)
{
  return Size;
}
//---------------------------------------------------------------------------
///  STTSLOG
//---------------------------------------------------------------------------

SttsLog::SttsLog (char *pth, int mxStp) : mxStp(mxStp)
{
  sum = avg = nzs = nza = 0.0;
  crStp = 0;
  f = pth? fopen(pth, "wt"): NULL;
};
SttsLog::~SttsLog (void)
{
  if (f)
    fclose(f);
}
void SttsLog::Set(int key, int val) {
    sum += val;
    avg += key * val;
    if (key)
      {
        nzs += val;
	nza += key * val;
      }
    if (f && ++crStp<mxStp)
        fprintf(f, "%6i\t%10i\n", key, val);
}
void SttsLog::Inc (int key)
{
  std::cout << "Doing nothin with" << key << std::endl;
  return;
}
int SttsLog::Fm (void)
{
  return 0;
}
int SttsLog::To (void)
{
  return 0;
}
double SttsLog::Avg (void)
{
  return sum==0? 0: avg/sum;
}
double SttsLog::nzAvg (void)
{
  return nzs==0? 0: nza/nzs;
}
void SttsLog::ValToFile (const char *nm)
{
  std::cout << "Doing nothing with " << *nm << std::endl;
}
void SttsLog::PdfToFile (const char *nm)
{
 std::cout << "Doing nothing with " << *nm << std::endl;
}

int SttsLog::Get (int key)
{
  std::cout << "Doing nothing with " << key << std::endl;
  return 0;
}



