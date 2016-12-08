#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iterator>
#include<chrono>
#include<ctime>
#include<time.h>
using namespace std;



int N; 
int numThreads; 

int Call(int col, int rowM, int dia1, int dia2) 
{
        if(col==N)
        {
                return 1; 
        }
    
    int row= 0; 
    int ans= 0; 
    
    for(row=0;row<N;row++)
            {
                if(!(rowM & (1<<row)) & !(dia1 & (1<<(row+col))) & !(dia2 & (1<<((row+N-1)-col))))
                            {
                                
                                    ans+= Call(col+1, rowM | 1<<row, dia1 | (1<<(row+col)), dia2 | (1<<((row+N-1)-col))); 
                            }
            }
    
            return ans; 
    
}


                                double parallel()
                                {
                                    double st= omp_get_wtime(); 
                                    int ans=0; 
                                    int i; 
                                    int rowM=0,dia1=0,dia2=0; 
                                    
                                    
                                    
                                    
                                    #pragma omp parallel for reduction(+:ans) shared(i,rowM)
                                                
                                                for(i=0;i<N;i++)
                                                        {
                                                            rowM=0; 
                                                            dia1=0, dia2=0; 
                                                            int col=0, row=i; 
                                                            
                                                      ans+=Call(1,rowM |1<<row,dia1 | (1<<(row+col)),dia2|(1<<((row+N-1)-col)));     
                                                            
                                                        }
                                
                                                printf("Found %d config for n=%d\n", ans,N); 
                                                double en= omp_get_wtime(); 
                                                printf("Time %1f\n", en-st); 
                                                
                                                return en-st; 
                                    
                                    
                                }
                                
                                
            int main(int argc, char ** argv)
            {
                if(argc==3)
                {
                
                
                N=atof(argv[1]); 
                numThreads=atof(argv[1]); 
                omp_set_num_threads(numThreads);
                double ptime= parallel(); 
                
                }
                
                
                
            }
            