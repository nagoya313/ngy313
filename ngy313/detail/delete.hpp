#pragma once
#include <cassert>
#include <memory>
#include <Windows.h>
#include <XAudio2.h>

namespace ngy313 {
namespace detial {
struct handle_delete {
  void operator ()(const HANDLE handle) const {
    assert(handle && "ハンドルが不正");
    CloseHandle(handle);
  }
};

struct window_delete {
  void operator ()(const HWND window_handle) const {
    assert(window_handle && "ウィンドウハンドルが不正 ");
    DestroyWindow(window_handle);
  }
};

struct com_delete {
  void operator ()(IUnknown * const ptr) {
    assert(ptr && "COMポインタが不正");
    ptr->Release();
  }
};

struct mastering_voice_delete {
  void operator ()(IXAudio2MasteringVoice * const voice) {
    assert(voice && "マスターボイスポインタが不正");
    voice->DestroyVoice();
  }
};
}
}