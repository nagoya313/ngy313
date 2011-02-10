#pragma once
#include <cstdint>
#include <d3d9.h>

namespace ngy313 { namespace graphic {
typedef D3DTEXTUREOP texture_option;

const texture_option kTextureOptionDisable = D3DTOP_DISABLE;
const texture_option kTextureOptionSelectArg1 = D3DTOP_SELECTARG1;
const texture_option kTextureOptionModulate = D3DTOP_MODULATE;
const texture_option kTextureOptionModulate2 = D3DTOP_MODULATE2X;
const texture_option kTextureOptionModulate4 = D3DTOP_MODULATE4X;
const texture_option kTextureOptionAdd = D3DTOP_ADD;
const texture_option kTextureOptionAddSigned = D3DTOP_ADDSIGNED;
const texture_option kTextureOptionAddSigned2 = D3DTOP_ADDSIGNED2X;
const texture_option kTextureOptionSubtract = D3DTOP_SUBTRACT;
const texture_option kTextureOptionAddSmooth = D3DTOP_ADDSMOOTH;
const texture_option kTextureOptionBlendDiffuseAlpha = D3DTOP_BLENDDIFFUSEALPHA;
const texture_option kTextureOptionBlendTextureAlpha = D3DTOP_BLENDTEXTUREALPHA;
const texture_option kTextureOptionBlendFactorAlpha = D3DTOP_BLENDFACTORALPHA;
const texture_option kTextureOptionBlendTextureAlphaPM = D3DTOP_BLENDTEXTUREALPHAPM;
const texture_option kTextureOptionBlendCurrentAlpha = D3DTOP_BLENDCURRENTALPHA;
const texture_option kTextureOptionPreModulate = D3DTOP_PREMODULATE;
const texture_option kTextureOptionModulateAlphaAddColor = D3DTOP_MODULATEALPHA_ADDCOLOR;
const texture_option kTextureOptionModulateColorAddAlpha = D3DTOP_MODULATECOLOR_ADDALPHA;
const texture_option kTextureOptionModulateInvAlphaAddColor = D3DTOP_MODULATEINVALPHA_ADDCOLOR;
const texture_option kTextureOptionModulateInvColorAddAlpha = D3DTOP_MODULATEINVCOLOR_ADDALPHA;
const texture_option kTextureOptionBumpEnvMap = D3DTOP_BUMPENVMAP;
const texture_option kTextureOptionBumpEnvMapLuminance = D3DTOP_BUMPENVMAPLUMINANCE;
const texture_option kTextureOptionDotProduct3 = D3DTOP_DOTPRODUCT3;
const texture_option kTextureOptionMultiPlyadd = D3DTOP_MULTIPLYADD;
const texture_option kTextureOptionLeap = D3DTOP_LERP;

// ëÂêlÇµÇ≠DWORDÇ≈Ç‡Ç¢Ç¢Ç©Ç‡ÇµÇÍÇ»Ç¢
typedef std::uint32_t texture_arg;

const texture_arg kTextureArgMask = D3DTA_SELECTMASK;
const texture_arg kTextureArgDiffuse = D3DTA_DIFFUSE;
const texture_arg kTextureArgCurrent = D3DTA_CURRENT;
const texture_arg kTextureArgTexture = D3DTA_TEXTURE;
const texture_arg kTextureArgTFactor = D3DTA_TFACTOR;
const texture_arg kTextureArgSpecular = D3DTA_SPECULAR;
const texture_arg kTextureArgTemp = D3DTA_TEMP;
const texture_arg kTextureArgConstant = D3DTA_CONSTANT;
const texture_arg kTextureArgComplement = D3DTA_COMPLEMENT;
const texture_arg kTextureArgAlphaReplicate = D3DTA_ALPHAREPLICATE;
}}
