//
//  Resource.hpp
//  Pong
//
//  Created by John Geiger on 3/9/22.
//

#ifndef Resource_hpp
#define Resource_hpp

#include <string>

namespace Torti {

///
/// Attaches extra data to a particular resource, such as the length and format of a sound file.
///
class IResourceExtraData
{
public:
    virtual std::string VToString()=0;
};

///
/// Represents a resource for caching
///
class Resource
{
public:
    std::string mName;
    Resource(const std::string &name);
};

///
/// Holds a Resource, its extra data, and its size
///
class ResourceHandle
{
    //friend class ResourceCache;
private:
    Resource mResource;
    char *mBuffer;
    unsigned int mSize;
    std::shared_ptr<IResourceExtraData> m_pExtra;
    //ResourceCache *m_pResourceCache;

public:
    ResourceHandle(Resource &resource, char *buffer, unsigned int size); // ResourceCache *pResCache);
    virtual ~ResourceHandle();

    const std::string GetName() { return mResource.mName; }
    unsigned int Size() const { return mSize; }
    char *Buffer() const { return mBuffer; }
    char *WritableBuffer() { return mBuffer; }
    std::shared_ptr<IResourceExtraData> GetExtra() { return m_pExtra; }
    void SetExtra(std::shared_ptr<IResourceExtraData> extra) { m_pExtra = extra; }
};

}

#endif /* Resource_hpp */
