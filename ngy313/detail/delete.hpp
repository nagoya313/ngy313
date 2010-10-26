#pragma once
#include <cassert>
#include <memory>
#include <Windows.h>
#include <XAudio2.h>

namespace ngy313 {
namespace detial {
struct handle_delete {
  void operator ()(const HANDLE handle) const {
    assert(handle && "�n���h�����s��");
    CloseHandle(handle);
  }
};

struct window_delete {
  void operator ()(const HWND window_handle) const {
    assert(window_handle && "�E�B���h�E�n���h�����s�� ");
    DestroyWindow(window_handle);
  }
};

struct com_delete {
  void operator ()(IUnknown * const ptr) {
    assert(ptr && "COM�|�C���^���s��");
    ptr->Release();
  }
};

struct mastering_voice_delete {
  void operator ()(IXAudio2MasteringVoice * const voice) {
    assert(voice && "�}�X�^�[�{�C�X�|�C���^���s��");
    voice->DestroyVoice();
  }
};
}
}