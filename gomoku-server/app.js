fs = require('fs');
var cors = require('cors');


//var io = require('socket.io')(4000);
//const zmq = require("zeromq");

const express = require("express");
const http = require("http");
var zmq = require('zeromq');
const socketIo = require("socket.io");

const port = process.env.PORT || 4000;
const index = require("./routes/index");

const app = express();
app.use(cors());
app.use(index);


const server = http.createServer(app);

const io = socketIo(server);

const sock = new zmq.Dealer;

async function run() {
  //const sock = new zmq.Dealer

  sock.connect("tcp://chorus.servegame.com:23510")
  console.log("Producer bound to port 23510")
  sock.routingId ="routingId";
  //await sock.send("Test message")
  while (true) {
    const [result] = await sock.receive()
    console.log(result.toString());
    io.emit("dAIMove", JSON.parse(result.toString()));
  }

}

run();


//Connect to SocketIO 
io.on('connection', function (socket) {
  console.log('a user connected');
  socket.on('userMove', async function (data) {
    console.log(data);
    await sock.send(JSON.stringify(data));
    //await sock.send(data);


  });
});


server.listen(port, () => console.log(`Listening on port ${port}`));
