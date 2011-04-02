#ifndef NGY313_GRAPHIC_DETAIL_LINUX_DARW_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_DRAW_HPP_
#include <GL/gl.h>
#include <boost/noncopyable.hpp>
#include <boost/mpl/at.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/detail/linux/graphic_device.hpp>
//#include <ngy313/graphic/detail/scoped_addressing.hpp>
//#include <ngy313/graphic/detail/scoped_blend.hpp>
//#include <ngy313/graphic/detail/scoped_texture_stage.hpp>
#include <ngy313/graphic/detail/linux/texture.hpp>
#include <ngy313/graphic/detail/linux/scoped_enable.hpp>
#include <ngy313/graphic/drawable_access.hpp>
#include <ngy313/graphic/fvf_traits.hpp>

namespace ngy313 { namespace graphic { namespace detail {
// クラスである必要性がないかもしれない
template <typename Drawable>
class draw : private boost::noncopyable {
 public:
  draw(const device_handle &device, const Drawable &drawable) : /*device_(device), */drawable_(drawable) {
    common_draw();
  }

 private:
  void common_draw() const {
    // fvf値からちゃんとEnableするものを選ぶ
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    const auto vertex = drawable_access::copy_vertex(drawable_);
    scoped_list<fvf_traits<typename boost::mpl::at<typename Drawable::list_type, fvf_key>::type>::fvf_type::value> list(vertex);
    //boost::fusion::result_of::as_vector<enable_list>::type enable_list(vertex);
    //glVertexPointer(3, GL_FLOAT, sizeof(vertex.front()), &vertex_member_at<position>(vertex[0]).x);
    //glColorPointer(4, GL_FLOAT, sizeof(vertex.front()), &vertex_member_at<diffuse>(vertex[0]).r);
    //glTexCoordPointer(2, GL_FLOAT, sizeof(vertex.front()), &vertex_member_at<tex>(vertex[0]).tex_array[0].u);
    glDrawArrays(boost::mpl::at<typename Drawable::list_type, primitive_key>::type::type::value,
                   0,
                 boost::mpl::at<typename Drawable::list_type, size_key>::type::type::value);
    set_texture(drawable_);
    //glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    /*
    assert(device_);
    // 空のクラスが展開されたとき最適化がかかるか審議-mplなしの現状かかる
    // テクスチャステージとアドレッシングはmplのvectorにしてmplのfor_eachで回す
    const scoped_texture_stage<typename Drawable::list_type> texture_stage(device_);
    const scoped_addressing<typename Drawable::list_type> addressing(device_);
    const scoped_blend<typename Drawable::list_type> blend(device_);
    set_texture(device_, drawable_);
    const auto vertex = drawable_access::copy_vertex(drawable_);
    device_->SetFVF(fvf_traits<typename boost::mpl::at<typename Drawable::list_type, fvf_key>::type>::fvf_type::value);
    device_->DrawPrimitiveUP(boost::mpl::at<typename Drawable::list_type, primitive_key>::type::type::value,
                             boost::mpl::at<typename Drawable::list_type, count_key>::type::type::value, 
                             vertex.data(), 
                             sizeof(vertex.front()));*/
  }

  //const device_handle &device_;
  const Drawable &drawable_;
};
}}}

#endif

