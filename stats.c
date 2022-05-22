#include "stats.h"
#include "alerter.h"

int emailAlertCallCount = 0;
int ledAlertCallCount = 0;

struct Stats compute_statistics(const float* numberset, int setlength) {
    struct Stats s;
    s.average = 0;
    s.min = 0;
    s.max = 0;
    int sum = 0;
    
    for(int i = 0; i<= setlength; i++)
    {
       sum = sum + numberset[i];
       if((s.max == 0) &&(s.min == 0))
       {
           s.max = numberset[i];
           s.min = numberset[i];
       }
       else if(s.max < numberset[i])
       {
           s.max = numberset[i];
       }
       else if(s.min > numberset[i])
       {
           s.min = numberset[i]; 
       }
        else
        {
            //do nothing
        }
    }
    s.average = sum/setlength;
    
    return s;
        

}

void check_and_alert(float maxThreshold, alerter_funcptr alerters[], struct Stats computedStats)
{ 
    if(maxThreshold > computedStats.max)
    {
        (*alerters[0])();
        (*alerters[1])();  
        emailAlertCallCount = 1; 
        ledAlertCallCount = 1;
    }
}
