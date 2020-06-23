#include "stdafx.h"

#include "View.h"
#include "ViewModel.h"

using namespace std;
using namespace types;
using namespace Wt;

//
//  TViewModel
//
TViewModel::TViewModel(TView* view)
    // Member Initializer List
    : view_(view)
{
    model_ = make_unique<TModel>(this);
}

void TViewModel::ConnectEvent(OpID opID, WPushButton* obj)
{
    if (opID == OpID::Buy)
    {
        obj->clicked().connect(bind(&TViewModel::EventHandler1, this));
    }
    else if (opID == OpID::Login)
    {
        obj->clicked().connect(bind(&TViewModel::EventHandler3, this));
    }
    else if (opID == OpID::Portfolio)
    {
        obj->clicked().connect(bind(&TViewModel::EventHandler4, this));
    }
    else if (opID == OpID::Quote)
    {
        obj->clicked().connect(bind(&TViewModel::EventHandler5, this));
    }
    else if (opID == OpID::Sell)
    {
        obj->clicked().connect(bind(&TViewModel::EventHandler6, this));
    }
    else if (opID == OpID::SignUp)
    {
        obj->clicked().connect(bind(&TViewModel::EventHandler7, this));
    }
    else if (opID == OpID::TransLog)
    {
        obj->clicked().connect(bind(&TViewModel::EventHandler8, this));
    }
}

void TViewModel::GetStockCodes()
{
    // Retrieve all stock codes
    wstring url = L"http://localhost:9090/wIQserver_mt/StockCodes/";
    model_->HttpGet(OpID::Codes, url);
}

bool TViewModel::IsLogged()
{
    user_ = view_->GetUser();
    pwd_  = view_->GetPwd();

    if (user_.empty() || pwd_.empty())
    {
        ShowMessage(L"Warning", L"User must be logged");
        return false;
    }
    return true;
}

void TViewModel::ShowMessage(const wstring& title, const wstring& text)
{
    WMessageBox* msg = new WMessageBox(title, text, Wt::Information, Wt::Ok);

    msg->setModal(false);
    msg->buttonClicked().connect(bind([=](){delete msg;}));
    msg->show();

    return;
}

//
//  Ui Event Handlers
//
void TViewModel::EventHandler1()
{
    if (IsLogged())
    {
        wstring quantity = view_->edtQuantity_ ->text();
        wstring price    = view_->edtPrice_    ->text();

        int idx = view_->cbxStockCode_->currentIndex();
        wstring stock = view_->cbxStockCode_->itemText(idx);

        if (stock.empty() || quantity.empty() || price.empty()) {
            ShowMessage(L"Error", L"Must inform Stock, Quantity and Price");
        }
        else
        {
            wstring url = L"http://localhost:9090/wIQserver_mt/";
            const wchar_t* path = L"StockBuy";

            web::json::value json;

            json[0] = web::json::value::string(user_);
            json[1] = web::json::value::string(pwd_);

            json[2] = web::json::value::string(stock);
            json[3] = web::json::value::string(quantity);
            json[4] = web::json::value::string(price);

            // Perform Http request
            model_->HttpPost(OpID::Buy, path, url, json);
        }
    }
}

void TViewModel::EventHandler3()
{
    wstring arg1 = view_->edtUser_->text();
    wstring arg2 = view_->edtPwd_ ->text();

    if (arg1.empty() || arg2.empty())
    {
        ShowMessage(L"Warning", L"Must fill User Name and Password");
        return;
    }

    wstring url = L"http://localhost:9090/wIQserver_mt/Login/%1%/%2%/";
    url = boost::str(boost::wformat(url) % arg1 % arg2);

    // Perform Http request
    model_->HttpGet(OpID::Login, url);
}

void TViewModel::EventHandler4()
{
    if (IsLogged())
    {
        wstring url = L"http://localhost:9090/wIQserver_mt/Portfolio/%1%/%2%/";
        url = boost::str(boost::wformat(url) % user_ % pwd_);

        // Perform Http request
        model_->HttpGet(OpID::Portfolio, url);
    }
}

void TViewModel::EventHandler5()
{
    if (IsLogged())
    {
        int idx = view_->cbxStockCode_->currentIndex();
        wstring code = view_->cbxStockCode_->itemText(idx);

        wstring url = L"http://localhost:9090/wIQserver_mt/StockQuote/%1%/%2%/%3%/";
        url = boost::str(boost::wformat(url) % user_ % pwd_ % code);

        // Perform Http request
        model_->HttpGet(OpID::Quote, url);
    }
}

void TViewModel::EventHandler6()
{
    if (IsLogged())
    {
        wstring quantity = view_->edtQuantity_ ->text();
        wstring price    = view_->edtPrice_    ->text();

        int idx = view_->cbxStockCode_->currentIndex();
        wstring stock = view_->cbxStockCode_->itemText(idx);

        if (stock.empty() || quantity.empty() || price.empty()) {
            ShowMessage(L"Error", L"Must inform Stock, Quantity and Price");
        }
        else
        {
            wstring url = L"http://localhost:9090/wIQserver_mt/";
            const wchar_t* path = L"StockSell";

            web::json::value json;

            json[0] = web::json::value::string(user_);
            json[1] = web::json::value::string(pwd_);

            json[2] = web::json::value::string(stock);
            json[3] = web::json::value::string(quantity);
            json[4] = web::json::value::string(price);

            // Perform Http request
            model_->HttpPost(OpID::Sell, path, url, json);
        }
    }
}

void TViewModel::EventHandler7()
{
    wstring arg1 = view_->edtUser_->text();
    wstring arg2 = view_->edtPwd_ ->text();

    if (arg1.empty() || arg2.empty()) {
        ShowMessage(L"Warning", L"Must fill User Name and Password");
        return;
    }

    wstring url = L"http://localhost:9090/wIQserver_mt/";
    const wchar_t* path = L"SignUp";

    web::json::value json;
    json[0] = web::json::value::string(arg1);
    json[1] = web::json::value::string(arg2);

    // Perform Http request
    model_->HttpPost(OpID::SignUp, path, url, json);
}

void TViewModel::EventHandler8()
{
    if (IsLogged())
    {
        wstring url = L"http://localhost:9090/wIQserver_mt/Transactions/%1%/%2%/";
        url = boost::str(boost::wformat(url) % user_ % pwd_);

        // Perform Http request
        model_->HttpGet(OpID::TransLog, url);
    }
}

//
//  Http Result Handlers
//
void TViewModel::HttpResultHandler1(web::json::value json)
{
    if (json == true) {
        ShowMessage(L"Buy Stock", L"Operation completed. View Transactions Log");
    }
    else {
        ShowMessage(L"Buy Stock", L"Operation completed with error");
    }
}

void TViewModel::HttpResultHandler2(web::json::value json)
{
    // Fill ComboBox with stock codes
    for (unsigned i = 0; i < json.size(); ++i)
    {
        wstring code = json[i].as_string();
        view_->cbxStockCode_->addItem(code);
    }
}

void TViewModel::HttpResultHandler3(web::json::value json)
{
    if (json == false) {
        ShowMessage(L"Login Info", L"Invalid User Name or Password");
    }
    else
    {
        // Store values in the main application
        view_->SetUser();
        view_->SetPwd ();

        ShowMessage(L"Login Info", L"Login completed successfully");
    }
}

void TViewModel::HttpResultHandler4(web::json::value json)
{
    auto p = view_->tblPortfolio_;

    // Clear all table elements
    p->clear();

    // Create table header
    p->elementAt(0, 0)->addWidget(new WText(L"Stock" ));
    p->elementAt(0, 1)->addWidget(new WText(L"Company Name" ));
    p->elementAt(0, 2)->addWidget(new WText(L"Quantity" ));
    p->elementAt(0, 3)->addWidget(new WText(L"Total Cost"));
    p->elementAt(0, 4)->addWidget(new WText(L"Last Sale Price"));

    for (auto it = json.as_object().cbegin(); it != json.as_object().cend(); ++it)
    {
        const wstring& name = it->first;
        const web::json::value& obj = it->second;

        // Line counter
        int l = 1;

        for (auto i : obj.as_array())
        {
            auto c1 = i[ L"StockID"      ].as_string();
            auto c2 = i[ L"CompanyName"  ].as_string();
            auto c3 = i[ L"Quantity"     ].as_string();
            auto c4 = i[ L"TotalCost"    ].as_string();
            auto c5 = i[ L"LastSalePrice"].as_string();

            p->elementAt(l, 0)->addWidget(new WText(c1));
            p->elementAt(l, 1)->addWidget(new WText(c2));
            p->elementAt(l, 2)->addWidget(new WText(c3));
            p->elementAt(l, 3)->addWidget(new WText(c4));
            p->elementAt(l, 4)->addWidget(new WText(c5));

            // Increment line
            l += 1;
        }
    }
}

void TViewModel::HttpResultHandler5(web::json::value json)
{
    wstring code = L" $" + json.as_string();
    view_->lblStockPrice_->setText(code);
}

void TViewModel::HttpResultHandler6(web::json::value json)
{
    if (json == true) {
        ShowMessage(L"Sell Stock", L"Operation completed. View Transactions Log");
    }
    else {
        ShowMessage(L"Sell Stock", L"Operation completed with error");
    }
}

void TViewModel::HttpResultHandler7(web::json::value json)
{
    if (json == false) {
        ShowMessage(L"Sign up Info", L"User Name already exists");
    }
    else
    {
        // Store values in the main application
        view_->SetUser();
        view_->SetPwd ();

        ShowMessage(L"Sign up Info", L"Sign up completed successfully");
    }
}

void TViewModel::HttpResultHandler8(web::json::value json)
{
    auto p = view_->tblTransactions_;

    // Clear all table elements
    p->clear();

    // Create table header
    p->elementAt(0, 0)->addWidget(new WText(L"Stock" ));
    p->elementAt(0, 1)->addWidget(new WText(L"Quantity" ));
    p->elementAt(0, 2)->addWidget(new WText(L"Date Time"));
    p->elementAt(0, 3)->addWidget(new WText(L"Operation"));
    p->elementAt(0, 4)->addWidget(new WText(L"Status"   ));

    for (auto it = json.as_object().cbegin(); it != json.as_object().cend(); ++it)
    {
        const wstring& name = it->first;
        const web::json::value& obj = it->second;

        // Line counter
        int l = 1;

        for (auto i : obj.as_array())
        {
            auto c1 = i[ L"StockID"  ].as_string();
            auto c2 = i[ L"Quantity" ].as_string();
            auto c3 = i[ L"DateTime" ].as_string();
            auto c4 = i[ L"Operation"].as_string();
            auto c5 = i[ L"Status"   ].as_string();

            p->elementAt(l, 0)->addWidget(new WText(c1));
            p->elementAt(l, 1)->addWidget(new WText(c2));
            p->elementAt(l, 2)->addWidget(new WText(c3));
            p->elementAt(l, 3)->addWidget(new WText(c4));
            p->elementAt(l, 4)->addWidget(new WText(c5));

            // Increment line
            l += 1;
        }
    }
}
