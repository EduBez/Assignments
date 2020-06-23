#pragma once
#include "Typedefs.h"

// Forward class declarations
class TViewModel;

//
//  TModel
//
class TModel
{
public:
    // Ctor
    TModel(TViewModel* viewModel);

    // Http REST Dispatchers
    web::json::value HttpGet(types::OpID           opID,
                             const std::wstring&   url);

    web::json::value HttpPost(types::OpID          opID,
                              const wchar_t*       path,
                              const std::wstring&  url,
                              const web::json::value& json);
private:
    // Data Member
    TViewModel* viewModel_;

    // MapOf Callbacks
    types::OpID opID_;
    types::MapOp op_;
};

