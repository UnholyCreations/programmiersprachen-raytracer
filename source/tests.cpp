#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <ostream>
#include "color.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "shape.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "scene.hpp"
#include "light.hpp"
#include <string>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <memory> 
TEST_CASE("LoadMat", "[LoaderMat]")
{
}

int main(int argc, char *argv[])
{
    Scene myscene;
 
  
    std::string line;
    std::ifstream file ("scene.sdf");
     if(file.is_open()){

      while(std::getline(file,line)){
        std::stringstream ss;
        std::string keyword;

        ss<<line;
        ss>>keyword;

        if(keyword == "define"){
          ss>>keyword;

          if(keyword == "material"){

            Color mat_get_ka{0,0,0};
            Color mat_get_kd{0,0,0};
            Color mat_get_ks{0,0,0};
            std::string mat_get_name;
            float mat_get_m;
            ss>>mat_get_name;

            ss>> mat_get_ka.r;
            ss>> mat_get_ka.g;
            ss>> mat_get_ka.b;
            ss>> mat_get_kd.r;
            ss>> mat_get_kd.g;
            ss>> mat_get_kd.b;
            ss>> mat_get_ks.r;
            ss>> mat_get_ks.g;
            ss>> mat_get_ks.b;
            ss>> mat_get_m;
            Material temp_mat(mat_get_name,mat_get_ka,mat_get_kd,mat_get_ks, mat_get_m);
            myscene.MaterialMap.insert({mat_get_name,temp_mat});
            }
            else if(keyword == "light")
            {
            std::string name;
            glm::vec3 LightPos;
            Color LightColor(0,0,0);
            float Brightness;
            ss>>name;
            ss>>LightPos.x;
            ss>>LightPos.y;
            ss>>LightPos.z;
            ss>>LightColor.r;
            ss>>LightColor.g;
            ss>>LightColor.b;
            ss>>Brightness;
            Light light(name,LightPos,LightColor,Brightness); 
            myscene.LightVector.push_back(light);   
            }
            else if(keyword == "shape"){
              ss>>keyword;
            if (keyword =="box")


            {
            std::string box_name;
            glm::vec3 box_min;
            glm::vec3 box_max;
            std::string mat_name;



            ss>> box_name;
            ss>> box_min.x;
            ss>> box_min.y;
            ss>> box_min.z;
            ss>> box_max.x;
            ss>> box_max.y;
            ss>> box_max.z;
            ss>> mat_name;
            
    
             
            std::shared_ptr<Shape> temp_ptr=std::make_shared<Box>(Box {box_name, myscene.MaterialMap[mat_name], box_min, box_max});
             myscene.ShapeVector.push_back(temp_ptr);
            
            
            }
            if (keyword =="sphere")
            {
            glm::vec3 sphere_center;
            double sphere_radius;
            std::string mat_name;
            std::string sphere_name;
            ss>> sphere_name; 
            ss>> sphere_center.x;
            ss>> sphere_center.y;
            ss>> sphere_center.z; 
            ss>> sphere_radius;
            ss>> mat_name;
            std::shared_ptr<Shape> temp_ptr=std::make_shared<Sphere>(
            Sphere (sphere_name,myscene.MaterialMap[mat_name],sphere_center,sphere_radius));
            myscene.ShapeVector.push_back(temp_ptr);
        
            }
            else if(keyword == "camera"){
  
            std::string name;
            int fov;
            float px, py, pz, dx, dy, dz, upx, upy, upz;
            ss>>name;
            ss>>fov;
            ss>>px;
            ss>>py;
            ss>>pz;
            ss>>dx;
            ss>>dy;
            ss>>dz;
            ss>>upx;
            ss>>upy;
            ss>>upz;
            glm::vec3 p{px, py, pz};
            glm::vec3 d{dx, dy, dz};
            glm::vec3 up{upx, upy, upz};
            Camera temp_camera{name, fov, p, d, up};
            myscene.SceneCamera=temp_camera;
            }



                                     }} }}
//Print Stuff..
std::cout<<"\n________________________________________________________________________________________"; 
std::cout<<"\nPrint Loaded Shapes:\n";  
std::cout<<"________________________________________________________________________________________\n";                                      
myscene.Print_Shapes();
std::cout<<"\n________________________________________________________________________________________"; 
std::cout<<"\nPrint Loaded Materials:\n";  
std::cout<<"________________________________________________________________________________________\n";  
myscene.Print_Materials();
std::cout<<"\n________________________________________________________________________________________"; 
std::cout<<"\nPrint Loaded Camera:\n";  
std::cout<<"________________________________________________________________________________________\n";  
myscene.Print_Camera();
std::cout<<"\n________________________________________________________________________________________"; 
std::cout<<"\nPrint Loaded Lights:\n";  
std::cout<<"________________________________________________________________________________________\n";  
myscene.Print_Lights();
  return Catch::Session().run(argc, argv);
}
