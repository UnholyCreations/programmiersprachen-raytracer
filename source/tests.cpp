#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfloader.cpp" 
#include "ray.hpp"
#include "hit.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
#include <omp.h>
TEST_CASE("LoadMat", "[LoaderMat]")
{
}

int main(int argc, char *argv[])
{

int tid;
#pragma omp parallel for
for (unsigned int i=0; i<300; i++){
tid=omp_get_thread_num();
std::cout<<"i = "<<i <<" thread ="<<tid<<std::endl;
}






/*
	//1
  Scene loadedscene = sdf_loader();
	//2
	float x=89.0f;
	std::cout<<"x="<<x<<"\n";
	std::cout<<"cos(x)="<<std::cos(x*M_PI/180)<<"\n";
	std::cout<<"fixed cos(x)="<<std::fixed<<std::cos(x*M_PI/180)<<"\n";
	std::cout<<"scientific cos(x)="<<std::scientific<<std::cos(x*M_PI/180)<<"\n";
	*/
  return Catch::Session().run(argc, argv);
}
