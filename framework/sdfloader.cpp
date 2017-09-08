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


Scene sdf_loader()
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
              if (keyword=="ambient")
                {  
                Color scene_ambience{0,0,0}; 
                ss>>scene_ambience.r;
                ss>>scene_ambience.g;
                ss>>scene_ambience.b;
                myscene.SceneAmbience=scene_ambience;
                }  
                if (keyword=="focal")
                {  
                ss>>myscene.dof_focal;
                }  

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
        }
            else if(keyword == "camera"){
  
            std::string name;
            int fov;
            ss>>name;
            ss>>fov;
            Camera temp_camera{name, fov};
            myscene.SceneCamera=temp_camera;
            }



                                     }
        //sdfloader kills braincells too ;D
        if(keyword == "transform")
        {
            ss>>keyword;
            //////////////////////////
            //CAMERA
            /////////////////////////
            if (myscene.SceneCamera.get_name()==keyword)
            {
                ss>>keyword;
                if(keyword == "rotate")
                {
                float angle;
                glm::vec3 axis;
                ss>>angle;
                ss>>axis.x;
                ss>>axis.y;
                ss>>axis.z;
                myscene.SceneCamera.CamRotate(angle,axis);
                }
                if(keyword == "translate")
                {
                glm::vec3 offset;
                ss>>offset.x;
                ss>>offset.y;
                ss>>offset.z;
                myscene.SceneCamera.CamTranslate(offset);
                }
                if(keyword == "scale")
                {
                float value;
                ss>>value;
                myscene.SceneCamera.CamScale(value);
                }
            }
            else
            //////////////////////////
            //CAMERA
            /////////////////////////
            for (int i=0;i<myscene.ShapeVector.size();i++)
                {   
                //std::cout<<"name "<<myscene.ShapeVector[i]->get_name()<<"\n";
                if (myscene.ShapeVector[i]->get_name()==keyword)
                    {
                    ss>>keyword;
                    if(keyword == "scale")
                        {
                        glm::vec3 value;
                        ss>>value.x;
                        ss>>value.y;
                        ss>>value.z;
                        myscene.ShapeVector[i]->ShapeScale(value);
                        }

                    }
                }

        }




 }}
//Print Stuff..
/*                                
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
std::cout<<"________________________________________________________________________________________\n";  
std::cout<<"\nPrint Loaded Ambience:\n";  
std::cout<<"________________________________________________________________________________________\n";  
myscene.Print_Ambience();
std::cout<<"________________________________________________________________________________________\n";  
std::cout<<"\nPrint Loaded Focal:\n";  
std::cout<<"________________________________________________________________________________________\n";  
myscene.Print_Focal();
*/

return myscene;
}
