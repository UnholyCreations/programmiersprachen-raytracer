#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "scene.hpp"
#include "sdfloader.cpp"
#include "sdfwriter.hpp"
#include <fstream>
#include <iostream>
#include <string>
int main(int argc, char* argv[])
{
  unsigned const width = 640;
  unsigned const height = 480;
  Scene loadedscene = sdf_loader("animationstart.sdf");
  loadedscene.x_resolution=width;
  loadedscene.y_resolution=height;
  //loadedscene.x_resolution=height;
  //loadedscene.y_resolution=width;




  Renderer app(loadedscene);
  //app.render(1); 
  for (int i=1;i<141;i++)
  {
  loadedscene.ShapeVector[0]->ShapeTranslate({0,0,6});	
  loadedscene.ShapeVector[0]->ShapeRotate(1,{1,1,1});	
  loadedscene.ShapeVector[1]->ShapeTranslate({0,0,6});	
  loadedscene.ShapeVector[2]->ShapeTranslate({0,0,6});	
  loadedscene.ShapeVector[2]->ShapeRotate(1,{1,1,1});
  write_frame_sdf(i);




  app.render(i);
  }
  //std::thread thr([&app]() { app.render(); });
  /*
  Window win{glm::ivec2{width,height}};

  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }
    win.show(app.colorbuffer());
  }
	*/
  //thr.join();

  return 0;
}
