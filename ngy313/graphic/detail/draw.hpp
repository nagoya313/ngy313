#pragma once
#include <cassert>
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/graphic/detail/scoped_addressing.hpp>
#include <ngy313/graphic/detail/scoped_blend.hpp>
#include <ngy313/graphic/detail/scoped_texture_stage.hpp>
#include <ngy313/graphic/detail/texture.hpp>
#include <ngy313/graphic/drawable_access.hpp>

namespace ngy313 { namespace graphic { namespace detail {
// �N���X�ł���K�v�����Ȃ���������Ȃ�
template <typename Drawable>
class draw : private boost::noncopyable {
 public:
  draw(const device_handle &device, const Drawable &drawable) : device_(device), drawable_(drawable) {
    common_draw();
  }

 private:
  void common_draw() const {
    assert(device_);
    // ��̃N���X���W�J���ꂽ�Ƃ��œK���������邩�R�c
    const scoped_addressing<typename Drawable::addressing_tuple_type> addressing(device_);
    const scoped_blend<typename Drawable::blend_pair_type> blend(device_);
    set_texture(device_, drawable_);
    const auto vertex = drawable_access::copy_vertex(drawable_);
    device_->SetFVF(Drawable::fvf_type::fvf_type::value);
    device_->DrawPrimitiveUP(Drawable::primitive_type::type::value,
                             Drawable::count_type::value, 
                             &(vertex.front()), 
                             sizeof(vertex.front()));
  }

  const device_handle &device_;
  const Drawable &drawable_;
};
}}}
