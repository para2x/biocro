#include <R.h>
#include <math.h>
#include <Rmath.h>
#include <Rinternals.h>
#include "AuxBioCro.h"
#include "Century.h"
#include "BioCro.h"
#include "AuxcaneGro.h"
#include "crocent.h"

void createNULLmiscanthus(struct miscanthus *miscanthus,int vecsize)
{
   int i;
   miscanthus->leafvec=malloc((vecsize+1)*sizeof(*miscanthus->leafvec));
   miscanthus->stemvec=malloc((vecsize+1)*sizeof(*miscanthus->stemvec));
   miscanthus->rootvec=malloc((vecsize+1)*sizeof(*miscanthus->rootvec));
   miscanthus->rhizomevec=malloc((vecsize+1)*sizeof(*miscanthus->rhizomevec));
  
   for (i = 0; i<=vecsize;i++)
   {
      miscanthus->leafvec[i].newbiomass=0.0;
      miscanthus->leafvec[i].newlitter=0.0;
       miscanthus->leafvec[i].ageinTT=0.0;
       miscanthus->stemvec[i].newbiomass=0.0;
      miscanthus->stemvec[i].newlitter=0.0;
       miscanthus->stemvec[i].ageinTT=0.0;
       miscanthus->rootvec[i].newbiomass=0.0;
      miscanthus->rootvec[i].newlitter=0.0;
       miscanthus->rootvec[i].ageinTT=0.0;
       miscanthus->rhizomevec[i].newbiomass=0.0;
      miscanthus->rhizomevec[i].newlitter=0.0;
       miscanthus->rhizomevec[i].ageinTT=0.0;
       
   }
   
   miscanthus->leaf.biomass=0.0;
   miscanthus->stem.biomass=0.0;
   miscanthus->root.biomass=0.0;
   miscanthus->rhizome.biomass=0.0;
   miscanthus->leaf.litter=0.0;
   miscanthus->stem.litter=0.0;
   miscanthus->root.litter=0.0;
   miscanthus->rhizome.litter=0.0;
   miscanthus->rhizome.carbohydratefraction=0.6; // Lets assume that in the beginning carbohydrate fraction of dry biomass is  60%
   return;
}


/*

double canopyFrostsenescence(struct leaf *leaf, double T0,double T100, double T)
{
  double temp,fraction, senesced;
  fraction = (T0-T)/(T0-T100);
  temp = fraction>1.0? 1.0:(fraction <0.0? 0.0:fraction);
  senesced=(leaf->biomass)*fraction;
  return(senesced);
}







double getDailyRemobilization(double current, double k, double senesced, double remobFac)
{
  double tmp;
  tmp=0.0;
  if(k<0.0)
  {
    tmp+=current*k;
    tmp=fabs(tmp);
    current-=tmp; // here i am up
    if(tmp>=current)error("One of the remobilization organ has become zero\n");
  }
  if(senesced>0.0)
  {
    tmp+=senesced*remobFac;
  }
}

double getDailyGrowth(double current, double netDailyCanopyAssim, double mResp, double k, double TotalRemobilize)
{
  double tmp;
  if(k>=0)
  {
    tmp=(netDailyCanopyAssim+TotalRemobilize)*k;
  }
  else
  {
    tmp=current*k;
    if(fabs(tmp)>=currrent) error("One of the remobilization organ has become zero\n");
  }
  tmp-=mResp;
  return (tmp);
}
// Function to calculate  complete structure of the new addition for a one particular day
struct plant DailyPlantBiomassGrowth(struct plant *current, struct litter *leaflitter, int Nday, int TTc, struct crop_phenology DBP)
{
  struct plant *tmp;
  int tmpN;
  tmpN=Nday*24;
  // Leaves
   tmp->leaf.litter=getDailySenescence(leaflitter,tmpN, current->leaf.parms.criticalTT, current->leaf.parms.remobFac);
   current->leaf.parms.k=getDBP(TTc);
   Leafremobilized=getDailyRemobilization(current->leaf.biomass, current->leaf.parms.k,newsenesced, current->leaf.parms.remobFac);
   // Stem
   tmp->stem.litter=getDailySenescence(stemlitter,tmpN, current->stem.parms.criticalTT, current->stem.parms.remobFac);
   current->stem.parms.k=getDBP(TTc);
   Stemremobilized=getDailyRemobilization(current->stem.biomass, current->stem.parms.k,newsenesced, current->stem.parms.remobFac);
   // Root
   tmp->root.litter=getDailySenescence(rootlitter,tmpN, current->root.parms.criticalTT, current->root.parms.remobFac);
   current->root.parms.k=getDBP(TTc);
   Rootremobilized=getDailyRemobilization(current->root.biomass, current->root.parms.k,newsenesced, current->root.parms.remobFac);
    // Rhizome
   tmp->rhizome.litter=getDailySenescence(rhizomelitter,tmpN, current->rhizome.parms.criticalTT, current->rhizome.parms.remobFac);
   current->rhizome.parms.k=getDBP(TTc);
   Rhizomeremobilized=getDailyRemobilization(current->rhizome.biomass, current->rhizome.parms.k,newsenesced, current->rhizome.parms.remobFac);
   
   TotalRemob=Leafremobilized+Stemremobilized+Rootremobilized+Rhizomeremobilized;
   
   tmp->leaf.biomass=getDailyGrowth(current->leaf.biomass,dailynetassim, leafMresp,current->leaf.parms.k, TotalRemob);
   tmp->stem.biomass=getDailyGrowth(current->stem.biomass,dailynetassim, stemMresp,current->stem.parms.k, TotalRemob);
   tmp->root.biomass=getDailyGrowth(current->root.biomass,dailynetassim, rootMresp,current->root.parms.k, TotalRemob);
   tmp->rhizome.biomass=getDailyGrowth(current->rhizome.biomass,dailynetassim, rhizomeMresp,current->rhizome.parms.k, TotalRemob);
   
  // here I am updating CE content of the daily plant material
  // Get minimum CE ratios as suggested by partitionin coefficients
  tmp->leaf.E = DBP->leaf.E;
  tmp->stem.E = DBP->stem.E;
  tmp->root.E = DBP ->root.E;
  tmp->rhizome.E = DBP ->rhizome.E;
  // DO I need to do above isnt it same aq equal to litter CE content?
  
  // Calculate E demand based on new biomass growh in the current day
  maxNdemand=(tmp->leaf.biomass)/(tmp->leaf.E.CN)+(tmp->stem.biomass)/(tmp->stem.E.CN)
           +(tmp->root.biomass)/(tmp->root.E.CN)+(tmp->rhizome.biomass)/(tmp->rhizome.E.CN);
  // I need to calculate N demand in gram /m2
 // to convert Mg/ha of biomass to gram C/m2 I need to multiple
 // by 0.01 (Mg/ha to gram/m2) and 0.4 (carbohydrate to C)
 Ndemand=Ndemand*0.01*0.4;      
           
 NfromRemob= (Leafremobilized/current->leaf.E.CN)+ (Stemremobilized/current->stem.E.CN)
             + (Rootremobilized/current->root.E.CN)+ (Rhizomeremobilized/current->rhizome.E.CN);
             
 // unit conversion Mg biomass/ha to gram C/m2
 NfromRemob=NfromRemob*0.01*0.04;
 // How much from Soil is Required?
 NdemandfromSoil=maxNdemand-NfromRemob;
 Navailability=getAvailableN(&CropCent_soilML);
    if(NdemandfromSoil<0.0)
        { 
          extraNforRhizome=(-1)*NdemandfromSoil;
          NdemandfromSoil=0.0
        }
     else
     {
          extraNforRhizome=0.0;
          NavailablefromSoil=get_max_available_N_from_CropCent(&cropcent);
          if(NavailablefromSoil>NdemandfromSoil)
          {
            remove_CropCent_E(&cropcent,NdemandfromSoil);
          }
          else
          {
            remove_CropCent_E(&cropcent,NavailablefromSoil);
            addjustPlantEuptake(tmp,NavailablefromSoil); // now E uptake by plant is limited by maximum soil E availability
          } 
     }
     return;
}

struct plant DailyPlantNutrientUptake (struct plant *current, struct plant *daily, struct crop_phenology *DBP, double TTc)
{
  // CE cpmcemtratopm of different plant components can be read directly from partitioning table
  daily->leaf.E = DBP->leaf.E;
  daily->stem.E = DBP->stem.E;
  daily->root.E = DBP ->root.E;
  daily->rhizome.E = DBP ->rhizome.E;
  
  // Calculate E demand based on new biomass growh in the current day
  Ndemand=(daily->leaf.biomass)/(daily->leaf.E.CN)+(daily->stem.biomass)/(daily->stem.E.CN)
           +(daily->root.biomass)/(daily->root.E.CN)+(daily->rhizome.biomass)/(daily->rhizome.E.CN);
 
 // I need to calculate N demand in gram /m2
 // to convert Mg/ha of biomass to gram C/m2 I need to multiple
 // by 0.01 (Mg/ha to gram/m2) and 0.4 (carbohydrate to C)
 Ndemand=Ndemand*0.01*0.4;
 
 NfromRemob=
 
 
  
  
  
}


double dailyEdemand(double plant *plant, double plant *dailygrowth,)
{
  
}
*/
double getThermaltime (double temp, double Tbase)
{
  double res;
  if(temp<=Tbase)
  {
    res=0.0;
  }
  else
  {
    res=(temp-Tbase);
  }
  return(res);
}


double getThermalSenescence(double criticalTT, double currentTT, double biomass, double dailyfractionalloss)
{
  /*************************************
   * Purpose
   * To calculate senescence as a constant fraction of exisiting biomass after a critical threshold temperature
   * Input:
   * criticalTT: This is critical Thermal temperature, beyond which senescence begins
   * currentTT: Current thermal TT or phenological stage
   * biomass: Exisiting biomass
   * dailyfractionalloss: Fraction of biomass which will be lost
   * Output:
   * 
   * Returns senesced biomass
   * 
   * **********************************/
   double tmp;
  if(currentTT <= criticalTT)
  {
   tmp=0.0;
  }
  else
  {
   tmp=biomass*dailyfractionalloss;
  }
  return(tmp);
}

double getFrostdamage(double T0, double T100,double T, double biomass)
{
   /*************************************
   * Purpose
   * To calculate senescence as a fraction of exisiting biomass due to frost
   * Input:
   * T0: This is maximum temperature when frost damage occurs, This also represent Temperature 
   * damage will be zero percentage of exisiting biomass
   * T100: This is minimum temperature where all the existing biomass senescee (i.e. 100% senescence)
   * biomass: Exisiting biomass
   *
   * Output:
   * 
   * Returns senesced biomass
   * 
   * **********************************/
  double temp,fraction;
  fraction = (T0-T)/(T0-T100);
  temp = fraction>1.0? 1.0:(fraction <0.0? 0.0:fraction);
  return(temp*biomass);
}

double canopyNsenescence(struct leaf *leaf, double SLA, double kN,  double leafNsen)
{
  /*****************************************************
   * Purpose:
   * 
   * Purpose of this function is to calculate additional N senescence due to N deficiency
   * It uses current value of average canopy N, use this and an exponential coefficient to
   * determine vertical distribution of leaf N canopy.
   * If this vertical distrbution results in leaf N of lower canopy which is less than a threshold value
   *  then an leaf biomass (equivalent to LAI which is having lower than threshold leaf N conc.) is senesced
   * Input
   * leaf: pointer to leaf structure
   * SLA: specific leaf area (in ha/Mg)
   * kN:  coefficient determining exponentially declining leaf N conc (dimensionless)
   * leafNsen: any leaf with leaf N conc lower than leafNsen will be senesced (mmol N m-2)
   * Output/return
   * Senesced leaf biomass (Mg/ha)
   * ***************************************************/
  double tmp;
  double laimax,laicurrent;
  double leafN;
  leafN=leaf->biomassE.CN;
  laimax=(1/kN)*log(1+(kN*leafN/leafNsen));
  laicurrent=leaf->biomass*SLA;
  if(laicurrent<=laimax)
  {
    tmp=0.0;
  }
  else
  {
    tmp=(laicurrent-laimax)/SLA;
  }
  return(tmp);
}


double getLeafSenescence(struct leaf *leaf, double criticalTT, double senefraction,  double Temp, struct frostParms *frostparms, double TT,struct canopyparms *canopyparm)
{
  /******************************************************
   * Purpose:
   * This function calculates Leaf Senescence
   * 
   * Input Arguments:
   * stem : is a pointer to stem structure
   * criticalTT: is critical value of accumulated thermal time where senesence begins
   * Temp: minimum daily temperature
   * frostparms: is a pointer to structure containing parameters to somulate damage due to frost
   * TT: is current [daily] value of accumutaed thermal time
   * 
   * Output/Returns
   * Biomass  to be semesced due to aging (thermal time) and frost, together
   * ****************************************************/
  double ttsen, frostsen, Nsen;
  double totalsen;
  Nsen=0.0;
  ttsen=getThermalSenescence(criticalTT,TT,leaf->biomass,senefraction);
//  Rprintf("TSEN=%f,critcalT=%f, TT=%f, biomass=%f, senfraction=%f \n",ttsen,criticalTT, TT,leaf->biomass,senefraction);
  frostsen=getFrostdamage(frostparms->leafT0,frostparms->leafT100, Temp,leaf->biomass);
  // Nsen=canopyNsenescence(leaf, canopyparm->SLA, canopyparm->kN,canopyparm->leafNsen);
  totalsen=ttsen+frostsen+Nsen;
  totalsen= (totalsen>(leaf->biomass))?(leaf->biomass):totalsen;
  return(totalsen);
}

double getStemSenescence(struct stem *stem, double criticalTT, double senefracion,  double Temp, struct frostParms *frostparms, double TT)
{
  /******************************************************
   * Purpose:
   * This function calculates Stem Senescence
   * 
   * Input Arguments:
   * stem : is a pointer to stem structure
   * criticalTT: is critical value of accumulated thermal time where senesence begins
   * Temp: minimum daily temperature
   * frostparms: is a pointer to structure containing parameters to somulate damage due to frost
   * TT: is current [daily] value of accumutaed thermal time
   * 
   * Output/Returns
   * Biomass to be semesced due to aging (thermal time) and frost, together
   * ****************************************************/
  double ttsen, frostsen;
  double totalsen;
  frostsen=0.0;
  ttsen=getThermalSenescence(criticalTT,TT,stem->biomass,senefracion);
  frostsen=getFrostdamage(frostparms->stemT0, frostparms->stemT100, Temp,stem->biomass);
  totalsen=ttsen+frostsen;
  totalsen= (totalsen>(stem->biomass))?(stem->biomass):totalsen;
  return(totalsen);
}

double getRootSenescence(struct root *root, double criticalTT, double senefracion,  double Temp, struct frostParms *frostparms, double TT)
{
  /******************************************************
   * Purpose:
   * This function calculates Root Senescence
   * 
   * Input Arguments:
   * stem : is a pointer to stem structure
   * criticalTT: is critical value of accumulated thermal time where senesence begins
   * Temp: minimum daily temperature
   * frostparms: is a pointer to structure containing parameters to somulate damage due to frost
   * TT: is current [daily] value of accumutaed thermal time
   * 
   * Output/Returns
   * Biomassto be semesced due to aging (thermal time) and frost, together
   * ****************************************************/
  double ttsen, frostsen;
  double totalsen;
  frostsen=0.0;
  ttsen=getThermalSenescence(criticalTT,TT,root->biomass,senefracion);
  frostsen=getFrostdamage(frostparms->rootT0, frostparms->rootT100, Temp,root->biomass);
  totalsen=ttsen+frostsen;
  totalsen= (totalsen>(root->biomass))?(root->biomass):totalsen;
  return(totalsen);
}

double getRhizomeSenescence(struct rhizome *rhizome, double criticalTT, double senefracion,  double Temp, struct frostParms *frostparms, double TT)
{
  /******************************************************
   * Purpose:
   * This function calculates Root Senescence
   * 
   * Input Arguments:
   * stem : is a pointer to stem structure
   * criticalTT: is critical value of accumulated thermal time where senesence begins
   * Temp: minimum daily temperature
   * frostparms: is a pointer to structure containing parameters to somulate damage due to frost
   * TT: is current [daily] value of accumutaed thermal time
   * 
   * Output/Returns
   * Biomass  to be senesced due to aging (thermal time) and frost, together
   * ****************************************************/
  double ttsen, frostsen;
  double totalsen;
  frostsen=0.0;
  ttsen=getThermalSenescence(criticalTT,TT,rhizome->biomass,senefracion);
  frostsen=getFrostdamage(frostparms->rhizomeT0, frostparms->rhizomeT100, Temp,rhizome->biomass);
  totalsen=ttsen+frostsen;
  totalsen= (totalsen>(rhizome->biomass))?(rhizome->biomass):totalsen;
  return(totalsen);
}

void updatedailyvec(struct dailyvec *dailyvec,double newbiomass,double newlitter, int N,double delTT)
{
  int i;
  for (i=0; i<=N;i++)
  {
     dailyvec[i].ageinTT+=delTT;
  }
  dailyvec[N].newbiomass=newbiomass;
  dailyvec[N].newlitter=newlitter;
  return;
}

void updatebiomass(double *res,double toadd,double toremove)
{
  *res=*res+toadd-toremove;
  return;
}

double newbiomass(double AcanopyNet,double k, double GrowthRespCoeff)
{
  double tmp;
  tmp=AcanopyNet*k/(1+GrowthRespCoeff);
  return(tmp);
}

void getfrostparms(struct frostParms *frostparms)
{
   frostparms->leafT0=0.0;
   frostparms->leafT100=-5.0;
   frostparms->stemT0=0.0;
   frostparms->stemT100=-10.0;
   frostparms->rootT0=-200.0;
   frostparms->rootT100=-200.0;
   frostparms->rhizomeT0=-200.0;
   frostparms->rhizomeT100=-200.0;
   return;
}
void getsenescenceparms(struct senthermaltemp *senparms)
{
    senparms->leafcriticalT = 3600;
    senparms->leaffr=0.05;
    senparms->stemcriticalT = 3600;
    senparms->stemfr=0.02;
    senparms->rootcriticalT = 3600;
    senparms->rootfr=0.05;
    senparms->rhizomecriticalT = 3600;
    senparms->rhizomefr=0.001;
  return;
}


double CalculateGrowthResp(double newbiomass,double growthRespCoeff)
{
  return(newbiomass*growthRespCoeff);
}
// struct miscanthus 
void dailymiscanthus(struct miscanthus *miscanthus,double coefs[25],double TherPrds[6], double TherTime, double Temp,double dailynetassim,
struct senthermaltemp *senparms, struct canopyparms *canopyparms, struct frostParms *frostparms, int N, double delTT,
struct respirationParms *RESP)

{

  double remobStem,remobRoot,remobRhiz;
  remobStem=canopyparms->remobFac;
  remobRoot=canopyparms->remobFac;
  remobRhiz=canopyparms->remobFac;
  double deadleaf,deadstem,deadroot,deadrhiz;
  double dailysenesced;
  double remobilized;
  double totalassimilate;
  struct crop_phenology cropdbp;
  double newleaf,newstem,newrhiz,newroot;
  double kLeaf,kStem,kRoot,kRhizome;
  double newLeaf,newStem,newRhizome,newRoot;
  double newLeaflitter,newStemlitter,newRhizomelitter,newRootlitter;
  double totalmaintenance;
  

// double getStemSenescence(struct stem *stem, struct littervec *littervec, double criticalTT, double Temp, double remobfa, struct frostParms *frostparms, int N)
 // calculate senescing biomass for today based on Thermal Time, N conce. and Frost conditions 
   getfrostparms(frostparms);
   getsenescenceparms(senparms);


                   deadleaf=getLeafSenescence(&miscanthus->leaf,senparms->leafcriticalT,senparms->leaffr, Temp, frostparms,TherTime,canopyparms);
                   deadstem=getStemSenescence(&miscanthus->stem,senparms->stemcriticalT,senparms->stemfr, Temp, frostparms,TherTime);
                   deadroot=getRootSenescence(&miscanthus->root, senparms->rootcriticalT,senparms->rootfr, Temp, frostparms,TherTime);
                   deadrhiz=getRhizomeSenescence(&miscanthus->rhizome,senparms->rhizomecriticalT,senparms->rhizomefr, Temp, frostparms,TherTime); 

              
    
//     
//          Rprintf("Emergence=%i,TherT=%f, Temp=%f Leaf=%f, senesced Leaf= %f\n",emergence,TherTime,Temp,miscanthus->leaf.biomass,deadleaf);
          dailysenesced=deadleaf+deadstem+deadroot+deadrhiz;
          remobilized = dailysenesced*canopyparms->remobFac; // assuming all the dead organs remobilizes same fraction
          totalmaintenance=miscanthus->autoresp.stemmaint+miscanthus->autoresp.rootmaint+miscanthus->autoresp.rhizomemaint;
          totalassimilate=dailynetassim+remobilized-totalmaintenance;
          if(totalassimilate<=0.0)
          {
          newLeaf=0.0;
          newStem=0.0;
          newRoot=0.0;
          newRhizome=totalassimilate; // negative values of assimilate (i.e. respiration) are to be supplied from rhizome
          }
          else
          {
          cropcent_dbp(coefs,TherPrds,TherTime, &cropdbp);
          kLeaf = cropdbp.DBP.kLeaf;
          kStem = cropdbp.DBP.kStem;
          kRoot = cropdbp.DBP.kRoot;
          kRhizome = cropdbp.DBP.kRhiz;
          newLeaf=newbiomass(totalassimilate,kLeaf,0.0);
          newStem=newbiomass(totalassimilate,kStem,RESP->growth.stem);
          newRoot=newbiomass(totalassimilate,kRoot,RESP->growth.root);
          newRhizome=newbiomass(totalassimilate,kRhizome,RESP->growth.rhizome);       
          }
           // updating miscanthus growth respiration
          if(totalassimilate <=0)
          {
            miscanthus->autoresp.stemgrowth=0;
            miscanthus->autoresp.rootgrowth=0;
            miscanthus->autoresp.rhizomegrowth=0;
          }
          else
          {
          miscanthus->autoresp.stemgrowth=CalculateGrowthResp(newStem,RESP->growth.stem);
          miscanthus->autoresp.rootgrowth=CalculateGrowthResp(newRoot,RESP->growth.stem);
          miscanthus->autoresp.rhizomegrowth=CalculateGrowthResp(newRhizome,RESP->growth.stem);
          }
          miscanthus->autoresp.total=miscanthus->autoresp.leafdarkresp+totalmaintenance+miscanthus->autoresp.stemgrowth+miscanthus->autoresp.rootgrowth+miscanthus->autoresp.rhizomegrowth;
         
  
          UpdateStandingLeaf(&miscanthus->leaf,newLeaf,deadleaf,canopyparms->remobFac);
          UpdateStandingStem(&miscanthus->stem,newStem,deadstem,canopyparms->remobFac);
          UpdateStandingRoot(&miscanthus->root,newRoot,deadroot,canopyparms->remobFac);
          UpdateStandingRhizome(&miscanthus->rhizome,newRhizome,deadrhiz,canopyparms->remobFac); 
    return;
}



void UpdateStandingLeaf(struct leaf *leaf, double newbiomass, double deadleaf, double remobFactor)
{
  leaf->biomass+=newbiomass-deadleaf;
  leaf->litter+=deadleaf*(1-remobFactor);
  return;
}

void UpdateStandingStem(struct stem *stem, double newbiomass, double deadstem, double remobFactor)
{
  stem->biomass+=newbiomass-deadstem;
  stem->litter+=deadstem*(1-remobFactor);
  return;
}

void UpdateStandingRoot(struct root *root, double newbiomass, double deadroot, double remobFactor)
{
  root->biomass+=newbiomass-deadroot;
  root->litter+=deadroot*(1-remobFactor);
  return;
}

void UpdateStandingRhizome(struct rhizome *rhizome, double newbiomass, double deadrhizome, double remobFactor)
{
  rhizome->biomass+=newbiomass-deadrhizome;
  rhizome->litter+=deadrhizome*(1-remobFactor);
  return;
}

int CheckEmergence(struct dailyclimate *dailyclimate, double EmergTemperature)
{
  int flag;
  if(((dailyclimate->minimumTemp)>EmergTemperature)&&((dailyclimate->doy)>90)&&((dailyclimate->doy)<270)){
    flag =1;
  }
  else
  {
    flag = 0;
  }
  return(flag);
}


void getdailyclimate(struct dailyclimate *dailyclimate, int *doy,double *solar,double *temp, double *rh, double *windspeed, double*precip, int currenthour, int vecsize)
{
  //For the first hour after planting
  int i,indx;
  if ((currenthour==0)||(currenthour==vecsize))
      {
         dailyclimate->doy=*(doy+currenthour);
         dailyclimate->solar=*(solar+currenthour);
         dailyclimate->temp=*(temp+currenthour);
         dailyclimate->rh=*(rh+currenthour);
         dailyclimate->windspeed=*(windspeed+currenthour);
         dailyclimate->precip=*(precip+currenthour);
         dailyclimate->minimumTemp=*(temp+currenthour);
      }
   else
      {
        dailyclimate->solar=0.0;
        dailyclimate->temp=0.0;
        dailyclimate->minimumTemp=*(temp+currenthour);
        dailyclimate->rh=0.0;
        dailyclimate->windspeed=0.0;
        dailyclimate->precip=0.0;
          for(i=1;i<=24;i++)
            {
              indx = currenthour-i+1;      
              dailyclimate->solar+=*(solar+indx);
              dailyclimate->temp+=*(temp+indx);
              dailyclimate->rh+=*(rh+indx);
              dailyclimate->windspeed+=*(windspeed+indx);
              dailyclimate->precip+=*(precip+indx);
              dailyclimate->minimumTemp=(dailyclimate->minimumTemp>(*(temp+indx)))?(*(temp+indx)):dailyclimate->minimumTemp;
            }
            dailyclimate->solar=dailyclimate->solar/24.0;
            dailyclimate->temp=dailyclimate->temp/24.0;
            dailyclimate->rh=dailyclimate->rh/24.0;
            dailyclimate->windspeed= dailyclimate->windspeed/24.0;
            dailyclimate->doy=*(doy+currenthour);
      }
     return;     
}


void dailymiscanthusupdate(struct miscanthus *miscanthus,struct miscanthus *deltamiscanthus)
{
  double toadd,toremove;
  
  toadd=deltamiscanthus->leaf.biomass;
  toremove=deltamiscanthus->leaf.litter;
  updatebiomass(&miscanthus->leaf.biomass,toadd,toremove);
  updatebiomass(&miscanthus->leaf.litter,toremove,0.0);
  
  toadd=deltamiscanthus->stem.biomass;
  toremove=deltamiscanthus->stem.litter;
  updatebiomass(&miscanthus->stem.biomass,toadd,toremove);
  updatebiomass(&miscanthus->stem.litter,toremove,0.0);
  
  toadd=deltamiscanthus->root.biomass;
  toremove=deltamiscanthus->root.litter;
  updatebiomass(&miscanthus->root.biomass,toadd,toremove);
  updatebiomass(&miscanthus->root.litter,toremove,0.0);
  
  toadd=deltamiscanthus->rhizome.biomass;
  toremove=deltamiscanthus->rhizome.litter;
  updatebiomass(&miscanthus->rhizome.biomass,toadd,toremove);
  updatebiomass(&miscanthus->rhizome.litter,toremove,0.0);
   return;
}



void dailyC3tree(struct c3tree *c3tree,double coefs[25],double TherPrds[6], double TherTime, double Temp,double dailynetassim,
struct senthermaltemp *senparms, struct canopyparms *canopyparms, struct frostParms *frostparms, struct respirationParms *RESP)
{
  /**************************************************************************
   * Purpose: This function simulate growth of c3 tree
   *  Input:
   * c3tree-- is a pointer to c3tree structure containing leaf,root, stem, and rhizome(storage) structures
   * coefs -- is vector (length 25) representing dry biomass partitioning coefficients, similar to older versionof BioCro
   * TherPrds-- is a vector of length 6, containing thermal time for different pehnological stages
   * TherTime-- is what is the accumulated thermal time until today. This will be used to identify current pehnological stage and will accordingly 
   * be used in determining dry biomass partiitoning coefficients
   * dailynetassim-- is net canopy assimilation after taking care of leaf dark respiration. this is one of the output of canopy function
   * senparms-- This is a pointer to senescence parameters structure. Values contained in this structure will be used to cause senescence of each component
   * canopyparms-- This is a pointer to canopy parms structure, Values containined in this strucure may be used to induce senesnce under N limited conditions when 
   * N conc. of leaves is too thi (for now, let us not use this for c3 tree)
   * frostparms-- this ia apointer tostructure containing parameters governing senescence due to frost
   * RESP-- this is pointer to structure containing parameters to calculate growth and maintenenace respiration of different plant organs
   * 
   * ************************************************************************/
   double deadleaf,deadstem,deadroot,deadrhiz,dailysenesced;
   double totalassimilate,remobilized,totalmaintenance;
   double newLeaf,newStem,newRoot,newRhizome;
   double kLeaf,kStem,kRoot,kRhizome;
   struct crop_phenology cropdbp;
    
    /******************************************************************************
    * here I am reading fixed frost and senescence parameterr 
    * This need to be replaced so that I can change these parameters from R 
    * ***************************************************************************/
     getfrostparms(frostparms);
     getsenescenceparms(senparms);
   
   
   
   /********************************************************************************
    * Here, I am calculating senesceing due to thermal aging and senescence
    * ******************************************************************************/
     deadleaf=getLeafSenescence(&c3tree->leaf,senparms->leafcriticalT,senparms->leaffr, Temp, frostparms,TherTime,canopyparms);
     deadstem=getStemSenescence(&c3tree->stem,senparms->stemcriticalT,senparms->stemfr, Temp, frostparms,TherTime);
     deadroot=getRootSenescence(&c3tree->root, senparms->rootcriticalT,senparms->rootfr, Temp, frostparms,TherTime);
     deadrhiz=getRhizomeSenescence(&c3tree->rhizome,senparms->rhizomecriticalT,senparms->rhizomefr, Temp, frostparms,TherTime); 
     
     /*******Performing some calculations************************************************/
     /*****total senescnece of biomass for today *********/
     dailysenesced=deadleaf+deadstem+deadroot+deadrhiz; 
     /**I am assumung that remobilization of each plan organ is same. we can change this in future based on literature if remobilization from leaf versus root are not same **/
     remobilized = dailysenesced*canopyparms->remobFac; 
     /**** Evaluating total maintenance respiration from today's maintenance respiration of different plan organs **/
     totalmaintenance=c3tree->autoresp.stemmaint+c3tree->autoresp.rootmaint+c3tree->autoresp.rhizomemaint;
     /** Here, I am calculating total assimilate that is available for plant growth todaay ****/    
     totalassimilate=dailynetassim+remobilized-totalmaintenance;
     
     /** If total assimilate is less than zero than no growth will take place *****/
     /*** we only need to make sure that negative value (or loss fue to respiration is satisfied from the storage value **/
     /** Otherwise we need to get dry biomass partitioning coefficients to simulate growth of each component******/          
          if(totalassimilate<=0.0)
          {
          newLeaf=0.0;
          newStem=0.0;
          newRoot=0.0;
          newRhizome=totalassimilate; // negative values of assimilate (i.e. respiration) are to be supplied from rhizome
          }
          else
          {
          cropcent_dbp(coefs,TherPrds,TherTime, &cropdbp);
          kLeaf = cropdbp.DBP.kLeaf;
          kStem = cropdbp.DBP.kStem;
          kRoot = cropdbp.DBP.kRoot;
          kRhizome = cropdbp.DBP.kRhiz;
          newLeaf=newbiomass(totalassimilate,kLeaf,0.0);
          newStem=newbiomass(totalassimilate,kStem,RESP->growth.stem);
          newRoot=newbiomass(totalassimilate,kRoot,RESP->growth.root);
          newRhizome=newbiomass(totalassimilate,kRhizome,RESP->growth.rhizome);       
          }
          
          /**Calculatng growth respiration. Remember that leaf dark respiration is already taken care of in net canopy assimilation**/
          /**** we only need to calculate growth respiratin of stem, root, and rhizome***********************************************/
          if(totalassimilate <=0)
          {
            c3tree->autoresp.stemgrowth=0;
            c3tree->autoresp.rootgrowth=0;
            c3tree->autoresp.rhizomegrowth=0;
          }
          else
          {
          c3tree->autoresp.stemgrowth=CalculateGrowthResp(newStem,RESP->growth.stem);
          c3tree->autoresp.rootgrowth=CalculateGrowthResp(newRoot,RESP->growth.stem);
          c3tree->autoresp.rhizomegrowth=CalculateGrowthResp(newRhizome,RESP->growth.stem);
          }
          
          /*** Updating total autotrophic respiration for today***************/
          c3tree->autoresp.total= c3tree->autoresp.leafdarkresp + totalmaintenance+ c3tree->autoresp.stemgrowth + c3tree->autoresp.rootgrowth+ c3tree->autoresp.rhizomegrowth;
          
          /****** Updating dead biomass pool after taking care of remobilization ******/
          deadleaf =deadleaf*(1-canopyparms->remobFac);
          deadstem =deadstem*(1-canopyparms->remobFac);
          deadroot =deadroot*(1-canopyparms->remobFac);
          deadrhiz =deadrhiz*(1-canopyparms->remobFac);
  
         /***** Update standing biomass (both alive and dead) for today**************/
          UpdateStandingLeaf(&c3tree->leaf,newLeaf,deadleaf,canopyparms->remobFac);
          UpdateStandingStem(&c3tree->stem,newStem,deadstem,canopyparms->remobFac);
          UpdateStandingRoot(&c3tree->root,newRoot,deadroot,canopyparms->remobFac);
          UpdateStandingRhizome(&c3tree->rhizome,newRhizome,deadrhiz,canopyparms->remobFac); 
          
          /**** Checking for error message if rhizome becomes negative ****/
          if((c3tree->rhizome.biomass) < 0)
          {
            error("Rhizome biomass has become negative");
          }
    return;
}

void updatedormantstage(struct miscanthus *miscanthus)
{
  double LostinRespiration,availablecarb,newcarb;
  LostinRespiration=miscanthus->autoresp.stemmaint + miscanthus->autoresp.rootmaint +  miscanthus->autoresp.rhizomemaint;
  // This loss will occur at the expense of carbohydrate fraction of rhizome, resulting in change in the carbohydrate fraction of the rhizome
  availablecarb= miscanthus->rhizome.biomass*miscanthus->rhizome.carbohydratefraction;
  newcarb=availablecarb-LostinRespiration;
  miscanthus->rhizome.biomass-=LostinRespiration;
  miscanthus->rhizome.carbohydratefraction=newcarb/miscanthus->rhizome.biomass;
  
  if((miscanthus->rhizome.carbohydratefraction)<0.05)miscanthus->rhizome.carbohydratefraction=0.05;
  if(miscanthus->rhizome.biomass <0)error("rhizome has become negative");

  miscanthus->autoresp.stemgrowth=0;
  miscanthus->autoresp.rootgrowth=0;
  miscanthus->autoresp.rhizomegrowth=0;
  miscanthus->autoresp.total= LostinRespiration;
  
}