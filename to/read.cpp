#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <time.h>

using namespace std;

int CountLines(char *filename)  
{  
    ifstream ReadDump;  
    int n=0;  
    string tmp;  
    ReadDump.open(filename, ios::in);
    if(ReadDump.fail())
    {  
        return 0;  
    }  
    else  
    {  
        while(getline(ReadDump,tmp,'\n'))  
        {  
            n++;  
        }  
       
        ReadDump.close();  
        return n;  
    }  
}  

//
int ReadLine(char *filename,int line, int natoms)  
{  
   
   double data[natoms][5];  
   double polar[3];

    ifstream ReadDump;  
    ReadDump.open(filename,ios::in);  
    
    
    if(ReadDump.fail())  
    {  
        cout << "No Displdump file, please check again." << endl;
        return 1;  
    }  
    
    for(int i = 0; i < line-natoms; ++i)
    {
        ReadDump.ignore (numeric_limits<streamsize>::max(),'\n' );
    }

    while (!ReadDump.eof())
   
  {  
         for(int j = 0; j < natoms; j++)
         {    
             for(int k = 0; k < 5; k++)
             {
              ReadDump >>  data[j][k];
             // cout << data[j][k] << " " << endl; 
             }
         }
         
   }
    ReadDump.close();
    for(int k = 2; k < 5; k++)
    {
    double sum = 0.0;
         for(int j = 0; j < natoms; j++)
         {
            sum += data[j][k];
            polar[0] = sum;
            cout << data[j][k] << " " << endl; 
         }
            cout << polar[0] << " " << endl;
   }
    return 0;  
}  

int main()  
{  
    
    clock_t t1, t2;
    t1 = clock();
    char filename[]="displdump";  
    int n = CountLines(filename);
    int natoms = 10;
    cout<<"number of lines："<< n <<"\n"<<endl;  
   
    ReadLine(filename, n, natoms);
    t2 = clock();
    cout<<"Time: "<< double (t2-t1)/CLOCKS_PER_SEC << " s."<<endl;
}  
//no problem

