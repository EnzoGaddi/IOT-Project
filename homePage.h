// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(

<html lang="en">
<head>

    <title>IOT RC Car Project</title>
</head>

<style>
    body
  {
      background-color: black;
  }

  #Title
  {
      text-align: center;
      position: relative;
      margin-bottom: 10px;
      color: white;
  }

  #VehicleStat
  {
      width: 100%;
      text-align: center;
      float: center;
      margin-bottom: 10px;
  }

  #Brake
  {
      width: 50%;
      text-align: center;
      float: left;
  }

  #SensorInfo
  {
      width: 20%;
      text-align: center;
      margin: auto;
      color: white;
      margin: auto;
  }

  #Accelerator
  {
      width: 50%;
      text-align: center;
      float: right;
  }

  #tr,td,th
  {
    color:white;
  }
</style> http://172.20.10.4/sensor

<script>

let fuelInterval;

  async function fetchDistanceData() {
    fetch('/distanceSensor')  
    .then(response => {
        if (!response.ok) {
            throw new Error("HTTP error! Status: " + response.status);
        }
        return response.json();
    })
    .then(data => {

        document.getElementById("distanceValue").innerText = data.distance + " cm";
        updateImage(data.distance);
    })
    .catch(error => console.error('Fetch error:', error));
}
setInterval(fetchDistanceData, 500);

async function fetchAccelerationData() {
    fetch('/accelerationSensor')  
    .then(response => {
        if (!response.ok) {
            throw new Error("HTTP error! Status: " + response.status);
        }
        return response.json();
    })
    .then(data => {

        document.getElementById("accelerationValue").innerText = data.acceleration + " m/s";
    })
    .catch(error => console.error('Fetch error:', error));
}
setInterval(fetchAccelerationData, 500);

function updateImage(distanceValue) 
  {
      let img = document.getElementById("proximitySensor");
      
      if (distanceValue <= 7) 
      {
          img.src = "car.png";
      }

      else if (distanceValue <= 20 && distanceValue > 7) 
      {
          img.src = "car2.png";
      }

      else 
      {
          img.src = "car3.png";
      }
  }

function motorGo() 
  {
    fetch('/motor-go', { method: 'POST' })  
    .then(response => response.text())
    .then(data => console.log(data))
    .catch(error => console.error('Error:', error));

    fuelInterval = setInterval(() => {
    fetch("/fuelSystem", { method: "POST" });
    },
     500); // adjust interval to match fuel drain speed
  }

function motorStop() 
  {
    fetch('/motor-stop', { method: 'POST' })  
    .then(response => response.text())
    .then(data => console.log(data))
    .catch(error => console.error('Error:', error));

    clearInterval(fuelInterval);
  }

function updateFuel() {
  fetch("/fuelSystem")
    .then(response => response.text())
    .then(data => {
      document.getElementById("getFuel").innerText = data + "%";
    })
    .catch(error => {
      document.getElementById("getFuel").innerText = "Error";
    });
}

setInterval(updateFuel, 500); 

document.addEventListener("DOMContentLoaded", () => 
{
    const accelerateImg = document.getElementById("accelerate");
    const brakeImg = document.getElementById("brake");

    function preventDoubleTrigger(event) 
    {
      event.preventDefault(); // Stops the event from firing twice
    }

    if (accelerateImg) 
    {
      accelerateImg.addEventListener("click", motorGo); 
      accelerateImg.addEventListener("touchstart", motorGo);  
      accelerateImg.addEventListener("touchend", preventDoubleTrigger);
    }

    if (brakeImg) 
    {
      brakeImg.addEventListener("click", motorStop);
      brakeImg.addEventListener("touchstart", motorStop);
      brakeImg.addEventListener("touchend", preventDoubleTrigger);
    }
});
</script>

<div id="Title">
    <h1> <img src="LOGO-PERFORMANCE-CAR-ESTESO.png" style="height: 100px"> </h1>
</div>

<body>

    <div id="VehicleStat" >
    <img id="proximitySensor" src="car3.png" style="height: 400px">
    </div>

  <div id="SensorInfo">
    <table border="3">
        <tr>
            <th>SENSOR</th>
            <th>VALUES</th>
        </tr>
        <tr>
            <th>Front Bumper</th>
            <td>
            <span id="distanceValue"> </span>
            </td>
        </tr>
        <tr>
            <th>Acceleration</th>
            <td>
            <span id="accelerationValue"> </span>
            </td>
        </tr>
        <tr>
            <th><img src="Fuel.jpg" style="height: 70px" ></th>
            <td>
            <span id="getFuel"> </span>
            </td>
        </tr>
    </table>

<button id="refillButton">Refill Fuel</button>

<script>
    document.getElementById("refillButton").addEventListener("click", () => {
      fetch("/refillFuel", { method: "POST" })
        .then(response => response.text())
        .then(data => {
          console.log(data);
          updateFuelDisplay();
        })
        .catch(error => console.error("Refill error:", error));
    });
  </script>

  </div>
  
<hr>

  <div id="Brake">
        <img id="brake" src="brake.jpg" style="height: 200px">
    </div>

  <div id="Accelerator">
        <img id="accelerate" src="accelerator.jpg" style="height: 200px">
    </div>

</body>
</html>
)=====");

