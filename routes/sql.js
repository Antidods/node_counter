const express = require('express');
const sqlAdd = express.Router();
const mysql = require('mysql');

const connection = mysql.createConnection({
   host: 'localhost',
   database: 'Antidods_nodemcu',
   user: 'Antidods_nodemcu',
   password: 'NMJcbbDyev21',
});

const addToSql =
   'INSERT INTO click(id, date, time) VALUES (rand()*10000,CURRENT_DATE,CURRENT_TIME)';

sqlAdd.post('/', (req, res) => {
   connection.connect();
   connection.query(addToSql);
   res.send('add data to MySQL');
   connection.end();
});

module.exports = sqlAdd;
