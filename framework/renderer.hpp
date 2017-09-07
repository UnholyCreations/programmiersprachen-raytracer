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
class Renderer
{
public:
  Renderer();
  Renderer(Scene const& scene);

  void render();
  void write(Pixel const& p);

  Color raytrace(Ray const& ray);  //Prozedural kommt hier
  Color shades(Hit const& hit);
  Color addambient(Hit const& hit);
   Color adddiffuse(Hit const& hit);
   Color addfog(Hit const& hit,float end);
  Color adddiffusespecular(Hit const& hit);
  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }
public:
float m_focal=0.0f;
glm::vec3 focal_plane;
glm::vec3 focal_normal={0,0,1};
private:
  Scene scene_;
  std::vector<Color> colorbuffer_;
  PpmWriter ppm_;

};

#endif // #ifndef BUW_RENDERER_HPP
