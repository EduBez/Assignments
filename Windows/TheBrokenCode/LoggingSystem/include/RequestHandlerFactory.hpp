#ifndef REQUEST_HANDLER_FACTORY_HPP_INCLUDED
#define REQUEST_HANDLER_FACTORY_HPP_INCLUDED

#pragma once

#include "RequestHandler.hpp"

namespace brokencode {
namespace server {
    
class RequestHandlerFactory final {
public:
    RequestHandlerFactory() = delete;
    static HandlerMap CreateHandlers();
};
    
}
}

#endif //REQUEST_HANDLER_FACTORY_HPP_INCLUDED
