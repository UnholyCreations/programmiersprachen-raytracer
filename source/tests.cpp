#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfloader.cpp" 
#include "ray.hpp"
#include "hit.hpp"
#include <glm/glm.hpp>
#include <iostream>
#include <cmath>
TEST_CASE("LoadMat", "[LoaderMat]")
{
}

int main(int argc, char *argv[])
{
  Scene loadedscene = sdf_loader();
	/*
	float x=89.0f;
	std::cout<<"x="<<x<<"\n";
	std::cout<<"cos(x)="<<std::cos(x*M_PI/180)<<"\n";
	std::cout<<"fixed cos(x)="<<std::fixed<<std::cos(x*M_PI/180)<<"\n";
	std::cout<<"scientific cos(x)="<<std::scientific<<std::cos(x*M_PI/180)<<"\n";
	*/
  return Catch::Session().run(argc, argv);
}
