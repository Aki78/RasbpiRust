use std::{thread, time};

const LED: u64 = 13;

fn blink_morse(message: &str) {
    // Morse code dictionary
    let morse_code = vec![
        ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--",
        "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..",
        ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----.", "-----",
        "--..--", ".-.-.-", "..--..",
    ];

    for c in message.chars() {
        if c.is_ascii_alphabetic() {
            let code = morse_code[(c.to_ascii_lowercase() as u8 - b'a') as usize];
            for s in code.chars() {
                if s == '.' {
                    blink(200);
                } else if s == '-' {
                    blink(600);
                }
            }
        } else if c.is_ascii_digit() {
            let code = morse_code[(c as u8 - b'0') as usize + 26];
            for s in code.chars() {
                if s == '.' {
                    blink(200);
                } else if s == '-' {
                    blink(600);
                }
            }
        }
        // Space between letters
        thread::sleep(time::Duration::from_millis(400));
    }
}

fn blink(duration: u64) {
    println!("{}", duration);
    thread::sleep(time::Duration::from_millis(duration));
}

fn main() {
    let message = "Hello World";
    blink_morse(message);
}
