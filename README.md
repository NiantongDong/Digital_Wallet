# Digital_Wallet

The purpose of this project is to design a digital wallet to secure crypto transaction. A example from the market is [Ledger](https://www.ledger.com/). We are using FRDM to develop this device through this semester. This repo will be updated regularly to keep track the progress. 

To test, please download the above folder and open the project in MCUXpresso. Main code is in /source/wallet_main.c.

## Team Member

- Benjamin Kuter
- Niantong Dong

## Requirement for this project

- FRDM-K64F board
- Ethernet cable
- Type-C cable
- MCUXpresso IDE, C development
- Terminal to listen the port (Tera Term, Putty)

## Milestones

3/15/2021: 

Picking Pi vs FRDM. 

Result: We decided to pick the FRDM board, as it has the most secure end-result for our project. A pi would require too much overhead maintenance to ensure nothing icky is on the distro. With FRDM distribution, we can precisely code how access to our wallet is conducted. 

3/22/2021: 

Interfacing with the FRDM board via AWS FreeRTOS. Goal is simple. Prompt the FRDM board for input by providing a plaintext “password”. If the stdin password matches the FRDM’s hardcoded password we stdout a simple “Hello World\n!”.	

3/29/2021: TBD
4/05/2021: TBD

## Division of Labor

Physical Security - Ben

General Device Architecture - Ben

Encryption & Hashing Algorithms - Niantong

Github Management - Niantong

Documentation - BothSecurity Testbench - Both*i.e. trying to break our device**Everything working as intended!*

Input & Output Parsing Logic - Niantong *High level design through python.*

I/O Implementation - Ben



## License

[MIT](https://choosealicense.com/licenses/mit/)

​	
