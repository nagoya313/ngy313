#include <exception>
#include <boost/assert.hpp>
#include <ngy313/process/process.hpp>
#include <ngy313/window/message_box.hpp>
#include <ngy313/graphic/shape.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/utility/color_code.hpp>

using namespace ngy313;

namespace {
const auto kClearColor = utility::kBlack;
const auto kShapeColor = utility::kWhite;
}

int main() {
  try {
    return process::run([] {
      {
        const graphic::scoped_render render;
        if (render.succeeded()) {
          graphic::clear_screen(kClearColor);
          const float pixel_x = 64.f;
          const float pixel_y = 120.f;
          const graphic::pixel pixel(pixel_x, pixel_y, kShapeColor);
          graphic::draw(pixel);
          BOOST_ASSERT(pixel.x() == pixel_x && pixel.y() == pixel_y);
          const float line_x[] = {130.f, 254.f};
          const float line_y[] = {2.f, 238.f};
          const graphic::line line(line_x[0], line_y[0], line_x[1], line_y[1], kShapeColor);
          graphic::draw(line);
          BOOST_ASSERT(line.x1() ==line_x[0] && line.y1() == line_y[0] && line.x2() == line_x[1] && line.y2() == line_y[1]);
          const float triangle_x[] = {320.f, 382.f, 258.f};
          const float triangle_y[] = {2.f, 238.f, 238.f};
          const graphic::triangle triangle(triangle_x[0], 
                                           triangle_y[0],
                                           triangle_x[1],
                                           triangle_y[1],
                                           triangle_x[2],
                                           triangle_y[2],
                                           kShapeColor);
          graphic::draw(triangle);
          BOOST_ASSERT(triangle.x1() == triangle_x[0] && triangle.y1() == triangle_y[0] && 
                       triangle.x2() == triangle_x[1] && triangle.y2() == triangle_y[1] &&
                       triangle.x3() == triangle_x[2] && triangle.y3() == triangle_y[2]);
          const float line_triangle_x[] = {448.f, 510.f, 386.f};
          const float line_triangle_y[] = {2.f, 238.f, 238.f};
          const graphic::line_triangle line_triangle(line_triangle_x[0], 
                                                     line_triangle_y[0],
                                                     line_triangle_x[1], 
                                                     line_triangle_y[1], 
                                                     line_triangle_x[2],
                                                     line_triangle_y[2],
                                                     kShapeColor);
          graphic::draw(line_triangle);
          BOOST_ASSERT(line_triangle.x1() == line_triangle_x[0] && line_triangle.y1() == line_triangle_y[0] && 
                       line_triangle.x2() == line_triangle_x[1] && line_triangle.y2() == line_triangle_y[1] &&
                       line_triangle.x3() == line_triangle_x[2] && line_triangle.y3() == line_triangle_y[2]);
          const float box_x = 514.f;
          const float box_width = 124.f;
          const float box_y = 2.f;
          const float box_height = 236.f;
          const graphic::box box(box_x, box_y, box_width, box_height, kShapeColor);
          graphic::draw(box);
          BOOST_ASSERT(box.width() == box_width && box.height() == box_height);
          const float line_box_x = 2.f;
          const float line_box_width = 124.f;
          const float line_box_y = 242.f;
          const float line_box_height = 236.f;
          const graphic::line_box line_box(line_box_x, line_box_y, line_box_width, line_box_height, kShapeColor);
          graphic::draw(line_box);
          BOOST_ASSERT(line_box.width() == line_box_width && line_box.height() == line_box_height);
          const float circle_x = 192.f;
          const float circle_y = 360.f;
          const float circle_r = 62.f;
          const graphic::circle circle(circle_x, circle_y, circle_r, kShapeColor);
          graphic::draw(circle);
          BOOST_ASSERT(circle.x() == circle_x && circle.y() == circle_y && circle.r() == circle_r);
          const float line_circle_x = 320.f;
          const float line_circle_y = 360.f;
          const float line_circle_r = 62.f;
          const graphic::line_circle line_circle(line_circle_x, line_circle_y, line_circle_r, kShapeColor);
          graphic::draw(line_circle);
          BOOST_ASSERT(line_circle.x() == line_circle_x && line_circle.y() == line_circle_y && line_circle.r() == line_circle_r);
          const float oval_x = 448.f;
          const float oval_y = 360.f;
          const float oval_rx = 62.f;
          const float oval_ry = 118.f;
          const graphic::oval oval(oval_x, oval_y, oval_rx, oval_ry, kShapeColor);
          graphic::draw(oval);
          BOOST_ASSERT(oval.x() == oval_x && oval.y() == oval_y && oval.rx() == oval_rx && oval.ry() == oval_ry);
          const float line_oval_x = 576.f;
          const float line_oval_y = 360.f;
          const float line_oval_rx = 62.f;
          const float line_oval_ry = 118.f;
          const graphic::line_oval line_oval(line_oval_x, line_oval_y, line_oval_rx, line_oval_ry, kShapeColor);
          graphic::draw(line_oval);
          BOOST_ASSERT(line_oval.x() == line_oval_x && line_oval.y() == line_oval_y && line_oval.rx() == line_oval_rx && line_oval.ry() == line_oval_ry);
        }
      }
      graphic::present();
    });
  } catch(const std::exception &error) {
    window::message_box(error.what(), "error", window::kButtonOk, window::kIconStop);
    return 0;
  }
}