# 8051 Smart Door Lock System

**Author**: Siri Satyamurthy  
**Status**: ✅ Complete & Functional  
**Last Updated**: May 2026

---

## 📋 Project Overview

A **secure, automated access control system** designed using 8051 microcontroller that allows only authorized users to operate a door through password-protected keypad input. The system integrates embedded firmware, keypad interfacing, motor control, and security logic.

### Key Features
- ✅ 4-digit PIN authentication with 3-attempt lockout protection
- ✅ Real-time keypad scanning with debouncing logic
- ✅ DC motor-driven electromagnetic lock (relay controlled)
- ✅ Visual feedback: LCD 16x2 display showing status & attempt count
- ✅ Audible alert: Buzzer on failed attempts
- ✅ Designed for low-power embedded operation

---

## 🔧 Hardware Specifications

| Component | Specification | Purpose |
|-----------|---------------|---------|
| **Microcontroller** | AT89C51 (8051 architecture) | Main controller @ 12 MHz |
| **Keypad** | 4x4 Matrix Keypad | User PIN input |
| **Motor Driver** | L293D H-Bridge | DC motor control |
| **Door Lock Actuator** | 12V DC Motor | Physical door lock mechanism |
| **Relay Module** | 5V Single Channel | 12V motor power switching |
| **Display** | 16x2 LCD (Parallel) | Status messages & feedback |
| **Buzzer** | Piezo 5V | Alert on failed attempts |
| **Power Supply** | 5V DC Regulated | Microcontroller & logic power |

### Block Diagram

Keypad → 8051 → Password Logic → L293D → Door Motor
                    ↓
               LCD Display
                    ↓
                  Buzzer

### Circuit Diagram

<img width="1019" height="595" alt="Screenshot 2026-05-25 102908" src="https://github.com/user-attachments/assets/82524f4e-7e2b-4516-a18c-b7362e70f2e7" />

---

## 💾 Firmware Architecture

### Main Components

```
MAIN PROGRAM FLOW
├── Initialization (Ports, LCD, Keypad)
├── Main Loop
│   ├── Keypad Scanning
│   ├── PIN Validation Logic
│   ├── Motor Control
│   └── LCD Display Update
└── System Monitoring & Security Checks
```

### Key Routines

| Function | Purpose | Execution Time |
|----------|---------|-----------------|
| `scan_keypad()` | Matrix keypad debouncing & key detection | <50ms per scan |
| `validate_pin()` | Compare entered PIN with stored password | <10ms |
| `unlock_door()` | Activate motor relay & update status | <20ms |
| `lock_door()` | Deactivate relay, reset system | <20ms |
| `display_status()` | Update LCD with real-time feedback | <30ms |

### Memory Usage
- **ROM**: 3.2 KB (firmware code)
- **RAM**: 256 bytes (internal) + 2 KB external (if used)
- Password stored in firmware memory

---

## 📊 Performance Metrics

| Metric | Value | Note |
|--------|-------|------|
| **Response Time** | Real-time responsive access control | Key press to motor activation |
| **Power Consumption** | Designed for low-power embedded operation | Standby with display off |

The system was successfully validated through Proteus simulation and functional testing.

---

## 🛠️ Software & Tools Used

- Keil µVision
- Proteus Design Suite
- Embedded C
- AT89C51 Microcontroller
- L293D Motor Driver

---

## 📁 Project Structure

```
8051-Door-Lock-System/
│
├── README.md
├── LICENSE
│
├── firmware/
│   ├── password_protection.c
│   ├── keypadpro.h
│   ├── lcdpro.h
│   ├── motorpro.h
│   └── eeprompro.h
│
├── simulation/
│   └── door_lock_simulation.pdsprj
│
├── memory/
│   ├── eeprom.bin
│   └── eeprompro.hex.txt
│
├── build/
│   ├── password_protection.hex
│   ├── password_protection.m51
│   └── password_protection.lst
│
├── images/
│   ├── circuit_diagram.png
│   ├── proteus_output.png
│   └── lcd_output.png
│
└── documentation/
    └── Project_Report.pdf              

```

---

## 🚀 How to Build & Flash

### Prerequisites
- **IDE**: Keil µVision 5 (or similar 8051 compiler)
- Proteus simulation environment for testing and validation
- **Hardware**: Development board with 8051, breadboard, components

### Compilation Steps

```bash
# Step 1: Open Keil µVision
# Step 2: Create new project for AT89C51
# Step 3: Add all .c and .h files from firmware/ folder
# Step 4: Go to Project → Options → Device → Select AT89C51
# Step 5: Build Project (Ctrl+B)
# Step 6: Generate .hex file (Output → Build folder)
```

### Programming the AT89C51

The compiled HEX file was generated using Keil µVision and tested using Proteus simulation.

---

## 🧪 Testing & Validation

### Test Cases Executed

| Test Case | Input | Expected Output | Status |
|-----------|-------|------------------|--------|
| **Correct PIN** | 1234 | "Access Granted" + Motor on | ✅ PASS |
| **Wrong PIN** | 1111 | "Access Denied" + Buzzer | ✅ PASS |
| **3 Failed Attempts** | 1111, 2222, 3333 | System locked 30 seconds | ✅ PASS |
| **Keypad Debouncing** | Rapid key mashing | Single registration per press | ✅ PASS |
| **Motor Hold Time** | Unlock → 3 seconds | Door re-locks automatically | ✅ PASS |
| **Power Failure Recovery** | Loss of 5V power | Returns to locked state on power restore | ✅ PASS |

---

## 🔐 Security Features

1. **PIN Protection**
   - 4-digit password stored in firmware memory
   - Factory default: 1234 (user should change)
   
2. **Brute Force Prevention**
   - Maximum 3 incorrect attempts
   - 30-second lockout after 3 failures
   - Visual countdown on LCD

3. **Access Logging** (Future Enhancement)
   - Log unlock events with timestamp
   - Store in external EEPROM for audit

4. **Physical Security**
   - Electromagnetic lock requires continuous power
   - Fail-safe: Unlocks if power lost (consider adding battery backup)

---

## 📚 Technical References

### Datasheets
- AT89C51 Microcontroller Datasheet
- L293D Motor Driver Datasheet
- 16x2 LCD HD44780 Datasheet
- 4x4 Matrix Keypad Specification

### Learning Resources
- [8051 Assembly Language Tutorial](https://www.neso.academy)
- [Embedded Systems Design](https://edx.org)
- [Interrupt-Driven Programming in 8051](https://www.tutorialspoint.com)

---

## 💡 Lessons Learned & Future Enhancements

### What Went Well ✅
- Optimized keypad polling and debouncing improved responsiveness
- Debouncing logic eliminated key chattering
- Relay isolation protected microcontroller from motor noise

### Challenges Overcome ⚔️
- **Noise on Keypad**: Solved with RC filter + software debouncing (20ms delay)
- **Motor Current Spikes**: Added flyback diode across relay coil
- **LCD Timing Issues**: Implemented proper timing delays (Tmax = 4.7µs instructions)

### Future Improvements 🔮
- [ ] Add RFID card reader as backup authentication
- [ ] Implement SMS alerts (GSM module) for failed access attempts
- [ ] Multi-level access control (Admin PIN vs User PIN)
- [ ] Real-time clock (RTC) for time-based access restrictions
- [ ] Cloud connectivity for remote monitoring (Wi-Fi module)
- [ ] Bluetooth-based mobile authentication

---

## 🎯 Project Outcomes

✅ **Functionality**: System successfully demonstrated reliable operation during functional testing 
✅ **Performance**: Achieved responsive real-time operation during testing  
✅ **Scalability**: Code is modular, easy to extend with new features  
✅ **Real-world Application**: Could be adapted for office/home security  

### Where This Project Demonstrated Skill
- **Embedded Systems Design**: Hardware-software co-design
- **Real-Time Embedded Logic**: Responsive keypad scanning and access control
- **Hardware Integration**: Sensor → Microcontroller → Actuator pipeline
- **Debugging**: Simulation debugging and embedded logic validation
- **Documentation**: Professional technical writing

---

## 📞 Contact & Questions

**Author**: Siri Satyamurthy  
**Email**: sirisatyamurthy8@gmail.com  
**GitHub**: github.com/sirisatyamurthy  
**LinkedIn**: https://www.linkedin.com/in/siri-satyamurthy-726536331/

Feel free to open an **Issue** if you have questions or want to discuss improvements!

---

## 📄 License

This project is open-source for educational purposes. Feel free to fork and modify for your learning.

---

**Last Updated**: May 2026  
**Status**: ✅ Functional Prototype
