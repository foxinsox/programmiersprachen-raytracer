#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "sdf_reader.hpp"

int main(int argc, char* argv[])
{

  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./raytracing.ppm";
  std::string const SDF_filepath = "../SDFFiles/testfile.sdf";

  SDFReader reader(SDF_filepath);
  bool read = reader.load();

  //SDF_scene:
  Scene scene = reader.scene();

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
