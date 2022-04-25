//
//  XmlResourceFile.hpp
//  Pong
//
//  Created by John Geiger on 4/9/22.
//
#pragma once

#ifndef XmlResourceFile_hpp
#define XmlResourceFile_hpp

#include "ResourceInterfaces.hpp"
#include "tinyxml2.h"

namespace Torti {

using XmlDocument = tinyxml2::XMLDocument;
using XmlDocumentPtr = XmlDocument*;

///
/// Xml Resource File
/// 
class XmlResourceFile : public IResourceFile 
{
    XmlDocumentPtr m_pXmlDocumentPtr;
    std::string mResourceFileName;

public:
    XmlResourceFile(const std::string resourceFileName);
    virtual ~XmlResourceFile();

    virtual bool VOpen();
    virtual int VGetRawResourceSize(const Resource &r);
    virtual int VGetRawResource(const Resource &r, char *buffer);
    virtual int VGetNumResources() const { return m_pXmlDocumentPtr != NULL ? 1 : 0; }
    virtual std::string VGetResourceName(int num) const;
    virtual bool VIsUsingDevelopmentDirectories(void) const { return false; }
};

}
#endif /* XmlResourceFile_hpp */
