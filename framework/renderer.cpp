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
    {
    //focal_plane=scene_.SceneCamera.m_dir*m_focal;
    }

Renderer::Renderer(Scene const& scene):
    scene_(scene),
    colorbuffer_(scene.x_resolution*scene.y_resolution, Color{0,0,0}),
    ppm_(scene.x_resolution, scene.y_resolution, scene.file_name)
    {
    //focal_plane=scene_.SceneCamera.m_dir*m_focal;
    }

/*

void Renderer::render()
{
float startTime = omp_get_wtime();

//focal_plane=scene_.SceneCamera.m_dir*m_focal;
//focal_normal=-1.0f*glm::normalize(scene_.SceneCamera.m_dir*m_focal);
//std::cout<<"focal_plane "<<focal_plane.x<<" "<<focal_plane.y<<" "<< focal_plane.z<<"\n";
//std::cout<<"focal_normal "<<focal_normal.x<<" "<<focal_normal.y<<" "<< focal_normal.z<<"\n";
m_focal=scene_.dof_focal;
glm::vec3 pos=scene_.SceneCamera.m_pos;
//float intersectionDistance;
//glm::vec3 new_dir;
//glm::vec3 new_pos;
//bool intersect;



Ray plane_ray = scene_.SceneCamera.castray(0.0f,0.0f
      ,scene_.x_resolution, scene_.y_resolution);
focal_plane=m_focal*plane_ray.m_direction;
focal_normal=glm::normalize(-plane_ray.m_direction);
//std::cout<<"focal_plane:"<<focal_plane.x<<" "<<focal_plane.y<<" "<<focal_plane.z<<"\n";
//std::cout<<"focal_normal:"<<focal_normal.x<<" "<<focal_normal.y<<" "<<focal_normal.z<<"\n";
int x,y,xd,yd,xa,ya;
#pragma omp parallel for private(x,y,xd,yd,xa,ya) num_threads(8)
for (y = 0; y < scene_.y_resolution; ++y)
  { 
    //#pragma omp parallel for private(x) num_threads(2) 
    for (x = 0; x < scene_.x_resolution; ++x)
    {
    Pixel p(x,y);
      Ray camera_ray = scene_.SceneCamera.castray(float(x)-(scene_.x_resolution/2.0f),float(y)-(scene_.y_resolution/2.0f)
      ,scene_.x_resolution/2.0f, scene_.y_resolution/2.0f);
      float intersectionDistance;
      bool intersect=glm::intersectRayPlane(camera_ray.m_origin,camera_ray.m_direction,focal_plane,focal_normal,intersectionDistance);
      //if (intersect==1) {p.color =test;} 
        //std::cout<<"old dir: "<<camera_ray.m_direction.x<<" "<<camera_ray.m_direction.y<<" "<<camera_ray.m_direction.z<<"\n";
        //std::cout<<"new dir: "<<new_dir.x<<" "<<new_dir.y<<" "<<new_dir.z<<"\n";
        //int xd,yd;
        //#pragma omp parallel for private(xd) num_threads(2)
        //#pragma omp parallel for private(xd,yd) num_threads(2)
        for (xd=-5; xd<=5; xd+=5)
        {
        ////#pragma omp parallel for private(yd) num_threads(2)
        Color dof_color ={0.0f,0.0f,0.0f};
        for (yd=-5; yd<=5; yd+=5)
        {
        //Ray dof_ray = scene_.SceneCamera.castray(float(x)+xd-(scene_.x_resolution/2.0f),float(y)+yd-(scene_.y_resolution/2.0f)
        // ,scene_.x_resolution/2.0f, scene_.y_resolution/2.0f);  

        glm::vec3 new_pos={scene_.SceneCamera.m_pos.x+float(xd),scene_.SceneCamera.m_pos.y+float(yd),scene_.SceneCamera.m_pos.z};
        glm::vec3 new_dir=camera_ray.m_direction*intersectionDistance;
        new_dir={new_dir.x-xd,new_dir.y-yd,new_dir.z};
        new_dir=glm::normalize(new_dir);
        
        //Ray dof_ray{new_pos,new_dir};
        //dof_ray=dof_ray.transformRay(scene_.SceneCamera.m_worldtrans);
        //dof_color = raytrace(dof_ray);
        //p.color += dof_color*0.11f;
        
        
        for (xa=-1; xa<=1; xa+=1)
        {
        for (ya=-1; ya<=1; ya+=1)
        {
        Ray dof_ray{{new_pos.x+float(xa)*0.33f,new_pos.y+float(ya)*0.33f,new_pos.z},new_dir};
        dof_ray=dof_ray.transformRay(scene_.SceneCamera.m_worldtrans);
        Color dof_color = raytrace(dof_ray);
        p.color += dof_color*0.012345679f;
        }}
        


      
         }
       } 

        //std::cout<<"intersection distance"<<intersectionDistance<<"\n";
      


      //}}
      write(p);
    }
  }   
//ppm_.save("az");
/////////////////////////////////////////////////////////////////
float stopTime = omp_get_wtime();
std::cout<<"render execulation time: "<<stopTime - startTime<<"\n";
}
*/

Color Renderer::raytrace(Ray const& ray)
{
  Hit first_hit;
  Color pixel_color=Color{0,0,0};
  double shortest = INFINITY; 
  int shortest_obj_index;
  for (int i=0;i<scene_.ShapeVector.size();i++)
        {   
        Hit hit=scene_.ShapeVector[i]->intersect(ray);
        if(hit.m_hit == true)
        {
          if(hit.m_distance < shortest)
          {
          shortest = hit.m_distance;
          first_hit = hit;
          shortest_obj_index=i;
          }
        }
        };
  if(shortest == INFINITY)
  {
  pixel_color = Color{scene_.SceneAmbience.r,scene_.SceneAmbience.g,scene_.SceneAmbience.b};
  }
  else
  {
  pixel_color=shades(first_hit,shortest_obj_index);
  }
  return pixel_color;
}
Color Renderer::shades(Hit const& hit,const int index)
{

  Color Ia=addambient(hit);
  Color Ids=adddiffusespecular(hit,index);
  Color Ifog=addfog(hit,1000);
  Color I=Ia+Ids;
  I=gettonemapped(I);
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

Color Renderer::adddiffusespecular(Hit const& hit,const int index)
{
Color kd=hit.m_shape_ptr->get_material().m_kd;
float dotproduct =0.0f;
float Ip_RGB=0.0f;
Color ks=hit.m_shape_ptr->get_material().m_ks;
float m=hit.m_shape_ptr->get_material().m_m;
glm::vec3 internorm =hit.m_norm; //N

Color Id={0,0,0};
Color Is={0,0,0};
Color Ids={0,0,0};
Color UnShadows{1,1,1};
    for (int i=0;i<scene_.LightVector.size();i++)
        {
          glm::vec3 lightnorm =glm::normalize(scene_.LightVector[i].m_pos-hit.m_intersect);
          Ray shadowray {hit.m_intersect + lightnorm * 0.05f,lightnorm};
          shadowray.transformRay(hit.m_shape_ptr->get_worldtrans_inv());
          for (int i=0;i<scene_.ShapeVector.size();i++)
          {   
          Hit shadowhit=scene_.ShapeVector[i]->intersect(shadowray);
          float lightdistance= glm::distance(hit.m_intersect,scene_.LightVector[i].m_pos);
          if (shadowhit.m_distance<lightdistance ) { //works
              if (i!=index)
              {
              UnShadows={0.0f,0.0f,0.0f};
              break;
              }
           }
           else
           {
            UnShadows={1,1,1};
           };
          }
          
          dotproduct = glm::dot(internorm,lightnorm); 
          Ip_RGB=scene_.LightVector[i].m_brightness;
          Ip_RGB*=dotproduct;
          Id=Id+kd*Ip_RGB;
          glm::vec3 cameranorm =glm::normalize(hit.m_intersect-scene_.SceneCamera.m_pos); //V
          glm::vec3 reflect=2*glm::dot(internorm,lightnorm)*internorm-lightnorm; //R
          float RdotVpowM=pow(glm::dot(reflect,lightnorm),m);
          Ip_RGB=scene_.LightVector[i].m_brightness;
          Color Ip_RGB_mod={Ip_RGB*RdotVpowM,Ip_RGB*RdotVpowM,Ip_RGB*RdotVpowM};
          Is=Is+ks*Ip_RGB_mod;

          Ids=0.5f*(Ids+(Is+Id)*UnShadows);
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

void Renderer::render()
{
float startTime = omp_get_wtime();
glm::vec3 pos=scene_.SceneCamera.m_pos;
  int y,x; 
  #pragma omp parallel for private(y)
  for (y = 0; y < scene_.y_resolution; ++y)
  { 
    #pragma omp parallel for private(x)
    for (x = 0; x < scene_.x_resolution; ++x)
    {
    Pixel p(x,y);
      for (float xa=-0.2f; xa<=0.2f; xa+=0.2f) //am i mentally dead?
      {
      for (float ya=-0.2f; ya<=0.2f; ya+=0.2f)
      {
      Ray camera_ray = scene_.SceneCamera.castray(float(x)+xa-(scene_.x_resolution/2.0f),float(y)+ya-(scene_.y_resolution/2.0f)
      ,scene_.x_resolution/2.0f, scene_.y_resolution/2.0f);
      //Ray Plane intersection returns vec3
      //From pixels around x and y shoot rays through normalized returned vec3 and get intersections with objects

      Color pixel_color = raytrace(camera_ray);
      p.color += pixel_color*0.11;
      }}
      write(p);
    }
  }   
    ppm_.save(scene_.file_name);
    float stopTime = omp_get_wtime();
    std::cout<<"render execulation time: "<<stopTime - startTime<<"\n";
}



Color Renderer::gettonemapped(Color const& color)
{
Color temp;
temp.r = color.r/(color.r+1.0f);
temp.g = color.g/(color.g+1.0f);
temp.b = color.b/(color.b+1.0f);
return temp;
}