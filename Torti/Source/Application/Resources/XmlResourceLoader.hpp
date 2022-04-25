//
//  XmlResourceLoader.hpp
//  Pong
//
//  Created by John Geiger on 4/1/22.
//
#pragma once

#ifndef XmlResourceLoader_hpp
#define XmlResourceLoader_hpp

#include "tinyxml2.h"
#include "ResourceInterfaces.hpp"

namespace Torti {

using XmlElementPtr = tinyxml2::XMLElement*;

///
/// Extra data for XML Resources
///
class XmlResourceExtraData : public IResourceExtraData
{
    tinyxml2::XMLDocument mXmlDocument;

public:
    virtual std::string VToString() { return "XmlResourceExtraData"; }
    void ParseXml(char* pRawBuffer);
    XmlElementPtr GetRoot() { return mXmlDocument.RootElement(); }
};

///
/// Loader for XML Documents
/// 
class XmlResourceLoader : public IResourceLoader
{
public:
    virtual bool VUseRawFile() { return false; }
    virtual bool VDiscardRawBufferAfterLoad() { return true; }
    virtual unsigned int VGetLoadedResourceSize(char *rawBuffer, unsigned int rawSize) { return rawSize; }
    virtual bool VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResourceHandle> handle);
    virtual std::string VGetPattern() { return "*.xml"; }

    // convenience function
    static XmlElementPtr LoadAndReturnRootXmlElement(const char* resourceString);
    
private:
    static std::shared_ptr<ResourceHandle> GetHandle(Resource &resource); // ???
};

}

#endif /* XmlResourceLoader_hpp */
