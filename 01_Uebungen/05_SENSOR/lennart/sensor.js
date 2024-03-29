// Request sensor values
function get_env_values() {
  var req = new XMLHttpRequest();
  req.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      handleResponse(this.responseText);
    }

  };
  req.open("GET", "/cgi-bin/sensor.py");
  req.send()
  
  // Set interval to get the environment values each 5 seconds
  setInterval(() => {
    req.open("GET", "/cgi-bin/sensor.py");
    req.send();
  }, 5000)
}


// Handle the response and add the received values to html
function handleResponse(resp) {
  console.log(resp)
  data = JSON.parse(resp)
  document.getElementById("temp").innerHTML = data["temp"];
  document.getElementById("hum").innerHTML = data["hum"];
}

get_env_values()
