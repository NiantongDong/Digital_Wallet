# Digital_Wallet

The purpose of this project is to design a digital wallet to secure crypto transaction. A example from the market is [Ledger](https://www.ledger.com/). We are using FRDM to develop this device through this semester. This repo will be updated regularly to keep track the progress. 

To test, please download the above folder (frdmk64f_mbedtls_benchmark) and open the project in MCUXpresso. Main code is in /source/wallet_main.c.

Please check out video_links.txt for higher quality demos on Youtube.

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

3/29/2021:

Plan is somewhat revised. We will be focusing purely on K64F and C. First we need to get the code up and running, and do reserach.

4/05/2021: 

We have found some solid example code through MBEDTLS demos! However it has been very difficult to get the code up and running using any of the AWS demos.

4/12/2021:

Well we got the examples working. We were stuck for a week trying to get the various contexts loaded. There was definitely some backend issue setting up the K64F. Way more stuff to configure than embedded Linux. For now we have the code running on an MBEDTLS demo.

4/19/2021: 

Wow this semester is going by quickly. We're nearly finished. But at the same time, the code is nearly finished! They key was using the &olen variable instead of strlen(some_message)

4/26/2021:

Final week. Time to record the videos, and edit the paper. 

4/28/2021:

Videos and paper uploaded! There's still the chance I'll update something, but this project is essentially finished. 

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
