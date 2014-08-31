#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "sdf_reader.hpp"

int main(int argc, char* argv[])
{

  unsigned  width = 600;
  unsigned  height = 600;
  std::string const filename = "./raytracing.ppm";
  std::string const SDF_filepath = "../SDFFiles/testfile.sdf";

  SDFReader reader(SDF_filepath);
  bool read = reader.load();

  //SDF_scene:
  Scene scene = reader.scene();

  std::shared_ptr<Renderer> app = reader.renderer();
  //Renderer app = reader.renderer();


  // Renderer app(width, height, filename, scene);

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
