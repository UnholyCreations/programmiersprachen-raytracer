#include <renderer.hpp>
#include <window.hpp>

#include <GLFW/glfw3.h>
#include <thread>
#include <utility>
#include <cmath>
#include "scene.hpp"
#include "sdfloader.cpp"
int main(int argc, char* argv[])
{
  unsigned const width = 640;
  unsigned const height = 480;
  std::string const filename = "./checkerboard.ppm";
  Scene loadedscene = sdf_loader();
  loadedscene.x_resolution=width;
  loadedscene.y_resolution=height;
  //loadedscene.x_resolution=height;
  //loadedscene.y_resolution=width;
  Renderer app(loadedscene);
  app.render(); 
  //std::thread thr([&app]() { app.render(); });

  Window win{glm::ivec2{width,height}};

  while (!win.should_close()) {
    if (win.get_key(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      win.close();
    }
    win.show(app.colorbuffer());
  }

  //thr.join();

  return 0;
}
