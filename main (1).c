#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

#define MAXNAME 15
#define MAXITEM 100
#define TIMEPERITEM 5
#define TIMEPERCUSTOMER 30
#define MAXTIME 1000000000
#define LINES 12

                                      /* COP 3502C Assignment 2 
                                      This program is written by: Antonio Acosta */ 


typedef struct customer
{
  int time;
  int lineNum;
  int numofTickets;
  char lastName[MAXNAME];
}customer;


typedef struct node
{
  customer* myC;
  struct node* next;
}node;


typedef struct queue
{
  node* front;
  node* back;
}queue;


int empty(queue* qPtr)
{
  if(qPtr->front == NULL)
    return 1;
  return 0;
}

                            /* Queue Functions */

void initqueue(queue *qPtr)
{
    qPtr->front = NULL;
    qPtr->back = NULL;
}

//If statements to check if the qPtr = NULL
// if empty create new node for front and back
// otherwise back->next and back = newNode
void enqueue(queue *qLines, node *cust,int lineNum)
{
  // Check if lines is empty
  if(empty(&qLines[lineNum]) == 1)
  {
    qLines[lineNum].front = cust;
    qLines[lineNum].back = cust;
  }
  else
  {
    qLines[lineNum].front->next = cust;
  }
}



// If empty return NULL
// Else return customer ptr
customer* frontCustomer(queue* qPtr)
{
  if(qPtr == NULL)
  {
    return NULL;
  }
  else
    return qPtr->front->myC;
}

// If empty return NULL
// Set ptr = ptr->front
// ptr->front = ptr->front->next
// if front = NULL
// back = NULL
// return ptr->front
node* dequeue(queue *qRemove)
{
  node* returnVal;
  if(empty(qRemove) == 1)
  {
    return NULL;
  }
  else
  {
    returnVal = qRemove->front;
    qRemove->front = qRemove->front->next;
    if(qRemove->front == NULL)
    {
      qRemove->back = NULL;
    }
    return returnVal;
  }
}


queue* peek(queue *qPtr)
{
  if(!empty(qPtr))
  {
    return qPtr;
  }
  else
  {
    return NULL;
  }
}

                        /* Functions for mallocing */

// malloc for tmp(customer struct)
// strcpy name
// point tmp and set equal to timeinline, line #, number of tickets
// return tmp
customer* makeCustomerNode(int time,int lineNum,char* lastName,int numofTickets)
{
  customer* tmp = malloc(sizeof(customer));
  strcpy(tmp->lastName,lastName);
  tmp->time = time;
  tmp->lineNum = lineNum;
  tmp->numofTickets = numofTickets;

  return tmp;
}
//loop number of customers
  //scanf(time, line, name, ticket_num)
  //temp Pointer = make_customer_node function called
  //temp Pointer = malloc sizeof(node)
  //temp node -> customer pointer = temp Pointer
  //temp node -> next = NULL
  //call enqueue(lines)
void loadqueue(queue* qLines,int numCustomer)
{
  int time, lineNum, numofTickets;
  char lastName[MAXNAME];
  
  for(int i = 0;i < numCustomer; i++)
    {
      
      // make lineNum int and make it eqal to qline line.
      
      scanf("%d %d",&time, &lineNum);
      scanf(" %s", lastName);
      scanf(" %d", &numofTickets);
      customer* tmp = makeCustomerNode(time, lineNum, lastName, numofTickets);
      node* cust = malloc(sizeof(node));
      cust->myC = tmp;
      cust->next = NULL;
      int line = cust->myC->lineNum-1;



      enqueue(qLines, cust, line);
      
    }
}

// free customerPtr
// free ptr
void freeCustomerNode(node *ptrNode)
{
  free(ptrNode->myC);
  free(ptrNode);
}

                          /* Helper functions */

// set res = -1 & mintickets->maxitems+1
// loop using # of lines
// if lines[i] = empty, continue
// tmp = front(customer[times]
// tmp -> timeinline > curTime : continue
// if tmp->#tickets < minTickets
//    - res = i
//    - minTickets = tmp->#tickets
// if res!= return rest
// int bestTime = nextTime + 1;
// loop using # lines
// if lines[i] is empty, continue
// tmp = frontcustomer(lines[i])
// if timeinline < bestTime:
//    -res = ii
//    -bestTime = timeinline
// return res.
int getNext(queue *lines, int curTime)
{
  int res = -1, minTickets = MAXITEM + 1;

  // First just look for active lines, if it's NULL just skip it ( go in order to break ties)
  for(int i = 0; i < LINES; i++)
    {

      if(lines[i].front == NULL)
      {
        continue;
      }
      else
      {
        customer* tmp = frontCustomer(&lines[i]);
        if(tmp->time > curTime)
        {
          continue;
        }
        if(tmp->numofTickets < minTickets)
        {
          res = i;
          minTickets = tmp->numofTickets;
        }
      }
    }
  //we check if our initial processing did lead to a value result, if that is
  // the case then we just return it no need to cotinue comparing
  if(res != -1)
    return res;
      
    // declare bestTime before we begin the conversion process
    
    int bestTime = MAXTIME + 1;
    // if we get here, then we are just looking for the first active line
    for(int i = 0 ; i < LINES; i++)
      {
        if(lines[i].front == NULL)
        {
          continue;
        }
        else
        {
          customer *tmp = frontCustomer(&lines[i]);
          if(tmp->time < bestTime)
          {
            res = i;
            bestTime = tmp->time;
          }
        }
        
      }  
  return res;
}
  


int timeUsed(customer *custPtr)
{
  return  TIMEPERCUSTOMER + (custPtr->numofTickets * TIMEPERITEM);
}




// Scan for number of cases
// Call queue
// loop and initialize queue
// load queues
// loop and call getnext ,dequeue, and point using timePointer and timeNode
// Increment time used
// Nena
int main(void)
{
  atexit(report_mem_leak);
  // Take input first and load everything into the queues
  // queue qLines[12] is an array of queues, and you need to get the users information and place them in that line.
  int numCases, numTickets, numCustomers, time, lineNum, numofTickets;
  char lastName[MAXNAME];
  queue qLines[LINES];
  int i,j;
  
  scanf("%d", &numCases);

  for(int i = 0; i < numCases; i++)
    {
      

      for(int k = 0; k < LINES; k++)
        {
          initqueue(&qLines[k]);
        }
        
      scanf("%d", &numCustomers);
      loadqueue(qLines,numCustomers);
      // Simulation
      int curTime = 0;
      for(j = 0; j < numCustomers; j++)
        {

          // call the get next customer to be processed function and send the queue array and the current time as parameters
          int lineInd = getNext(qLines,curTime);
          // this will give you back the index of the line that you need to dequeue from
          // dequeue this item from the appropriate queue
         node* tmpNode = dequeue(&qLines[lineInd]);

          // so we type less...
          customer* tmpPtr = tmpNode->myC;

          // Update starting time, if necessary ,you need to kep track of this one otherwise for every iteration it will be faulty          
          if(curTime < tmpPtr->time)
          { 
            curTime = tmpPtr->time;
          }

          // Now process this customer by adding the curTime to the checkout time equation results
          curTime = curTime + timeUsed(tmpPtr);
            //call the time used function and send the customer pointer as parameter

            // printfout the status
            printf("%s from line %d checks out at time %d.\n", tmpPtr->lastName, tmpPtr->lineNum, curTime); 
          
          free(tmpNode->myC);
          free(tmpNode);
        }
      
    }
  return 0;
}