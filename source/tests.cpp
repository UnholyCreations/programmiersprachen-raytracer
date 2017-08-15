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
    //Temp Brackets
    {   
        Camera cam;
        std::cout<<"\n default name:"<<cam.get_name()<<"\n";
        std::cout<<"\n default fov:"<<cam.get_fov()<<"\n";
        glm::vec3 cam_pos=cam.get_pos(); 
        std::cout<<"\n default pos:"<<cam_pos.x<<" "<<cam_pos.y<<" "<<cam_pos.z<<"\n";
        glm::vec3 cam_dir=cam.get_dir(); 
        std::cout<<"\n default dir:"<<cam_dir.x<<" "<<cam_dir.y<<" "<<cam_dir.z<<"\n";
        glm::vec3 cam_upvec=cam.get_upvec(); 
        std::cout<<"\n default upvec:"<<cam_upvec.x<<" "<<cam_upvec.y<<" "<<cam_upvec.z<<"\n";
        Camera cam2("User_Camera",60,{0,0,0}, {0,-1,0}, {0,0,1});
        std::cout<<"\n default name:"<<cam2.get_name()<<"\n";
        std::cout<<"\n default fov:"<<cam2.get_fov()<<"\n";
        glm::vec3 cam2_pos=cam2.get_pos(); 
        std::cout<<"\n default pos:"<<cam2_pos.x<<" "<<cam2_pos.y<<" "<<cam2_pos.z<<"\n";
        glm::vec3 cam2_dir=cam2.get_dir(); 
        std::cout<<"\n default dir:"<<cam2_dir.x<<" "<<cam2_dir.y<<" "<<cam2_dir.z<<"\n";
        glm::vec3 cam2_upvec=cam2.get_upvec(); 
        std::cout<<"\n default upvec:"<<cam2_upvec.x<<" "<<cam2_upvec.y<<" "<<cam2_upvec.z<<"\n";
        } //will get deleted
 
  
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
            Material newmat(mat_get_name,mat_get_ka,mat_get_kd,mat_get_ks, mat_get_m);
            myscene.MaterialMap.insert({mat_get_name,newmat});


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
            
    
            //Temporary Brackets        
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

                                     }} }}
//Print Stuff..
std::cout<<"\n Print Loaded:\n";                                     
//myscene.Print_Shapes();

  return Catch::Session().run(argc, argv);
}
