// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <random>
Renderer::Renderer():
    scene_(),
    colorbuffer_(scene_.x_resolution*scene_.y_resolution, Color{0,0,0}),
    ppm_(scene_.x_resolution, scene_.y_resolution, "default_constrtor_img.ppm")
    {}

Renderer::Renderer(Scene const& scene):
    scene_(scene),
    colorbuffer_(scene.x_resolution*scene.y_resolution, Color{0,0,0}),
    ppm_(scene.x_resolution, scene.y_resolution, scene.file_name)
    {}


void Renderer::render()
{
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < (scene_.y_resolution); ++y) {
    std::uniform_real_distribution<float> distribution(0.0,1.0);
    std::default_random_engine generator;
    for (unsigned x = 0; x < (scene_.x_resolution); ++x) {
      Pixel p(x,y);
      if (x%32==0)
      {
      p.color=Color(1,1,1);
      }
      else
      {
        if (y%32==0)
        {
        p.color=Color(1,1,1);  
        }  
        else
        {
      p.color=Color(0,0,0); 
        }
      };
              
      
  
      
      write(p);
    }
  }
  ppm_.save(scene_.file_name);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (scene_.x_resolution*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
