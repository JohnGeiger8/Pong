//
//  XmlResourceFile.cpp
//  Pong
//
//  Created by John Geiger on 4/9/22.
//

#include <filesystem>
#include <iostream>
#include <fstream>
#include "XmlResourceFile.hpp"

namespace Torti {

XmlResourceFile::XmlResourceFile(const std::string resourceFileName)
  : mResourceFileName(resourceFileName)
{
    m_pXmlDocumentPtr = new XmlDocument();
}

XmlResourceFile::~XmlResourceFile()
{
    m_pXmlDocumentPtr->Clear(); // Not sure if this is necessary
    delete m_pXmlDocumentPtr;
}

bool XmlResourceFile::VOpen()
{
    int error = m_pXmlDocumentPtr->LoadFile(mResourceFileName.c_str());
    if (error != tinyxml2::XML_SUCCESS)
    {
        printf("Error: %s\n", m_pXmlDocumentPtr->ErrorStr());
        return false;
    }
    
    return true;
}

int XmlResourceFile::VGetRawResourceSize(const Resource &r)
{
    std::streampos size = -1;
    
    std::ifstream myFile(r.mName, std::ios::in|std::ios::binary|std::ios::ate);
    if (myFile.is_open())
    {
        size = myFile.tellg();
        myFile.close();
    }
    
    return size;
}

int XmlResourceFile::VGetRawResource(const Resource &r, char *buffer)
{
    std::streampos size;
    std::ifstream myFile(r.mName, std::ios::in|std::ios::binary|std::ios::ate);
    
    if (myFile.is_open())
    {
        // Get size, move file position to beginning, read into buffer, close file
        size = myFile.tellg();
        myFile.seekg(0, std::ios::beg);
        myFile.read(buffer, size);
        myFile.close();
    }
    else
    {
        printf("Error: Couldn't open resource %s", r.mName.c_str());
        return -1;
    }
    return size;
}

std::string XmlResourceFile::VGetResourceName(int num) const
{
    return mResourceFileName;
}

}
