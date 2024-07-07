/*  

Copyright: Center for Innovation and Entrepreneurship, PES University.

Author: Dheemanth R Joshi
Research Assistant, CIE, PES University 

 */

#include<iostream>

#include<fstream>

#include<cstring>

#include<sstream>

using namespace std;

// File operations for loading trained network parameters and images
 
	//LoadImage loads the test image to test the network inference 
	
 double* LoadImage(int M, int N, string FilePath)
 {
 	ifstream imagefile; 
 	
 	double value; 
 	
 	double* Image = (double*) malloc(M*N*sizeof(double));
 	
 	imagefile.open(FilePath); 
 	
 	for (int i = 0; i< M*N; i++)
 		{
 			imagefile >> value; 
 			
 			Image[i] = value; 

 		}
 		
 	imagefile.close();
 		
 	return Image; 

 }
 
 	// LoadWeights and LoadBiases loads the network parameters (weights and biases) from the text files. 
  
double* LoadWeights(int M, int N, string FilePath)

{
	
	ifstream weightfile; 
	
	double value;
	
	double* weights = (double*) malloc(M*N*sizeof(double));
	
	weightfile.open(FilePath);
	
	for (int i = 0; i < M*N; i++)
		
		{
			weightfile >> value; 
			
			weights[i] = value; 	
		}
		
	weightfile.close();
	
	return weights; 

}

double* LoadBiases(int N, string FilePath)

{
	ifstream biasfile; 
	
	double value;
	
	double* biases = (double*) malloc(N*sizeof(double));
	
	biasfile.open(FilePath);
	
	for (int i = 0; i < N; i++)
		
		{
			biasfile >> value; 
			
			biases[i] = value; 	
		}
		
	biasfile.close();
	
	return biases; 
}

// Forward pass parameters. 
 
 	// ReLU implemented in its vanilla form. 
 
 double* ReLU(int N, double* activations)
 {
 	for (int i = 0; i < N; i++)
 		
 		{
 			if(activations[i] > 0)
 				
 				{
 					activations[i] = activations[i]; 
 				}
 				
 			else
 				
 				{
 					activations[i] = 0; 
 				}
 				
 		}
 		
 	return activations; 
 }


	// LinearPass feed forwards the image for inference 
	
 double* LinearPass(int M, int N, double* inputs, double* weights, double* biases)

 {
 	
 	double* activations = (double*) malloc(N*sizeof(double)); 
 	
 	for (int i = 0; i < N; i++)
 	
 		{
 			for (int j = 0; j < M; j++)
 				
 				{
 					
 					activations[i] += weights[M * i + j] *  inputs[j]; 
 					
 				}
 				
 			activations[i] += biases[i]; 
 		}
 		
 	free(inputs);
 	
 	free(weights); 
 	
 	free(biases); 
 		
 	return activations; 
 
 }
  
int main()
{  
	// initialize network parameters (image dimensions and )
   
   int ImgDimx = 28;
	
   int ImgDimy = 28;
	
	int InLayerM = 784; 
	
	int InLayerN = 100;
	
	int HlM = 100;
	
    int HlN = 100; 
	
	int OutLayerM = 100; 
	
	int OutLayerN = 10;
	
	//load input image
	
	double* InputImage = LoadImage(ImgDimx, ImgDimy, "testimage.txt");
	
	//Load Input Layer Weights and Biases 
	
	double* InLayerWeights = LoadWeights(InLayerM, InLayerN, "in_layer_weights.txt");
	
	double* InLayerBiases = LoadBiases(InLayerN, "in_layer_biases.txt");
	
	//infer first layer. 
	
	double* activationsL1 = LinearPass(InLayerM, InLayerN, InputImage, InLayerWeights, InLayerBiases); 
	
	double* activationsL1R = ReLU(InLayerN, activationsL1);
	
	//load the weigths and biases for second layer.
		
	double* HlWeights = LoadWeights(HlM, HlN, "hl_layer_weights.txt");
	
	double* HlBiases = LoadBiases(HlN, "hl_layer_biases.txt"); 
	
	//infer the second layer. 
	
	double* activationsL2 = LinearPass(HlM, HlN, activationsL1R, HlWeights, HlBiases); 
	
	double* activationsL2R = ReLU(HlN, activationsL2);
	
	//load output layer weights and biases. 
	
    double* OutLayerWeights = LoadWeights(OutLayerM, OutLayerN, "out_layer_weights.txt");
	
	double* OutLayerBiases = LoadBiases(OutLayerN, "out_layer_biases.txt");
	
	//infer the output layer. Note that ReLU function is not used here. 
	
	double* activationsL3 = LinearPass(OutLayerM, OutLayerN, activationsL2R, OutLayerWeights, OutLayerBiases); 
	
	//print the response. 
	
	for (int i = 0; i < 10; i++)
		{
			std::cout<< activationsL3[i]<<std::endl;
		}
	
	free(activationsL3); 
	
	return 0; 
}