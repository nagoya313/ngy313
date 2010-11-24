#pragma once
#include <stdexcept>
#include "com_fwd.hpp"

namespace ngy313 { namespace detail {
inline
font_handle create_font(const graphic_device_handle &graphic_device, const int size, const string_piece &font_name) {
  assert(graphic_device);
  LPD3DXFONT ft;
  if (FAILED(D3DXCreateFont(graphic_device.get(), 
                            size,
                            0,
                            FW_NORMAL, 
                            1,
                            FALSE,
                            SHIFTJIS_CHARSET,
                            OUT_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            DEFAULT_PITCH | FF_SWISS,
                            font_name.c_str(),
                            &ft))) {
    throw std::runtime_error("ÉtÉHÉìÉgÇÃçÏê¨Ç…é∏îsÇµÇ‹ÇµÇΩ");
  }
  return font_handle(ft);
}
}}