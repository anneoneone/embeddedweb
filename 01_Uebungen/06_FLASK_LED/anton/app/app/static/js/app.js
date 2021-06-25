
function setLedAjax(ledState) {

    const payload = {
        "ledState" : ledState
    };
    
    console.log("Hello from app.js! AJAXXX");
    console.log(ledState);

    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (this.readyState == true && this.status == 200) {
            handleResponse(this.responseText);
        }
    }
    req.open("POST", "/controlLed");

    req.setRequestHeader("Content-Type", "application/json")
    req.send(JSON.stringify(payload))

}