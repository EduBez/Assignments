#pragma once

namespace Evolve {
    namespace Rest {

// Type Aliases
using CallBack = std::function<void (web::json::value&)>;

//
//  RESTfull
//
class RESTfull
{
public:
    // Member Function
    void Invoke(CallBack func, const Wt::WString& uri, const Wt::WString& value);
};

}};//EndOf namespace
// Namespace alias
namespace rest = Evolve::Rest;