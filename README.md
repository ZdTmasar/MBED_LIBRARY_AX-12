# MBED_LIBRARY_AX-12
This is a library based on MBED to control and command AX-12+ Dynamixel servomotors.


HOW TO USE IT :

  Create a serial bus thanks to the Comm_AX12, just select 2 serial port of your nucleo board (these ports need to have a USART function). Then you can affect this bus to an AX12 object You have differents ways to create an AX12 object :
      -You don't know the adress nor the Baudrate;
      -You know the adress but not the Baudrate
      -You know the adress and the Baudrate
  If you don't know the adress, you can use the function SetID but only one motor has to be linked to the bus, otherwise, all the motors will have the same adress.
  If you don't know the Baudrate, the default one is 115200. That's the default one of the AX12 (and your board).
  
  The Init function is usefull because it sets all the intern contraints to the maximum (Torque limit, Ange limit, temperature limit, MAx Torque routine (it won't stop if the maximum Torque is achieved but the led will be light on).
  
  Once you've created your object you can control all your AX12 thanks to the different function (EndlessTurn, GoToPosition for a precise angle between 0 and 300°, etc..)
  I let you understand the other function, they are really easy to understand.
  
  If you have any question, you can ask it at my email : thomas.saliba@hotmail.fr
  
  
  !!!!! Right now, i can't receive information from the motor but i'l working on it !!!!!
  
  
