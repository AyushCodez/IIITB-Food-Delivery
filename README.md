# IIITB Food-Delivery

## Working of the code
The code is run by calling functions from customer_UI.c, restowner_UI.c, and delivery_UI.c that allow you to login and use functionality of each aspect of food delivery respectively. These import there functions from other files where the various features are implemented.

## Features
### Customer
As a customer, you can add money to your account. Using this money you can order from added restaurants and filter items by various parameters. Once you place your order, an OTP is given to you thta is used to confirm that the food has been delivered to you. You can also keep a track of all your orders, past and current.

### Deliverer
As a deliverer, you can accept deliveries and money will be added to your account based on the distance driven.

### Restaurant Owner
As a restaurant owner you can add restuarants and add various items to the menu, money will be added to your account as per the orders. You can track all orders recieved.

## How to run
We are using a make file to create the 3 executable files from individual c codes.
To use the MakeFile you can run the commands `make customer` ,`make restowner`, `make delivery` to create the executables customer,restowner and delivery respectively. Run these executables to run the app.
