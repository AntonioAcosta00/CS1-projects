#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//include "leak_detector_c.h"
/* COP 3502C Assignment 1 
This program is written by: Antonio Acosta */ 
typedef struct monster {
  char *name;
  char *element;
  int population;
} monster;
typedef struct region {
  char *name;
  int nmonsters;
  int total_population;
  monster **monsters;
} region;
typedef struct itinerary {
  int nregions;
  region **regions;
  int captures;
} itinerary;
typedef struct trainer {
  char *name;
  itinerary *visits;
} trainer;
monster *makeMonster(char *name, char *element, int population) {
  // returns a dynamically allocated monster
  // Need malloc for name and element
  int namelength = 1 + strlen(name);
  int elementlength = 1 + strlen(element);
  // Malloc for a monster Struct
  monster *myM = malloc(sizeof(monster));
  // makes enough space for mallocing name and element
  myM->name = malloc(namelength*sizeof(char));
  myM->element = malloc(elementlength*sizeof(char));
  //Copies the input into the struct
  strcpy(myM->name,name);
  strcpy(myM->element,element);
  
  myM->population = population;
  return myM;
}
  /*This function returns an array of monster pointers where each monster pointer points to     the dynamically allocated monsters with fill-up information from the provided inputs. It     can use the makeMonster function in this process. This function also updates the passed      variable reference pointed by monsterCount so that the caller to this function knows how     many monsters are returned from the function. */
monster **readMonsters(int *monsterCount)
{
  int pop;
  int total = 0;
  char name[51], ele[51], k[51];
  //Makes mList able to hold double pointers
  monster **mList = malloc(sizeof(monster *));
  for(int i = 0; i < *monsterCount; i++)
    {
      //Allocates space for monster struct and sets it
     mList[i] = malloc(*monsterCount * (sizeof(monster)));
          scanf(" %s", name);        
          scanf(" %s", ele);
          scanf(" %d", &pop);
          mList[i] = makeMonster(name, ele, pop);
          total += 1;
           
    }
  monsterCount = &total;
  return mList;
}
 /* This function returns an array of region pointers where each region pointer points to a dynamically allocated region, filled up with the information from the inputs, and the region’s monsters member points to an appropriate list of monsters from the monsterList passed to this function. This function also updates the passed variable reference pointed by countRegions (to inform the caller about this count). As the loadMonsters function has created all the monsters using dynamic memory allocation, you are getting this feature to use/re-use those monsters in this process. */
/*After that the input contains information about rcount number of regions. Where the first line of a region contains thename of the region, next line contains the number of different monsters rmcount in that region with the word monsters.The next rmcount lines contain the name of different monsters in the region.
*/
region** readRegions(int *countRegions, monster** monsterList, int monsterCount)
{
  int rmCount = 0, total1 = 0;
  char regN[51], f[50], rmName[51];
 region **myR = malloc(sizeof(region*));
  for(int rLoop = 0; rLoop < *countRegions; rLoop++)
    {
      //Declares necessary space
      myR[rLoop] = malloc(*countRegions * (sizeof(region)));
      
      //Region name input
      scanf(" %s", regN);
      int regNLength = 1 + strlen(regN);
      myR[rLoop]->name = malloc(regNLength*sizeof(char));
      strcpy(myR[rLoop]->name,regN);
      
      
      //Takes user input for region monster count and sets it
      scanf(" %d %s", &rmCount, f);
      myR[rLoop]->nmonsters = rmCount;
      //Mallocs space for the amount of monsters dependent on each region
      myR[rLoop]->monsters = malloc(rmCount*sizeof(monster*));
      //Search Function
      for(int monsterLoop = 0; monsterLoop < rmCount; monsterLoop++)
        {
          //Mallocs space for the specific monsters for each region via monster struct
         myR[rLoop]->monsters[monsterLoop] = malloc(rmCount*sizeof(monster));
          scanf(" %s", rmName);
          //Searches
          for(int mlLoop = 0; mlLoop < monsterCount; mlLoop++)
            {
              //compares the strings and sets necessary elements if it is found
              //mlLoop = monster list loop
              //monster loop = general mosnter loop depending on the amount of monsters in region
              if(strcmp(rmName,monsterList[mlLoop]->name)==0)
              {
                int z = strlen(monsterList[mlLoop]->name)+1;
                myR[rLoop]->monsters[monsterLoop]->name = malloc(z*sizeof(char));
                strcpy( myR[rLoop]->monsters[monsterLoop]->name , monsterList[mlLoop]->name);
                myR[rLoop]->monsters[monsterLoop]->element = monsterList[mlLoop]->element;
                myR[rLoop]->monsters[monsterLoop]->population = monsterList[mlLoop]->population;
                myR[rLoop]->total_population += monsterList[mlLoop]->population;
                break;
              }
              
            }
          
        }
      total1 = total1 + 1;
    }
  countRegions = &total1;
  return myR;
}
/* This function returns a dynamically allocated array of trainers, filled up with the information from the inputse, and the trainer’s visits field points to a dynamically allocated itinerary which is filled based on the passed regionList. This function also updates the passed variable reference pointed by trainerCount. As the loadRegions function has crated all the regions using dynamic memory allocation, you are getting this feature to use/re-use those regions in this process.  */
trainer* loadTrainers(int *trainerCount, region** regionList, int countRegions)
{
  int tcaptures, trcount, total2 = 0;
  char name[51], f[50], h[50], rname[51];
  trainer *myT = malloc(*trainerCount * sizeof(trainer));
  for(int tLoop = 0; tLoop < *trainerCount; tLoop++)
    {
      //Take in and malloc info
      //Take in Name
      scanf(" %s", name);
      int lname = 1 + strlen(name);
      myT[tLoop].name = malloc(lname*sizeof(char));
      strcpy(myT[tLoop].name,name);
      //Malloc size of visits to hold itinerary struct
      myT[tLoop].visits = malloc(sizeof(itinerary));
      //Scans the intented captures and sets it to unique trainer
      scanf("%d %s", &tcaptures, f);
      myT[tLoop].visits->captures = tcaptures;
      //Takes region count and sets it to unique trainer
      scanf("%d %s", &trcount, h);
      myT[tLoop].visits->nregions = trcount;
      //Makes region** an array of regions depending on user input
      myT[tLoop].visits->regions = malloc(trcount*sizeof(region*));
      //Search Algo
      for(int rLoop = 0; rLoop<trcount; rLoop++)
        {
          //Makes space for each region depending on trainer region count
          myT[tLoop].visits->regions[rLoop] = malloc(trcount*sizeof(region));
          scanf(" %s", rname);
          //Searches for the name
          for(int rSearchloop = 0; rSearchloop < countRegions; rSearchloop++)
            {
              if(strcmp(regionList[rSearchloop]->name,rname)==0)
              {
                //If the name is found it makes space for malloc character and copies necessary elements 
                int z = strlen((regionList[rSearchloop]->name)+1);
                myT[tLoop].visits->regions[rLoop]->name = malloc(z*sizeof(char));
                strcpy(myT[tLoop].visits->regions[rLoop]->name,regionList[rSearchloop]->name);
                myT[tLoop].visits->regions[rLoop]->nmonsters = regionList[rSearchloop]->nmonsters;
                myT[tLoop].visits->regions[rLoop]->total_population = regionList[rSearchloop]->total_population;
                //This might be the problem line? I don't think so though
                myT[tLoop].visits->regions[rLoop]->monsters = regionList[rSearchloop]->monsters;
                break;
              }
            }
        }
      total2 = total2 + 1;
    }
  trainerCount = &total2;
  return myT;
}
/* This function processes all the data and produce the output. During this process, you can create/use more functions if you want. */
void processInputs(monster** monsterList, int monsterCount, region** regionList, 
int regionCount, trainer* trainerList, int trainerCount )
{
  for(int tLoop = 0; tLoop < trainerCount; tLoop++)
    {
      printf("%s\n", trainerList[tLoop].name);
      for(int rLoop = 0; rLoop < trainerList[tLoop].visits->nregions; rLoop++)
        {
          printf("%s\n", trainerList[tLoop].visits->regions[rLoop]->name);
          for(int mLoop = 0; mLoop < trainerList[tLoop].visits->regions[rLoop]->nmonsters; mLoop++)
            {
              float regTot = (float)trainerList[tLoop].visits->regions[rLoop]->total_population;
              float monPop = (float)trainerList[tLoop].visits->regions[rLoop]->monsters[mLoop]->population; 
              int totCap = (int)trainerList[tLoop].visits->captures;
              //Necessary math to produce output
              int results = round((monPop/regTot)*totCap);
              if(results > 0)
             {
                char *monsterName = trainerList[tLoop].visits->regions[rLoop]->monsters[mLoop]->name;
                printf("%d#%s\n", results, monsterName);
              }
              
            }
         
        }
       printf("\n");
    }
}
void releaseMemory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount )
{
  //Frees all necessary monster stuff
  for(int i = 0;i < monsterCount; i++)
    {
      free(monsterList[i]->name);
      free(monsterList[i]->element);
      free(monsterList[i]);
    }
  //Frees all necessary region stuff
  for(int i = 0; i < regionCount; i++)
    {
      free(regionList[i]->name);
      free(regionList[i]->monsters);
      free(regionList[i]);
    }
  //Frees all necessary trainer stuff
  for(int i = 0; i < trainerCount;i++)
    {
      free(trainerList[i].name);
      free(trainerList[i].visits->regions);
      free(trainerList[i].visits);
    }
    
  
}
int main()
{
  //atexit(report_mem_leak);
  int monsterCount;
  char z[50], o[50], h[50];
  scanf("%d %s", &monsterCount, z);
  monster** go0 = readMonsters(&monsterCount);
  int regionCount;
  scanf("%d %s", &regionCount, o);
  region** go1 = readRegions(&regionCount, go0, monsterCount);
  int trainerCount;
  scanf("%d %s", &trainerCount, h);
  trainer* go2 = loadTrainers(&trainerCount, go1, regionCount);
  processInputs(go0, monsterCount, go1, regionCount, go2, trainerCount);
  releaseMemory(go0, monsterCount, go1, regionCount, go2, trainerCount);
}