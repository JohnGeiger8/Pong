//
//  ResourceInterfaces.hpp
//  Pong
//
//  Created by John Geiger on 3/9/22.
//
#pragma once

#ifndef ResourceInterfaces_hpp
#define ResourceInterfaces_hpp

#include "Resource.hpp"

namespace Torti {

///
/// Represents any resource file that may need to be loaded into program. Should be derived from for any specific file types, e.g. zip, cab, etc.
///
class IResourceFile
{
public:
    virtual bool VOpen()=0;
    virtual int VGetRawResourceSize(const Resource &r)=0;
    virtual int VGetRawResource(const Resource &r, char* buffer)=0;
    virtual int VGetNumResources() const=0;
    virtual std::string VGetResourceName(int num) const=0;
    virtual ~IResourceFile() { }
};

///
/// Represents Resource Loaders.
///
class IResourceLoader
{
    ///
    /// Gets the wildcard pattern that the cache uses to distinguish which loaders are used with which files.
    /// @Return string: wildcard pattern.
    ///
    virtual std::string VGetPattern()=0;
    
    ///
    /// @Return true if the resource loader can use the bits stored in the raw file, no extra processing needed.
    ///
    virtual bool VUseRawFile()=0;
    
    ///
    /// @Return size of resource if different from size stored in file.
    ///
    virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize)=0;
    
    ///
    /// Load resource from file.
    /// @Return true if successful.
    virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResourceHandle> handle)=0;
};

///
/// Used to load resources when they need no extra processing.
///
class DefaultResourceLoader : public IResourceLoader
{
public:
    virtual std::string VGetPattern() { return "*"; }
    virtual bool VUseRawFile() { return true; }
    virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize) { return rawSize; }
    virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResourceHandle> handle) { return true; }
};

}

#endif /* ResourceInterfaces_hpp */
