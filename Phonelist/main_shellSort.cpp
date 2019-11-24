//
//  phonelist
//  Thorsten 2016-12
//

#include <iostream>
#include <string>

using namespace std;

int main()
{
    //optimize I/O performance:
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    //temporary variables:
    unsigned int testCases, t, i, longest;
    int j, matches=0;
    string  sortString, testString;

    //data saving variables:
    unsigned int listLength[40];
    string numbers[10000][40];  //phone numbers are saved as strings

    cin >> testCases;

    //*** read in test cases: ***
    for(t=0; t<testCases; t++)
    {
        cin >> listLength[t];

        //save phone numbers:
        for(i=0; i<listLength[t]; i++)
            cin >> numbers[i][t];
    }

    for(t=0; t<testCases; t++)
    {
        //*** sort numbers according to length (shell sort): ***
        for(int gap=listLength[t]/2; gap>0; gap/=2)
        {
            for(i=gap; i<listLength[t]; i++)
            {
                sortString=numbers[i][t];
                for(j=i; (j>= gap) && (sortString.length() < numbers[j-gap][t].length()); j-=gap)
                {
                    numbers[j][t]=numbers[j-gap][t];
                }
                numbers[j][t]=sortString;
            }
        }

        //*** print sorted list of numbers: ***
        //for(i=0; i<listLength[t]; i++)
        //    cout << numbers[i][t] << endl;

        //*** look for inconsistent number pairs: ***
        longest=numbers[ listLength[t]-1 ][t].length();     //length of longest number (last in list)

        for(i=0, testString=""; testString.length() < longest; i++) //compare all strings with longer ones
        {
            testString=numbers[i][t];

            //start loop at i: don't check the same strings multiple times, i+1: don't check test string on itself
            for(j=i+1; j<listLength[t]; j++)
            {
                //cout << testString << endl;
                if (numbers[j][t].find(testString) == 0)    //check if strings starts with test string
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
