#include "stdafx.h"

#include <CkMailMan.h>
#include <CkEmail.h>

#include "SMTP.h"

using namespace smtp;
using namespace std;

//
//  SMTP
//

// Ctor
SMTP::SMTP(string server, unsigned port, string user, string password)
    // Member Initialization List
    : server_   (server)
    , port_     (port)
    , username_ (user)
    , password_ (password)
{
}

// Member Function
bool SMTP::Send(string from, string to, string subject, string message)
{
    bool result = true;

    CkMailMan smtp;

    // This is a 30 day trial library
    result = smtp.UnlockComponent("30-day trial");

    if (!result)
    {
        wcout << smtp.lastErrorText() << endl;
        return result;
    }

    smtp.put_SmtpHost("localhost");

    smtp.put_SmtpUsername(username_.c_str());
    smtp.put_SmtpPassword(password_.c_str());

    CkEmail email;

    email.put_Subject ("wIQserver_mt Alert");
    email.put_Body    (message.c_str());
    email.put_From    (from.c_str());
    email.AddTo       ("<Eduardo Bezerra>", to.c_str());

    result = smtp.SendEmail(email);

    if (!result)
    {
        wcout << smtp.lastErrorText() << endl;
        return result;
    }

    result = smtp.CloseSmtpConnection();

    if (!result)
    {
        wcout << smtp.lastErrorText() << endl;
        return result;
    }

    return result;
}
