#ifndef SDF_WRITER
#define SDF_WRITER
#include <string>
#include <iostream>
#include <fstream>

void write_frame_sdf(int i)
{
std::fstream fstr;
std::ofstream outfile ("frame"+std::to_string(i)+".sdf");
fstr.open("frame"+std::to_string(i)+".sdf", std::ios::out);


fstr << "# materials"<<"\n";
fstr << "define material blues 0 0 1 0 0 1 1 1 1 7"<<"\n";
fstr << "define material greenb 0 1 0 0 1 0 0 0 0 5"<<"\n";
fstr << "# geometry"<<"\n";

fstr << " define shape box box0 -25 -25 -25 25 25 25 greenb"<<"\n";
fstr << " define shape sphere sphere0 100 0 20 30 blues"<<"\n";
fstr << " define shape box box1 -25 -25 -25 25 25 25 greenb"<<"\n";
fstr << "#  transformationen"<<"\n";
fstr << " transform box0 translate 0 0 -650"<<"\n";
fstr << " transform sphere0 translate 0 60 130"<<"\n";
fstr << " transform box1 translate 0 -60 -600"<<"\n";
fstr << "#  scene xform"<<"\n";
fstr << "  lights"<<"\n";
fstr << " define light light1 -100 0 0 1.0 1.0 1.0 3"<<"\n";
fstr << " ambient 0.2 0.2 0.2"<<"\n";
fstr << "  camera"<<"\n";
fstr << " focal 0"<<"\n";
fstr << " define camera eye 120 -5 0 5 0 0 -1 0 1 0"<<"\n";
fstr << "  camera xform"<<"\n";
fstr << " transform eye rotate -45 1 0 0"<<"\n";
fstr << " transform eye translate 0 100 0"<<"\n";
fstr << " #scene animation"<<"\n";
fstr << "transform box0 translate 0 0 "<<i*6<<"\n";
fstr << "transform box0 rotate "<<i<<" 0 0 1"<<"\n";
fstr << "transform sphere0 translate 0 0 -"<<i*6<<"\n";
fstr << "transform box1 translate 0 0 "<<i*6<<"\n";
fstr << "transform box1 rotate "<<i<<" 0 0 1"<<"\n";
	/*
	loadedscene.ShapeVector[0]->ShapeTranslate({0,0,6}); box0 	
  loadedscene.ShapeVector[0]->ShapeRotate(1,{0,0,1}); box0 		
  loadedscene.ShapeVector[1]->ShapeTranslate({0,0,-6});	sphere0 	
  loadedscene.ShapeVector[2]->ShapeTranslate({0,0,6});	box1 	
  loadedscene.ShapeVector[2]->ShapeRotate(1,{0,0,1}); box01
	*/


fstr.close();
}
#endif 