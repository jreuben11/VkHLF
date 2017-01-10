/* Copyright (c) 2016-2017, NVIDIA CORPORATION. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the
*    documentation and/or other materials provided with the distribution.
*  * Neither the name of NVIDIA CORPORATION nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
* EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
* PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
* PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#pragma once

#include <vkhlf/Config.h>
#include <vkhlf/Reference.h>
#include <vkhlf/Types.h>

namespace vkhlf
{

  /************************************************************************/
  /* Framebuffer                                                          */
  /************************************************************************/
  class Framebuffer : public Reference<Device, RenderPass, Allocator>
  {
    public:
    VKHLF_API Framebuffer(std::shared_ptr<Device> const & device, std::shared_ptr<vkhlf::RenderPass> const & renderPass, vk::ArrayProxy<const std::shared_ptr<vkhlf::ImageView>> attachments,
                       vk::Extent2D const& extent, uint32_t layers, std::shared_ptr<Allocator> const& allocator);
      VKHLF_API virtual ~Framebuffer();

      VKHLF_API operator vk::Framebuffer () const;

      VKHLF_API Framebuffer(Framebuffer const& rhs) = delete;
      VKHLF_API Framebuffer & operator=(Framebuffer const& rhs) = delete;

    private:
      vk::Framebuffer                              m_framebuffer;
      std::vector<std::shared_ptr<vkhlf::ImageView>> m_attachments;
  };

  inline Framebuffer::operator vk::Framebuffer () const
  {
    return m_framebuffer;
  }

} // namespace vk
