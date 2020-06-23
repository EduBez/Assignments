#pragma once

#include "ViewModel.h"
#include "Model.h"

//
//  TView
//
class TView : public Wt::WApplication
{
    friend class TViewModel;
    friend class TModel;

public:
    TView(const Wt::WEnvironment& env);

    // Getters
    std::wstring GetUser()
        {return user_;}

    std::wstring GetPwd()
        {return pwd_;}

    // Setters    
    void SetUser()
        {user_ = edtUser_->text();}

    void SetPwd()
        {pwd_  = edtPwd_ ->text();}

protected:
    void initialize();

private:
    // Data Members
    std::unique_ptr<TViewModel> viewModel_;

    std::wstring user_;
    std::wstring pwd_;

    // Member Functions
    void WebUiCreate ();

    void WebUiDesign (Wt::WContainerWidget* root);

    // UI Elements

    // Login Info
    Wt::WContainerWidget     *cwLoginInfo_;
    Wt::WPanel               *pnlLoginInfo_;
                             
    Wt::WText                *lblUser_;
    Wt::WLineEdit            *edtUser_;
                             
    Wt::WText                *lblPwd_;
    Wt::WLineEdit            *edtPwd_;
                             
    Wt::WPushButton          *btnLogin_;
    Wt::WPushButton          *btnSignup_;
                             
    // Buy, Sell & Quote Stocks
    Wt::WContainerWidget     *cwBuySellStocks_;
    Wt::WPanel               *pnlBuySellStocks_;
                             
    Wt::WText                *lblStockCode_;
    Wt::WComboBox            *cbxStockCode_;
    Wt::WText                *lblStockPrice_;
                             
    Wt::WText                *lblQuantity_;
    Wt::WLineEdit            *edtQuantity_;
                             
    Wt::WText                *lblPrice_;
    Wt::WLineEdit            *edtPrice_;
                             
    Wt::WPushButton          *btnBuy_;
    Wt::WPushButton          *btnSell_;
    Wt::WPushButton          *btnQuote_;
                             
    // Transactions Log      
    Wt::WContainerWidget     *cwTransactionLog_;
    Wt::WPanel               *pnlTransactionLog_;
                             
    Wt::WTable               *tblTransactions_;
    Wt::WPushButton          *btnTrans_;

    // Trader's Portfolio
    Wt::WContainerWidget     *cwPortfolio_;
    Wt::WPanel               *pnlPortfolio_;
                             
    Wt::WTable               *tblPortfolio_;
    Wt::WPushButton          *btnPortfolio_;
};

