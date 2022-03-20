//
//  ZipResourceFile.cpp
//  Pong
//
//  Created by John Geiger on 3/9/22.
//

#include "ZipResourceFile.hpp"

namespace Torti {

//ZipResourceFile::~ZipResourceFile()
//{
//    delete m_pZipFile; // FIXME: is this safe?
//}
//
/////
///// Opens the Zip File.
///// @Return true if successful
/////
//bool ZipResourceFile::VOpen()
//{
//    m_pZipFile = new ZipFile(); // GCC_NEW
//    if (!m_pZipFile->Init(mResFileName))
//    {
//        printf("Error: opening file: %s", mResFileName.c_str());
//        return false;
//    }
//    
//    return true;
//}
//
/////
///// Get size of raw resource.
///// @Parameters r: Resource whose size we're getting.
///// @Returns size of file, -1 if not found.
/////
//int ZipResourceFile::VGetRawResourceSize(const Resource &r)
//{
//    int index = m_pZipFile->Find(r.mName.c_str());
//    if (index != -1)
//    {
//        return m_pZipFile->GetFileLength(index);
//    }
//    else
//    {
//        printf("Error: couldn't find resource: %s", r.mName.c_str());
//        return index;
//    }
//}
//
/////
///// Fetches raw resource file.
///// @Param r Resource whose raw file we're fetching.
///// @Param buffer buffer to load the resource into.
///// @Returns Size of resource, -1 if unsuccessful.
///// 
//int ZipResourceFile::VGetRawResource(const Resource &r, char *buffer)
//{
//    int size = 0;
//    int index = m_pZipFile->Find(r.mName.c_str());
//    if (index != -1)
//    {
//        size = m_pZipFile->GetFileLength(index);
//        if (!m_pZipFile->ReadFile(index, buffer))
//            printf("Error: couldn't read resource: %s", r.mName.c_str());
//    }
//    else
//        printf("Error: couldn't find resource: %s", r.mName.c_str());
//    
//    return size;
//}
//
/////
///// @Return Number of files in zip file.
/////
//int ZipResourceFile::VGetNumResources() const
//{
//    return (m_pZipFile == NULL) ? 0 : m_pZipFile->GetNumFiles();
//}
//
/////
///// @Param num Index for resource whose name we're returning.
///// @Return Name of resource at index num.
/////
//std::string ZipResourceFile::VGetResourceName(int num) const
//{
//    std::string resName = "";
//    if (m_pZipFile != NULL && num >= 0 && num < m_pZipFile->GetNumFiles())
//    {
//        resName = m_pZipFile->GetFilename(num);
//    }
//    return resName;
//}

}
