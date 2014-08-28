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
      if(i.hit){
        p.color = shade(ray,i);
      }
      else{
        //BackgroundColor
        Color white(1,1,1);
        p.color = white;
      }

      

      write(p);
    }
  }
  ppm_.save(filename_);
}

Intersection Renderer::trace(Ray const& ray)const{
  //strahl wird nach intersections abgecheckt. kleinste intersection wird zurückgegeben.


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

Color Renderer::shade(Ray const& ray, Intersection const& i)const{

  Color result(0.0f, 0.0f, 0.0f);
  auto p = ray.point_at(i.ray_parameter);
  auto lights = scene_.lights();
  auto material = i.material;
  auto eye_dir = -ray.direction;
auto normal = i.point; //glm::faceforward(i.n, ray.d, i.n);

//gehe alle Lichtquellen durch
for (auto const& light: lights) {
  auto light_dir = glm::normalize (light.position() - p);
  Ray shadow_ray(p + RAY_EPSILON * light_dir, light_dir, ray.depth);
  auto shadow_color = shadow(shadow_ray);
  if(!shadow_color.is_black()){
// diffuse light
    auto cos_phi = glm::dot (light_dir, normal);
    cos_phi = cos_phi > 0.0f ? cos_phi : 0.0f;
    result += cos_phi * (light.diff_term() * material->diffuse_color_);
// specular highlights
    auto reflect_light_dir = glm::normalize (glm::reflect (light_dir, normal));
    auto cos_beta = glm::dot (reflect_light_dir, eye_dir);
    cos_beta = cos_beta > 0.0f ? cos_beta : 0.0f;
    auto cos_beta_m = glm::pow (cos_beta, material->specular_exp_);
    result += cos_beta_m * (light.diff_term() * material->specular_color_);
  }
  result = shadow_color * result;
// ambient light
  result += light.amb_term() * material->ambient_color_;
}

/*  //TODO: Material anpassen
if (ray.depth > 0) {
// reflection
  Color reflected_color;
  if (material->is_reflective()) {
    auto d = glm::reflect (ray.d, normal);
    auto o = p + d * RAY_EPSILON;
    Ray reflected_ray(o, d, ray.depth-1);
    reflected_color = material->specular_color_ * shade(reflected_ray, trace(reflected_ray));
    result += reflected_color;
  }
// refraction
  if (material->transparency > 0.0f) {
    auto eta = material->n;
// inside the material?
    if (glm::dot(ray.d, isec.n) < 0.0f) {
      eta = 1.0f / eta;
    } else {
      normal *= -1;
    }
    auto d = glm::refract (ray.d, normal, eta);
    auto o = p + d * RAY_EPSILON;
// inner reflection
    if (d == glm::vec3(0.0f)) {
      return reflected_color;
    }
    Ray refracted_ray(o, d, ray.depth-1);
    result = (1.0f - material->transparency) * result;
    result += material->transparency * shade(refracted_ray, trace(refracted_ray));
  }
}
*/
return result;
}

Color Renderer::shadow(Ray const& ray) const{

  auto i = trace(ray);
  if (i.hit) {
    auto material = i.material;

/*
    //transparenz
    if (material->transparency > 0) {
      ray.o = ray.point_at(i.t) + RAY_EPSILON * ray.d;
      auto normal = glm::faceforward(i.n, ray.d, i.n);
      auto cos_phi = glm::dot(normal, ray.d);
//cos_phi = cos_phi >= 0.0f ? cos_phi : 0.0f;
      auto result = Color(1) - material->kd;;
      result *= material->transparency;
      result += material->kd;
      result *= cos_phi;
      if (result.is_black())
        return Color(0);
      else
        return result * shadow(ray);
    } else {
      */
      return Color(0);
    //}
    } else {
      return Color(1);
    }
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
