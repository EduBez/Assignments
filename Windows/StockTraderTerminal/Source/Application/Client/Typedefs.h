#pragma once

namespace evolve {
    namespace types {

// Enum Class
enum class OpID
{
      None
    , Buy
    , Codes
    , Login
    , Portfolio
    , Quote
    , Sell
    , SignUp
    , TransLog
};

// Type Aliases
using Operation = std::function<void (web::json::value)>;
using MapOp = std::map<OpID, Operation>;

}};//EndOf namespace

// Namespace alias
namespace types = evolve::types;

