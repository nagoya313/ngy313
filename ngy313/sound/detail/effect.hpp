#pragma once
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include <XAPOBase.h>

namespace ngy313 { namespace sound { namespace detail {
struct xapo_delete {
  void operator ()(IXAPO * const com) const {
    assert(com);
    com->Release();
  }
};

template <typename Effect, typename Parameter>
class effect : public CXAPOParametersBase {
 public:
  effect() : CXAPOParametersBase(&kProperties_, reinterpret_cast<BYTE *>(&param_), sizeof(Parameter), FALSE),
             param_(),
             format_() {}

  STDMETHOD(LockForProcess)(UINT32 input_parmeter_count, 
                            const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS *input_parameter,
                            UINT32 output_parmeter_count,
                            const XAPO_LOCKFORPROCESS_BUFFER_PARAMETERS *output_parameter) {
    const HRESULT hr = CXAPOParametersBase::LockForProcess(input_parmeter_count,
                                                           input_parameter,
                                                           output_parmeter_count,
                                                           output_parameter);
    if (SUCCEEDED(hr)) {
      std::memcpy(&format_, input_parameter[0].pFormat, sizeof(*input_parameter[0].pFormat));
    }
    return hr;
  }

  STDMETHOD_(void, Process)(UINT32 input_parmeter_count, 
                            const XAPO_PROCESS_BUFFER_PARAMETERS *input_parameter,
                            UINT32 output_parmeter_count,
                            XAPO_PROCESS_BUFFER_PARAMETERS *output_parameter,
                            BOOL enabled) {
    assert(IsLocked());
    assert(input_parmeter_count == 1);
    assert(output_parmeter_count == 1);
    assert(input_parameter[0].pBuffer == output_parameter[0].pBuffer);
    Parameter *param = reinterpret_cast<Parameter *>(BeginProcess());
    if (input_parameter[0].BufferFlags == XAPO_BUFFER_SILENT) {
      std::memset(input_parameter[0].pBuffer, 
                  0,
                  input_parameter[0].ValidFrameCount * format_.nChannels * sizeof(FLOAT32));
      static_cast<Effect &>(*this).do_process(*param, 
                                              static_cast<float *>(input_parameter[0].pBuffer), 
                                              input_parameter[0].ValidFrameCount,
                                              format_.nChannels);
    } else if (input_parameter[0].BufferFlags == XAPO_BUFFER_VALID) {
      static_cast<Effect &>(*this).do_process(*param, 
                                              static_cast<float *>(input_parameter[0].pBuffer), 
                                              input_parameter[0].ValidFrameCount,
                                              format_.nChannels);
    }
    EndProcess();
  }

 private:
  static const XAPO_REGISTRATION_PROPERTIES kProperties_;
  Parameter param_;
  WAVEFORMATEX format_;
};

template <typename Effect, typename Parameter>
const XAPO_REGISTRATION_PROPERTIES effect<Effect, Parameter>::kProperties_ = {
  CLSID(),
  L"ngy313-effect",
  L"",
  1,
  0,
  XAPOBASE_DEFAULT_FLAG,
  1,
  1,
  1,
  1
};
}}}
