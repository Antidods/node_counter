const express = require('express');
const sqlAdd = express.Router();
const mysql = require('mysql');

const connection = mysql.createConnection({
   host: '',
   database: '',
   user: '',
   password: '',
});

const addToSql =
   'INSERT INTO click(id, date, time) VALUES (rand()*10000,CURRENT_DATE,CURRENT_TIME)';

sqlAdd.get('/', (req, res) => {
   connection.query(addToSql, function (err, rows, fields) {
      if (err) throw err;
   });
   res.send('add data to MySQL');
});

module.exports = sqlAdd;
