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
  Color adddiffusespecular(Hit const& hit);
  
  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  Scene scene_;
  std::vector<Color> colorbuffer_;
  PpmWriter ppm_;

};

#endif // #ifndef BUW_RENDERER_HPP
