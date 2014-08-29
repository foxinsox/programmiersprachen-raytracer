#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "sdf_reader.hpp"

int main(int argc, char* argv[])
{

  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./raytracing.ppm";
  std::string const SDF_filepath = "../SDFFiles/testfile.txt";

  SDFReader reader(SDF_filepath);
  bool read = reader.load();

  //manuelle scene:
  Scene scene;


  //manuelle camera:
  Camera cam;
  scene.camera(cam);

  //licht:
  glm::vec3 lightPos(100,0,100);
  Color lightDiff(0.8f,0.8f,0.8f);
  Color lightAmb(0.6f,0.6f,0.6f);
  Light l(lightPos,lightDiff,lightAmb);
  scene.add_light(l);

  //manuelles material:
  Color ambCol0(1,0,1);
  Color diffCol0(0.8f,1,1);
  Color specCol0(0.2f,1,1);
  float specExp0(200.0f);
  auto mint = std::make_shared<Material>(ambCol0,diffCol0,specCol0,specExp0);
  
  Color ambCol1(0.1,0.1,0.1);
  Color diffCol1(0.5,0.5,1);
  Color specCol1(0.3);
  float specExp1(200.0f);
  auto blue = std::make_shared<Material>(ambCol1,diffCol1,specCol1,specExp1);

  Color ambCol2(0.1,0.1,0.1);
  Color diffCol2(1,0.2,0.2);
  Color specCol2(0.5);
  float specExp2(200.0f);
  auto red = std::make_shared<Material>(ambCol2,diffCol2,specCol2,specExp2);

  //manuelle formen:
  auto sphere = std::make_shared<Sphere>(blue);
  auto sphere2 = std::make_shared<Sphere>(mint);
  auto box = std::make_shared<Box>(red);
  glm::vec3 axisVector_z(0,0,1);
  float radians = M_PI/4;
  //sphere->scale(glm::vec3(0.2,0.2,0.2));      //0.2
  //sphere->translate(translationVector0);
  sphere->translate(glm::vec3(0,0,-10));
  sphere2->translate(glm::vec3(-1,-1,-11));
  box->rotate(radians,glm::vec3(1,1,0));
  box->scale(glm::vec3(0.2,0.2,0.2));
  box->translate(glm::vec3(1,-.1,-8));
  
  scene.add_shape(sphere);  
  scene.add_shape(sphere2);  
  scene.add_shape(box);



  Renderer app(width, height, filename, scene);

  std::thread thr([&app]() {
    app.render(); 
  });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
      , app.colorbuffer().data());

    win.update();
  }

  thr.join();
  return 0;
}
