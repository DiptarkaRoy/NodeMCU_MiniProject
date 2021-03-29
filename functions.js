//DOM variables
const motorSwitch = document.getElementsByClassName('switch'),
    waterStatus = document.querySelector('#water-status'),
    sensorLog = document.querySelector('#sensor-log');

//Variables
let newLog,
    time = new Date();

// NodeMCU Variables
const waterLevel = false;
let motorStatus = true;

//Initialising everything
init();

//============== functions and middlewares==================// 

function init() {
    setInterval(() => {
        changeWaterStatus();
        changeMotorStatus();
    }, 1000);  //this code checks motor and water status every second
}

function changeWaterStatus() {
    if (waterStatus.textContent !== 'FULL' && waterLevel) {
        waterStatus.textContent = 'FULL';
    } else if (waterStatus.textContent !== 'EMPTY' && !waterLevel) {
        waterStatus.textContent = 'EMPTY';
    } else if (waterLevel === undefined) {
        alert('Water level information not found');
    }
}


function changeMotorStatus() {
    if (motorSwitch[0].checked !== motorStatus) {
        time = "unknown";
        changeMotorLog(time);
    }
}

function changeMotorLog(time) {
    if (motorStatus == true) {
        motorSwitch[0].checked = true;
        motorON(time);
    } else {
        motorSwitch[0].checked = false;
        motorOFF(time);
    }
}

function motorON(time) {
    newLog = document.createElement("div");
    newLog.classList.add("log")
    newLog.innerText = `~Motor Switched ON at ${time}`;
    sensorLog.append(newLog);
    motorStatus = true;

    //ADD FUNCTIONALITY FOR TURNING ON THE MOTOR.
    // The functionality will send a signal to the NodeMCU and turn the motor on.

    // Insert code here.
}

function motorOFF(time) {
    newLog = document.createElement("div");
    newLog.classList.add("log")
    newLog.innerText = `~Motor Switched OFF at ${time}`;
    sensorLog.append(newLog);

    //ADD FUNCTIONALITY FOR TURNING OFF THE MOTOR.
    // The functionality will send a signal to the NodeMCU and turn the motor on.

    // Insert code here.
}

// TOGGLES and EVENTS
motorSwitch[0].addEventListener("click", () => {
    motorStatus = !motorStatus;
    time = new Date();
    changeMotorLog(time);
})
