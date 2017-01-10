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


#include <vkhlf/Buffer.h>
#include <vkhlf/BufferView.h>
#include <vkhlf/Device.h>

namespace vkhlf
{

  BufferView::BufferView(std::shared_ptr<vkhlf::Buffer> const& buffer, vk::Format format, vk::DeviceSize offset, vk::DeviceSize range, std::shared_ptr<Allocator> const& allocator)
    : Reference( buffer, allocator )
  {
    if ( range == ~0 )
    {
      range = buffer->getSize() - offset;
    }
    assert( offset + range <= buffer->getSize() );

#pragma message("flags are missing here")
    vk::BufferViewCreateInfo bufferViewCreateInfo = {vk::BufferViewCreateFlags(), *buffer, format, offset, range};

    m_bufferView = static_cast<vk::Device>(*get<Buffer>()->get<Device>()).createBufferView(bufferViewCreateInfo, *get<Allocator>());
  }

  BufferView::~BufferView( )
  {
    static_cast<vk::Device>(*get<Buffer>()->get<Device>()).destroyBufferView(m_bufferView, *get<Allocator>());
  }

} // namespace vk
