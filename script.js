var waterStatus = document.querySelector('#water-status');
        var motorStatus = document.querySelector('#motor-status');
        var on = document.querySelector('#on');
        var off = document.querySelector('#off');

        // This variable will contain the water level information in the form of true or false. 
        var waterLevel = false; // We can test this variable by putting true,false or no values in it.

        // TOGGLES and EVENTS
        on.addEventListener("click", function () {
            if (motorStatus.textContent !== 'ON') {
                motorStatus.textContent = 'ON';
            } else {
                alert('Motor is already On');
            }

            //ADD FUNCTIONALITY FOR TURNING ON THE MOTOR.
            // The functionality will send a signal to the NodeMCU and turn the motor on.
            // Insert code here.
        });

        off.addEventListener("click", function () {
            if (motorStatus.textContent !== 'OFF') {
                motorStatus.textContent = 'OFF';
            } else {
                alert('Motor is already Off');
            }

            //ADD FUNCTIONALITY FOR TURNING OFF THE MOTOR.
            // The functionality will send a signal to the NodeMCU and turn the motor off .
            // Insert code here.
        });

        function changeWaterStatus() {
            if (waterStatus.textContent !== 'FULL' && waterLevel) {
                waterStatus.textContent = 'FULL';
            } else if (waterStatus.textContent !== 'EMPTY' && !waterLevel) {
                waterStatus.textContent = 'EMPTY';
            } else if (waterLevel === undefined) {
                alert('Water level information not found');
            }
        }

        // Runs the above function every second and sees if the value of water level has changed or not.
        setInterval("changeWaterStatus()", 1000);