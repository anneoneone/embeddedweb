const express = require('express');
const app = express();
const low = require('lowdb');
const FileSync = require('lowdb/adapters/FileSync')
const adapter = new FileSync('db.json');
const db = low(adapter);
db.defaults({ posts: [] })
 .write();

const mqtt = require('mqtt');
const client = mqtt.connect("mqtt://test.mosquitto.org");
client.subscribe("/anton/forgottenPlants",{qos:1});

fahrenheitToCelsius = (fahrenheit) => {
    var fTempVal = parseFloat(fahrenheit);
    var cTempVal = (fTempVal - 32) * (5 / 9);
    return (Math.round(cTempVal * 100) / 100);
}

client.on('message', function (topic, message) {
    // message is buffer
    var stringBuf = message && message.toString('utf-8')

    try {
        var json = JSON.parse(stringBuf);
        console.log(json);

        if (json.sensor) {
            db.get('posts').push({ 
                sensorType: json.sensor, 
                humidity: json.data,
                pumpStatus: json.pumpStatus, 
                time: json.time 
            }).write()
        }
        /*
        if (json.model === 'inFactory sensor') {
            if (json.id === 91 || json.id === 32) {
            // catch my specific sensor model
                if (json.temperature_F && json.humidity) {
                    // add data to lowdb
                    const time = moment.utc(json.time).tz("Europe/Berlin");
                    const formattedTime = time.format('YYYY-MM-DD HH:mm:ss');
                    console.log('write post');
                    db.get('posts')
                    .push({ id: uuid.v1(), room: json.id, temp: 
                            fahrenheitToCelsius(json.temperature_F), 
                            humidity: json.humidity, time: formattedTime }).write()
                }
            }
        }
        */
    } catch (e) {
        console.error("error :(")
        console.error(stringBuf);
    }
});

app.get('/api', (req, res) => {
    res.send(db.get('posts'));
});

// test
app.get('/', function (req, res) {
    res.send('hello world!');
});
app.listen(3000, () => console.log('App listening on port ', 3000));