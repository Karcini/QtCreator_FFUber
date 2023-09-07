Final project for C++ class, create a POS (point of sales) system that fully handles a process of a business.
QT make version - Qt 5.15.2 MinGW 64bit

To run this app, download the 'QtCreator_FFUber_exe' folder
fresh files of the database and receipt are found in the 'other files' folder


GUI displays a functional service for a fake uber based on the fictional land in Final Fantasy 14.  The following is an explanation on the app and how to use it.

The menu allows you to create an account for 'riders' and 'drivers'.  All data is saved onto a database, don't use real passwords this is a mockup.  The app automatically logs you into a 'guest' account, but you can login to rider accounts to create traveling plans in Eorzea.  You cannot login as a driver, but if a driver account is created they will appear as eligible drivers with the rates processed in the creation process.

The map is interactable through the gui and also through the Map tab.  There are no triggers set on the map, this is meant to simply give the feeling that a person in this world would want to see where they are going.

Each Trip is started by selecting a driver, a 'from' destination and a 'to' destination.  Once a selection is legally possible, the app will allow you to add the destination.  The display will show all current information.  Before you confirm a trip, you can add more destinations, but you will be locked to your choice of driver, and previously reached destination.  This way you can set a traveling plan.  You can cancel your trip at any time, and any error messages will display on the bottom right status UI. 

Once a trip is fully finalized, a receipt will be issued and saved onto the database.  This information can be accessed on the transaction history on the Menu.  This will only give the user information of the logged in account.  Note that guests cannot save their transaction history, the starting default only shows the example template of what it will look like if you were to create an account, login, and create trips.