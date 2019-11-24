//
//  phonelist
//  Thorsten 2016-12
//
//  Latest version: Adaptive memory usage using a vector (to avoid crashes),
//  speed optimizations: 1. Number length initialization (values saved in struct) to minimize calling .lengh() function in sort loop
//  2. Replace string find with compare (find searches the full string),
//  3. Pre sorting, compare only first letter in string before checking the full string.
//

#include <iostream>
#include <string>
#include <vector>
#define T_MAX 40

using namespace std;

struct numbersStruct{
    string number[T_MAX];
    unsigned int len[T_MAX];
};

int main()
{
    ios::sync_with_stdio(false);                            //optimize I/O performance
    
    //variables:
    unsigned int testCases, t, i, longest, testLength;
    int j, matches=0;
    string  input, testString;
    
    unsigned int listLength[T_MAX];
    vector<numbersStruct> n;                                //phone numbers are saved as strings
    
    
    cin >> testCases;
    
    //*** read in test cases: ***
    for(t=0; t<testCases; t++)
    {
        cin >> listLength[t];
        
        //save phone numbers:
        for(i=0; i<listLength[t]; i++)
        {
            cin >> input;
            n.push_back(numbersStruct());                   //create new struct for each entry
            n[i].number[t]=input;
        }
    }
    
    
    for(t=0; t<testCases; t++)
    {
        //determine length of numbers:
        for(i=0; i<listLength[t]; i++)
            n[i].len[t]=n[i].number[t].length();
        
        //*** sort numbers according to length (insertion sort): ***
        /*for(i=1; i<listLength[t]; i++)
         {
         testString=n[i].number[t];
         testLength=testString.length();
         
         for(j=i-1; j>=0; j--)                           //check all saved numbers from last to first
         {
         if(n[j].len[t] > testLength)                //shift up one position if new number is shorter
         {
         n[j+1].number[t]=n[j].number[t];
         n[j+1].len[t]=n[j].len[t];
         }
         else
         break;                                  //stop shifting if right spot was found
         }
         n[j+1].number[t]=testString;                    //insert number in empty spot
         n[j+1].len[t]=testLength;
         }*/
        
        //shell sort
        for(int gap=listLength[t]/2; gap>0; gap/=2)
        {
            for(i=gap; i<listLength[t]; i++)
            {
                testString=n[i].number[t];
                testLength=testString.length();
                
                for(j=i; (j>= gap) && (testLength < n[j-gap].len[t]); j-=gap)
                {
                    n[j].number[t]=n[j-gap].number[t];
                    n[j].len[t]=n[j-gap].len[t];
                }
                n[j].number[t]=testString;
                n[j].len[t]=testLength;
            }
        }
        
        //*** print sorted list of numbers: ***
        //for(i=0; i<listLength[t]; i++)
        //  cout << n[i].number[t] << endl;
        
        //*** look for inconsistent number pairs: ***
        longest=n[ listLength[t]-1 ].len[t];                //length of longest number (last in list)
        for(i=0, testString=""; testString.length() < longest; i++) //don't compare with strings of same size
        {
            testString=n[i].number[t];
            testLength=n[i].len[t];
            
            //start loop at i: don't check the same strings multiple times, i+1: don't check test string on itself
            for(j=i+1; j<listLength[t]; j++)
            {
                if(n[j].number[t][0] == testString[0])      //quick check if first numbers are the same
                    if(n[j].number[t].compare(0,testLength,testString) == 0)    //if so, compare all numbers
                        //if(n[j].number[t].find(testString) == 0)
                        matches++;
            }
        }
        
        //is the list consistent?
        if(matches==0)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        matches=0;                                          //reset matching sequence counter
    }
    
    return 0;
}
