//
//  phonelist
//  Thorsten 2016-12
//
//  Speed optimizations: Sort after first digit and only search within list with same first digit,
//  stop search after first match, replace string find with compare (find searches the full string)
//

#include <iostream>
#include <string>
#include <vector>
#define N_MAX 10000

using namespace std;

struct numbersStruct{
    string number[N_MAX];
    unsigned int len[N_MAX];
    unsigned int firstDigit[N_MAX];
};

int main()
{
    ios::sync_with_stdio(false);                            //optimize I/O performance
    
    //variables:
    unsigned int testCases, testLength, testDigit, listLength[40], end, t, i;
    int j;
    bool match=false;
    string testNumber;
    vector<numbersStruct> n;                                //phone numbers are saved as strings
    
    //read test cases:
    cin >> testCases;
    
    for(t=0; t<testCases; t++)
    {
        cin >> listLength[t];
        
        n.push_back(numbersStruct());                       //create new struct for each test case

        //save phone numbers:
        for(i=0; i<listLength[t]; i++)
        {
            cin >> n[t].number[i];
            n[t].firstDigit[i] = n[t].number[i][0] - '0';   //convert first digit to integer and save
        }
    }
    
    
    for(t=0; t<testCases; t++)
    {
        //sort numbers after first digit (insertion sort):
        for(i=1; i<listLength[t]; i++)
        {
            testNumber=n[t].number[i];
            testDigit=n[t].firstDigit[i];
            
            for(j=i-1; j>=0; j--)                           //check all saved numbers from last to first
            {
                if(n[t].firstDigit[j] > testDigit)          //shift up one position if new begins with a smaller digit
                {
                    n[t].number[j+1]=n[t].number[j];
                    n[t].firstDigit[j+1]=n[t].firstDigit[j];
                }
                else
                    break;                                  //stop shifting if right spot was found
            }
            n[t].number[j+1]=testNumber;                    //insert number in empty spot
            n[t].firstDigit[j+1]=testDigit;
        }
        
        
        //look for inconsistent number pairs:
        for(i=0,testLength=0; i<listLength[t]; i++)
        {
            //initialize test number to compare, it's first digit and lenght:
            testNumber = n[t].number[i];
            testDigit = n[t].firstDigit[i];
            testLength = n[t].number[i].length();
            
            //find starting point for search (first list entry with same first digit):
            for(j=0; j<=listLength[t]; j++)
            {
                if(n[t].firstDigit[j]==testDigit)
                    break;
            }
            
            //find end point for search:
            for(end=j+1; end<=listLength[t]; end++)
            {
                if(n[t].firstDigit[j]>testDigit)
                    break;
            }
            
            //search within numbers with same starting digit:
            for(; j<end; j++)
            {
                //compare with longer numbers, don't check test string on itself:
                if(n[t].number[j].length()>testLength && i!=j)
                {
                    //set match flag and stop searching if match was found:
                    if(n[t].number[j].compare(0,testLength,testNumber) == 0)
                    {
                        match=true;
                        break;
                    }
                }
            }
            if(match==true)                                 //flag to leave nested loop
                break;
        }
        
        //Print result of test case:
        if(match==true)
        {
            cout << "NO" << endl;
            match=false;
        }
        else
            cout << "YES" << endl;
    }
    
    return 0;
}
    
