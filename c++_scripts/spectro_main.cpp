#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <complex>
#include <fftw3.h>
#include <iterator>
#include <cmath>
#include <gnuplot-iostream.h>
//#include <cstdio>
#include <map>
#include <thread>
#include <chrono>
#include <fstream>
#include <bitset>
#include <stdio.h>
#include "spectro.h"

//run with following flags: -lfftw3 -lm -lboost_iostreams -lboost_filesystem -lboost_system 



using namespace std;

/*long getFileSize(FILE *file) {
	
	long lCurPos, lEndPos;
	lCurPos = ftell(file);
	fseek(file, 0, 2);
	lEndPos = ftell(file);
	fseek(file, lCurPos, 0);
	return lEndPos;
}


//this_thread::sleep_for(chrono::seconds());
int main(int argc, char** argv) {
	

typedef unsigned char BYTE;
const char *filePath = "/media/sf_WINLAB/exp2.bin"; 

    BYTE *fileBuf;          // Pointer to our buffered data

    FILE *file = NULL;      // File pointer

 

    // Open the file in binary mode using the "rb" format string

    // This also checks if the file exists and/or can be opened for reading correctly

    if ((file = fopen(filePath, "rb")) == NULL)

        cout << "Could not open specified file" << endl;

    else

        cout << "File opened successfully" << endl;
// Get the size of the file in bytes

    long fileSize = getFileSize(file);

 

    // Allocate space in the buffer for the whole file

    fileBuf = new BYTE[fileSize];

 

    // Read the file in to the buffer

    fread(fileBuf, fileSize, 1, file);

 

    // Now that we have the entire file buffered, we can take a look at some binary infomation

    // Lets take a look in hexadecimal

    for (int i = 0; i < fileSize; i++)

        printf("%X ", fileBuf[i]);

 

    cin.get();

    delete[]fileBuf;

        fclose(file);   // Almost forgot this
*/




int main () {

Gnuplot gp;

ifstream file ("exp2.bin", fstream::binary); //| fstream::ate);

//file.seekg(0, file.end);
//int length = file.tellg();
//cout<<length<<endl;
file.seekg(0, file.beg);

char* buffer = new char[sizeof(float)];

if (file) {
    cout<<"File opened successfully"<<endl;
}
else {
    cout<<"Error opening file"<<endl;

}

float* floats;

double reals;
double imags;

int i = 0;
vector<complex<double> > y;
while(i < 20*80000) {

file.read(buffer, sizeof(float));
floats = (float*)buffer;
if (i % 2 == 0) {
    reals = (*floats);
    //cout<<reals<<" ";
}

else {
    imags = (*floats);
    //cout<<imags<<'\n';
    y.push_back(complex<double>(reals,imags));
    //cout<<"hello"<<endl;
}
i++;
//if (i % 10000 == 0) {
  //  cout<< i/2 <<endl;
//}
}




//cout.write(buffer, sizeof(float));

file.close();




//Gnuplot gp; 
float pi = acos(-1);

//vector<complex<double> > samples (10000,complex<double>(0,0));
/*for (unsigned int i = 0; i < samples.size(); i++) {
	float f = 50*sin(2*pi*i/10);
	samples.at(i) = complex<double> (f,f);
}*/
//samples[4] = complex<float>(300,300);
//vector<complex<double> > samples (10,complex<double>(10,0));
double c_freq = 800e6;
double s_freq = 10e6;
unsigned int fftsize = 40000;
double overlap = 0;
vector<complex<double> > window (40000,complex<double>(1,0));
unsigned int av = 1;

fft_avg ob(y, c_freq, s_freq, fftsize, overlap, window, av);
ob.spectro();
vector<vector<double> >* x = ob.get_fft_data();

/*for (auto I = x->begin(); I < x->end(); I++) {
	for (auto J = I->begin(); J < I->end(); J++){
		cout<<(*J)<<" ";
	}
	cout<<endl;
} */
gp << "set terminal x11\n";
//gp << "set zero 1e-20\n";

vector<pair<double,double> > xy_pts_A;
for (auto I = x->begin(); I < x->end(); I++) {
	for (int i = 0; i < I->size(); i++) {
		//gp << i << " " << x->at(0).at(i) <<'\n';
		xy_pts_A.push_back(make_pair(i,20*log10((I->at(i))/1000.0)));
}
//gp << "plot '-' with lines\n";
//gp << "clear\n";
gp << "plot '-' binary" << gp.binFmt1d(xy_pts_A, "record") << "with lines notitle\n";
//gp.send1d(xy_pts_A);
gp.sendBinary1d(xy_pts_A);
gp.flush();
this_thread::sleep_for(chrono::milliseconds(1000));

xy_pts_A.clear();
}
//gp << " 1 3 \n";
//gp << " 3 4 \n";
//gp << "e\n";

delete[] buffer;
return 0;
}
