// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(

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
      margin-bottom: 10px;
  }

  #SensorInfo
  {
      width: 10%;
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
</style>

  <html lang="en">
<head>
    <link rel="stylesheet" type="text/css" href="vehiclePerformance.css" />
    <title>IOT RC Car Project</title>
</head>

<div id="Title">
    <h1> <img src="LOGO-PERFORMANCE-CAR-ESTESO.jpeg" style="height: 100px"> </h1>
</div>

<body>
    <script src="vehiclePerformance.js"> </script>

    <div id="VehicleStat" >
    <img id="toggleImage" src="car3.jpg" style="height: 400px" onclick="toggle()">
    </div>

    <script>
        function toggle()
        {
            let img = document.getElementById("toggleImage");
            img.src = (img.src.includes("car3.jpg")) ? "car2.jpg" : "car3.jpg";
        }
    </script>

<hr>

</body>
</html>
 )=====");

String homePagePart2 = F(R"=====(
  <div id="SensorInfo">
    <table border="3">
        <tr>
            <th>SENSOR</th>
            <th>DISTANCE</th>
        </tr>
        <tr>
            <th>Front Bumper</th>
            <td>VALUE!</td>
        </tr>
        <tr>
            <th>Rear Bumper</th>
            <td>VALUE!</td>
        </tr>
    </table>
</div>)=====");

String homePagePart3 = F(R"=====(
  <div id="Brake">
        <img src="pedals_cropped (2).jpg" style="height: 200px">
    </div>

    <div id="Accelerator">
        <img src="pedals_cropped (1).jpg" style="height: 200px">
    </div>
))
