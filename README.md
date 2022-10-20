# Laboratory instrument control emulator
# multithreaded programming

Device:

The laboratory device consists of a pump and two pressure sensors - D1, D2. The pump is controlled by commands
- Turn on at a given speed
- Stop

Each pressure sensor is controlled by commands
- Set pressure
- Reset pressure to zero

*************************************************

Emulator operation:

- The command handler is executed in a separate thread, the handler provides for the order in which commands are executed.

- It is possible to submit commands by the user through the console.

- The handler executes commands with a specified period. When the next period ends, the handler extracts one command from the queue and executes it, then sleeps until the end of the new period.

- If there are no commands in the queue, the handler updates the device state:

*************************************************

-> For a pump:
* Current operating mode: "Stopped" / "Speed"

* Current speed. If the pump is on, i.e. in the "Speed" mode, the current speed is equal to the set one
on command plus a little random noise. If disabled, the current speed is exactly 0.

-> For pressure sensors D1, D2:
* Current pressure of each sensor. The pressure is equal to the commanded one (including if the sensor was zeroed on command) plus a small random noise.
* Pressure difference D1 minus D2.

*************************************************
New commands during the valid period do not wake up the thread, but are queued.

- Possibility to change the period directly in the course of work is provided. When the period changes, the thread wakes up without waiting for the end of the current period.

- Implemented the ability to carefully close the program. When closed, the handler wakes up and ends its thread of execution without waiting for the current period to end. The program waits for the thread to complete and then closes.

- Implemented the ability to display the current status of the device on the screen upon request.
