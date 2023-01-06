use rppal::gpio::{Gpio, Level, OutputPin}; // Import the necessary modules for working with GPIO pins.
use std::env; // Import the env module for parsing command line arguments.
use std::thread; // Import the thread module for sleeping.
use std::time::Duration; // Import the Duration type for specifying sleep times.

fn main() {
    let args: Vec<String> = env::args().collect(); // Get a vector of the command line arguments.

    // Check that a pin number was provided as an argument.
    if args.len() < 2 {
        println!("Usage: gate_control <pin number>");
        return;
    }

    // Try to parse the pin number from the command line argument.
    let pin = match args[1].parse::<u8>() {
        Ok(num) => num, // If the parse was successful, use the resulting number.
        Err(_) => { // If the parse failed, print an error message and exit.
            println!("Invalid pin number");
            return;
        }
    };

    // Initialize the GPIO interface and get a handle to the specified pin.
    let mut gpio = Gpio::new().unwrap();
    let mut pin = gpio.get(pin).unwrap().into_output();

    // Run an infinite loop to turn the gate on and off repeatedly.
    loop {
        println!("Turning on the gate");
        pin.set_high(); // Turn the gate on by setting the pin to a high level.
        thread::sleep(Duration::from_secs(5)); // Sleep for 5 seconds.

        println!("Turning off the gate");
        pin.set_low(); // Turn the gate off by setting the pin to a low level.
        thread::sleep(Duration::from_secs(5)); // Sleep for 5 seconds.
    }
}
