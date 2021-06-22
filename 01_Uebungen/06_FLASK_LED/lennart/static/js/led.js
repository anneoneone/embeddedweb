// Send post request to turn on the given color
function turn(color, state) {

  const payload = {
    "color" : color,
    "state" : state
  };

  var req = new XMLHttpRequest();
  req.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      handleResponse(this.responseText);
    }
  };

  // Open request
  req.open("POST", "/led", true);

  // Set the conten type to JSON
  req.setRequestHeader("Content-Type", "application/json");

  // Send the JSON payload
  req.send(JSON.stringify(payload)); 
}


// Handle the response, and color the state spans
function handleResponse(resp) {
  if (resp.startsWith("Error")) {
    alert(resp);
  }else {
    var red_part = resp.slice(0, resp.indexOf("&"));
    var grn_part = resp.slice(resp.indexOf("&")+1);

    var red_state = red_part.slice(red_part.indexOf("=")+1);
    var grn_state = grn_part.slice(grn_part.indexOf("=")+1);

    document.getElementById("redled").style["background-color"] = red_state == 1 ? "f00" : "8a4141" ;
    document.getElementById("grnled").style["background-color"] = grn_state == 1 ? "19eb15" : "0f5c0e" ;

  }
}
