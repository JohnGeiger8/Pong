// FIXME: This class just doesn't currently work on my Mac
//
//  ZipFile.hpp
//  Pong
//
//  Created by John Geiger on 3/6/22.
//
#pragma once

#ifndef ZipFile_hpp
#define ZipFile_hpp

#include <memory>
#include <string>
#include <map>

namespace Torti {

//using ZipContentsMap = std::map<std::string, int>;
//
/////
///// Represents a .zip file based on its structure.
/////
//class ZipFile
//{
//private:
//    FILE *m_pFile;      // Zip file
//    char *m_pDirData;   // Raw data buffer
//    int mNumEntries;    // Number of entries
//    
//public:
//    ZipFile() :
//        mNumEntries(0),
//        m_pFile(NULL),
//        m_pDirData(NULL)
//    { }
//    virtual ~ZipFile() { End(); fclose(m_pFile); }
//    
//    bool Init(const std::string &resourceFileName);
//    void End();
//    
//    int GetNumFiles() const { return mNumEntries; }
//    std::string GetFilename(int i) const;
//    int GetFileLength(int i) const;
//    bool ReadFile(int i, void *pBuffer);
//    int Find(const std::string &path) const;
//    
//    ZipContentsMap mZipContentsMap;
//    
//private:
//    struct TZipDirHeader;
//    struct TZipDirFileHeader;
//    struct TZipLocalHeader;
//    
//    // Pointers to the dir entries in pDirData
//    const TZipDirFileHeader **m_papDir;
//};

}
#endif /* ZipFile_hpp */
