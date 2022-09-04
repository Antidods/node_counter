const express = require('express');
const morgan = require('morgan');
const fs = require('fs');
const app = express();
const port = 3000;

app.use(morgan('dev'));
app.use(express.urlencoded({ extended: false }));
app.use(express.json());
app.use('/sqladd', require('./routes/sql.js'));

app.use(function (request, response, next) {
   let now = new Date();
   let hour = now.getHours();
   let minutes = now.getMinutes();
   let seconds = now.getSeconds();
   let data = `${hour}:${minutes}:${seconds} ${request.method} ${
      request.url
   } ${request.get('user-agent')}`;
   console.log(data);
   fs.appendFile('server.log', data + '\n', function () {});
   next();
});

app.use(function (err, req, res, next) {
   console.error(err.stack);
   let now = new Date();
   let hour = now.getHours();
   let minutes = now.getMinutes();
   let seconds = now.getSeconds();
   let date = `${hour}:${minutes}:${seconds} ${err.stack}`;
   fs.appendFile('server.log', data + '\n', function () {});
   next();
});

app.listen(port, () => {
   console.log('server node_counter started on localhost:' + port);
});
