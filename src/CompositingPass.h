/***************************************************************************
 # Copyright (c) 2020-2021, NVIDIA CORPORATION.  All rights reserved.
 #
 # NVIDIA CORPORATION and its licensors retain all intellectual property
 # and proprietary rights in and to this software, related documentation
 # and any modifications thereto.  Any use, reproduction, disclosure or
 # distribution of this software and related documentation without an express
 # license agreement from NVIDIA CORPORATION is strictly prohibited.
 **************************************************************************/

#pragma once

#include <nvrhi/nvrhi.h>
#include <memory>

namespace donut::engine
{
    class CommonRenderPasses;
    class BindlessScene;
    class ShaderFactory;
    class IView;
}

class RenderTargets;
class EnvironmentLight;

class CompositingPass
{
private:
    nvrhi::DeviceHandle m_Device;

    nvrhi::ShaderHandle m_ComputeShader;
    nvrhi::ComputePipelineHandle m_ComputePipeline;
    nvrhi::BindingLayoutHandle m_BindingLayout;
    nvrhi::BindingLayoutHandle m_BindlessLayout;
    nvrhi::BindingSetHandle m_BindingSetEven;
    nvrhi::BindingSetHandle m_BindingSetOdd;

    nvrhi::BufferHandle m_ConstantBuffer;

    std::shared_ptr<donut::engine::ShaderFactory> m_ShaderFactory;
    std::shared_ptr<donut::engine::CommonRenderPasses> m_CommonPasses;
    std::shared_ptr<donut::engine::BindlessScene> m_BindlessScene;

public:
    CompositingPass(
        nvrhi::IDevice* device,
        std::shared_ptr<donut::engine::ShaderFactory> shaderFactory,
        std::shared_ptr<donut::engine::CommonRenderPasses> commonPasses,
        std::shared_ptr<donut::engine::BindlessScene> bindlessScene,
        nvrhi::IBindingLayout* bindlessLayout);

    void CreatePipeline();

    void CreateBindingSet(const RenderTargets& renderTargets);

    void Render(
        nvrhi::ICommandList* commandList,
        const donut::engine::IView& view,
        const donut::engine::IView& viewPrev,
        bool enableTextures,
        uint32_t denoiserMode,
        const EnvironmentLight& environmentLight);

    void NextFrame();
};