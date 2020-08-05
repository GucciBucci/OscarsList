#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;

struct Awards           //Awards Struct
{
    int year;
    string category;
    string winner;
    string entity;

};


int main() {
    ifstream inF;               //File input stream
    string temp;                //temp string to hold
    string input;
    vector<int> won;            //holds indexes of wins 
    vector<int> nom;            //holds indexes of nominations
    vector<Awards> oscarList;
    Awards tStruct;             //Temporary struct
    
    inF.open("oscars.csv");     //opens file
        if(!inF.is_open())      //checks if file open succesfully
            {
                cout << "Could not open: Terminating";
                return 1;
            }
    
    getline(inF, temp);         //skips first line


    while(getline(inF, temp))   //loop reads to end of file
        {
            istringstream iSS(temp);
            
            iSS >> tStruct.year;
            iSS.ignore();
            getline(iSS, tStruct.category, ',');
            getline(iSS, tStruct.winner, ',');
            getline(iSS, tStruct.entity);
   
            temp.clear();

            oscarList.push_back(tStruct);

        }

        cout << "Enter recipient: ";
        getline(cin, input);
        
        for(int k=0; k < oscarList.size(); k++)         //loop stores indexes of wins and nominations into vectors
            {
                if(input == oscarList[k].entity)
                    {
                        if(oscarList[k].winner == "TRUE")
                            {
                                won.push_back(k);   
                            }
                        else
                            {
                                nom.push_back(k);
                            }
                    }
            }
        
        if(won.size())                      //checks if they have won atleast one award
            {
            cout << "WON: " << endl;
            }
        else
            cout << "WON: nothing" << endl;
        for(int i=0; i<won.size(); i++)
            cout << oscarList[won[i]].category << " (" << oscarList[won[i]].year << ")" << endl;
        
        if(nom.size())                      //checks if they have been nominated atleast one award
            cout << "NOMINATED FOR: " << endl;
        else
            cout << "NOMINATED FOR: nothing" << endl;
        for(int j=0; j<nom.size(); j++)
            cout << oscarList[nom[j]].category << " (" << oscarList[nom[j]].year << ")" << endl;
        
    return 0;
}