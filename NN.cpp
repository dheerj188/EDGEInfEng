#include<iostream>

#include<cmath>

using namespace std;

void daxpy(double* W, double* bias, int rows, int columns, double Inp[], double Output[])
{
	int sum;
	
	for (int i=0; i<rows; i++)
		{
			sum=0;
			
			
			for (int j=0; j<columns; j++)
				
				{
					int del= *(W+columns*i+j);
					
					sum+=del*Inp[j];
				}
				
			Output[i]=sum+bias[i];
		}
}

double sigmoid(double z)
{
	double temp= exp(-z);
	
	double out= 1/(1+z);
	
	return out;
}

double sigmoid_prime(double z)
{
	double temp=exp(z);
	
	double out=z/((1+z)*(1+z));
	
	return out
}

double dc_dw(double a, double a_prev, double y_t, double z)
{
	double sig_prime=sigmoid_prime(z);
	
	double del_W= 2*(a-y_t)*sig_prime*a_prev;
	
	return del_W;
}

double dc_db(double a, double a_prev, double y_t)
{
	double sig_prime=sigmoid_prime(z);
	
	double del_B= 2*(a-y_t)*sig_prime;
	
	return del_B;
	
}


class Neural_Net
{
	private:
	
		double** Weight_Pointers;
		
		double** bias_pointers;
		
		double** activations;
			
	public:
	
	    int input_dim;
	    
		int output_dim;
		
		int Num_layers;
		
	    int* rows_dim;
	    
		int* cols_dim;
		
		Neural_Net(int input_d, int output_d, int Num_layer)
		{
			input_dim=input_d;
			
			output_dim=output_d;
			
			Num_layers=Num_layer;
		}
		
				
		void def_Neural_Net_arch()
		{
			/* Collect data, by invoking for loop */
			
			double** Weight_M_pointers=(double**) malloc((Num_layers-1)*sizeof(double));
			
			double** bias_V_pointers=(double**) malloc((Num_layers-1)*sizeof(double));
			
			double** activation=(double**) malloc((Num_layers-1)*sizeof(double));

			int* rows_d=(int*)malloc((Num_layers-1)*sizeof(int));
			
			int* cols_d=(int*)malloc((Num_layers-1)*sizeof(int));
			

			int m;
			
			int n;
			
			for(int i=0; i<Num_layers-1;i++)
				{
					cout<<"Enter "<<i+1<<"th layer dimension"<<endl;
					
					cin>>m>>n;
					
					Weight_M_pointers[i]=(double*)malloc(m*n*sizeof(double));
					
					bias_V_pointers[i]=(double*)malloc(m*sizeof(double));
					
					rows_d[i]=m;
					
					cols_d[i]=n;
				}
			
			Weight_Pointers=Weight_M_pointers;
			
			bias_pointers=bias_V_pointers;
			
			activations=activation;
			
			rows_dim=rows_d;
			
			cols_dim=cols_d;
		
			/*  Data collection complete*/
		
		}
		
		
		void forward(double* X)
		
		{
			double* in_p;
									
			in_p=X;
			
			for(int i=0; i<Num_layers-1;i++)
				
				{
					double* Out=(double*)malloc(rows_dim[i]*sizeof(double));
					
					daxpy(Weight_Pointers[i],bias_pointers[i],rows_dim[i],cols_dim[i],in_p,Out);
					
					activations[i]=Out;
					
					in_p=Out;
						
					
				}
		
		}					
};

	
int main()
{
	Neural_Net NN(3,3,4);	
	
	NN.def_Neural_Net_arch();
	
	double X[3]={1,1,1};
	
	NN.forward(X);
	
	
	return 0;
}

