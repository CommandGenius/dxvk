#pragma once

#include "../util/config/config.h"

#include "../dxgi/dxgi_options.h"

#include "../dxvk/dxvk_device.h"

#include "d3d11_include.h"

namespace dxvk {

  std::string GetDXGIFormatNameAsString(
          DXGI_FORMAT Format);

  enum class FORMAT_TYPE {
    FORMAT_UNKNOWN,
    FORMAT_UNSUPPORTED,
    FORMAT_IGNORE,
    FORMAT_TYPELESS,
    FORMAT_SFLOAT,
    FORMAT_UFLOAT,
    FORMAT_UNORM,
    FORMAT_SNORM,
    FORMAT_UINT,
    FORMAT_SINT,
    FORMAT_UNORM_SRGB,
    FORMAT_TYPELESS_UINT,
    FORMAT_FLOAT_TYPELESS,
    FORMAT_FLOAT_UINT,
    FORMAT_UNORM_UNIT
  };

  struct FormatUpgradeInfo
  {
    FORMAT_TYPE type           = FORMAT_TYPE::FORMAT_UNKNOWN;
    DXGI_FORMAT upgradedFormat = DXGI_FORMAT_UNKNOWN;
  };

  struct D3D11Options {
    D3D11Options(const Config& config);

    /// Enables speed hack for mapping on deferred contexts
    ///
    /// This can substantially speed up some games, but may
    /// cause issues if the game submits command lists more
    /// than once.
    bool dcSingleUseMode = false;

    /// Zero-initialize workgroup memory
    ///
    /// Workargound for games that don't initialize
    /// TGSM in compute shaders before reading it.
    bool zeroInitWorkgroupMemory = false;

    /// Force thread-group shared memory accesses to be volatile
    ///
    /// Workaround for compute shaders that read and
    /// write from the same shared memory location
    /// without explicit synchronization.
    bool forceVolatileTgsmAccess = false;

    /// Use relaxed memory barriers
    ///
    /// May improve performance in some games,
    /// but might also cause rendering issues.
    bool relaxedBarriers = false;

    /// Ignore graphics barriers
    ///
    /// May improve performance in some games,
    /// but might also cause rendering issues.
    bool ignoreGraphicsBarriers = false;

    /// Maximum tessellation factor.
    ///
    /// Limits tessellation factors in tessellation
    /// control shaders. Values from 8 to 64 are
    /// supported, other values will be ignored.
    int32_t maxTessFactor = 0;

    /// Anisotropic filter override
    ///
    /// Enforces anisotropic filtering with the
    /// given anisotropy value for all samplers.
    int32_t samplerAnisotropy = -1;

    /// Mipmap LOD bias
    ///
    /// Enforces the given LOD bias for all samplers.
    float samplerLodBias = 0.0f;

    /// Clamps negative LOD bias
    bool clampNegativeLodBias = false;

    /// Declare vertex positions in shaders as invariant
    bool invariantPosition = true;

    /// Enable float control bits
    bool floatControls = true;

    /// Back buffer count for the Vulkan swap chain.
    /// Overrides DXGI_SWAP_CHAIN_DESC::BufferCount.
    int32_t numBackBuffers = 0;

    /// Override maximum frame latency if the app specifies
    /// a higher value. May help with frame timing issues.
    int32_t maxFrameLatency = 0;

    /// Defer surface creation until first present call. This
    /// fixes issues with games that create multiple swap chains
    /// for a single window that may interfere with each other.
    bool deferSurfaceCreation = false;

    /// Enables sample rate shading by interpolating fragment shader
    /// inputs at the sample location rather than pixel center,
    /// unless otherwise specified by the application.
    bool forceSampleRateShading = false;

    /// Forces the sample count of all textures to be 1, and
    /// performs the required shader and resolve fixups.
    bool disableMsaa = false;

    /// Dynamic resources with the given bind flags will be allocated
    /// in cached system memory. Enabled automatically when recording
    /// an api trace.
    uint32_t cachedDynamicResources = 0;

    /// Always lock immediate context on every API call. May be
    /// useful for debugging purposes or when applications have
    /// race conditions.
    bool enableContextLock = false;

    /// Whether to expose the driver command list feature. Enabled by
    /// default and generally beneficial, but some games may assume that
    /// this is not supported when running on an AMD GPU.
    bool exposeDriverCommandLists = true;

    /// enable render target upgrades
    bool enableRenderTargetUpgrades;

    /// array that describes which format will be ugprade to which
    std::array<FormatUpgradeInfo, 116> formatUpgradeInfoArray =
    {{
      // DXGI_FORMAT_UNKNOWN
      {FORMAT_TYPE::FORMAT_UNKNOWN},
      // DXGI_FORMAT_R32G32B32A32_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R32G32B32A32_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_R32G32B32A32_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R32G32B32A32_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R32G32B32_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R32G32B32_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_R32G32B32_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R32G32B32_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R16G16B16A16_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R16G16B16A16_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_R16G16B16A16_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R16G16B16A16_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R16G16B16A16_SNORM
      {FORMAT_TYPE::FORMAT_SNORM},
      // DXGI_FORMAT_R16G16B16A16_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R32G32_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R32G32_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_R32G32_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R32G32_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R32G8X24_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_D32_FLOAT_S8X24_UINT
      {FORMAT_TYPE::FORMAT_FLOAT_UINT},
      // DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS
      {FORMAT_TYPE::FORMAT_FLOAT_TYPELESS},
      // DXGI_FORMAT_X32_TYPELESS_G8X24_UINT
      {FORMAT_TYPE::FORMAT_TYPELESS_UINT},
      // DXGI_FORMAT_R10G10B10A2_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R10G10B10A2_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R10G10B10A2_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R11G11B10_FLOAT
      {FORMAT_TYPE::FORMAT_UFLOAT},
      // DXGI_FORMAT_R8G8B8A8_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R8G8B8A8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R8G8B8A8_UNORM_SRGB
      {FORMAT_TYPE::FORMAT_UNORM_SRGB},
      // DXGI_FORMAT_R8G8B8A8_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R8G8B8A8_SNORM
      {FORMAT_TYPE::FORMAT_SNORM},
      // DXGI_FORMAT_R8G8B8A8_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R16G16_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R16G16_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_R16G16_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R16G16_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R16G16_SNORM
      {FORMAT_TYPE::FORMAT_SNORM},
      // DXGI_FORMAT_R16G16_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R32_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_D32_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_R32_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_R32_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R32_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R24G8_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_D24_UNORM_S8_UINT
      {FORMAT_TYPE::FORMAT_UNORM_UNIT},
      // DXGI_FORMAT_R24_UNORM_X8_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_X24_TYPELESS_G8_UINT
      {FORMAT_TYPE::FORMAT_TYPELESS_UINT},
      // DXGI_FORMAT_R8G8_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R8G8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R8G8_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R8G8_SNORM
      {FORMAT_TYPE::FORMAT_SNORM},
      // DXGI_FORMAT_R8G8_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R16_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R16_FLOAT
      {FORMAT_TYPE::FORMAT_SFLOAT},
      // DXGI_FORMAT_D16_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R16_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R16_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R16_SNORM
      {FORMAT_TYPE::FORMAT_SNORM},
      // DXGI_FORMAT_R16_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_R8_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_R8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R8_UINT
      {FORMAT_TYPE::FORMAT_UINT},
      // DXGI_FORMAT_R8_SNORM
      {FORMAT_TYPE::FORMAT_SNORM},
      // DXGI_FORMAT_R8_SINT
      {FORMAT_TYPE::FORMAT_SINT},
      // DXGI_FORMAT_A8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R1_UNORM
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_R9G9B9E5_SHAREDEXP
      {FORMAT_TYPE::FORMAT_UFLOAT},
      // DXGI_FORMAT_R8G8_B8G8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_G8R8_G8B8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_BC1_TYPELESS
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC1_UNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC1_UNORM_SRGB
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC2_TYPELESS
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC2_UNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC2_UNORM_SRGB
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC3_TYPELESS
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC3_UNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC3_UNORM_SRGB
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC4_TYPELESS
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC4_UNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC4_SNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC5_TYPELESS
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC5_UNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC5_SNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_B5G6R5_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_B5G5R5A1_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_B8G8R8A8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_B8G8R8X8_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
      // DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_B8G8R8A8_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_B8G8R8A8_UNORM_SRGB
      {FORMAT_TYPE::FORMAT_UNORM_SRGB},
      // DXGI_FORMAT_B8G8R8X8_TYPELESS
      {FORMAT_TYPE::FORMAT_TYPELESS},
      // DXGI_FORMAT_B8G8R8X8_UNORM_SRGB
      {FORMAT_TYPE::FORMAT_UNORM_SRGB},
      // DXGI_FORMAT_BC6H_TYPELESS
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC6H_UF16
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC6H_SF16
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC7_TYPELESS
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC7_UNORM
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_BC7_UNORM_SRGB
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_AYUV
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_Y410
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_Y416
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_NV12
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_P010
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_P016
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_420_OPAQUE
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_YUY2
      {FORMAT_TYPE::FORMAT_IGNORE},
      // DXGI_FORMAT_Y210
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_Y216
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_NV11
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_AI44
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_IA44
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_P8
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_A8P8
      {FORMAT_TYPE::FORMAT_UNSUPPORTED}, // Unsupported
      // DXGI_FORMAT_B4G4R4A4_UNORM
      {FORMAT_TYPE::FORMAT_UNORM},
    }};

    //DXGI_FORMAT upgrade_RGBA16_TYPELESS_To;
    //DXGI_FORMAT upgrade_RGBA16_FLOAT_To;
    //DXGI_FORMAT upgrade_RGBA16_UNORM_To;
    //DXGI_FORMAT upgrade_RGBA16_UINT_To;
    //DXGI_FORMAT upgrade_RGBA16_SNORM_To;
    //DXGI_FORMAT upgrade_RGBA16_SINT_To;
    //DXGI_FORMAT upgrade_RGB10A2_TYPELESS_To;
    //DXGI_FORMAT upgrade_RGB10A2_UNORM_To;
    //DXGI_FORMAT upgrade_RGB10A2_UINT_To;
    //DXGI_FORMAT upgrade_RG11B10_FLOAT_To;
    //DXGI_FORMAT upgrade_RGBA8_TYPELESS_To;
    //DXGI_FORMAT upgrade_RGBA8_UNORM_To;
    //DXGI_FORMAT upgrade_RGBA8_UNORM_SRGB_To;
    //DXGI_FORMAT upgrade_RGBA8_UINT_To;
    //DXGI_FORMAT upgrade_RGBA8_SNORM_To;
    //DXGI_FORMAT upgrade_RGBA8_SINT_To;
    //DXGI_FORMAT upgrade_BGRA8_UNORM_To;
    //DXGI_FORMAT upgrade_BGRX8_UNORM_To;
    //DXGI_FORMAT upgrade_BGRA8_TYPELESS_To;
    //DXGI_FORMAT upgrade_BGRA8_UNORM_SRGB_To;
    //DXGI_FORMAT upgrade_BGRX8_TYPELESS_To;
    //DXGI_FORMAT upgrade_BGRX8_UNORM_SRGB_To;

    /// enable back buffer upgrade
    bool enableBackBufferUpgrade;

    /// back buffer format to upgrade to
    DXGI_FORMAT upgradeBackBufferTo;

    /// enable upgrade swapchain
    bool enableSwapChainUpgrade;

    /// which output format to upgrade to
    VkFormat upgradeSwapChainFormatTo;

    /// output color space to upgrade to
    VkColorSpaceKHR upgradeSwapChainColorSpaceTo;

    /// Ensure that for the same D3D commands the output VK commands
    /// don't change between runs. Useful for comparative benchmarking,
    /// can negatively affect performance.
    bool reproducibleCommandStream = false;

    /// Shader dump path
    std::string shaderDumpPath;
  };

}
