Project Directory Structure

How to replicate the project folder structure

The uploaded file Eduardo_Bezerra_CppAssignment2.zip must be extracted to a <root drive> such as C:\.
After the file has been extracted you should end with a directory structure like this:

<root driver>\Eduardo_Bezerra_CppAssignment2\Design.doc
<root driver>\Eduardo_Bezerra_CppAssignment2\ReadMe.txt
<root driver>\Eduardo_Bezerra_CppAssignment2\Demo
<root driver>\Eduardo_Bezerra_CppAssignment2\Source
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Application
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Application\Client
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Application\Service
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Binaries
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Docs
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\boost_1_62_0
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\MySQL
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\MySQL\include
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\MySQL\include\cppconn
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\MySQL\lib
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\Wt
<root driver>\Eduardo_Bezerra_CppAssignment2\Source\Scripts


Libraries Installation

How to install and configure the Project Libraries


The project is dependent on the following libraries

Wt C++ Web Toolkit

•	Download the Wt C++ Web Toolkit library from:
•	https://github.com/emweb/wt/releases/download/3.3.6/Wt-3.3.6-msvs2015-Windows-x86-SDK.zip
•	Extract the file Wt-3.3.6-msvs2015-Windows-x86-SDK.zip to: <root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\Wt-3.3.6-msvs2015-Windows-x86-SDK
•	Rename the folder to: <root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\Wt

Boost Libraries 1.62

•	Download the Boost Libraries for Visual Studio 2015 from:
•	https://sourceforge.net/projects/boost/files/boost-binaries/1.62.0/boost_1_62_0-msvc-14.0-32.exe/download
•	Run the installation program boost_1_62_0-msvc-14.0-32.exe
•	Choose the directory <root driver>\Eduardo_Bezerra_CppAssignment2\Source\Library\boost_1_62_0 as the path for installation
•	Click Next to install


C++ REST SDK Library

Note on upload size restriction

Due to the restriction on upload size the project does not contain the C++ REST SDK installed

When opening the project solution RESTfullClient.sln or RESTfullService.sln you will be asked by NuGet to download the C++ REST SDK

You must accept the download in order to compile both projects.


MySQL Server Installation

How to install and configure MySQL Community Edition


A.	Download the MySQL installer from: http://dev.mysql.com/downloads/installer/
B.	Choose the options Windows (x86, 32-bit), MSI Installer - 5.7.16 - 385.2M
C.	Run the installer program: mysql-installer-community-5.7.16.0.msi
D.	Accept the license terms
E.	Choose Developer Default
F.	Ignore any Check Requirements and click Next
G.	Click Next to configure MySQL
H.	On page Type and Network accept the defaults  and click Next
I.	On page Accounts and Roles, option MySQL Root Password type root as the password and confirm the same password
J.	Click Next to continue
K.	On page Windows Service accept the defaults  and click Next
L.	On page  Plugins and Extensions accept the defaults  and click Next
M.	On page Apply Server Configuration click Execute
N.	Click Finish to proceed
O.	On page Product Configuration click Next to advance
P.	On page Connect To Server click Check and then Next
Q.	On page Apply Server Configuration click Execute and then Finish
R.	On page Product Configuration click Next to advance
S.	On page Installation Complete click Finish to end installation


Database & Tables Creation

How to create the database and populate the tables


•	Execute the MySQL Workbench program
•	On MySQL Connection click Local Instance MySQL57
•	Enter root as the password, check Save password in vault and click OK
•	Click File / Run SQL Script
•	Select the file <root driver>\Eduardo_Bezerra_CppAssignment2\Source\Scripts\NationalStolenVehicles.sql
•	On the Run SQL Script window click Run
•	Click Close to end the process
•	Close the MySQL Workbench program


Visual Studio Community 2015 Update 3

How to download Visual Studio 2015 with update 3


•	You can download VS 2015 from:
•	https://www.visualstudio.com/downloads/
•	Click on the option View All Downloads
•	Select Visual Studio Community 2015 with Update 3 – Free
•	Check the ISO option
•	Click the Download button


Final Notes

Pre-built project binaries


On the directory <root driver>\Eduardo_Bezerra_CppAssignment2\Source\Binaries you will find fully functional binaries ready to be executed to test the application.
