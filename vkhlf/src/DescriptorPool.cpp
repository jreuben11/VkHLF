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


#include <vkhlf/DescriptorPool.h>
#include <vkhlf/Device.h>

namespace vkhlf
{
  DescriptorPool::DescriptorPool(std::shared_ptr<Device> const & device, vk::DescriptorPoolCreateFlags flags, uint32_t maxSets, vk::ArrayProxy<const vk::DescriptorPoolSize> poolSizes,
                                 std::shared_ptr<Allocator> const& allocator)
    : Reference(device, allocator)
  {
    flags |= vk::DescriptorPoolCreateFlagBits::eFreeDescriptorSet;    // we need to set this bit to enable free on their descriptor sets
    vk::DescriptorPoolCreateInfo createInfo(flags, maxSets, vkhlf::checked_cast<uint32_t>(poolSizes.size()), poolSizes.data());

    m_descriptorPool = static_cast<vk::Device>(*get<Device>()).createDescriptorPool(createInfo, *get<Allocator>());
  }

  DescriptorPool::~DescriptorPool()
  {
    static_cast<vk::Device>(*get<Device>()).destroyDescriptorPool(m_descriptorPool, *get<Allocator>());
  }

  void DescriptorPool::reset()
  {
    static_cast<vk::Device>(*get<Device>()).resetDescriptorPool(m_descriptorPool);
  }

} // namespace vk
