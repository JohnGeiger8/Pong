//
//  ZipResourceFile.hpp
//  Pong
//
//  Created by John Geiger on 3/9/22.
//
#pragma once

#ifndef ZipResourceFile_hpp
#define ZipResourceFile_hpp

#include "ResourceInterfaces.hpp"
#include "ZipFile.hpp"

namespace Torti {

///
/// Implements the IResourceFile interface with a ZipFile.
///
//class ZipResourceFile : public IResourceFile
//{
//    ZipFile *m_pZipFile; // FIXME: should this be a raw pointer?
//    std::string mResFileName;
//
//public:
//    ZipResourceFile(const std::string resFileName )
//        : mResFileName(resFileName),
//          m_pZipFile(NULL)
//    { }
//    virtual ~ZipResourceFile();
//
//    virtual bool VOpen();
//    virtual int VGetRawResourceSize(const Resource &r);
//    virtual int VGetRawResource(const Resource &r, char *buffer);
//    virtual int VGetNumResources() const;
//    virtual std::string VGetResourceName(int num) const;
//    virtual bool VIsUsingDevelopmentDirectories(void) const { return false; }
//};

}

#endif /* ZipResourceFile_hpp */
