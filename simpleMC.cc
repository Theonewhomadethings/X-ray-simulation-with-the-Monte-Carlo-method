// Program to illustrate use of ROOT random number and histogram classes
// Glen Cowan, RHUL, Physics, November 2007

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
	vector <double> thickness{1, 0.1, 0.01, 2, 10, 0.5, 0.05, 5, 7, 3}; //units of mm
	vector <double> meanEnergy{7153, 4618, 3764, 6789, 8283, 5627, 4296, 7658, 7975, 7175}; //units of eV
	vector <double> meanEnergy2{}; //meanenergy calculated by reading value of of root histogram value output.
	vector <double> standardDeviation2{}; //standard deviation calculated by reading value of root histogram value


// Open output file (apparently needs to be done before booking)

  TFile file("simpleMC.root", "recreate");

// Book histograms, i.e., create TH1D objects
// 1st argument is a string; by convention same as object name
// 2nd argument is histogram title (will appear on plots)
// 3rd argument is number of bins (type int)
// 4th and 5th arguments:  upper and lower limits of histogram (type double)
  //TH1D h_Uniform1("h_Uniform1", "Random Number", 100, 0, 1); //random number distribution histogram 
  //TH1D h_Uniform2("h_Uniform2", "Generated Photon Energies ", 100, 0, 1e4); //generated photon energies initial histogram
  TH1D h_Uniform3("h_Uniform3", " Energy values of 10 million photons that passed through Berylium of thickness x = 5mm", 100, 0, 1e4); //energy values of photons which pass through berylium material.

// Create a TRandom3 object to generate random numbers
  int seed = 12345;
  TRandom3 ran(seed);

double scale1 = 1.e12; //scalefactor
FunctionFromTable edist("FunctionFromTable/data.txt", scale1); //defining 2 function from table variables and referenceing data to use method for.
FunctionFromTable mdist("FunctionFromTable/lengthData.txt"); //

// Generate some random numbers and fill histograms

  const int numValues = 1000000;
  for (int i=0; i<numValues; ++i){
    double r1 = ran.Rndm();             // random number between 0 and 1
	double r2 = ran.Rndm(); 			//random number between 0 and 1 
	double Emax = 1e4;					//emax value from visual inspection of largest E value in data.txt graph
	double Fmax = 2e13 /scale1 ;		//fmax value from visual inspection of peak of graph from data.txt
	//std::cout << "r1 = " << r1  << "\n";
	//std::cout << "r2 = " << r2 << "\n";
	//std::cout << "Emax = " << Emax << "\n";
	//std::cout << "Fmax = " << Fmax << "\n";  //lines 63-66 debugging purposes
	double E = r1 * Emax;					    // E variable defined
	//h_Uniform1.Fill(r1);
	//std::cout << "E = " << E << "\n";
	TotalEnergyValues.push_back(E);					// Current E values of flat histogram stored in TotalEnergyValues vector
	double f = (r2 * Fmax);							// f variable defined
	double y = edist.val(E);						// y variable defined and obtained by using functionfromtable class above
	//std::cout << "f = " << f << "\n"; 
	//std::cout << i << " y = " << y << "\n";
	
	if (f < y) {		// IMPORTANTif point(E, F) is below curve, accept E as the generated photon energy. otherwise repeat until a value is accepted.
		energyAcceptanceValues.push_back(E);
		double attenLength = mdist.val(E);			//uses function from table class
		attenuationLength.push_back(attenLength);		//saves this current attenuation length data in a vector and is looped over in this loop until iterations are comeplete
		//h_Uniform2.Fill(E);								
		if (numValues < 120) {			//DEBUGING purposes IGNORE BELOW CODE
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
    int counter = energyAcceptanceValues.size();  //variable to use size of real energy values vector size as limit for loop below
  
  for (int n = 0; n < counter; ++n) {
	  //define r3 which is a random number between 0 and 1
	  double r3 = ran.Rndm();
	  //std::cout << "\nr3 = " << r3;
	  //define x which is thickness of material
	  double x = 5000; 
	  //define P which is the probability of energy E absorbed before x
	  double p = 1-exp(-x/attenuationLength[n]);
	  //std::cout<< "\n P = " << p ;
	  //1
	  probability.push_back(p);
	  //std::cout << "\n" << " For photon:" << n << " ,energy value = " << energyAcceptanceValues[n] << " ,Probability for photon being absorbed = " << p << "\n";
	  if (r3 > p) {			//IMPORTANT if r<p then photon is absorbed. if not it makes it through. SO i used if r>p then photon passes through material.
		acceptedProbability.push_back(p);	//saves current probability value in vector
		finalPhotonEnergy.push_back((energyAcceptanceValues[n]));   //saves current photon energy value as a vector
		randomNumber3.push_back(r3);			
		h_Uniform3.Fill(energyAcceptanceValues[n]); //saving the photons which passed through the material in the histogram plot
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
  std::cout << "\n" ;
  std::cout << "accepted photon probability vector size  " << acceptedProbability.size();
  std::cout << " \n " ;
  if (acceptedProbability.size() >0) {
		//std::cout << "Final probability values: \n" ;
		//print(acceptedProbability);
  }
  std::cout << "\naccepted photon energy value size " << finalPhotonEnergy.size();
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



