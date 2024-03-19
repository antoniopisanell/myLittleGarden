# myLittleGarden

## To Run the Application
### Prerequists
- Be sure to have docker installed on your machine

### Steps
1. open the makefile and execute the following command
```bash
make create_database
```
This will create a docker container with a mongodb instance running on port 27017

2. open the makefile and execute the following command
```bash
make install_requirements
```
To install the required python packages

3. (*Optional*) open the makefile and execute the following command
```bash
make populate_database
```
If you want to populate the database with some initial data, each time you run this command it will remove the whole collection and inseert the 5 initial documents

4. open the makefile and execute the following command
```bash
make run_server
```
This will start the server on port 10000 (by default) the makefile will take automatically the ip address, be sure to use the correct one

It is also possible to run full locally for testing purposes, just run the following command
```bash
make run_mock_esp32
```
This will mock the service of the `esp32` this time is a python server that will send the data to the main server

This command launch both the server and the mock esp32