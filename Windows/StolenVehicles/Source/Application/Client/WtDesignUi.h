#pragma once
#include "RESTfull.h"

// Type Alias
using rows_t =
    std::vector<
        std::tuple<
              std::wstring
            , std::wstring
            , std::wstring
            , std::wstring
        >>;

//
//  WtDesignUi
//
class WtDesignUi : public Wt::WApplication
{
    // Data Members
    Wt::WContainerWidget* containerOpt_;
    Wt::WContainerWidget* containerRes_;

    Wt::WPanel* panelOpt_;
    Wt::WPanel* panelRes_;

    Wt::WTable* tableOpt_;
    Wt::WTable* tableRes_;

    Wt::WLineEdit* leReg_;
    Wt::WLineEdit* leMak_;
    Wt::WLineEdit* leMod_;
    Wt::WLineEdit* leOwn_;

    Wt::WPushButton* pbReg_;
    Wt::WPushButton* pbMak_;
    Wt::WPushButton* pbMod_;
    Wt::WPushButton* pbOwn_;
    Wt::WPushButton* pbAll_;
    
    // Member Functions
    void WebUiCreate           (Wt::WContainerWidget* root);
    void WebUiPopulateTable    (const rows_t& rows);

    // UI Event Handlers
    void HandlerSearchAll      ();
    void HandlerSearchByRegist ();
    void HandlerSearchByMaker  ();
    void HandlerSearchByModel  ();
    void HandlerSearchByOwner  ();
    
    rest::CallBack func_;

    // Callback Function
    void CallBackHandler(web::json::value& value);

public:
    // Ctor
    WtDesignUi(const Wt::WEnvironment& env);
};
