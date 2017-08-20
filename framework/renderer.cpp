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

  for (int y = 0; y < scene_.y_resolution; ++y)
  { 
    for (int x = 0; x < scene_.x_resolution; ++x)
    {
    Pixel p(x,y);
      Ray camera_ray = scene_.SceneCamera.castray(x-(scene_.x_resolution/2),y-(scene_.y_resolution/2)
      ,scene_.x_resolution/2, scene_.y_resolution/2);
      Color pixel_color = raytrace(camera_ray);
      p.color = pixel_color;
      write(p);
    }
  }   
    ppm_.save(scene_.file_name);
}

Color Renderer::raytrace(Ray const& ray)
{
  Hit first_hit;
  Color pixel_color=Color{0,0,0};
  double shortest = INFINITY; 
  for (int i=0;i<scene_.ShapeVector.size();i++)
        {   
        Hit hit=scene_.ShapeVector[i]->intersect(ray);
        if(hit.m_hit == true)
        {
          if(hit.m_distance < shortest)
          {
          shortest = hit.m_distance;
          first_hit = hit;
          }
        }
        };
  if(shortest == INFINITY)
  {
  pixel_color = Color{0,0,0};
  }
  else
  {
  pixel_color=shades(first_hit);
  }
  return pixel_color;
}
Color Renderer::shades(Hit const& hit)
{
  Color Ia=scene_.SceneAmbience;
  Color ka=hit.m_shape_ptr->get_material().m_ka;
  return Ia*ka;
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
