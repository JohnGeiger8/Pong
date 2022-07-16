//
//  ITexture.hpp
//  Pong
//
//  Created by John Geiger on 7/10/22.
//

#ifndef ITexture_hpp
#define ITexture_hpp

#include <string>

namespace Torti {

///
/// Interface for textures
///
class ITexture
{
    virtual bool VLoadTextureFromFile(std::string path)=0;
    virtual void VShutdown()=0;
    virtual void VOnRender()=0;
};

}
#endif /* ITexture_hpp */
