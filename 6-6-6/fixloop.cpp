#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
using namespace std;
int main(int argc,char **argv)
{
	clock_t t1, t2;
	t1 = clock();
	if(argc != 4) 
		{
		cout << "Usage: ./fixloop ne_min ne_max delta.\n" << "ne_min and ne_max are the min and max number your loop used in infile of lammps\n" << "delta is the number multipled the min and the max number to get the final loop of electric strength." << endl;
		}
	else
		{
			int ne_min = atoi(argv[1]);
			int ne_max = atoi(argv[2]);
			double delta = atof(argv[3]);
			const char *filename = "loop.in";
			ofstream fout(filename, ios::out|ios::trunc);
			for(int i = ne_min; i < ne_max +1; ++i)
			{
				
				double exf = double(i) * delta;
				double ex = exf / sqrt(3.0);
				double ey = exf / sqrt(3.0);
				double ez = exf / sqrt(3.0);
				
	
//fix npt/nph has tilted box too far in one step - periodic cell is too far from equilibrium state (../fix_nh.cpp:1197)

				fout << "fix AVE_LAT all ave/time 1 10000 20000 v_lla v_llb v_llc file ave_lat" << endl;
				fout << "fix AVE_ATOM all ave/atom 1 10000 20000 c_dr[1] c_dr[2] c_dr[3]" << endl;
				fout << "dump core_displ_" << i << " all custom 20000 displcoredump id type f_AVE_ATOM[1] f_AVE_ATOM[2] f_AVE_ATOM[3]" << endl;
				fout <<"variable TEMP equal temp" << endl;
				fout <<"fix AVE_T all ave/time 1 10000 20000 v_TEMP file ave_temp"  << endl;
				fout << "fix ef all efield " << ex << " " << ey << " " << ez << endl;
				fout << "print \" electric field strength = " << exf << " .\"" << endl;
				fout << "fix_modify ef energy yes " << endl;
				fout <<"#-------------------------------------------------MD SIMULATION SETTINGS" << endl;
				fout <<"velocity all create 10 146981634 dist gaussian mom yes rot no bias yes temp CSequ" << endl;

				fout <<"timestep 0.00001" << endl;

				fout <<"velocity all scale 10 temp CSequ" << endl;
				fout << "print \" 1.\"" << endl;
				fout <<"fix NPT all npt temp 10 10 0.1 x 1.0 1.0 0.1 y 1.0 1.0 0.1 xy 0.0 0.0 0.1 couple none" << endl;
				fout << "print \" 2.\"" << endl;
				fout <<"fix_modify NPT temp CSequ" << endl;
				fout << "print \" 3.\"" << endl;
				fout <<"run 10000" << endl;
				fout << "print \" 4.\"" << endl;
				fout <<"unfix NPT" << endl;
				fout << "print \" 5.\"" << endl;
				fout <<"fix NPT all npt temp 10 10 0.1 x 1.0 1.0 0.1 y 1.0 1.0 0.1 xy 0.0 0.0 0.1 couple none" << endl;
				fout <<"fix_modify NPT temp CSequ" << endl;
				fout <<"run 10000" << endl;
				fout <<"unfix NPT" << endl;
				//fout << "reset_timestep 0" << endl;

				/*fout << "min_style fire" << endl;
				fout << "minimize 0.0 1e-05 30000 100000" << endl;	
				fout << "unfix ef" << endl;
				fout << "min_style quickmin" << endl;
				fout << "minimize 0.0 1e-04 30000 100000" << endl;
				fout <<"unfix NPT" << endl;
				fout <<"min_style fire" << endl;
				fout <<"minimize 0.0 1e-05 60000 100000" << endl;
				fout << "print \" 6.\"" << endl;*/
/*				fout <<"compute pol all polar/atom" << endl;
				fout <<"reset_timestep 0" << endl;
				fout <<"dump dump_pol all custom 100 poldump id type c_pol[1] c_pol[2] c_pol[3]" << endl;*/
				fout << "unfix ef" << endl;
				fout <<"unfix AVE_T" << endl;
				fout <<"unfix AVE_ATOM" << endl;
				fout <<"unfix AVE_LAT" << endl;
				
			}
			fout.close();
			return 0;
		}



}
