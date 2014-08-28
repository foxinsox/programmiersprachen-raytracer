#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>

int main(int argc, char* argv[])
{
  
  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./raytracing.ppm";


  //manuelle scene:
  Scene scene;
  Camera cam;
  auto mat = std::make_shared<Material>();
  auto sphere = std::make_shared<Sphere>(mat);
  scene.camera(cam);
  scene.add_shape(sphere);  



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
