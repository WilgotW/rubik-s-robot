

//I2C drivers for color sensor
//How I2C works:
//The system consists of a master and slaves that is connected to each other via two common lines: SDA and SCL
//SDA is the data line while SCL is the common clock line that all devices will use to be synchronized.  
//Both the SDA and SCL line are connected to a pull up resistor to reduce noise in the data and clock. This means that communications occures by pulling the lines from HIGH to LOW

//1. The master starts by pulling the data line to LOW, this signals to all slaves that a message is comming. 
//2. The master then sends a 8 bit address that's owned by one of the slaves. In the message is an additional read/write bit which tells the correct reciever if it should recieve or send data in the upcoming step
//3. The address reaches all the slaves: The slaves compare the address to it's internal address and checks if there's a match. If not, the internal state machine goes into an ignore mode, which means it wont listen to upcoming data on the SDA line. If there's an match, the correct slave responds to the master by sending an ACK (acknowledgement) to signal that it recieved the signal.
// If the master doesnt recieve an ACK after a timer runs out, it knows that something went wrong, and tries again. 
//4. Now that the master has recieved the ACK, theres an active path between the right slave and the master. Data can now be sent
//5. depending on the write/read bit that was sent on step 2, the slave or the masters sends data. After each packet of data, the reciever needs to send an ACK to confirm that it got everything right.

//To implement this driver, we have to control several registers to make this work:
//Control register: I2C_CR1 and I2C_CR2. These registers are configured to send start and stop condition of the communication. Aswell as enabling ACKs. 
//Data register: I2C_DR is the data register. Data stored here is automaticaly sent out on the SDA line.
//Status registers: I2C_SR1 and I2C_SR2. these registers are used to constantly check that communication is going as planned. All the bits in these registers tells what is going on:
// -SB bit: did start condition finish?
// -ADDR bit: Did sensor ACK its address?
// -TXE bit: is SDR empty so new data can be sent?



