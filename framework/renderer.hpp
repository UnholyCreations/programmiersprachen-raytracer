// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <glm/glm.hpp>
#include "scene.hpp"
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <time.h>
#include <omp.h>
#include <string>
#include "AABB.hpp"
class Renderer
{
public:
  Renderer();
  Renderer(Scene const& scene);

  void render(int frame);
  void write(Pixel const& p);
  bool intersectAABB(Ray const& ray);
  Color raytrace(Ray const& ray);  
  Color shades(Hit const& hit,Ray const& ray);
  Color addambient(Hit const& hit);
   Color adddiffuse(Hit const& hit);
   Color gettonemapped(Color const& color);
   Color addfog(Hit const& hit,float end);
  Color adddiffusespecular(Hit const& hit,Ray const& ray);
  glm::vec3 get_scene_max();
  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }
public:
float m_focal;
glm::vec3 focal_plane;
glm::vec3 focal_normal;
glm::vec3 max;
glm::vec3 min;
private:
  Scene scene_;
  std::vector<Color> colorbuffer_;
  PpmWriter ppm_;

};

#endif // #ifndef BUW_RENDERER_HPP
