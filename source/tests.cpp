#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <ostream>
#include "color.hpp"
#include "box.hpp"
#include "sphere.hpp"
#include "shape.hpp"
#include "material.hpp"
#include "scene.hpp"
#include <string>
#include <fstream> 
#include <sstream>
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <memory> 
Material find_mat(std::vector<Material> vec,std::string mat_name)
  {
    Material put_mat;
            for (Material i : vec)

            {
              if (i.m_name==mat_name){Material put_mat=i; 
                //std::cout<<"works\n";
                 return put_mat;}
              
            }
            return put_mat;
}


TEST_CASE("LoadMat", "[LoaderMat]")
{
}

int main(int argc, char *argv[])
{
    Scene myscene;
  std::vector<Shape> ShapeVec;
 
  
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
            //Material loadmat(mat_get_name,mat_get_ka,mat_get_kd,mat_get_ks, mat_get_m);
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
            
    
            
            std::shared_ptr<Shape> temp_ptr=std::make_shared<Box>(Box (box_name, myscene.MaterialMap[mat_name], box_min, box_max));
               //std::cout<<"pointers at push"<<temp_ptr.use_count();
             myscene.ShapeVector.push_back(temp_ptr);
            //box.print(std::cout);
            
            }
            if (keyword =="sphere")
            {
            //std::cout<<"keyword sphere  \n";
            glm::vec3 sphere_center;
            double sphere_radius;
            std::string mat_name;
            std::string sphere_name;
            ss>> sphere_name; 
            //std::cout<<"sphere name:"+sphere_name+"\n";
            ss>> sphere_center.x;
            ss>> sphere_center.y;
            ss>> sphere_center.z; 
            ss>> sphere_radius;
            ss>> mat_name;
            //std::cout<<"put_mat: "+put_mat.m_name<<"\n";
            std::shared_ptr<Shape> temp_ptr=std::make_shared<Sphere>(
            Sphere (sphere_name,myscene.MaterialMap[mat_name],sphere_center,sphere_radius));
            myscene.ShapeVector.push_back(temp_ptr);
            //sphere.print(std::cout);
            }

                                     }} }}
//Print Stuff..
//std::cout<<"pointers"<<temp_ptr.use_count();
std::cout<<"\n Print Loaded:\n";                                     
myscene.Print_Shapes();

  return Catch::Session().run(argc, argv);
}
