//
//  XmlResourceLoader.cpp
//  Pong
//
//  Created by John Geiger on 4/1/22.
//

#include "XmlResourceLoader.hpp"
#include "Globals.hpp"
#include "XmlResourceFile.hpp"

namespace Torti {

// FIXME: For testing only, all resources belong in TortiApp
std::list<std::shared_ptr<ResourceHandle>> gResources = std::list<std::shared_ptr<ResourceHandle>>();

void XmlResourceExtraData::ParseXml(char* pRawBuffer)
{
    mXmlDocument.Parse(pRawBuffer);
}

bool XmlResourceLoader::VLoadResource(char *rawBuffer, unsigned int rawSize, std::shared_ptr<ResourceHandle> handle)
{
    if (rawSize <= 0)
        return false;

    std::shared_ptr<XmlResourceExtraData> pExtraData = std::shared_ptr<XmlResourceExtraData>(new XmlResourceExtraData());
    pExtraData->ParseXml(rawBuffer);

    handle->SetExtra(std::shared_ptr<XmlResourceExtraData>(pExtraData));

    return true;
}


std::shared_ptr<XmlResourceLoader> CreateXmlResourceLoader()
{
    return std::make_shared<XmlResourceLoader>();
}

/// XMLResourceLoader

XmlElementPtr XmlResourceLoader::LoadAndReturnRootXmlElement(const char* resourceString)
{
    Resource resource(resourceString);
    std::shared_ptr<ResourceHandle> pResourceHandle = GetHandle(resource);
    std::shared_ptr<XmlResourceExtraData> pExtraData = std::static_pointer_cast<XmlResourceExtraData>(pResourceHandle->GetExtra());
    return pExtraData->GetRoot();
}

std::shared_ptr<ResourceHandle> XmlResourceLoader::GetHandle(Resource &resource)
{
    // FIXME: for testing only. Should go into app class
    std::shared_ptr<ResourceHandle> handle;
    std::shared_ptr<XmlResourceLoader> loader = CreateXmlResourceLoader();
    
    std::shared_ptr<XmlResourceFile> file = std::make_shared<XmlResourceFile>(resource.mName);
    
    if (!file->VOpen())
    {
        printf("File couldn't be opened: %s\n", resource.mName.c_str());
        return handle;
    }
    
    int rawSize = file->VGetRawResourceSize(resource);
    if (rawSize < 0)
    {
        printf("Resource not found: %s", resource.mName.c_str());
        return handle;
    }
    
    char *rawBuffer = new char[rawSize];
    if (rawBuffer == NULL || file->VGetRawResource(resource, rawBuffer) == 0)
    {
        return handle;
    }
    
    handle = std::make_shared<ResourceHandle>(resource, rawBuffer, rawSize);
    if (!loader->VLoadResource(rawBuffer, rawSize, handle))
        return std::shared_ptr<ResourceHandle>();
    
    gResources.push_back(handle);
    
    if (loader->VDiscardRawBufferAfterLoad())
        delete[] rawBuffer;
    
    return handle;

    
    return g_pApp->GetResourceHandle(resource);
}


}
