//
//  ZipFile.cpp
//  Pong
//
//  The implementation of a ZIP file reader class.
//  Original code written by Javier Arevalo.
//
//  Created by John Geiger on 3/6/22.
//

#include <string.h>
#include <cctype>
#include <stdio.h>
#include "zlib.h"
#include "ZipFile.hpp"

namespace Torti {

//const int MaxPath = 1024;
//
//// Basic Types
//using dword = unsigned long;
//using word = unsigned short;
//using byte = unsigned char;
//
//// ZIP file structures. Have to be packed to avoid compiler messing with structures.
//
//#pragma pack(1)
///// Zip Local Header
//struct ZipFile::TZipLocalHeader
//{
//    enum { SIGNATURE = 0x04034b50 };
//    
//    dword sig;
//    word version;
//    word flag;
//    word compression;   // COMP_xxxx
//    word modTime;
//    word modDate;
//    dword crc32;
//    dword cSize;
//    dword ucSize;
//    word fnameLen;      // Filename string follows header.
//    word xtraLen;       // Extra field follows filename.
//};
//
///// Zip Dir Header
//struct ZipFile::TZipDirHeader
//{
//    enum { SIGNATURE = 0x06054b50 };
//    
//    dword sig;
//    word nDisk;
//    word nStartDisk;
//    word nDirEntries;
//    word totalDirEntries;
//    dword dirSize;
//    dword dirOffset;
//    word cmntLen;
//};
//
///// Zip Dir File Header
//struct ZipFile::TZipDirFileHeader
//{
//    enum { SIGNATURE = 0x02014b50 };
//    
//    dword sig;
//    word verMade;
//    word verNeeded;
//    word flag;
//    word compression;       // COMP_xxxx
//    word modTime;
//    word modDate;
//    dword crc32;
//    dword cSize;            // Compressed size
//    dword ucSize;           // Uncompressed size
//    word fnameLen;          // Filename string follows header
//    word xtraLen;           // Extra field follows filename
//    word cmntLen;           // Comment field follows extra field
//    word diskStart;
//    word intAttr;
//    dword extAttr;
//    dword hdrOffset;
//    
//    char *GetName() const { return (char *)(this + 1); }
//    char *GetExtra() const { return GetName() + fnameLen; }
//    char *GetComment() const { return GetExtra() + xtraLen; }
//};
//#pragma pack()
//
/////
///// @Function:      Init
///// Initialize the object and read the zip file directory.
///// @Param resourceFileName A stdio FILE* used for reading.
///// @Return true if successful.
//bool ZipFile::Init(const std::string &resourceFileName)
//{
//  End();
//
//  m_pFile = std::fopen(resourceFileName.c_str(), "r");
//  if (!m_pFile)
//    return false;
//
//  // Assuming no extra comment at the end, read the whole end record.
//  TZipDirHeader dh;
//
//  fseek(m_pFile, -(int)sizeof(dh), SEEK_END);
//  long dhOffset = ftell(m_pFile);
//  memset(&dh, 0, sizeof(dh));
//  fread(&dh, sizeof(dh), 1, m_pFile);
//
//  // Check
//  if (dh.sig != TZipDirHeader::SIGNATURE)
//    return false;
//
//  // Go to the beginning of the directory.
//  fseek(m_pFile, dhOffset - dh.dirSize, SEEK_SET);
//
//  // Allocate the data buffer, and read the whole thing.
//  m_pDirData = new char[dh.dirSize + dh.nDirEntries * sizeof(*m_papDir)];
//  if (!m_pDirData)
//    return false;
//  memset(m_pDirData, 0, dh.dirSize + dh.nDirEntries*sizeof(*m_papDir));
//  fread(m_pDirData, dh.dirSize, 1, m_pFile);
//
//  // Now process each entry.
//  char *pfh = m_pDirData;
//  m_papDir = (const TZipDirFileHeader **)(m_pDirData + dh.dirSize);
//
//  bool success = true;
//
//  for (int i = 0; i < dh.nDirEntries && success; i++)
//  {
//    TZipDirFileHeader &fh = *(TZipDirFileHeader*)pfh;
//
//    // Store the address of nth file for quicker access.
//    m_papDir[i] = &fh;
//
//    // Check the directory entry integrity.
//    if (fh.sig != TZipDirFileHeader::SIGNATURE)
//      success = false;
//    else
//    {
//      pfh += sizeof(fh);
//
//      // Convert UNIX slashes to DOS backlashes.
//      for (int j = 0; j < fh.fnameLen; j++)
//        if (pfh[j] == '/')
//          pfh[j] = '\\';
//
//      char fileName[MaxPath];
//      memcpy(fileName, pfh, fh.fnameLen);
//      fileName[fh.fnameLen]=0;
//      //_strlwr_s(fileName, MaxPath); // FIXME: this won't work, we need a string lower function that's actually correct
//      std::string spath = fileName;
//      mZipContentsMap[spath] = i;
//
//      // Skip name, extra and comment fields.
//      pfh += fh.fnameLen + fh.xtraLen + fh.cmntLen;
//    }
//  }
//  if (!success)
//  {
//    delete[] m_pDirData;
//  }
//  else
//  {
//    mNumEntries = dh.nDirEntries;
//  }
//
//  return success;
//}
//
//
/////
///// @Function:      End
///// Finish the object
/////
//void ZipFile::End()
//{
//    mZipContentsMap.clear();
//    delete[] (m_pDirData);
//    mNumEntries = 0;
//}
//
/////
///// @Function:      GetFilename
///// @Return the name of a file
///// @Param i The file index and the buffer where to store the filename.
/////
//std::string ZipFile::GetFilename(int i)  const
//{
//    std::string fileName = "";
//    if (i >=0 && i < mNumEntries)
//    {
//      char pszDest[MaxPath];
//      memcpy(pszDest, m_papDir[i]->GetName(), m_papDir[i]->fnameLen);
//      pszDest[m_papDir[i]->fnameLen] = '\0';
//      fileName = pszDest;
//    }
//    return fileName;
//}
//
//
/////
///// @Function:      GetFileLen
///// @Return the length of a file so a buffer can be allocated.
///// @Param i The file index.
/////
//int ZipFile::GetFileLength(int i) const
//{
//  if (i < 0 || i >= mNumEntries)
//    return -1;
//  else
//    return m_papDir[i]->ucSize;
//}
//
/////
///// @Function:      ReadFile
///// Uncompress a complete file.
///// @Param i The file index.
///// @Param pBuffer The pre-allocated buffer.
///// @Return True if successful.
/////
//bool ZipFile::ReadFile(int i, void *pBuffer)
//{
//  if (pBuffer == NULL || i < 0 || i >= mNumEntries)
//    return false;
//
//  // Quick'n dirty read, the whole file at once.
//  // Ungood if the ZIP has huge files inside
//
//  // Go to the actual file and read the local header.
//  fseek(m_pFile, m_papDir[i]->hdrOffset, SEEK_SET);
//  TZipLocalHeader h;
//
//  memset(&h, 0, sizeof(h));
//  fread(&h, sizeof(h), 1, m_pFile);
//  if (h.sig != TZipLocalHeader::SIGNATURE)
//    return false;
//
//  // Skip extra fields
//  fseek(m_pFile, h.fnameLen + h.xtraLen, SEEK_CUR);
//
//  if (h.compression == Z_NO_COMPRESSION)
//  {
//    // Simply read in raw stored data.
//    fread(pBuffer, h.cSize, 1, m_pFile);
//    return true;
//  }
//  else if (h.compression != Z_DEFLATED)
//    return false;
//
//  // Alloc compressed data buffer and read the whole stream
//  char *pcData = new char[h.cSize];
//  if (!pcData)
//    return false;
//
//  memset(pcData, 0, h.cSize);
//  fread(pcData, h.cSize, 1, m_pFile);
//
//  bool ret = true;
//
//  // Setup the inflate stream.
//  z_stream stream;
//  int err;
//
//  stream.next_in = (Bytef*)pcData;
//  stream.avail_in = (uInt)h.cSize;
//  stream.next_out = (Bytef*)pBuffer;
//  stream.avail_out = h.ucSize;
//  stream.zalloc = (alloc_func)0;
//  stream.zfree = (free_func)0;
//
//  // Perform inflation. wbits < 0 indicates no zlib header inside the data.
//  err = inflateInit2(&stream, -MAX_WBITS);
//  if (err == Z_OK)
//  {
//    err = inflate(&stream, Z_FINISH);
//    inflateEnd(&stream);
//    if (err == Z_STREAM_END)
//      err = Z_OK;
//    inflateEnd(&stream);
//  }
//  if (err != Z_OK)
//    ret = false;
//
//  delete[] pcData;
//  return ret;
//}
//
/////
///// @Function:      Find
///// Find the index of the file at given path.
///// @Param path The path of the file to find.
///// @Return index of file in zip, -1 if not found.
///// 
//int ZipFile::Find(const std::string &path) const
//{
//    std::string lowerCase = path;
//    std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), (int(*)(int)) std::tolower);
//    ZipContentsMap::const_iterator i = mZipContentsMap.find(lowerCase);
//    if (i == mZipContentsMap.end())
//        return -1;
//
//    return i->second;
//}

}
