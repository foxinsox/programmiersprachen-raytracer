// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
// Edited by  : Alexander Pospischil
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"


Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene)
: width_(w)
, height_(h)
, colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
, filename_(file)
, ppm_(width_, height_)
, scene_(scene)
{}

void Renderer::render()
{
  //auflösung durchgehen, für jeden Pixel create_ray aufrufen.

  Camera cam = scene_.camera();

  for (unsigned h = 0; h < height_; ++h) {
    for (unsigned w = 0; w < width_; ++w) {

//von screen(auflösungs)-Koordinaten in Kamera-Koordinaten umrechnen:
      double image_aspect_ratio = width_/height_;
      double alph = M_PI/4;  //TODO: automatisieren!
      double pixelNormalizedX = (w+0.5)/width_;
      double pixelNormalizedY = (h+0.5)/height_;
      double pixelRemappedX = 2*pixelNormalizedX-1;
      double pixelRemappedY = 1 - 2*pixelNormalizedY;
      double pixelCameraX = (2*pixelRemappedX - 1)*image_aspect_ratio*tan(alph/2);
      double pixelCameraY = (1 - 2*pixelRemappedY)*tan(alph/2);
      glm::vec2 screen_coord(pixelCameraX,pixelCameraY);
      Pixel p(pixelCameraX,pixelCameraY);
      int rayDepth = 1000; //TODO: automatisieren!

      //primary-rays erzeugen!
      Ray ray = cam.generate_ray_at(screen_coord, rayDepth);

      //primary tracing:
      Intersection i = trace(ray);

      write(p);
    }
  }
  ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
    << "pixel out of ppm_ : "
    << (int)p.x << "," << (int)p.y
    << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}
