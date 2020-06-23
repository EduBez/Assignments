#include "stdafx.h"

#include "Typedefs.h"
#include "View.h"

using namespace std;
using namespace types;
using namespace Wt;

//
//  TView
//
TView::TView(const WEnvironment& env)
    // Member Initializer List
    : WApplication (env)
{
    // Data Member
    viewModel_ = std::make_unique<TViewModel>(this);

    WebUiCreate();
    WebUiDesign(root());

    viewModel_->ConnectEvent(OpID::Login     , btnLogin_);
    viewModel_->ConnectEvent(OpID::SignUp    , btnSignup_);
    viewModel_->ConnectEvent(OpID::Buy       , btnBuy_);
    viewModel_->ConnectEvent(OpID::Sell      , btnSell_);
    viewModel_->ConnectEvent(OpID::Quote     , btnQuote_);
    viewModel_->ConnectEvent(OpID::TransLog  , btnTrans_);
    viewModel_->ConnectEvent(OpID::Portfolio , btnPortfolio_);
}

void TView::initialize()
{
    removeCookie("UserName");
    removeCookie("Password");

    viewModel_->GetStockCodes();
}

void TView::WebUiCreate()
{
    setTheme(new WBootstrapTheme());

    // Login Info
    cwLoginInfo_         = new WContainerWidget (root());
    pnlLoginInfo_        = new WPanel           (root());

    lblUser_             = new WText       (cwLoginInfo_);
    edtUser_             = new WLineEdit   (cwLoginInfo_);

    lblPwd_              = new WText       (cwLoginInfo_);
    edtPwd_              = new WLineEdit   (cwLoginInfo_);

    btnLogin_            = new WPushButton (cwLoginInfo_);
    btnSignup_           = new WPushButton (cwLoginInfo_);

    // Buy, Sell & Quote Stocks     
    cwBuySellStocks_     = new WContainerWidget (root());
    pnlBuySellStocks_    = new WPanel (root());

    lblStockCode_        = new WText       (cwBuySellStocks_);
    cbxStockCode_        = new WComboBox   (cwBuySellStocks_);
    lblStockPrice_       = new WText       (cwBuySellStocks_);

    lblQuantity_         = new WText       (cwBuySellStocks_);
    edtQuantity_         = new WLineEdit   (cwBuySellStocks_);

    lblPrice_            = new WText       (cwBuySellStocks_);
    edtPrice_            = new WLineEdit   (cwBuySellStocks_);

    btnBuy_              = new WPushButton (cwBuySellStocks_);
    btnSell_             = new WPushButton (cwBuySellStocks_);
    btnQuote_            = new WPushButton (cwBuySellStocks_);

    // Transactions Log    
    cwTransactionLog_    = new WContainerWidget (root());
    pnlTransactionLog_   = new WPanel (root());

    tblTransactions_     = new WTable      (cwTransactionLog_);
    btnTrans_            = new WPushButton (cwTransactionLog_);

    // Trader's Portfolio
    cwPortfolio_         = new WContainerWidget (root());
    pnlPortfolio_        = new WPanel (root());

    tblPortfolio_        = new WTable      (cwPortfolio_);
    btnPortfolio_        = new WPushButton (cwPortfolio_);
}

void TView::WebUiDesign(Wt::WContainerWidget* root)
{
    setTitle("Stock Exchange");

    pnlLoginInfo_->setId("pnlLoginInfo_");
    pnlLoginInfo_->setStyleClass(WString::fromUTF8("panel panel-default panel panel-default"));
    pnlLoginInfo_->setInline(1);
    pnlLoginInfo_->setTitle(WString::fromUTF8("Login Info"));
    pnlLoginInfo_->setCollapsible(1);
    pnlLoginInfo_->setCentralWidget(cwLoginInfo_);

    {
        lblUser_->setId("lblUser_");
        lblUser_->setStyleClass(WString::fromUTF8(""));
        lblUser_->setInline(0);
        lblUser_->setTextFormat((TextFormat)0);
        lblUser_->setText(WString::fromUTF8("User Name:"));

        edtUser_->setId("edtUser_");
        edtUser_->setStyleClass(WString::fromUTF8("form-control form-control"));
        edtUser_->setInline(0);
        edtUser_->setEmptyText(WString::fromUTF8(""));

        lblPwd_->setId("lblPwd_");
        lblPwd_->setStyleClass(WString::fromUTF8(""));
        lblPwd_->setInline(0);
        lblPwd_->setTextFormat((TextFormat)0);
        lblPwd_->setText(WString::fromUTF8("Password:"));

        edtPwd_->setId("edtPwd_");
        edtPwd_->setEchoMode(WLineEdit::Password);
        edtPwd_->setStyleClass(WString::fromUTF8("form-control form-control"));
        edtPwd_->setInline(0);
        edtPwd_->setEmptyText(WString::fromUTF8(""));

        btnLogin_->setId("btnLogin_");
        btnLogin_->setStyleClass(WString::fromUTF8("btn btn-default with-label btn btn-default with-label"));
        btnLogin_->setInline(1);
        btnLogin_->setEmptyText(WString::fromUTF8(""));
        btnLogin_->setText(WString::fromUTF8("Login"));
        btnLogin_->setLink(WLink(""));

        btnSignup_->setId("btnSignup_");
        btnSignup_->setStyleClass(WString::fromUTF8("btn btn-default with-label btn btn-default with-label"));
        btnSignup_->setInline(1);
        btnSignup_->setEmptyText(WString::fromUTF8(""));
        btnSignup_->setText(WString::fromUTF8("Sign Up"));
        btnSignup_->setLink(WLink(""));
    }

    pnlBuySellStocks_->setId("pnlBuySellStocks_");
    pnlBuySellStocks_->setStyleClass(WString::fromUTF8("panel panel-default panel panel-default"));
    pnlBuySellStocks_->setInline(0);
    pnlBuySellStocks_->setTitle(WString::fromUTF8("Buy, Sell & Quote Stocks"));
    pnlBuySellStocks_->setCollapsible(1);
    pnlBuySellStocks_->setCentralWidget(cwBuySellStocks_);

    {
        lblStockCode_->setId("lblStockCode_");
        lblStockCode_->setStyleClass(WString::fromUTF8(""));
        lblStockCode_->setInline(0);
        lblStockCode_->setTextFormat((TextFormat)0);
        lblStockCode_->setText(WString::fromUTF8("Stock Code"));

        cbxStockCode_->setId("edtStockCode_");
        cbxStockCode_->setStyleClass(WString::fromUTF8("form-control form-control"));
        cbxStockCode_->setInline(1);
        cbxStockCode_->setEmptyText(WString::fromUTF8(""));

        lblStockPrice_->setId("lblStockPrice_");
        lblStockPrice_->setStyleClass(WString::fromUTF8(""));
        lblStockPrice_->setInline(1);
        lblStockPrice_->setTextFormat((TextFormat)0);
        lblStockPrice_->setText(WString::fromUTF8(""));

        lblQuantity_->setId("lblQuantity_");
        lblQuantity_->setStyleClass(WString::fromUTF8(""));
        lblQuantity_->setInline(0);
        lblQuantity_->setTextFormat((TextFormat)0);
        lblQuantity_->setText(WString::fromUTF8("Quantity"));

        edtQuantity_->setId("edtQuantity_");
        edtQuantity_->setStyleClass(WString::fromUTF8("form-control form-control"));
        edtQuantity_->setInline(1);
        edtQuantity_->setEmptyText(WString::fromUTF8(""));
        edtQuantity_->setInputMask("0000");

        lblPrice_->setId("lblPrice_");
        lblPrice_->setStyleClass(WString::fromUTF8(""));
        lblPrice_->setInline(0);
        lblPrice_->setTextFormat((TextFormat)0);
        lblPrice_->setText(WString::fromUTF8("Price"));

        edtPrice_->setId("edtPrice_");
        edtPrice_->setStyleClass(WString::fromUTF8("form-control form-control"));
        edtPrice_->setInline(0);
        edtPrice_->setEmptyText(WString::fromUTF8(""));
        edtPrice_->setInputMask("000.00");

        btnBuy_->setId("btnBuy_");
        btnBuy_->setStyleClass(WString::fromUTF8("btn btn-default with-label btn btn-default with-label"));
        btnBuy_->setInline(1);
        btnBuy_->setEmptyText(WString::fromUTF8(""));
        btnBuy_->setText(WString::fromUTF8("Buy"));
        btnBuy_->setLink(WLink(""));

        btnSell_->setId("btnSell_");
        btnSell_->setStyleClass(WString::fromUTF8("btn btn-default with-label btn btn-default with-label"));
        btnSell_->setInline(1);
        btnSell_->setEmptyText(WString::fromUTF8(""));
        btnSell_->setText(WString::fromUTF8("Sell"));
        btnSell_->setLink(WLink(""));

        btnQuote_->setId("btnQuote_");
        btnQuote_->setStyleClass(WString::fromUTF8("btn btn-default with-label btn btn-default with-label"));
        btnQuote_->setInline(1);
        btnQuote_->setEmptyText(WString::fromUTF8(""));
        btnQuote_->setText(WString::fromUTF8("Quote"));
        btnQuote_->setLink(WLink(""));
    }

    pnlTransactionLog_->setId("pnlTransactionLog_");
    pnlTransactionLog_->setStyleClass(WString::fromUTF8("panel panel-default panel panel-default"));
    pnlTransactionLog_->setInline(0);
    pnlTransactionLog_->setTitle(WString::fromUTF8("Transactions Log"));
    pnlTransactionLog_->setCollapsible(1);
    pnlTransactionLog_->setCentralWidget(cwTransactionLog_);

    {
        btnTrans_->setId("btnTransactiosView_");
        btnTrans_->setStyleClass(WString::fromUTF8("btn btn-default with-label btn btn-default with-label"));
        btnTrans_->setInline(1);
        btnTrans_->setEmptyText(WString::fromUTF8(""));
        btnTrans_->setText(WString::fromUTF8("View"));
        btnTrans_->setLink(WLink(""));

        tblTransactions_->setId("tblTransactions_");
        tblTransactions_->setStyleClass(WString::fromUTF8("table-bordered table-striped table-hover table"));
        tblTransactions_->setInline(0);
        tblTransactions_->setHeaderCount(1, Orientation::Horizontal);
        tblTransactions_->setHeaderCount(1, Orientation::Vertical);
    }

    pnlPortfolio_->setId("pnlPortfolio_");
    pnlPortfolio_->setStyleClass(WString::fromUTF8("panel panel-default panel panel-default"));
    pnlPortfolio_->setInline(0);
    pnlPortfolio_->setTitle(WString::fromUTF8("Trader's Portfolio"));
    pnlPortfolio_->setCollapsible(1);
    pnlPortfolio_->setCentralWidget(cwPortfolio_);

    {
        btnPortfolio_->setId("btnPortfolio_");
        btnPortfolio_->setStyleClass(WString::fromUTF8("btn btn-default with-label btn btn-default with-label"));
        btnPortfolio_->setInline(1);
        btnPortfolio_->setEmptyText(WString::fromUTF8(""));
        btnPortfolio_->setText(WString::fromUTF8("View"));
        btnPortfolio_->setLink(WLink(""));

        tblPortfolio_->setId("tblPortfolio_");
        tblPortfolio_->setStyleClass(WString::fromUTF8("table-bordered table-striped table-hover table"));
        tblPortfolio_->setInline(0);
        tblPortfolio_->setHeaderCount(1, Orientation::Horizontal);
        tblPortfolio_->setHeaderCount(1, Orientation::Vertical);
    }
}

