#include <iostream>
#include <cmath>
#include <TH1D.h>
#include <TFile.h>
#include <TRandom3.h>
#include "FunctionFromTable/FunctionFromTable.h"
#include <vector>
#include <fstream>
#include <string>

void print(std::vector <double> &a) {
	std:cout << " ";
	for (int i = 0; i < a.size(); i++) {
		std::cout << a.at(i) << " ";
	}
}
int main() {
	vector <double> energyAcceptanceValues{}; //energy values for real E beam
	vector <double> TotalEnergyValues{}; //energy values for flat beam
	vector <double> probability{}; //all probability for all energy values for real beam
	vector <double> attenuationLength{}; // attenuation length vector
	vector <double> acceptedProbability{}; //probability of photons that passed through materials as probability vector is full
	vector <double> finalPhotonEnergy{};   // energy values for the photons that passed through the material 
	vector <double> randomNumber3{};


// Open output file (apparently needs to be done before booking)

  TFile file("simpleMC.root", "recreate");

// Book histograms, i.e., create TH1D objects
// 1st argument is a string; by convention same as object name
// 2nd argument is histogram title (will appear on plots)
// 3rd argument is number of bins (type int)
// 4th and 5th arguments:  upper and lower limits of histogram (type double)
  //TH1D h_Uniform1("h_Uniform1", "Random Number", 100, 0, 1);
  //TH1D h_Uniform2("h_Uniform2", "Generated Photon Energies ", 100, 0, 1e4);
  TH1D h_Uniform3("h_Uniform3", " Energy values of photons that passed through material", 100, 0, 1.1e3);

// Create a TRandom3 object to generate random numbers
  int seed = 12345;
  TRandom3 ran(seed);

double scale1 = 1.e12; //scalefactor
double scale2 = 1.e-3;
FunctionFromTable edist("FunctionFromTable/data.txt", scale1);
FunctionFromTable mdist("FunctionFromTable/lengthData.txt", scale2);

// Generate some random numbers and fill histograms

  const int numValues = 1000000;
  for (int i=0; i<numValues; ++i){
    double r1 = ran.Rndm();             // uniform in [0,1]
	double r2 = ran.Rndm();
	double Emax = 1e4;
	double Fmax = 2e13 /scale1 ;
	//std::cout << "r1 = " << r1  << "\n";
	//std::cout << "r2 = " << r2 << "\n";
	//std::cout << "Emax = " << Emax << "\n";
	//std::cout << "Fmax = " << Fmax << "\n";
	double E = r1 * Emax;
	//h_Uniform1.Fill(r1);
	//std::cout << "E = " << E << "\n";
	TotalEnergyValues.push_back(E);
	double f = (r2 * Fmax);
	double y = edist.val(E);
	//std::cout << "f = " << f << "\n"; 
	//std::cout << i << " y = " << y << "\n";
	
	if (f < y) {
		energyAcceptanceValues.push_back(E);
		double attenLength = mdist.val(E);
		attenuationLength.push_back(attenLength);
		//h_Uniform2.Fill(E);
		if (numValues < 120) {
			//std:cout << " Energy value is accepted. vector updated ";
			//std::cout << "\n" << i << " f = " << f << "\n";
			//std::cout << i << " y = " << y << "\n";
			//std::cout << i << " E = " << E << "\n";
			//std::cout << " i index = " << i << "" << " energy values = " << E ;
			//std::cout << " attentuation length value = " << attenLength << "\n" ;
		}
		//h_Uniform2.Fill(E);
		//h_Uniform3.Fill(energyValues);
		
		}
	}
    int counter = energyAcceptanceValues.size(); 
  
  for (int n = 0; n < counter; ++n) {
	  //define r3 which is a random number 
	  double r3 = ran.Rndm();
	  //std::cout << "\nr3 = " << r3;
	  //define x which is thickness of material
	  double x = 1000; // 1mm
	  //define P which is the probability of energy E absorbed before x
	  double p = 1-exp(-x/attenuationLength[n]);
	  //std::cout<< "\n P = " << p ;
	  //1
	  probability.push_back(p);
	  //std::cout << "\n" << " For photon:" << n << " ,energy value = " << energyAcceptanceValues[n] << " ,Probability for photon being absorbed = " << p << "\n";
	  if (r3 > p) {
		acceptedProbability.push_back(p);
		finalPhotonEnergy.push_back((energyAcceptanceValues[n]));
		randomNumber3.push_back(r3);
		h_Uniform3.Fill(energyAcceptanceValues[n]);
		//std:cout << n ; //7
		//std::cout << "The photon has made it through the material " ;
		//Now i want to save the photons that made it through the material so i want to know these photons energy values!
		//std::cout << " index of n " << n << "attenuation length value = " << attenuationLength[n] << "Energy values = "<< energyAcceptanceValues[n] ;
	  }


	   }
  // Store all histograms in the output file and close up
  //std::cout<< counter1 << " photons got absorbed by the material";
  std::cout << "\n";
  std::cout << "size of flat energy beam = " << TotalEnergyValues.size();
  std::cout << "\n";
  std::cout << "size of real energy beam = " << energyAcceptanceValues.size();
  std::cout << "\n";
  //std::cout << "probability vector = " << probability;
  //std::cout << "attenuation length vector size = " << attenuationLength.size() << "\n" ;
  //std::cout<< "Attenuation length vector contents below: \n" ;
  //print(attenuationLength);
  //std::cout<< " \n Probability vector contents below: \n" ;
  //print(probability);
  //std::cout << "size of total probability vector = " << probability.size();
  std::cout << " \n " ;
  std::cout << " accepted photon probability vector size  " << acceptedProbability.size();
  std::cout << " \n " ;
  if (acceptedProbability.size() >0) {
		//std::cout << "Final probability values: \n" ;
		//print(acceptedProbability);
  }
  std::cout << "\n accepted photon energy value size " << finalPhotonEnergy.size();
  std::cout << " \n " ;
  if (finalPhotonEnergy.size() > 0) {
	//std::cout << "Final photon energy value vector: \n" ;
	//print(finalPhotonEnergy);
  }
  //std::cout<< "\n  non zero values of attenuation length \n";
  for (int index = 0; index < attenuationLength.size(); index++) {
	if (attenuationLength[index] > 0) {
		//std::cout << attenuationLength[index] << "\n";
	}
  }
  //std::cout << "random number values \n";
  //print(randomNumber3);


  file.Write();
  file.Close();

  return 0;
}
