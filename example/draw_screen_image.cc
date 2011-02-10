#include <random>
#include <vector>
#include <boost/range/algorithm/generate.hpp>
#include <ngy313/process/process.hpp>
#include <ngy313/window/window.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/graphic/pixel.hpp>
#include <ngy313/graphic/render_target.hpp>
#include <ngy313/graphic/sprite.hpp>
#include <ngy313/utility/color_code.hpp>

// デバイスロストからの復帰後画面が真っ黒になってしまうのは現状仕様
int main() {
  ngy313::window::show();
  const ngy313::graphic::render_target target(640.f, 480.f);
  {
    const ngy313::graphic::scoped_render_target new_render(target);
    const ngy313::graphic::scoped_render render;
    if (render.succeeded()) {
      std::random_device rnd;
      std::vector<std::uint_least32_t> v(10);
      boost::generate(v, std::ref(rnd));
      std::mt19937 engine(std::seed_seq(v.begin(), v.end())) ;
      std::uniform_real_distribution<float> distribution_x(0.f, 640.f);
      std::uniform_real_distribution<float> distribution_y(0.f, 480.f);
      ngy313::graphic::clear_screen(ngy313::utility::kBlack);
      for (int i = 0; i < 1000; ++i) {
        ngy313::graphic::draw(ngy313::graphic::pixel(distribution_x(engine), distribution_y(engine)));
      }
    }
  }
  return ngy313::process::run([&] {
    {
      const ngy313::graphic::scoped_render render;
      if (render.succeeded()) {
        ngy313::graphic::clear_screen(ngy313::utility::kBlack);
        ngy313::graphic::draw(ngy313::graphic::sprite(0.f, 0.f, target));
      }
    }
    ngy313::graphic::present();
  });
}