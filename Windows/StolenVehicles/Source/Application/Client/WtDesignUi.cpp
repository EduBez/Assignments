#include "stdafx.h"

#include "WtDesignUi.h"
#include "RESTfull.h"

using namespace rest;
using namespace std;
using namespace Wt;

//
//  WtDesignUi
//
WtDesignUi::WtDesignUi(const Wt::WEnvironment& env)
    // Member Initializer List
    : Wt::WApplication(env)
{
    // Assign callback
    func_ = std::bind(&WtDesignUi::CallBackHandler, this, std::placeholders::_1);

    // Instantiate UI elements
    leReg_ = new WLineEdit();
    leMak_ = new WLineEdit();
    leMod_ = new WLineEdit();
    leOwn_ = new WLineEdit();

    pbReg_ = new WPushButton("Registration");
    pbMak_ = new WPushButton("Make");
    pbMod_ = new WPushButton("Model");
    pbOwn_ = new WPushButton("Owner");
    
    pbAll_ = new WPushButton("Search All Vehicles");

    // UI Event Handlers
    auto func1 = boost::bind(&WtDesignUi::HandlerSearchByRegist, this);
    auto func2 = boost::bind(&WtDesignUi::HandlerSearchByMaker , this);
    auto func3 = boost::bind(&WtDesignUi::HandlerSearchByModel , this);
    auto func4 = boost::bind(&WtDesignUi::HandlerSearchByOwner , this);
    auto func5 = boost::bind(&WtDesignUi::HandlerSearchAll     , this);

    // Setup Events
    leReg_->enterPressed().connect(func1);
    leMak_->enterPressed().connect(func1);
    leMod_->enterPressed().connect(func1);
    leOwn_->enterPressed().connect(func1);

    pbReg_->clicked().connect(func1);
    pbMak_->clicked().connect(func2);
    pbMod_->clicked().connect(func3);
    pbOwn_->clicked().connect(func4);
    pbAll_->clicked().connect(func5);

    setTitle("National Stolen Vehicles Database");
    WebUiCreate(root());
}

//
//  WebUiCreate
//
void WtDesignUi::WebUiCreate(Wt::WContainerWidget* root)
{
    root->setId("WtRoot");
    root->setInline(false);

    WBreak* wbreak = new WBreak();

    // Search options container
    containerOpt_ = new Wt::WContainerWidget(root);

    panelOpt_ = new WPanel(root);
    panelOpt_->setId("WtPanelOpt");

    panelOpt_->setCentralWidget(containerOpt_);
    panelOpt_->setCollapsible(false);
    panelOpt_->setInline(false);
    panelOpt_->setTitle(WString::fromUTF8("Search Options"));
    panelOpt_->setStyleClass(Wt::WString::fromUTF8("panel panel-default panel panel-default"));

    {
        // Table 'Search Options'
        tableOpt_ = new WTable(containerOpt_);
        tableOpt_->setId("WtTableOpt");

        tableOpt_->setInline(false);
        tableOpt_->setStyleClass(WString::fromUTF8("table table-striped table-bordered table-hover"));

        tableOpt_->elementAt(1, 0)->addWidget(leReg_);
        tableOpt_->elementAt(1, 0)->addWidget(pbReg_);

        tableOpt_->elementAt(2, 0)->addWidget(leMak_);
        tableOpt_->elementAt(2, 0)->addWidget(pbMak_);

        tableOpt_->elementAt(3, 0)->addWidget(leMod_);
        tableOpt_->elementAt(3, 0)->addWidget(pbMod_);

        tableOpt_->elementAt(4, 0)->addWidget(leOwn_);
        tableOpt_->elementAt(4, 0)->addWidget(pbOwn_);

        tableOpt_->elementAt(5, 0)->addWidget(wbreak);
        tableOpt_->elementAt(6, 0)->addWidget(pbAll_);
    }

    root->addWidget(new WBreak());

    // Search results container
    containerRes_ = new WContainerWidget(root);

    panelRes_ = new WPanel(root);
    panelRes_->setId("WtPanelRes");

    panelRes_->setCentralWidget(containerRes_);
    panelRes_->setCollapsible(false);
    panelRes_->setStyleClass(WString::fromUTF8("panel panel-default panel panel-default"));
    panelRes_->setInline(false);
    panelRes_->setTitle(WString::fromUTF8("Search Result"));

    {
        // Table 'Search Results'
        tableRes_ = new WTable(containerRes_);
        tableRes_->setId("WtTableRes");

        tableRes_->setInline(false);
        tableRes_->setStyleClass(WString::fromUTF8("table table-bordered table-hover table-striped"));

        tableRes_->setWidth(WLength("50%"));
    }
}

void WtDesignUi::WebUiPopulateTable(const rows_t& rows)
{
    // Clear all table elements
    tableRes_->clear();

    // Check row count
    if (rows.size())
    {
        // Create table header
        tableRes_->elementAt(0, 0)->addWidget(new WText("Registration"));
        tableRes_->elementAt(0, 1)->addWidget(new WText("Make"));
        tableRes_->elementAt(0, 2)->addWidget(new WText("Model"));
        tableRes_->elementAt(0, 3)->addWidget(new WText("Owner"));

        // Line counter
        int l = 1;
    
        // Insert table elements
        for (auto it : rows)
        {
            tableRes_->elementAt(l, 0)->addWidget(new WText(get<0>(it)));
            tableRes_->elementAt(l, 1)->addWidget(new WText(get<1>(it)));
            tableRes_->elementAt(l, 2)->addWidget(new WText(get<2>(it)));
            tableRes_->elementAt(l, 3)->addWidget(new WText(get<3>(it)));

            // Increment line
            l += 1;
        }
    }
}

// UI Event Handlers
void WtDesignUi::HandlerSearchAll()
{
    // Clear edits before requesting
    leReg_->setText("");
    leMak_->setText("");
    leMod_->setText("");
    leOwn_->setText("");

    RESTfull r;
    r.Invoke(func_, "All", "ALL");
}

void WtDesignUi::HandlerSearchByRegist()
{
    // Clear edits before requesting
    leMak_->setText("");
    leMod_->setText("");
    leOwn_->setText("");

    RESTfull r;
    r.Invoke(func_, "Registration", leReg_->text());
}

void WtDesignUi::HandlerSearchByMaker()
{
    // Clear edits before requesting
    leReg_->setText("");
    leMod_->setText("");
    leOwn_->setText("");

    RESTfull r;
    r.Invoke(func_, "Make", leMak_->text());
}

void WtDesignUi::HandlerSearchByModel()
{
    // Clear edits before requesting
    leReg_->setText("");
    leMak_->setText("");
    leOwn_->setText("");

    RESTfull r;
    r.Invoke(func_, "Model", leMod_->text());
}

void WtDesignUi::HandlerSearchByOwner()
{
    // Clear edits before requesting
    leReg_->setText("");
    leMak_->setText("");
    leMod_->setText("");

    RESTfull r;
    r.Invoke(func_, "Owner", leOwn_->text());
}

// Callback Function
void WtDesignUi::CallBackHandler(web::json::value& value)
{
    rows_t rows;

    if (!value.is_null())
    {
        for (int id=0; id < value.size(); ++id)
        {
            auto key = boost::lexical_cast<wstring>(id);
            auto val = value.at(key);

            // Extract the record
            wstring c1 = val.at(U("Registration")) .to_string();
            wstring c2 = val.at(U("Make"))         .to_string();
            wstring c3 = val.at(U("Model"))        .to_string();
            wstring c4 = val.at(U("Owner"))        .to_string();

            // Remove "" from fields
            boost::replace_all(c1, "\"", "");
            boost::replace_all(c2, "\"", "");
            boost::replace_all(c3, "\"", "");
            boost::replace_all(c4, "\"", "");

            // Save row
            rows.push_back(std::make_tuple(c1, c2, c3, c4));
        }
    }
    // Update UI
    WebUiPopulateTable(rows);
}
