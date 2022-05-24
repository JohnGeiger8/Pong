//
//  XmlResourceLoader.cpp
//  Pong
//
//  Created by John Geiger on 4/1/22.
//

#include "XmlResourceLoader.hpp"
#include "TortiApp.hpp"

namespace Torti {

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


std::shared_ptr<IResourceLoader> CreateXmlResourceLoader()
{
    return std::shared_ptr<XmlResourceLoader>(new XmlResourceLoader());
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
    // FIXME: for testing only
    
    return g_pApp->GetResourceHandle(resource);
}


}
