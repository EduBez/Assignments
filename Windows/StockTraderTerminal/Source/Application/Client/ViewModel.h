#pragma once

#include "Model.h"
#include "Typedefs.h"

// Forward class declaration;
class TView;

//
//  TViewModel
//
class TViewModel
{
    friend class TModel;

public:
    // Ctor
    TViewModel(TView* view);

    // Member Functions
    void GetStockCodes ();

    // Bind Action to Handler
    void ConnectEvent(types::OpID opID, Wt::WPushButton* obj);

private:
    // Data Members
    TView* view_;
    std::unique_ptr<TModel> model_;

    std::wstring user_;
    std::wstring pwd_;

    // Member Functions
    bool IsLogged    ();

    void ShowMessage (const std::wstring& title,
                      const std::wstring& text);

    // Event Handlers
    void EventHandler1 (); // Buy
    void EventHandler3 (); // Login
    void EventHandler4 (); // Portfolio
    void EventHandler5 (); // Quote
    void EventHandler6 (); // Sell
    void EventHandler7 (); // SignUp
    void EventHandler8 (); // Transactions

    // Http Result Handlers
    void HttpResultHandler1 (web::json::value json);
    void HttpResultHandler2 (web::json::value json);
    void HttpResultHandler3 (web::json::value json);
    void HttpResultHandler4 (web::json::value json);
    void HttpResultHandler5 (web::json::value json);
    void HttpResultHandler6 (web::json::value json);
    void HttpResultHandler7 (web::json::value json);
    void HttpResultHandler8 (web::json::value json);
};
