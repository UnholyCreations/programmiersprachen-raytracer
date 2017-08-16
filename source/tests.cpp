#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sdfloader.cpp" 
TEST_CASE("LoadMat", "[LoaderMat]")
{
}

int main(int argc, char *argv[])
{
  Scene loadedscene = sdf_loader();
  return Catch::Session().run(argc, argv);
}
