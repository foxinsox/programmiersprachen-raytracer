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

  glm::vec2 res(width_, height_);

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {

//von screen(auflösungs)-Koordinaten in Kamera-Koordinaten umrechnen:
      glm::vec2 pos(x,y);
      glm::vec2 sample_pos = pos / res;
      
      int rayDepth = 1000; //TODO: automatisieren!

      //primary-rays erzeugen!
      Ray ray = cam.generate_ray_at(sample_pos, rayDepth);

      //primary tracing:
      Intersection i = trace(ray);

      Pixel p(x, y);
      
      //first test:
      if(i.hit == true){
        Color black(0,0,0);
        p.color = black;
      }
      else{
        Color white(1,1,1);
        p.color = white;
      }

      //shade!!

      write(p);
    }
  }
  ppm_.save(filename_);
}

Intersection Renderer::trace(Ray const& ray)const{
  //strahl wird nach intersections abgecheckt. kleinste intersection wird zurückgegeben.
  const float RAY_EPSILON = 0.01f;

  auto i = scene_.root().intersect_with(ray);
  // avoid too short ray intersections
  if (i.ray_parameter < RAY_EPSILON) {
    auto direction = ray.direction;
    auto origin = ray.origin + RAY_EPSILON * direction;
    Ray new_ray(origin, direction, ray.depth);
    i = scene_.root().intersect_with(new_ray);
  }
  return i;
}

Color Renderer::shade(Ray const& r, Intersection const& isec)const{
  //TODO: implement!
  Color c(0,0,0);
  return c;
}

Color Renderer::shadow(Ray const& r) const{
  //TODO: implement!
  Color c(0,0,0);
  return c;
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
