// Send post request to turn on the given color
function turn(color, state) {

  const payload = {
    "color" : color,
    "state" : state
  };

  var req = new XMLHttpRequest();
  req.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      color_circles(payload);
    }
  };

  // Open request
  req.open("POST", "/led", true);

  // Set the conten type to JSON
  req.setRequestHeader("Content-Type", "application/json");

  // Send the JSON payload
  req.send(JSON.stringify(payload)); 
}


// Color the circles
function color_circles(payload) {
  if ("red" == payload["color"]) {
    document.getElementById("redled").style["background-color"] = payload["state"] == "on" ? "f00" : "8a4141" ;
  }else {
    document.getElementById("grnled").style["background-color"] = payload["state"] == "on" ? "19eb15" : "0f5c0e" ;
  }
}
