//
//  TinyXmlElement.hpp
//  Pong
//
//  Created by John Geiger on 3/31/22.
//
#pragma once

#ifndef TinyXmlElement_hpp
#define TinyXmlElement_hpp

#include <string>
#include "tinyxml2.h"

namespace Torti {

// FIXME: Do i need?
///
/// Wraps the tinyxml2::XMLElement class
///
class TinyXmlElement
{
private:
    tinyxml2::XMLElement* m_pElement;
    
public:
    TinyXmlElement(std::string path);
    ~TinyXmlElement();
    
    tinyxml2::XMLElement* GetXmlElement() { return m_pElement; }
};

}

#endif /* TinyXmlElement_hpp */
