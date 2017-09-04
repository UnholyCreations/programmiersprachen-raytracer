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
glm::vec3 pos=scene_.SceneCamera.m_pos;

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
  pixel_color = Color{scene_.SceneAmbience.r,scene_.SceneAmbience.g,scene_.SceneAmbience.b};
  }
  else
  {
  pixel_color=shades(first_hit);
  }
  return pixel_color;
}
Color Renderer::shades(Hit const& hit)
{
  Color Ia=addambient(hit);
  Color Ids=adddiffusespecular(hit);
  Color Ifog=addfog(hit,2000);
  //Color Id=adddiffuse(hit);
  Color I=Ia+Ids+Ifog;
  return I;

}
Color Renderer::addfog(Hit const& hit,float end)
{
  float distance;
  if (hit.m_shape_ptr->get_type()==0)
  {
  distance=hit.m_distance;
  }
  if (hit.m_shape_ptr->get_type()==1)
  {
  distance=hit.m_distance*2.5;
  }

  float end_inv=1/end;
  Color Ifog={distance*end_inv,distance*end_inv,distance*end_inv};
return Ifog;
}


Color Renderer::addambient(Hit const& hit)
{
  Color Ia=scene_.SceneAmbience;
  Color ka=hit.m_shape_ptr->get_material().m_ka;

return Ia*ka;
}
/*
Color Renderer::adddiffuse(Hit const& hit)
{
Color kd=hit.m_shape_ptr->get_material().m_kd;
Color Id={0,0,0};
float anglecosine = 0.0f;
float dotproduct =0.0f;
float Ip_RGB=0.0f;
glm::vec3 internorm =glm::normalize(hit.m_norm); 
for (int i=0;i<scene_.LightVector.size();i++)
        {
          glm::vec3 lightnorm =glm::normalize(hit.m_intersect-scene_.LightVector[i].m_pos);
          dotproduct = glm::dot(internorm,lightnorm); 
          anglecosine = cos(acos(dotproduct));
          Ip_RGB=scene_.LightVector[i].m_brightness;
          Color Ip_mit_cos{Ip_RGB*dotproduct,Ip_RGB*dotproduct,Ip_RGB*dotproduct};
         Id=Id+kd*Ip_mit_cos;
       }
return Id*kd;
}
*/

//https://stackoverflow.com/questions/31064234/find-the-angle-between-two-vectors-from-an-arbitrary-origin#31064328
//Never forget the credit ;)

Color Renderer::adddiffusespecular(Hit const& hit)
{
Color kd=hit.m_shape_ptr->get_material().m_kd;
Color Id={0,0,0};
float anglecosine = 0.0f;
float dotproduct =0.0f;
float Ip_RGB=0.0f;
Color ks=hit.m_shape_ptr->get_material().m_ks;
float m=hit.m_shape_ptr->get_material().m_m;
Color Is={0,0,0};
glm::vec3 internorm =hit.m_norm; //N
Color Ids={0,0,0};
Color UnShadows{1,1,1};
    for (int i=0;i<scene_.LightVector.size();i++)
        {
          glm::vec3 lightnorm =glm::normalize(scene_.LightVector[i].m_pos-hit.m_intersect);
          Ray shadowray {hit.m_intersect + lightnorm * 0.01f,lightnorm};
          for (int i=0;i<scene_.ShapeVector.size();i++)
          {   
          Hit shadowhit=scene_.ShapeVector[i]->intersect(shadowray);
          float lightdistance= glm::distance(hit.m_intersect,scene_.LightVector[i].m_pos);
          if (shadowhit.m_distance<lightdistance ) { //works
          //if (shadowhit.m_hit==true ) {
              UnShadows={0,0,0};
              break;
            
           }
           else
           {
            UnShadows={1,1,1};
           };
          }
          
          dotproduct = glm::dot(internorm,lightnorm); 
          anglecosine = cos(acos(dotproduct));
          Ip_RGB=scene_.LightVector[i].m_brightness;
          Color Ip_mit_cos{Ip_RGB*anglecosine,Ip_RGB*anglecosine,Ip_RGB*anglecosine};
         Id=Id+kd*Ip_mit_cos;
          glm::vec3 cameranorm =glm::normalize(hit.m_intersect-scene_.SceneCamera.m_pos); //V
          glm::vec3 reflect=2*glm::dot(internorm,lightnorm)*internorm-lightnorm; //R
          float RdotVpowM=pow(glm::dot(reflect,lightnorm),m);
          Ip_RGB=scene_.LightVector[i].m_brightness;
          Color Ip_RGB_mod={Ip_RGB*RdotVpowM,Ip_RGB*RdotVpowM,Ip_RGB*RdotVpowM};
          Is=Is+ks*Ip_RGB_mod;

          Ids=(Is+Id)*UnShadows;
        }
    return Ids;
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
