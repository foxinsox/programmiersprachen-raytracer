#include <thread>
#include <chrono>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "sdf_reader.hpp"

int main(int argc, char* argv[])
{

bool use_window = true;

std::string SDF_filepath;
if(argc>=2){
  SDF_filepath = argv[1];
  if (argc>=3 && strcmp(argv[2], "--no-window") == 0) {
    use_window = false;
  } else {
    std::cout << "ERROR: unknown flag '" << argv[2] << "'" << std::endl;
  }
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
    auto begin = std::chrono::high_resolution_clock::now();
    app->render(); 
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
    std::cout << "rendered frame in " << duration << "ms" << std::endl;
  });

  if (use_window) {

    Window win(app->dimension());
    



    while (!win.shouldClose()) {
      if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
        win.stop();
      }

      glDrawPixels( app->dimension().x, app->dimension().y, GL_RGB, GL_FLOAT
          , app->colorbuffer().data());

      win.update();
    }
  }

  thr.join();
  return 0;
}
