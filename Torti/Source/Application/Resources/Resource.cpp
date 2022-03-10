//
//  Resource.cpp
//  Pong
//
//  Created by John Geiger on 3/9/22.
//

#include "Resource.hpp"

namespace Torti {

Resource::Resource(const std::string &name)
{
    mName = name;
    std::transform(mName.begin(), mName.end(), mName.begin(), (int(*)(int)) std::tolower); // Make all filenames lowercase
}

ResourceHandle::ResourceHandle(Resource &resource, char *buffer, unsigned int size)
    : mResource(resource),
      mBuffer(buffer),
      mSize(size),
      m_pExtra(NULL)
{ }

ResourceHandle::~ResourceHandle()
{
    // FIXME: is this safe?
    delete [] mBuffer;
    //m_pResourceCache->MemoryHasBeenFreed(mSize);
}

}
