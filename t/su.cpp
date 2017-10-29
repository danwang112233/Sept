#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 3) 
		{
		cout << "Usage: ./readpol filename ne_min.\n" << "filename is the file name you need to read.\n" << "ne_min is the min number your loop used in infile of lammps.\n" << "nz is the number of unit cells in the z-direction." << endl;
		}
	else
		{	
			char *filename = argv[1];
        		int ne_min = atoi(argv[2]);
			//int ne_max = atoi(argv[3]);
			//int nz = atoi(argv[4]);
			string temp;
			int lo = ne_min -1;

			ifstream input;
			input.open(filename, ios::in);

			
			
			while(!input.eof())
			{
char *a = new char[strlen("polarization_") +  sizeof(lo)];
			sprintf(a, "%s%d", "polarization_", lo);
			ofstream output(a, ios::out|ios::trunc);

				getline(input, temp);
			output << temp << endl;
				cout << temp<< endl;
				//output << temp << endl;
				/*while(temp != "0")
				//if(temp == "0")
{
					
					
				
output << temp << endl;
					cout << temp<< endl;
getline(input, temp);	

					//break;
					//output << temp << endl;
					
					//output << lo << endl;
						
				}//
		//else{getline(input, temp);output<<temp<<endl;}
output << temp << endl;*/
				//getline(input, temp);

				
				
					delete []a;
					output.close();
					//lo = lo +1;
					//break;
			}
			//output.close();
			input.close();
		}


}
