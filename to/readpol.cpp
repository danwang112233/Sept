#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <math.h>
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

int sgn(double d)
{
      if(d<0) return -1;
      else if (d==0) return 0;
      else return 1;
}

//
int ReadLine(char *filename,int line, int nz, int natoms)  
{  
   
   double data[natoms][5];  
   double polar[5];

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
//cout << data[j][k] << " " << endl; 
             }
         }
         
   }
    ReadDump.close();
polar[0] = nz;
//cout<< polar[0] <<endl;
      for(int k = 2; k < 5; k++)
         {   int sum =0.0;
             for(int j = 0; j < natoms; j++)
             {
              sum += data[j][k];
              polar[k - 1] = sum;
		
             }
             //cout << polar[k-1] << " " << endl;
         }  
           polar[4] = sqrt(polar[2] * polar[2] + polar[2] * polar[2] + polar[3] * polar[3]) * sgn(polar[1]) * sgn(polar[2]) * sgn(polar[3]);

         /* for(int k = 0; k < 5; k++)
          {
            cout << polar[k] << endl;
           }*/
    return 0;  
}  

int main()  
{  
    
    clock_t t1, t2;
    t1 = clock();
    //char filename[]="polpldump_1";  
    //char finalname[]="polpldump_fin_1";
    char filename[]="displdump"; 
    int nz = 3;//
    int n = CountLines(filename);
    //int nf = CountLines(finalname);
    int natoms = 3;//10 * 10 * nz;    
    cout<<"number of lines："<< n <<"\n"<<endl;  
    //cout<<"number of lines："<< nf <<"\n"<<endl;
   
    
    file.open("polarization");
    ReadLine(filename, n, nz, natoms);
    //ReadLine(finalname, nf, nz, natoms);
    t2 = clock();
    cout<<"Time: "<< double (t2-t1)/CLOCKS_PER_SEC << " s."<<endl;
}  

