// const express = require("express");
// const app = express();

// app.get("/", function (req, res) {
//   const cnt = 100;
//   let result = 0;
//   for (let i = 0; i < cnt; i++) {
//     result += Math.floor(Math.random() * 100);
//   }
//   res.json({ randomSum: result });
// });

// app.listen(3000);

var http = require("http");
//create a server object:
http
  .createServer(function (req, res) {
    const cnt = 5000;
    let result = 0;
    for (let i = 0; i < cnt; i++) {
      result += Math.floor(Math.random() * 100);
    }
    res.setHeader("Content-Type", "application/json");
    res.end(JSON.stringify({ randomSum: result }));
  })
  .listen(3000, function () {
    console.log("server start at port 3000"); //the server object listens on port 3000
  });
