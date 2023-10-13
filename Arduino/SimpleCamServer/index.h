const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>SimpleCamaraServer</title>
  <style>
    body { text-align:center; }
    .vert { margin-bottom: 10%; }
    .hori{ margin-bottom: 0%; }
    .btns{
      display:flex;
      align-items:center;
      justify-content:center;
      gap:10px;
      padding:7px;
      background:#70c1ff;
      border-radius:30px;
    }

    .btns button{
      padding:7px 15px;
      background:#0091ff;
      color:white;
      border-radius:10px;
      font-size:18px;
      border:none;
      outline:none;
      cursor:pointer;
    }
  </style>
</head>
<body>
  <div id="container">
    <h2>ESP32-CAM Camara server</h2>
    <p class="btns">
      <button onclick="rotatePhoto();">ROTATE</button>
      <button onclick="capturePhoto()">CAPTURE PHOTO</button>
      <button onclick="location.reload();" id="reload">REFRESH PAGE</button>
      <button onclick="flash();">Toggle Flash</button>

    </p>
  </div>
  <div><img src="https://cdn-icons-png.flaticon.com/512/883/883746.png" id="photo" height="auto" width="500px"></div>
</body>
<script>
  var deg = 0;
  function capturePhoto() {
    var xhr = new XMLHttpRequest();
    xhr.onload = function() {
      document.getElementById("photo").src=this.responseText;
    }
    xhr.open('GET', "/capture", true);
    xhr.send();
  }

  function flash() {
    var xhr = new XMLHttpRequest();
    xhr.open('GET', "/flash", true);
    xhr.send();
  }

  function rotatePhoto() {
    var img = document.getElementById("photo");
    deg += 90;
    if(isOdd(deg/90)){ document.getElementById("container").className = "vert"; }
    else{ document.getElementById("container").className = "hori"; }
    img.style.transform = "rotate(" + deg + "deg)";
  }
  function isOdd(n) { return Math.abs(n % 2) == 1; }
</script>
</html>)rawliteral";