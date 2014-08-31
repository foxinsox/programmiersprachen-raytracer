#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "sdf_reader.hpp"

int main(int argc, char* argv[])
{

std::string SDF_filepath;
if(argc>=2){
SDF_filepath = argv[1];
}
else{
std::cout<<"ERROR: no File to be opened"<<std::endl;
return 0;
}

  SDFReader reader(SDF_filepath);
  bool read = reader.load();

  Scene scene = reader.scene();

  std::shared_ptr<Renderer> app = reader.renderer();

  std::thread thr([&app]() {
    app->render(); 
  });

  Window win(app->dimension());
  



  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( app->dimension().x, app->dimension().y, GL_RGB, GL_FLOAT
        , app->colorbuffer().data());

    win.update();
  }

  thr.join();
  return 0;
}
